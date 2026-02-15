/*
 * evse_state_machine.c - Testable extraction of SmartEVSE-3.5 state machine
 *
 * This is a faithful extraction of the core logic from main.cpp.
 * All hardware interactions are replaced with HAL callbacks.
 * All globals are replaced with the evse_ctx_t context struct.
 *
 * Line references refer to the original SmartEVSE-3/src/main.cpp
 */

#include "evse_state_machine.h"
#include <stdlib.h>
#include <stdio.h>

// ---- Helper: min/max ----
static inline int min_int(int a, int b) { return a < b ? a : b; }
__attribute__((unused)) static inline int max_int(int a, int b) { return a > b ? a : b; }

// ---- Default HAL (no-ops for safety) ----
static void hal_noop_u32(uint32_t v) { (void)v; }
static void hal_noop_bool(bool v) { (void)v; }
static void hal_noop(void) {}

static evse_hal_t default_hal = {
    .set_cp_duty    = hal_noop_u32,
    .contactor1     = hal_noop_bool,
    .contactor2     = hal_noop_bool,
    .set_pilot      = hal_noop_bool,
    .actuator_lock  = hal_noop,
    .actuator_unlock= hal_noop,
    .actuator_off   = hal_noop,
    .on_state_change = NULL,
};

// ---- Recording HAL for test instrumentation ----
static void record_cp_duty(evse_ctx_t *ctx, uint32_t duty) {
#ifdef EVSE_TESTING
    ctx->last_pwm_duty = duty;
#endif
    if (ctx->hal.set_cp_duty) ctx->hal.set_cp_duty(duty);
}

static void record_contactor1(evse_ctx_t *ctx, bool on) {
#ifdef EVSE_TESTING
    ctx->contactor1_state = on;
#endif
    if (ctx->hal.contactor1) ctx->hal.contactor1(on);
}

static void record_contactor2(evse_ctx_t *ctx, bool on) {
#ifdef EVSE_TESTING
    ctx->contactor2_state = on;
#endif
    if (ctx->hal.contactor2) ctx->hal.contactor2(on);
}

static void record_pilot(evse_ctx_t *ctx, bool connected) {
#ifdef EVSE_TESTING
    ctx->pilot_connected = connected;
#endif
    if (ctx->hal.set_pilot) ctx->hal.set_pilot(connected);
}

// ---- Initialization ----
// cppcheck-suppress constParameterPointer
void evse_init(evse_ctx_t *ctx, evse_hal_t *hal) {
    memset(ctx, 0, sizeof(evse_ctx_t));

    // HAL
    if (hal) {
        ctx->hal = *hal;
    } else {
        ctx->hal = default_hal;
    }

    // Core state (matches power-on defaults from main.cpp)
    ctx->State = STATE_A;
    ctx->Mode = MODE_NORMAL;
    ctx->LoadBl = 0;

    // Authorization
    ctx->AccessStatus = OFF;
    ctx->RFIDReader = 0;
    ctx->OcppMode = false;
    ctx->OcppCurrentLimit = -1.0f;
    ctx->CPDutyOverride = false;

    // Power limits (from main.h defaults)
    ctx->MaxMains = MAX_MAINS;
    ctx->MaxCurrent = MAX_CURRENT;
    ctx->MinCurrent = MIN_CURRENT;
    ctx->MaxCircuit = MAX_CIRCUIT;
    ctx->MaxCapacity = MAX_CURRENT;  // Default to MaxCurrent
    ctx->MaxSumMains = MAX_SUMMAINS;
    ctx->MaxSumMainsTime = MAX_SUMMAINSTIME;
    ctx->GridRelayMaxSumMains = GRID_RELAY_MAX_SUMMAINS;
    ctx->GridRelayOpen = false;

    // Current distribution
    for (int i = 0; i < NR_EVSES; i++) {
        ctx->Balanced[i] = 0;
        ctx->BalancedMax[i] = 0;
        ctx->BalancedState[i] = STATE_A;
        ctx->BalancedError[i] = 0;
    }
    ctx->ChargeCurrent = 0;
    ctx->IsetBalanced = 0;
    ctx->OverrideCurrent = 0;

    // Meter readings
    ctx->Isum = 0;
    ctx->MainsMeterImeasured = 0;
    ctx->EVMeterImeasured = 0;
    ctx->MainsMeterType = 0;
    ctx->EVMeterType = 0;
    ctx->MainsMeterTimeout = COMM_TIMEOUT;
    ctx->EVMeterTimeout = COMM_EVTIMEOUT;

    // Error handling
    ctx->ErrorFlags = NO_ERROR;
    ctx->ChargeDelay = 0;
    ctx->NoCurrent = 0;

    // Phase switching
    ctx->EnableC2 = NOT_PRESENT;
    ctx->Nr_Of_Phases_Charging = 3;
    ctx->Switching_Phases_C2 = NO_SWITCH;

    // Phase switching measurement gating
    ctx->phasesLastUpdateFlag = true;    // Start as true for first calculation
    ctx->LimitedByMaxSumMains = false;

    // Modem
    ctx->ModemEnabled = false;
    ctx->ModemStage = 0;
    ctx->DisconnectTimeCounter = -1;     // Disabled
    ctx->RequiredEVCCID[0] = '\0';
    ctx->EVCCID[0] = '\0';

    // Solar config
    ctx->StartCurrent = START_CURRENT;
    ctx->StopTime = STOP_TIME;
    ctx->ImportCurrent = IMPORT_CURRENT;

    // Safety
    ctx->TempEVSE = 25;
    ctx->maxTemp = MAX_TEMPERATURE;
    ctx->RCmon = 0;
    ctx->RCMFault = false;

    // Misc
    ctx->DiodeCheck = 0;
    ctx->PilotDisconnected = false;
    ctx->PilotDisconnectTime = 0;
    ctx->ActivationMode = 255;  // Disabled

    // Node 0 (master) starts online
    ctx->Node[0].Online = 1;

#ifdef EVSE_TESTING
    // Test instrumentation defaults
    ctx->pilot_connected = true;
    ctx->contactor1_state = false;
    ctx->contactor2_state = false;
    ctx->transition_count = 0;
#endif
}

