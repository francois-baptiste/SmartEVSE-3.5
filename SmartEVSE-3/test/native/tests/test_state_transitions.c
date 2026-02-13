/*
 * test_state_transitions.c - Core pilot-driven state machine transitions
 *
 * Tests the fundamental IEC 61851-1 state transitions:
 *   STATE_A (disconnected) -> STATE_B (connected) -> STATE_C (charging)
 *   and all intermediate / error paths.
 */

#include "test_framework.h"
#include "evse_types.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

// ---- helpers ----
static void setup_idle(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
}

// Setup a context that's ready to transition from A->B
static void setup_ready_to_charge(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;           // Standalone
    ctx.ChargeCurrent = 100;  // 10A
    ctx.ModemStage = 1;       // Skip modem negotiation (already authenticated)
}

// ---- Tests ----

void test_init_state_is_A(void) {
    evse_init(&ctx, NULL);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_init_contactors_off(void) {
    evse_init(&ctx, NULL);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

void test_init_pilot_connected(void) {
    evse_init(&ctx, NULL);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
}

void test_init_no_errors(void) {
    evse_init(&ctx, NULL);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, ctx.ErrorFlags);
}

void test_A_stays_A_on_12V(void) {
    setup_ready_to_charge();
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_A_to_B_on_9V_when_ready(void) {
    setup_ready_to_charge();
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
}

void test_A_to_modem_when_modem_stage_0(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.ChargeCurrent = 100;
    ctx.ModemStage = 0;  // Modem not yet authenticated
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_REQUEST, ctx.State);
}

void test_A_stays_A_when_access_off(void) {
    setup_ready_to_charge();
    ctx.AccessStatus = OFF;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// Original line 3127-3128: with errors, 9V pilot triggers transition to B1
void test_A_to_B1_when_errors(void) {
    setup_ready_to_charge();
    ctx.ErrorFlags = TEMP_HIGH;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

// Original line 3127-3128: with ChargeDelay, 9V pilot triggers transition to B1
void test_A_to_B1_when_charge_delay(void) {
    setup_ready_to_charge();
    ctx.ChargeDelay = 10;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_B_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_B_to_C_on_6V_with_diode_check(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;

    // Need 500ms of 6V (>50 ticks at 10ms)
    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
}

void test_B_to_C_requires_diode_check(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 0;  // No diode check yet
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;

    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    // Should NOT reach STATE_C without diode check
    TEST_ASSERT_NOT_EQUAL(STATE_C, ctx.State);
}

void test_diode_check_sets_on_pilot_diode(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 0;
    evse_tick_10ms(&ctx, PILOT_DIODE);
    TEST_ASSERT_EQUAL_INT(1, ctx.DiodeCheck);
}

void test_C_contactor1_on(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_TRUE(ctx.contactor1_state);
}

void test_C_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
}

// Original line 3243-3244: STATE_C + 9V → STATE_B (not STATE_C1)
void test_C_to_B_on_9V(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(0, ctx.DiodeCheck);  // DiodeCheck reset (line 3245)
}

// PILOT_SHORT in STATE_C: debounce 500ms then go to STATE_B
void test_C_to_B_on_pilot_short(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    // Need >50 ticks of PILOT_SHORT (500ms debounce)
    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_SHORT);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
}

void test_C1_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// Original line 3212: STATE_C1 + 9V → STATE_B1 (not STATE_B)
void test_C1_to_B1_on_9V(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

// C1Timer countdown is in tick_1s (original lines 1616-1625)
void test_C1_timer_transitions_to_B1(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    // C1Timer is set to 6 on entry
    TEST_ASSERT_EQUAL_INT(6, ctx.C1Timer);
    // Tick 1s 7 times to expire timer (6 decrements + 1 to trigger)
    for (int i = 0; i < 7; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

void test_B1_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B1);
    // B1 entry sets PilotDisconnected=true when AccessStatus=ON
    // Must wait for PilotDisconnectTime to clear before pilot is read
    ctx.PilotDisconnected = false;
    ctx.PilotDisconnectTime = 0;
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_set_state_B1_sets_charge_delay(void) {
    setup_ready_to_charge();
    ctx.ChargeDelay = 0;
    evse_set_state(&ctx, STATE_B1);
    TEST_ASSERT_GREATER_THAN(0, ctx.ChargeDelay);
}

void test_set_state_A_clears_errors_and_delay(void) {
    setup_ready_to_charge();
    ctx.ErrorFlags = LESS_6A;
    ctx.ChargeDelay = 10;
    evse_set_state(&ctx, STATE_A);
    TEST_ASSERT_EQUAL_INT(0, ctx.ErrorFlags & LESS_6A);
    TEST_ASSERT_EQUAL_INT(0, ctx.ChargeDelay);
}

void test_transition_log_records_states(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(2, ctx.transition_count);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.transition_log[0]);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.transition_log[1]);
}

void test_set_state_C1_sets_pwm_off(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    evse_set_state(&ctx, STATE_C1);
    TEST_ASSERT_EQUAL_INT(1024, ctx.last_pwm_duty);  // PWM off = +12V
}

void test_full_charge_cycle(void) {
    setup_ready_to_charge();
    // A: vehicle not connected
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);

    // Vehicle plugs in -> 9V pilot
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_FALSE(ctx.contactor1_state);

    // Vehicle requests charge -> 6V after diode check
    ctx.DiodeCheck = 1;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
    TEST_ASSERT_TRUE(ctx.contactor1_state);

    // Vehicle stops -> 9V goes back to STATE_B (original line 3244)
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);

    // Vehicle disconnects -> 12V
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
}

