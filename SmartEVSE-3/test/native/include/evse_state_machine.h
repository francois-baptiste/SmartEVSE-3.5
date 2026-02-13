#ifndef EVSE_STATE_MACHINE_H
#define EVSE_STATE_MACHINE_H

#include "evse_types.h"

// ---- Initialization ----
// Initialize context to safe defaults (matches original power-on state)
void evse_init(evse_ctx_t *ctx, evse_hal_t *hal);

// ---- Core state machine functions ----
// Set new state with all side effects (contactors, PWM, pilot) - faithful to setState() in main.cpp:790
void evse_set_state(evse_ctx_t *ctx, uint8_t new_state);

// Main 10ms state machine tick - reads pilot and drives transitions
// pilot_reading: the simulated pilot voltage level (PILOT_12V, PILOT_9V, PILOT_6V, PILOT_DIODE)
void evse_tick_10ms(evse_ctx_t *ctx, uint8_t pilot_reading);

// 1-second timer tick - handles ChargeDelay countdown, meter timeouts, error recovery, solar timers
void evse_tick_1s(evse_ctx_t *ctx);

// ---- Power availability ----
// Check if current is available for one more EVSE to start charging
// Returns 1 if available, 0 if not - faithful to IsCurrentAvailable() in main.cpp:1061
int evse_is_current_available(evse_ctx_t *ctx);

// ---- Current distribution ----
// Calculate and distribute current across all active EVSEs
// mod=0: normal recalculation, mod=1: new EVSE is starting to charge
// Faithful to CalcBalancedCurrent() in main.cpp:1148
void evse_calc_balanced_current(evse_ctx_t *ctx, int mod);

// ---- Current to PWM conversion ----
// Convert charge current (Amps*10) to PWM duty cycle - faithful to SetCurrent() in main.cpp:718
uint32_t evse_current_to_duty(uint16_t current);

// ---- Authorization ----
// Set access status with side effects - faithful to setAccess() in main.cpp:967
void evse_set_access(evse_ctx_t *ctx, AccessStatus_t access);

// ---- Error management ----
void evse_set_error_flags(evse_ctx_t *ctx, uint8_t flags);
void evse_clear_error_flags(evse_ctx_t *ctx, uint8_t flags);

// Graceful power unavailable - faithful to setStatePowerUnavailable() in main.cpp:736
void evse_set_power_unavailable(evse_ctx_t *ctx);

// ---- Phase switching helper ----
// Returns 1 if single phase charging should be forced - faithful to Force_Single_Phase_Charging()
uint8_t evse_force_single_phase(evse_ctx_t *ctx);

// Check if phase switching is needed on entry to STATE_B - faithful to CheckSwitchingPhases()
void evse_check_switching_phases(evse_ctx_t *ctx);

#endif // EVSE_STATE_MACHINE_H