// ---- Phase switching helper ----
// Faithful to Force_Single_Phase_Charging() in main.cpp:681-696
// cppcheck-suppress constParameterPointer
uint8_t evse_force_single_phase(evse_ctx_t *ctx) {
    switch (ctx->EnableC2) {
        case NOT_PRESENT: return 0;  // 3P
        case ALWAYS_OFF:  return 1;  // 1P
        case SOLAR_OFF:   return (ctx->Mode == MODE_SOLAR) ? 1 : 0;
        case AUTO:        return (ctx->Nr_Of_Phases_Charging == 1) ? 1 : 0;
        case ALWAYS_ON:   return 0;  // 3P
        default:          return 0;
    }
}

// ---- Check switching phases (faithful to CheckSwitchingPhases() in main.cpp:542-575) ----
static void check_switching_phases(evse_ctx_t *ctx) {
    if (ctx->EnableC2 != AUTO || ctx->Mode == MODE_SOLAR) {
        if (evse_force_single_phase(ctx)) {
            if (ctx->Nr_Of_Phases_Charging != 1) {
                if (ctx->State != STATE_A) {
                    ctx->Switching_Phases_C2 = GOING_TO_SWITCH_1P;
                } else {
                    ctx->Nr_Of_Phases_Charging = 1;
                }
            } else {
                ctx->Switching_Phases_C2 = NO_SWITCH;
            }
        } else {
            if (ctx->Nr_Of_Phases_Charging != 3) {
                if (ctx->State != STATE_A) {
                    ctx->Switching_Phases_C2 = GOING_TO_SWITCH_3P;
                } else {
                    ctx->Nr_Of_Phases_Charging = 3;
                }
            } else {
                ctx->Switching_Phases_C2 = NO_SWITCH;
            }
        }
    } else if (ctx->Mode == MODE_SMART) {
        // SMART mode with CONTACT 2 set to AUTO: go back to 3P
        if (ctx->Nr_Of_Phases_Charging != 3) {
            ctx->Switching_Phases_C2 = GOING_TO_SWITCH_3P;
        } else {
            ctx->Switching_Phases_C2 = NO_SWITCH;
        }
    }
}

// Public wrapper for CheckSwitchingPhases
void evse_check_switching_phases(evse_ctx_t *ctx) {
    check_switching_phases(ctx);
}

// ---- Error management ----
void evse_set_error_flags(evse_ctx_t *ctx, uint8_t flags) {
    ctx->ErrorFlags |= flags;
}

void evse_clear_error_flags(evse_ctx_t *ctx, uint8_t flags) {
    ctx->ErrorFlags &= ~flags;
}

// ---- Graceful power unavailable ----
// Faithful to setStatePowerUnavailable() in main.cpp:736-748
void evse_set_power_unavailable(evse_ctx_t *ctx) {
    if (ctx->State == STATE_A)
        return;
    if (ctx->State == STATE_C)
        evse_set_state(ctx, STATE_C1);
    else if (ctx->State != STATE_C1 && ctx->State != STATE_B1)
        evse_set_state(ctx, STATE_B1);
}

// ---- Current to PWM ----
// Faithful to SetCurrent() in main.cpp:718-733
uint32_t evse_current_to_duty(uint16_t current) {
    uint32_t duty;
    if (current >= (MIN_CURRENT * 10) && current <= 510)
        duty = (uint32_t)(current / 0.6);
    else if (current > 510 && current <= 800)
        duty = (uint32_t)(current / 2.5) + 640;
    else
        duty = 100;  // Invalid, default to ~6A
    // v3 conversion: scale to 1024 = 100%
    duty = duty * 1024 / 1000;
    return duty;
}

// ---- Authorization ----
// Faithful to setAccess() in main.cpp:967-989
void evse_set_access(evse_ctx_t *ctx, AccessStatus_t access) {
    ctx->AccessStatus = access;
    if (access == OFF || access == PAUSE) {
        if (ctx->State == STATE_C)
            evse_set_state(ctx, STATE_C1);
        else if (ctx->State != STATE_C1 &&
                 (ctx->State == STATE_B ||
                  ctx->State == STATE_MODEM_REQUEST ||
                  ctx->State == STATE_MODEM_WAIT ||
                  ctx->State == STATE_MODEM_DONE ||
                  ctx->State == STATE_MODEM_DENIED))
            evse_set_state(ctx, STATE_B1);
    }
}