void test_actstart_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_ACTSTART);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_activation_mode_triggers_actstart(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.ActivationMode = 0;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_ACTSTART, ctx.State);
    TEST_ASSERT_EQUAL_INT(3, ctx.ActivationTimer);
}

// ActivationMode countdown and ActivationTimer in tick_1s
void test_activation_mode_countdown(void) {
    evse_init(&ctx, NULL);
    ctx.ActivationMode = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.ActivationMode);
}

void test_activation_mode_255_does_not_countdown(void) {
    evse_init(&ctx, NULL);
    ctx.ActivationMode = 255;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(255, ctx.ActivationMode);
}

void test_actstart_returns_to_B_when_timer_expires(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_ACTSTART);
    ctx.ActivationTimer = 0;
    evse_tick_10ms(&ctx, PILOT_9V);  // Non-12V pilot, timer expired
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(255, ctx.ActivationMode);
}

// COMM_B_OK handler
void test_comm_b_ok_transitions_to_B(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.State = STATE_COMM_B_OK;
    ctx.BalancedState[0] = STATE_COMM_B_OK;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(30, ctx.ActivationMode);
}

// COMM_C_OK handler
void test_comm_c_ok_transitions_to_C(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.State = STATE_COMM_C_OK;
    ctx.BalancedState[0] = STATE_COMM_C_OK;
    evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
}

// Node sends COMM_B when LoadBl > 1
void test_node_sends_comm_b(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 2;  // Node
    ctx.ModemStage = 1;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_COMM_B, ctx.State);
}

// CheckSwitchingPhases called on STATE_B entry
// When in STATE_A, phases are set directly; when in STATE_B+, Switching_Phases_C2 is set
void test_state_B_calls_check_switching_phases_from_A(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = ALWAYS_OFF;
    ctx.Nr_Of_Phases_Charging = 3;
    // From STATE_A, CheckSwitchingPhases sets Nr_Of_Phases directly
    evse_set_state(&ctx, STATE_B);
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
}

void test_state_B_calls_check_switching_phases_from_B(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = ALWAYS_OFF;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.State = STATE_B;  // Already past STATE_A
    ctx.BalancedState[0] = STATE_B;
    evse_set_state(&ctx, STATE_B);
    // From STATE_B, CheckSwitchingPhases sets Switching_Phases_C2
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_1P, ctx.Switching_Phases_C2);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("State Transitions");

    RUN_TEST(test_init_state_is_A);
    RUN_TEST(test_init_contactors_off);
    RUN_TEST(test_init_pilot_connected);
    RUN_TEST(test_init_no_errors);
    RUN_TEST(test_A_stays_A_on_12V);
    RUN_TEST(test_A_to_B_on_9V_when_ready);
    RUN_TEST(test_A_to_modem_when_modem_stage_0);
    RUN_TEST(test_A_stays_A_when_access_off);
    RUN_TEST(test_A_to_B1_when_errors);
    RUN_TEST(test_A_to_B1_when_charge_delay);
    RUN_TEST(test_B_to_A_on_disconnect);
    RUN_TEST(test_B_to_C_on_6V_with_diode_check);
    RUN_TEST(test_B_to_C_requires_diode_check);
    RUN_TEST(test_diode_check_sets_on_pilot_diode);
    RUN_TEST(test_C_contactor1_on);
    RUN_TEST(test_C_to_A_on_disconnect);
    RUN_TEST(test_C_to_B_on_9V);
    RUN_TEST(test_C_to_B_on_pilot_short);
    RUN_TEST(test_C1_to_A_on_disconnect);
    RUN_TEST(test_C1_to_B1_on_9V);
    RUN_TEST(test_C1_timer_transitions_to_B1);
    RUN_TEST(test_B1_to_A_on_disconnect);
    RUN_TEST(test_set_state_B1_sets_charge_delay);
    RUN_TEST(test_set_state_A_clears_errors_and_delay);
    RUN_TEST(test_transition_log_records_states);
    RUN_TEST(test_set_state_C1_sets_pwm_off);
    RUN_TEST(test_full_charge_cycle);
    RUN_TEST(test_actstart_to_A_on_disconnect);
    RUN_TEST(test_activation_mode_triggers_actstart);
    RUN_TEST(test_activation_mode_countdown);
    RUN_TEST(test_activation_mode_255_does_not_countdown);
    RUN_TEST(test_actstart_returns_to_B_when_timer_expires);
    RUN_TEST(test_comm_b_ok_transitions_to_B);
    RUN_TEST(test_comm_c_ok_transitions_to_C);
    RUN_TEST(test_node_sends_comm_b);
    RUN_TEST(test_state_B_calls_check_switching_phases_from_A);
    RUN_TEST(test_state_B_calls_check_switching_phases_from_B);

    TEST_SUITE_RESULTS();
}
