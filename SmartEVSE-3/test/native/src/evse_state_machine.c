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
};

// ---- Recording HAL for test instrumentation ----
static void record_cp_duty(evse_ctx_t *ctx, uint32_t duty) {
    ctx->last_pwm_duty = duty;
    if (ctx->hal.set_cp_duty) ctx->hal.set_cp_duty(duty);
}

static void record_contactor1(evse_ctx_t *ctx, bool on) {
    ctx->contactor1_state = on;
    if (ctx->hal.contactor1) ctx->hal.contactor1(on);
}

static void record_contactor2(evse_ctx_t *ctx, bool on) {
    ctx->contactor2_state = on;
    if (ctx->hal.contactor2) ctx->hal.contactor2(on);
}

static void record_pilot(evse_ctx_t *ctx, bool connected) {
    ctx->pilot_connected = connected;
    if (ctx->hal.set_pilot) ctx->hal.set_pilot(connected);
}

// ---- Initialization ----
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

    // Modem
    ctx->ModemStage = 0;

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

    // Test instrumentation
    ctx->pilot_connected = true;
    ctx->contactor1_state = false;
    ctx->contactor2_state = false;
    ctx->transition_count = 0;
}

// ---- Phase switching helper ----
// Faithful to Force_Single_Phase_Charging() in main.cpp:681-696
uint8_t evse_force_single_phase(evse_ctx_t *ctx) {
    switch (ctx->EnableC2) {
        case NOT_PRESENT: return 0;  // 3P
        case ALWAYS_OFF:  return 1;  // 1P
        case SOLAR_OFF:   return (ctx->Mode == MODE_SOLAR) ? 1 : 0;
        case AUTO_C2:     return (ctx->Nr_Of_Phases_Charging == 1) ? 1 : 0;
        case ALWAYS_ON:   return 0;  // 3P
        default:          return 0;
    }
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
    // Log transition
    if (ctx->State != new_state && ctx->transition_count < 64) {
        ctx->transition_log[ctx->transition_count++] = new_state;
    }

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
            // CheckSwitchingPhases simplified
            record_pilot(ctx, true);                     // PILOT_CONNECTED
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
// Simplified but covers Normal, Smart, Solar logic
void evse_calc_balanced_current(evse_ctx_t *ctx, int mod) {
    uint8_t n, ActiveEVSE = 0;
    int32_t TotalCurrent = 0;
    int32_t ActiveMax __attribute__((unused)) = 0;
    int32_t Baseload, Baseload_EV;

    // Phase 1: Count active EVSEs, compute totals (line 1148-1156)
    for (n = 0; n < NR_EVSES; n++) {
        if (ctx->BalancedState[n] == STATE_C) {
            ActiveEVSE++;
            ActiveMax += ctx->BalancedMax[n];
            TotalCurrent += ctx->Balanced[n];
        }
    }
    if (ActiveEVSE == 0) return;

    // Phase 2: Determine ChargeCurrent (line 1158-1179)
    ctx->ChargeCurrent = ctx->MaxCurrent * 10;
    if (ctx->MaxCurrent > ctx->MaxCapacity && ctx->MaxCapacity)
        ctx->ChargeCurrent = ctx->MaxCapacity * 10;
    ctx->BalancedMax[0] = ctx->ChargeCurrent;

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

    // Phase 3: Calculate IsetBalanced based on mode (lines 1198-1305)
    Baseload = ctx->MainsMeterImeasured - TotalCurrent;
    Baseload_EV = ctx->EVMeterImeasured - TotalCurrent;
    if (Baseload_EV < 0) Baseload_EV = 0;

    if (ctx->Mode == MODE_NORMAL) {
        // Normal mode (line 1198-1210)
        if (ctx->LoadBl == 1) {
            ctx->IsetBalanced = (ctx->MaxCircuit * 10) - Baseload_EV;
        } else {
            ctx->IsetBalanced = ctx->ChargeCurrent;
        }
    } else if (mod && ActiveEVSE) {
        // New EVSE joining - recalculate from scratch (line 1233-1248)
        int32_t from_mains = (ctx->MaxMains * 10) - Baseload;
        int32_t from_circuit = (ctx->MaxCircuit * 10) - Baseload_EV;
        ctx->IsetBalanced = min_int(from_mains, from_circuit);

        if (ctx->MaxSumMains) {
            int32_t from_sum = ((int32_t)(ctx->MaxSumMains * 10) - ctx->Isum) / 3;
            ctx->IsetBalanced = min_int(ctx->IsetBalanced, from_sum);
        }
    } else {
        // Ongoing regulation for Smart/Solar (lines 1251-1304)
        int32_t Idifference;

        if (ctx->MainsMeterType) {
            Idifference = (ctx->MaxMains * 10) - ctx->MainsMeterImeasured;
        } else {
            Idifference = 0;
        }

        if (ctx->LoadBl == 1 || (ctx->LoadBl == 0 && ctx->EVMeterType)) {
            int32_t circuit_diff = (ctx->MaxCircuit * 10) - ctx->EVMeterImeasured;
            Idifference = min_int(Idifference, circuit_diff);
        }

        if (ctx->MaxSumMains) {
            int32_t sum_excess = (ctx->MaxSumMains * 10) - ctx->Isum;
            Idifference = sum_excess;
        }

        if (ctx->Mode == MODE_SMART) {
            // Smart mode: slow increase, fast decrease (lines 1294-1304)
            if (Idifference > 0)
                ctx->IsetBalanced += (Idifference / 4);
            else
                ctx->IsetBalanced += Idifference;
        } else {
            // Solar mode: fine-grained regulation (lines 1268-1293)
            int32_t IsumImport = ctx->Isum - (10 * ctx->ImportCurrent);

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

    // Phase 4: Guard rails (lines 1307-1323)
    if (ctx->MainsMeterType && ctx->Mode != MODE_NORMAL) {
        int32_t mains_limit = (ctx->MaxMains * 10) - Baseload;
        if (ctx->IsetBalanced > mains_limit)
            ctx->IsetBalanced = mains_limit;
    }
    if (((ctx->LoadBl == 0 && ctx->EVMeterType && ctx->Mode != MODE_NORMAL) || ctx->LoadBl == 1)) {
        int32_t circuit_limit = (ctx->MaxCircuit * 10) - Baseload_EV;
        if (ctx->IsetBalanced > circuit_limit)
            ctx->IsetBalanced = circuit_limit;
    }
    if (ctx->GridRelayOpen) {
        uint8_t phases = ctx->Nr_Of_Phases_Charging ? ctx->Nr_Of_Phases_Charging : 1;
        int32_t relay_limit = (ctx->GridRelayMaxSumMains * 10) / phases;
        if (ctx->IsetBalanced > relay_limit)
            ctx->IsetBalanced = relay_limit;
    }

    // Clamp to minimum 0
    if (ctx->IsetBalanced < 0) ctx->IsetBalanced = 0;

    // Phase 5: Shortage detection (lines 1328-1440)
    bool hardShortage = (ctx->IsetBalanced < (int32_t)(ActiveEVSE * ctx->MinCurrent * 10));

    if (hardShortage && ctx->Mode != MODE_NORMAL) {
        ctx->NoCurrent++;
    } else {
        ctx->NoCurrent = 0;
    }

    // Phase 6: Distribution (lines 1442-1495)
    int32_t MaxBalanced = ctx->IsetBalanced;
    uint8_t remaining = ActiveEVSE;
    bool CurrentSet[NR_EVSES] = {false};

    // Clamp total to ChargeCurrent if single EVSE and not load balancing
    if (ActiveEVSE == 1 && ctx->LoadBl == 0) {
        if (MaxBalanced > ctx->ChargeCurrent)
            MaxBalanced = ctx->ChargeCurrent;
    }

    // First pass: assign EVSEs limited by their max
    if (remaining > 0) {
        int32_t avg = MaxBalanced / remaining;
        bool changed = true;
        while (changed) {
            changed = false;
            for (n = 0; n < NR_EVSES; n++) {
                if (ctx->BalancedState[n] == STATE_C && !CurrentSet[n]) {
                    if (avg >= (int32_t)ctx->BalancedMax[n] && ctx->BalancedMax[n] > 0) {
                        ctx->Balanced[n] = ctx->BalancedMax[n];
                        CurrentSet[n] = true;
                        remaining--;
                        MaxBalanced -= ctx->Balanced[n];
                        if (remaining > 0) avg = MaxBalanced / remaining;
                        changed = true;
                    }
                }
            }
        }
    }

    // Second pass: distribute remaining equally
    for (n = 0; n < NR_EVSES; n++) {
        if (ctx->BalancedState[n] == STATE_C && !CurrentSet[n]) {
            if (remaining > 0) {
                ctx->Balanced[n] = MaxBalanced / remaining;
                remaining--;
                MaxBalanced -= ctx->Balanced[n];
            } else {
                ctx->Balanced[n] = 0;
            }
            CurrentSet[n] = true;
        }
    }

    // Ensure minimum current per EVSE
    for (n = 0; n < NR_EVSES; n++) {
        if (ctx->BalancedState[n] == STATE_C) {
            if (ctx->Balanced[n] > 0 && ctx->Balanced[n] < ctx->MinCurrent * 10)
                ctx->Balanced[n] = ctx->MinCurrent * 10;
        }
    }
}

// ---- Main 10ms state machine tick ----
// Faithful to Timer10ms_singlerun() in main.cpp:3002-3275
void evse_tick_10ms(evse_ctx_t *ctx, uint8_t pilot) {

    // ---- STATE_A handling (lines 3079-3136) ----
    if (ctx->State == STATE_A) {
        if (pilot == PILOT_9V &&
            ctx->State != STATE_MODEM_REQUEST && ctx->State != STATE_MODEM_WAIT && ctx->State != STATE_MODEM_DONE) {

            if (pilot == PILOT_9V && ctx->ErrorFlags == NO_ERROR &&
                ctx->ChargeDelay == 0 && ctx->AccessStatus == ON) {

                // Check modem stage
                if (ctx->ModemStage == 0 && ctx->RFIDReader == 0) {
                    // Skip modem for now in test model (no modem hardware)
                }

                // Check current availability (line 3115-3126)
                if (evse_is_current_available(ctx)) {
                    ctx->MaxCapacity = ctx->MaxCapacity ? ctx->MaxCapacity : ctx->MaxCurrent;
                    ctx->BalancedMax[0] = ctx->MaxCapacity * 10;
                    ctx->Balanced[0] = ctx->ChargeCurrent ? ctx->ChargeCurrent : ctx->MaxCurrent * 10;
                    evse_set_state(ctx, STATE_B);

                    // Set PWM for the charge current
                    uint32_t duty = evse_current_to_duty(ctx->Balanced[0]);
                    record_cp_duty(ctx, duty);

                    // Start AccessTimer if RFID enabled (line 3090)
                    if ((ctx->RFIDReader == 2 || ctx->RFIDReader == 1) &&
                        ctx->AccessTimer == 0 && ctx->AccessStatus == ON) {
                        ctx->AccessTimer = RFIDLOCKTIME;
                    }
                } else {
                    evse_set_error_flags(ctx, LESS_6A);
                }
            } else {
                // Can't transition - set error if conditions not met
                if (ctx->ErrorFlags != NO_ERROR || ctx->ChargeDelay != 0 || ctx->AccessStatus != ON) {
                    // Stay in STATE_A
                }
            }
        }
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

    // ---- STATE_C1 handling (lines 3199-3233) ----
    if (ctx->State == STATE_C1) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        } else if (pilot == PILOT_9V) {
            evse_set_state(ctx, STATE_B);
        } else {
            // C1Timer countdown — force contactor off
            if (ctx->C1Timer > 0) {
                ctx->C1Timer--;
            }
            if (ctx->C1Timer == 0) {
                record_contactor1(ctx, false);
                record_contactor2(ctx, false);
                evse_set_state(ctx, STATE_B1);
            }
        }
        return;
    }

    // ---- STATE_C handling (lines 3236-3261) ----
    if (ctx->State == STATE_C) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        } else if (pilot == PILOT_9V) {
            // EV signals it wants to stop
            evse_set_state(ctx, STATE_C1);
        }
        // While in STATE_C, current regulation happens via ModbusRequestLoop / calc
        return;
    }

    // ---- STATE_B1 handling ----
    if (ctx->State == STATE_B1) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        } else if (pilot == PILOT_9V) {
            // Pilot reconnect after delay
            if (ctx->PilotDisconnectTime == 0 && !ctx->PilotDisconnected) {
                // Can potentially go back to STATE_B
                if (ctx->ErrorFlags == NO_ERROR && ctx->ChargeDelay == 0 && ctx->AccessStatus == ON) {
                    evse_set_state(ctx, STATE_B);
                }
            }
        }
        return;
    }

    // ---- STATE_ACTSTART handling ----
    if (ctx->State == STATE_ACTSTART) {
        if (pilot == PILOT_12V) {
            evse_set_state(ctx, STATE_A);
        }
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
// Faithful to Timer1S in main.cpp:1529-1830 (key parts)
void evse_tick_1s(evse_ctx_t *ctx) {

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

    // MainsMeter timeout (lines 1733-1755)
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

    // EVMeter timeout (lines 1758-1765)
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

    // Modem timers (lines 1548-1611)
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
            ctx->ModemStage = 1;  // Skip modem next time
            evse_set_state(ctx, STATE_B);
        }
    }
    if (ctx->State == STATE_MODEM_DENIED) {
        if (ctx->LeaveModemDeniedStateTimer > 0) {
            ctx->LeaveModemDeniedStateTimer--;
        }
        if (ctx->LeaveModemDeniedStateTimer == 0) {
            evse_set_state(ctx, STATE_A);
        }
    }
}