// ---- State transition ----
// Faithful to setState() in main.cpp:790-941
void evse_set_state(evse_ctx_t *ctx, uint8_t new_state) {
    uint8_t old_state = ctx->State;  // Save for callback

#ifdef EVSE_TESTING
    // Log transition for test assertions
    if (ctx->State != new_state && ctx->transition_count < 64) {
        ctx->transition_log[ctx->transition_count++] = new_state;
    }
#endif

    switch (new_state) {
        case STATE_B1:
            if (!ctx->ChargeDelay) ctx->ChargeDelay = 3;  // line 807
            if (ctx->State != STATE_B1 && !ctx->PilotDisconnected && ctx->AccessStatus == ON) {
                record_pilot(ctx, false);               // PILOT_DISCONNECTED
                ctx->PilotDisconnected = true;
                ctx->PilotDisconnectTime = 5;
            }
            // fall through
        case STATE_A:
            record_contactor1(ctx, false);               // CONTACTOR1_OFF
            record_contactor2(ctx, false);               // CONTACTOR2_OFF
            record_cp_duty(ctx, 1024);                   // PWM off, +12V

            if (new_state == STATE_A) {
                ctx->ModemStage = 0;                     // line 827
                evse_clear_error_flags(ctx, LESS_6A);    // line 828
                ctx->ChargeDelay = 0;                    // line 829
                ctx->Node[0].Timer = 0;
                ctx->Node[0].IntTimer = 0;
                ctx->Node[0].Phases = 0;
                ctx->Node[0].MinCurrent = 0;
            }
            break;

        case STATE_MODEM_REQUEST:
            ctx->ToModemWaitStateTimer = 0;
            record_pilot(ctx, false);                    // PILOT_DISCONNECTED
            record_cp_duty(ctx, 1024);
            record_contactor1(ctx, false);
            record_contactor2(ctx, false);
            break;

        case STATE_MODEM_WAIT:
            record_pilot(ctx, true);                     // PILOT_CONNECTED
            record_cp_duty(ctx, 51);                     // 5% duty
            ctx->ToModemDoneStateTimer = 60;
            break;

        case STATE_MODEM_DONE:
            record_pilot(ctx, false);                    // PILOT_DISCONNECTED
            ctx->LeaveModemDoneStateTimer = 5;
            break;

        case STATE_B:
            check_switching_phases(ctx);                 // line 863
            record_pilot(ctx, true);                     // PILOT_CONNECTED
            ctx->DisconnectTimeCounter = -1;             // line 866
            record_contactor1(ctx, false);
            record_contactor2(ctx, false);
            break;

        case STATE_C:
            ctx->ActivationMode = 255;                   // line 879

            // Phase switching on contactor entry (lines 890-909)
            if (ctx->Switching_Phases_C2 == GOING_TO_SWITCH_1P) {
                ctx->Nr_Of_Phases_Charging = 1;
            } else if (ctx->Switching_Phases_C2 == GOING_TO_SWITCH_3P) {
                ctx->Nr_Of_Phases_Charging = 3;
            }

            record_contactor1(ctx, true);                // CONTACTOR1_ON
            if (!evse_force_single_phase(ctx)) {
                record_contactor2(ctx, true);             // CONTACTOR2_ON
                ctx->Nr_Of_Phases_Charging = 3;
            } else {
                record_contactor2(ctx, false);
                ctx->Nr_Of_Phases_Charging = 1;
            }

            ctx->SolarStopTimer = 0;
            ctx->MaxSumMainsTimer = 0;
            ctx->Switching_Phases_C2 = NO_SWITCH;
            break;

        case STATE_C1:
            record_cp_duty(ctx, 1024);                   // PWM off, +12V
            ctx->C1Timer = 6;                            // line 919
            ctx->ChargeDelay = 15;                       // line 920
            break;

        default:
            break;
    }

    ctx->BalancedState[0] = new_state;
    ctx->State = new_state;

    // Fire platform callback for state transition side effects
    if (ctx->hal.on_state_change) {
        ctx->hal.on_state_change(old_state, new_state);
    }
}

// ---- Power availability check ----
// Faithful to IsCurrentAvailable() in main.cpp:1061-1133
int evse_is_current_available(evse_ctx_t *ctx) {
    uint8_t n, ActiveEVSE = 0;
    int Baseload, Baseload_EV, TotalCurrent = 0;

    for (n = 0; n < NR_EVSES; n++) {
        if (ctx->BalancedState[n] == STATE_C) {
            ActiveEVSE++;
            TotalCurrent += ctx->Balanced[n];
        }
    }

    // Solar mode checks (lines 1078-1091)
    if (ctx->Mode == MODE_SOLAR) {
        if (ActiveEVSE == 0 && ctx->Isum >= ((int)ctx->StartCurrent * -10)) {
            return 0;
        }
        if ((ActiveEVSE * ctx->MinCurrent * 10) > (unsigned)TotalCurrent) {
            return 0;
        }
        if (ActiveEVSE > 0 &&
            ctx->Isum > ((int)ctx->ImportCurrent * 10) + TotalCurrent - (ActiveEVSE * ctx->MinCurrent * 10)) {
            return 0;
        }
    }

    ActiveEVSE++;  // Simulate adding one more EVSE (line 1093)
    if (ActiveEVSE > NR_EVSES) ActiveEVSE = NR_EVSES;

    Baseload = ctx->MainsMeterImeasured - TotalCurrent;
    Baseload_EV = ctx->EVMeterImeasured - TotalCurrent;
    if (Baseload_EV < 0) Baseload_EV = 0;

    // MaxMains check (line 1100)
    if (ctx->Mode != MODE_NORMAL &&
        (ActiveEVSE * (ctx->MinCurrent * 10) + Baseload) > (int)(ctx->MaxMains * 10)) {
        return 0;
    }

    // MaxCircuit check (line 1104)
    if (((ctx->LoadBl == 0 && ctx->EVMeterType && ctx->Mode != MODE_NORMAL) || ctx->LoadBl == 1) &&
        ((ActiveEVSE * (ctx->MinCurrent * 10) + Baseload_EV) > (int)(ctx->MaxCircuit * 10))) {
        return 0;
    }

    // MaxSumMains check (line 1115)
    uint8_t Phases = 1;
    if (ctx->LoadBl == 0) Phases = evse_force_single_phase(ctx) ? 1 : 3;
    if (ctx->Mode != MODE_NORMAL && ctx->MaxSumMains &&
        ((Phases * ActiveEVSE * ctx->MinCurrent * 10) + ctx->Isum > (int)(ctx->MaxSumMains * 10))) {
        return 0;
    }

    // OCPP check (line 1122)
    if (ctx->OcppMode && !ctx->LoadBl &&
        ctx->OcppCurrentLimit >= 0.0f &&
        ctx->OcppCurrentLimit < ctx->MinCurrent) {
        return 0;
    }

    return 1;
}

// ---- Current distribution ----
// Faithful to CalcBalancedCurrent() in main.cpp:1148-1526
void evse_calc_balanced_current(evse_ctx_t *ctx, int mod) {
    uint8_t n, ActiveEVSE = 0;
    int32_t TotalCurrent = 0;
    int32_t ActiveMax = 0;
    int32_t Baseload, Baseload_EV;
    int32_t Idifference; // cppcheck-suppress variableScope
    int32_t IsumImport = 0;
    bool LimitedByMaxSumMains = false;
    char CurrentSet[NR_EVSES] = {0}; // cppcheck-suppress variableScope

    // ---- Phase 1: ChargeCurrent (lines 1158-1179) ----
    if (ctx->BalancedState[0] == STATE_C && ctx->MaxCurrent > ctx->MaxCapacity && ctx->MaxCapacity)
        ctx->ChargeCurrent = ctx->MaxCapacity * 10;
    else
        ctx->ChargeCurrent = ctx->MaxCurrent * 10;

    // Apply OCPP limit (line 1163-1175)
    if (ctx->OcppMode && !ctx->LoadBl && ctx->OcppCurrentLimit >= 0.0f) {
        if (ctx->OcppCurrentLimit < ctx->MinCurrent) {
            ctx->ChargeCurrent = 0;
        } else {
            uint16_t ocpp_limit = (uint16_t)(10.0f * ctx->OcppCurrentLimit);
            if (ocpp_limit < ctx->ChargeCurrent)
                ctx->ChargeCurrent = ocpp_limit;
        }
    }

    // Apply OverrideCurrent (line 1177-1179)
    if (ctx->OverrideCurrent)
        ctx->ChargeCurrent = ctx->OverrideCurrent;

    ctx->BalancedMax[0] = ctx->ChargeCurrent;

    // ---- Phase 2: Count active EVSEs (lines 1183-1187) ----
    for (n = 0; n < NR_EVSES; n++) {
        if (ctx->BalancedState[n] == STATE_C) {
            ActiveEVSE++;
            ActiveMax += ctx->BalancedMax[n];
            TotalCurrent += ctx->Balanced[n];
        }
    }

    Baseload_EV = ctx->EVMeterImeasured - TotalCurrent;
    if (Baseload_EV < 0) Baseload_EV = 0;
    Baseload = ctx->MainsMeterImeasured - TotalCurrent;

    int saveActiveEVSE = ActiveEVSE;

    // ---- Phase 3: Calculate IsetBalanced (lines 1198-1305) ----
    if (ctx->Mode == MODE_NORMAL) {
        // Normal mode (lines 1198-1210)
        if (ctx->LoadBl == 1)
            ctx->IsetBalanced = (ctx->MaxCircuit * 10) - Baseload_EV;
        else
            ctx->IsetBalanced = ctx->ChargeCurrent;

        if (ctx->Nr_Of_Phases_Charging != 3) {
            ctx->Switching_Phases_C2 = GOING_TO_SWITCH_3P;  // line 1207
        }
    } else {
        // Smart/Solar mode

        // Solar B-state phase determination (lines 1212-1231)
        if (ctx->Mode == MODE_SOLAR && ctx->State == STATE_B) {
            if (ctx->EnableC2 == AUTO) {
                if (-ctx->Isum >= (int32_t)(30 * ctx->MinCurrent + 30)) {
                    if (ctx->Nr_Of_Phases_Charging != 3)
                        ctx->Switching_Phases_C2 = GOING_TO_SWITCH_3P;
                } else {
                    if (ctx->Nr_Of_Phases_Charging != 1)
                        ctx->Switching_Phases_C2 = GOING_TO_SWITCH_1P;
                }
            }
        }

        // Calculate Idifference (lines 1235-1250)
        if ((ctx->LoadBl == 0 && ctx->EVMeterType) || (ctx->LoadBl == 1 && ctx->EVMeterType))
            Idifference = min_int((ctx->MaxMains * 10) - ctx->MainsMeterImeasured,
                                  (ctx->MaxCircuit * 10) - ctx->EVMeterImeasured);
        else
            Idifference = (ctx->MaxMains * 10) - ctx->MainsMeterImeasured;

        int32_t ExcessMaxSumMains = ((int32_t)(ctx->MaxSumMains * 10) - ctx->Isum);
        if (ctx->MaxSumMains) {
            Idifference = ExcessMaxSumMains;
            if (ExcessMaxSumMains < 0) {
                LimitedByMaxSumMains = true;
            } else {
                LimitedByMaxSumMains = false;
                ctx->MaxSumMainsTimer = 0;
            }
        }

        // Ongoing regulation (lines 1252-1265)
        if (!mod) {
            if (ctx->phasesLastUpdateFlag) {
                if (Idifference > 0) {
                    if (ctx->Mode == MODE_SMART)
                        ctx->IsetBalanced += (Idifference / 4);
                    // Solar increase is handled below
                } else {
                    ctx->IsetBalanced += Idifference;    // Immediately decrease (Smart and Solar)
                }
            }
            if (ctx->IsetBalanced < 0) ctx->IsetBalanced = 0;
            if (ctx->IsetBalanced > 800) ctx->IsetBalanced = 800;  // Hard limit 80A (line 1264)
        }

        // Solar fine-grained regulation (lines 1268-1293)
        if (ctx->Mode == MODE_SOLAR) {
            IsumImport = ctx->Isum - (10 * ctx->ImportCurrent);
            if (ActiveEVSE > 0 && Idifference > 0) {
                if (ctx->phasesLastUpdateFlag) {
                    if (IsumImport < 0) {
                        if (IsumImport < -10 && Idifference > 10)
                            ctx->IsetBalanced += 5;
                        else
                            ctx->IsetBalanced += 1;
                    } else if (IsumImport > 0) {
                        if (IsumImport > 20)
                            ctx->IsetBalanced -= (IsumImport / 2);
                        else if (IsumImport > 10)
                            ctx->IsetBalanced -= 5;
                        else if (IsumImport > 3)
                            ctx->IsetBalanced -= 1;
                    }
                }
            }
        } else {
            // Smart mode: new EVSE joining (lines 1296-1303)
            if (mod && ActiveEVSE) {
                ctx->IsetBalanced = min_int((ctx->MaxMains * 10) - Baseload,
                                            (ctx->MaxCircuit * 10) - Baseload_EV);
                if (ctx->MaxSumMains)
                    ctx->IsetBalanced = min_int(ctx->IsetBalanced,
                                                ((int32_t)(ctx->MaxSumMains * 10) - ctx->Isum) / 3);
            }
        }
    }

    // ---- Phase 4: Guard rails (lines 1307-1323) ----
    if (ctx->MainsMeterType && ctx->Mode != MODE_NORMAL)
        ctx->IsetBalanced = min_int(ctx->IsetBalanced, (ctx->MaxMains * 10) - Baseload);
    if (((ctx->LoadBl == 0 && ctx->EVMeterType && ctx->Mode != MODE_NORMAL) || ctx->LoadBl == 1))
        ctx->IsetBalanced = min_int(ctx->IsetBalanced, (ctx->MaxCircuit * 10) - Baseload_EV);
    if (ctx->GridRelayOpen) {
        int phases = evse_force_single_phase(ctx) ? 1 : 3;  // line 1320
        ctx->IsetBalanced = min_int(ctx->IsetBalanced,
                                    (ctx->GridRelayMaxSumMains * 10) / phases);
    }

    // ---- Phase 5: Shortage detection and distribution (lines 1328-1495) ----
    if (ActiveEVSE && (ctx->phasesLastUpdateFlag || ctx->Mode == MODE_NORMAL)) {

        if (ctx->IsetBalanced < (int32_t)(ActiveEVSE * ctx->MinCurrent * 10)) {
            // ---- Shortage of power (lines 1332-1440) ----
            ctx->IsetBalanced = ActiveEVSE * ctx->MinCurrent * 10;  // line 1336

            // Solar shortage: 3P->1P switching (lines 1337-1370)
            if (ctx->Mode == MODE_SOLAR) {
                // cppcheck-suppress knownConditionTrueFalse
                if (ActiveEVSE && IsumImport > 0 &&
                    (ctx->Isum > (int32_t)((ActiveEVSE * ctx->MinCurrent * ctx->Nr_Of_Phases_Charging
                                             - ctx->StartCurrent) * 10) ||
                     (ctx->Nr_Of_Phases_Charging > 1 && ctx->EnableC2 == AUTO))) {

                    if (ctx->Nr_Of_Phases_Charging > 1 && ctx->EnableC2 == AUTO &&
                        ctx->State == STATE_C) {
                        // Start solar stop timer for 3P->1P switch
                        if (ctx->SolarStopTimer == 0) {
                            if (IsumImport < (int32_t)(10 * ctx->MinCurrent))
                                ctx->SolarStopTimer = ctx->StopTime * 60;
                            if (ctx->SolarStopTimer == 0)
                                ctx->SolarStopTimer = 30;
                        }
                        if (ctx->SolarStopTimer <= 2) {
                            ctx->Switching_Phases_C2 = GOING_TO_SWITCH_1P;
                            evse_set_state(ctx, STATE_C1);
                            ctx->SolarStopTimer = 0;
                        }
                    } else {
                        if (ctx->SolarStopTimer == 0)
                            ctx->SolarStopTimer = ctx->StopTime * 60;
                    }
                } else {
                    ctx->SolarStopTimer = 0;
                }
            }

            // Check for HARD shortage (lines 1376-1398)
            bool hardShortage = false;
            if (ctx->MainsMeterType && ctx->Mode != MODE_NORMAL) {
                if (ctx->IsetBalanced > (int32_t)((ctx->MaxMains * 10) - Baseload))
                    hardShortage = true;
            }
            if (((ctx->LoadBl == 0 && ctx->EVMeterType && ctx->Mode != MODE_NORMAL) || ctx->LoadBl == 1) &&
                (ctx->IsetBalanced > (int32_t)((ctx->MaxCircuit * 10) - Baseload_EV)))
                hardShortage = true;
            if (!ctx->MaxSumMainsTime && LimitedByMaxSumMains)
                hardShortage = true;

            if (hardShortage && ctx->Switching_Phases_C2 != GOING_TO_SWITCH_1P) {
                ctx->NoCurrent++;
            } else {
                // Soft shortage - start MaxSumMains timer if needed (lines 1394-1397)
                if (LimitedByMaxSumMains && ctx->MaxSumMainsTime) {
                    if (ctx->MaxSumMainsTimer == 0)
                        ctx->MaxSumMainsTimer = ctx->MaxSumMainsTime * 60;
                }
            }

        } else {
            // ---- No shortage (lines 1399-1440) ----

            // Solar 1P->3P upgrade (lines 1404-1432)
            if (ctx->Mode == MODE_SOLAR && ctx->Nr_Of_Phases_Charging == 1 &&
                ctx->EnableC2 == AUTO &&
                ctx->IsetBalanced + 8 >= (int32_t)(ctx->MaxCurrent * 10) &&
                ctx->State == STATE_C) {

                int spareCurrent = (3 * ((int)ctx->MinCurrent + 1) - (int)ctx->MaxCurrent);
                if (spareCurrent < 0) spareCurrent = 3;
                if (-ctx->Isum > (10 * spareCurrent)) {
                    if (ctx->SolarStopTimer == 0) ctx->SolarStopTimer = 63;
                    if (ctx->SolarStopTimer <= 3) {
                        ctx->Switching_Phases_C2 = GOING_TO_SWITCH_3P;
                        evse_set_state(ctx, STATE_C1);
                        ctx->SolarStopTimer = 0;
                    }
                } else {
                    ctx->SolarStopTimer = 0;
                }
            } else {
                ctx->SolarStopTimer = 0;
                ctx->MaxSumMainsTimer = 0;
                ctx->NoCurrent = 0;
            }
        }

        // ---- Distribution (lines 1442-1495) ----
        if (ctx->IsetBalanced > ActiveMax) ctx->IsetBalanced = ActiveMax;  // line 1444
        int32_t MaxBalanced = ctx->IsetBalanced;

        // First pass: cap EVSEs at their max or solar startup min
        n = 0;
        while (n < NR_EVSES && ActiveEVSE) {
            int32_t Average = MaxBalanced / ActiveEVSE;
            if ((ctx->BalancedState[n] == STATE_C) && (!CurrentSet[n])) {
                // Solar startup: force MinCurrent (lines 1457-1465)
                if (ctx->Mode == MODE_SOLAR && ctx->Node[n].IntTimer < SOLARSTARTTIME) {
                    ctx->Balanced[n] = ctx->MinCurrent * 10;
                    CurrentSet[n] = 1;
                    ActiveEVSE--;
                    MaxBalanced -= ctx->Balanced[n];
                    ctx->IsetBalanced = TotalCurrent;
                    n = 0;
                    continue;
                } else if (Average >= (int32_t)ctx->BalancedMax[n]) {
                    ctx->Balanced[n] = ctx->BalancedMax[n];
                    CurrentSet[n] = 1;
                    ActiveEVSE--;
                    MaxBalanced -= ctx->Balanced[n];
                    n = 0;
                    continue;
                }
            }
            n++;
        }

        // Second pass: distribute remaining equally (lines 1484-1494)
        n = 0;
        while (n < NR_EVSES && ActiveEVSE) {
            if ((ctx->BalancedState[n] == STATE_C) && (!CurrentSet[n])) {
                ctx->Balanced[n] = MaxBalanced / ActiveEVSE;
                CurrentSet[n] = 1;
                ActiveEVSE--;
                MaxBalanced -= ctx->Balanced[n];
            }
            n++;
        }
    }

    // No active EVSEs: reset timers (lines 1497-1502)
    if (!saveActiveEVSE) {
        ctx->SolarStopTimer = 0;
        ctx->MaxSumMainsTimer = 0;
        ctx->NoCurrent = 0;
    }

    // Reset measurement flag (line 1505)
    ctx->phasesLastUpdateFlag = false;
}

// ---- Main 10ms state machine tick ----
// Faithful to Timer10ms_singlerun() in main.cpp:3002-3275
void evse_tick_10ms(evse_ctx_t *ctx, uint8_t pilot) {

    // ---- STATE_A / STATE_COMM_B / STATE_B1 handling (lines 3079-3130) ----
    // Original combines these three states in one handler
    if (ctx->State == STATE_A || ctx->State == STATE_COMM_B || ctx->State == STATE_B1) {

        if (ctx->PilotDisconnected) {
            // Pilot is floating, don't check voltage (line 3082-3086)
            if (ctx->PilotDisconnectTime == 0) {
                record_pilot(ctx, true);
                ctx->PilotDisconnected = false;
            }
        } else if (pilot == PILOT_12V) {
            // RFID lock timer start (line 3090)
            if ((ctx->RFIDReader == 2 || ctx->RFIDReader == 1) &&
                ctx->AccessTimer == 0 && ctx->AccessStatus == ON) {
                ctx->AccessTimer = RFIDLOCKTIME;
            }
            // Reset to STATE_A if stuck in COMM_B or B1 (line 3092)
            if (ctx->State != STATE_A) evse_set_state(ctx, STATE_A);
            ctx->ChargeDelay = 0;
        } else if (pilot == PILOT_9V && ctx->ErrorFlags == NO_ERROR &&
                   ctx->ChargeDelay == 0 && ctx->AccessStatus == ON &&
                   ctx->State != STATE_COMM_B) {
            // A->B transition (lines 3095-3126)
            ctx->DiodeCheck = 0;

            // Set ChargeCurrent based on MaxCapacity (line 3107-3108)
            if (ctx->MaxCurrent > ctx->MaxCapacity && ctx->MaxCapacity)
                ctx->ChargeCurrent = ctx->MaxCapacity * 10;
            else
                ctx->ChargeCurrent = ctx->MinCurrent * 10;

            // Node sends COMM_B to master (line 3111-3112)
            if (ctx->LoadBl > 1) {
                evse_set_state(ctx, STATE_COMM_B);
            // Master or standalone (lines 3114-3126)
            } else if (evse_is_current_available(ctx)) {
                ctx->BalancedMax[0] = ctx->MaxCapacity * 10;
                ctx->Balanced[0] = ctx->ChargeCurrent;

                // Modem stage check (lines 3119-3123, guarded by #if MODEM in original)
                if (ctx->ModemEnabled && ctx->ModemStage == 0) {
                    evse_set_state(ctx, STATE_MODEM_REQUEST);
                } else {
                    evse_set_state(ctx, STATE_B);
                }

                ctx->ActivationMode = 30;               // Line 3124: timeout to enter STATE_C
                ctx->AccessTimer = 0;                    // Line 3125

                // Set PWM for the charge current
                uint32_t duty = evse_current_to_duty(ctx->Balanced[0]);
                record_cp_duty(ctx, duty);
            } else {
                evse_set_error_flags(ctx, LESS_6A);
            }
        } else if (pilot == PILOT_9V && ctx->State != STATE_B1 &&
                   ctx->State != STATE_COMM_B && ctx->AccessStatus == ON) {
            // Errors or ChargeDelay prevent full transition, go to B1 (line 3127-3128)
            evse_set_state(ctx, STATE_B1);
        }
        return;
    }

    // ---- STATE_COMM_B_OK handling (lines 3132-3136) ----
    if (ctx->State == STATE_COMM_B_OK) {
        evse_set_state(ctx, STATE_B);
        ctx->ActivationMode = 30;
        ctx->AccessTimer = 0;
        return;
    }

    // ---- STATE_B / STATE_COMM_C handling (lines 3140-3197) ----
    if (ctx->State == STATE_B || ctx->State == STATE_COMM_C) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);                   // Disconnected
        } else if (pilot == PILOT_6V) {
            ctx->StateTimer++;
            if (ctx->StateTimer > 50) {                     // 500ms debounce (line 3145)
                if (ctx->DiodeCheck == 1 &&
                    ctx->ErrorFlags == NO_ERROR &&
                    ctx->ChargeDelay == 0 &&
                    ctx->AccessStatus == ON) {

                    // Node must request permission from master
                    if (ctx->LoadBl > 1) {
                        if (ctx->State != STATE_COMM_C)
                            evse_set_state(ctx, STATE_COMM_C);
                    } else {
                        // Master or standalone (lines 3158-3170)
                        ctx->BalancedMax[0] = ctx->ChargeCurrent;
                        if (evse_is_current_available(ctx)) {
                            ctx->Balanced[0] = ctx->MinCurrent * 10;
                            evse_calc_balanced_current(ctx, 1);
                            ctx->DiodeCheck = 0;
                            evse_set_state(ctx, STATE_C);
                        } else {
                            evse_set_error_flags(ctx, LESS_6A);
                        }
                    }
                }
            }
        } else if (pilot == PILOT_9V) {
            ctx->StateTimer = 0;                            // Reset B->C timer
            // Activation mode check (line 3177)
            if (ctx->ActivationMode == 0) {
                evse_set_state(ctx, STATE_ACTSTART);
                ctx->ActivationTimer = 3;
            }
        }

        // Diode check (line 3187-3195)
        if (pilot == PILOT_DIODE) {
            ctx->DiodeCheck = 1;
        }
        return;
    }

    // ---- STATE_C1 handling (lines 3199-3217) ----
    // Note: C1Timer countdown is in tick_1s, not tick_10ms (matches original Timer1S lines 1616-1625)
    if (ctx->State == STATE_C1) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        } else if (pilot == PILOT_9V) {
            evse_set_state(ctx, STATE_B1);           // Original line 3212: STATE_B1, not STATE_B
        }
        return;
    }

    // ---- STATE_C handling (lines 3236-3261) ----
    if (ctx->State == STATE_C) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);               // Disconnected
        } else if (pilot == PILOT_9V) {
            evse_set_state(ctx, STATE_B);               // Original line 3244: back to STATE_B
            ctx->DiodeCheck = 0;
        } else if (pilot == PILOT_SHORT) {
            ctx->StateTimer++;                           // Original line 3250: debounce 500ms
            if (ctx->StateTimer > 50) {
                ctx->StateTimer = 0;
                evse_set_state(ctx, STATE_B);
                ctx->DiodeCheck = 0;
            }
        } else {
            ctx->StateTimer = 0;                         // Original line 3259: reset on normal pilot
        }
        return;
    }

    // ---- STATE_ACTSTART handling (lines 3220-3223) ----
    if (ctx->State == STATE_ACTSTART) {
        if (ctx->ActivationTimer == 0) {
            evse_set_state(ctx, STATE_B);
            ctx->ActivationMode = 255;               // Disable ActivationMode
        }
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        }
        return;
    }

    // ---- STATE_COMM_C_OK handling (lines 3225-3232) ----
    if (ctx->State == STATE_COMM_C_OK) {
        ctx->DiodeCheck = 0;
        evse_set_state(ctx, STATE_C);
        return;
    }

    // ---- Modem states (simplified) ----
    if (ctx->State == STATE_MODEM_REQUEST || ctx->State == STATE_MODEM_WAIT ||
        ctx->State == STATE_MODEM_DONE || ctx->State == STATE_MODEM_DENIED) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        }
        return;
    }
}

// ---- 1-second timer tick ----
// Faithful to Timer1S_singlerun() in main.cpp:1529-1830
void evse_tick_1s(evse_ctx_t *ctx) {

    // ActivationMode countdown (lines 1541-1543)
    if (ctx->ActivationMode && ctx->ActivationMode != 255) {
        ctx->ActivationMode--;
    }

    // ActivationTimer countdown (line 1546)
    if (ctx->ActivationTimer) ctx->ActivationTimer--;

    // Modem timers (lines 1548-1611, guarded by #if MODEM in original)
    if (ctx->ModemEnabled) {
        if (ctx->State == STATE_MODEM_REQUEST) {
            if (ctx->ToModemWaitStateTimer > 0) {
                ctx->ToModemWaitStateTimer--;
            } else {
                evse_set_state(ctx, STATE_MODEM_WAIT);
            }
        }
        if (ctx->State == STATE_MODEM_WAIT) {
            if (ctx->ToModemDoneStateTimer > 0) {
                ctx->ToModemDoneStateTimer--;
            }
            if (ctx->ToModemDoneStateTimer == 0) {
                evse_set_state(ctx, STATE_MODEM_DONE);
            }
        }
        if (ctx->State == STATE_MODEM_DONE) {
            if (ctx->LeaveModemDoneStateTimer > 0) {
                ctx->LeaveModemDoneStateTimer--;
            }
            if (ctx->LeaveModemDoneStateTimer == 0) {
                // EVCCID validation (lines 1585-1598)
                record_cp_duty(ctx, 1024);                      // Reset CP (line 1581)
                record_pilot(ctx, false);                        // PILOT_DISCONNECTED (line 1582)
                if (ctx->RequiredEVCCID[0] == '\0' ||
                    strcmp(ctx->RequiredEVCCID, ctx->EVCCID) == 0) {
                    ctx->ModemStage = 1;                         // Skip modem next time
                    evse_set_state(ctx, STATE_B);
                } else {
                    ctx->ModemStage = 0;
                    ctx->LeaveModemDeniedStateTimer = 60;
                    evse_set_state(ctx, STATE_MODEM_DENIED);
                }
            }
        }
        if (ctx->State == STATE_MODEM_DENIED) {
            if (ctx->LeaveModemDeniedStateTimer > 0) {
                ctx->LeaveModemDeniedStateTimer--;
            }
            if (ctx->LeaveModemDeniedStateTimer == 0) {
                evse_set_state(ctx, STATE_A);
                record_pilot(ctx, true);                         // PILOT_CONNECTED (line 1608)
            }
        }
    }

    // C1Timer countdown (lines 1616-1625)
    if (ctx->State == STATE_C1) {
        if (ctx->C1Timer > 0) {
            ctx->C1Timer--;
        } else {
            evse_set_state(ctx, STATE_B1);
        }
    }

    // SolarStopTimer countdown (lines 1670-1679)
    if (ctx->SolarStopTimer > 0) {
        ctx->SolarStopTimer--;
        if (ctx->SolarStopTimer == 0) {
            if (ctx->State == STATE_C) evse_set_state(ctx, STATE_C1);
            evse_set_error_flags(ctx, LESS_6A);
        }
    }

    // Pilot disconnect timer (line 1682)
    if (ctx->PilotDisconnectTime > 0) {
        ctx->PilotDisconnectTime--;
        if (ctx->PilotDisconnectTime == 0) {
            record_pilot(ctx, true);                    // PILOT_CONNECTED
            ctx->PilotDisconnected = false;
        }
    }

    // Charge timer per node (lines 1685-1690)
    for (int x = 0; x < NR_EVSES; x++) {
        if (ctx->BalancedState[x] == STATE_C) {
            ctx->Node[x].IntTimer++;
            ctx->Node[x].Timer++;
        } else {
            ctx->Node[x].IntTimer = 0;
        }
    }

    // MaxSumMains timer (lines 1705-1711)
    if (ctx->MaxSumMainsTimer > 0) {
        ctx->MaxSumMainsTimer--;
        if (ctx->MaxSumMainsTimer == 0) {
            if (ctx->State == STATE_C) evse_set_state(ctx, STATE_C1);
            evse_set_error_flags(ctx, LESS_6A);
        }
    }

    // ChargeDelay countdown (line 1713)
    if (ctx->ChargeDelay > 0) ctx->ChargeDelay--;

    // AccessTimer (lines 1715-1719)
    if (ctx->AccessTimer > 0 && ctx->State == STATE_A) {
        ctx->AccessTimer--;
        if (ctx->AccessTimer == 0) {
            evse_set_access(ctx, OFF);
        }
    } else if (ctx->State != STATE_A) {
        ctx->AccessTimer = 0;
    }

    // Temperature recovery (line 1722-1723)
    if ((ctx->TempEVSE < (ctx->maxTemp - 10)) && (ctx->ErrorFlags & TEMP_HIGH)) {
        evse_clear_error_flags(ctx, TEMP_HIGH);
    }

    // LESS_6A auto-recovery (lines 1726-1729)
    if ((ctx->ErrorFlags & LESS_6A) && (ctx->LoadBl < 2) && evse_is_current_available(ctx)) {
        evse_clear_error_flags(ctx, LESS_6A);
    }

    // MainsMeter timeout (lines 1732-1755)
    if (ctx->MainsMeterType && ctx->LoadBl < 2) {
        if (ctx->MainsMeterTimeout == 0 && !(ctx->ErrorFlags & CT_NOCOMM) && ctx->Mode != MODE_NORMAL) {
            evse_set_error_flags(ctx, CT_NOCOMM);
            evse_set_power_unavailable(ctx);
        } else if (ctx->MainsMeterTimeout > 0) {
            ctx->MainsMeterTimeout--;
        }
    } else if (ctx->LoadBl > 1) {
        if (ctx->MainsMeterTimeout == 0 && !(ctx->ErrorFlags & CT_NOCOMM)) {
            evse_set_error_flags(ctx, CT_NOCOMM);
            evse_set_power_unavailable(ctx);
        } else if (ctx->MainsMeterTimeout > 0) {
            ctx->MainsMeterTimeout--;
        }
    } else {
        ctx->MainsMeterTimeout = COMM_TIMEOUT;
    }

    // EVMeter timeout (lines 1758-1766)
    if (ctx->EVMeterType) {
        if (ctx->EVMeterTimeout == 0 && !(ctx->ErrorFlags & EV_NOCOMM) && ctx->Mode != MODE_NORMAL) {
            evse_set_error_flags(ctx, EV_NOCOMM);
            evse_set_power_unavailable(ctx);
        } else if (ctx->EVMeterTimeout > 0) {
            ctx->EVMeterTimeout--;
        }
    } else {
        ctx->EVMeterTimeout = COMM_EVTIMEOUT;
    }

    // CT_NOCOMM recovery (line 1769)
    if ((ctx->ErrorFlags & CT_NOCOMM) && ctx->MainsMeterTimeout > 0) {
        evse_clear_error_flags(ctx, CT_NOCOMM);
    }

    // EV_NOCOMM recovery (line 1771)
    if ((ctx->ErrorFlags & EV_NOCOMM) && ctx->EVMeterTimeout > 0) {
        evse_clear_error_flags(ctx, EV_NOCOMM);
    }

    // Temperature check (lines 1773-1778)
    if (ctx->TempEVSE > ctx->maxTemp && !(ctx->ErrorFlags & TEMP_HIGH)) {
        evse_set_error_flags(ctx, TEMP_HIGH);
        evse_set_power_unavailable(ctx);
    }

    // LESS_6A active: enforce power unavailable + charge delay (lines 1780-1787)
    if (ctx->ErrorFlags & LESS_6A) {
        evse_set_power_unavailable(ctx);
        if (ctx->ChargeDelay == 0)
            ctx->ChargeDelay = CHARGEDELAY;
    }
}
