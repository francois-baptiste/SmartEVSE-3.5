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

void test_A_stays_A_when_access_off(void) {
    setup_ready_to_charge();
    ctx.AccessStatus = OFF;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_A_stays_A_when_errors(void) {
    setup_ready_to_charge();
    ctx.ErrorFlags = TEMP_HIGH;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_A_stays_A_when_charge_delay(void) {
    setup_ready_to_charge();
    ctx.ChargeDelay = 10;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
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

void test_C_to_C1_on_9V(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

void test_C1_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_C1_to_B_on_9V(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
}

void test_C1_timer_transitions_to_B1(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C1);
    // C1Timer is set to 6 on entry
    TEST_ASSERT_EQUAL_INT(6, ctx.C1Timer);
    // Tick 6V until timer expires
    for (int i = 0; i < 7; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

void test_B1_to_A_on_disconnect(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B1);
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

    // Vehicle stops -> 9V
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);

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

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("State Transitions");

    RUN_TEST(test_init_state_is_A);
    RUN_TEST(test_init_contactors_off);
    RUN_TEST(test_init_pilot_connected);
    RUN_TEST(test_init_no_errors);
    RUN_TEST(test_A_stays_A_on_12V);
    RUN_TEST(test_A_to_B_on_9V_when_ready);
    RUN_TEST(test_A_stays_A_when_access_off);
    RUN_TEST(test_A_stays_A_when_errors);
    RUN_TEST(test_A_stays_A_when_charge_delay);
    RUN_TEST(test_B_to_A_on_disconnect);
    RUN_TEST(test_B_to_C_on_6V_with_diode_check);
    RUN_TEST(test_B_to_C_requires_diode_check);
    RUN_TEST(test_diode_check_sets_on_pilot_diode);
    RUN_TEST(test_C_contactor1_on);
    RUN_TEST(test_C_to_A_on_disconnect);
    RUN_TEST(test_C_to_C1_on_9V);
    RUN_TEST(test_C1_to_A_on_disconnect);
    RUN_TEST(test_C1_to_B_on_9V);
    RUN_TEST(test_C1_timer_transitions_to_B1);
    RUN_TEST(test_B1_to_A_on_disconnect);
    RUN_TEST(test_set_state_B1_sets_charge_delay);
    RUN_TEST(test_set_state_A_clears_errors_and_delay);
    RUN_TEST(test_transition_log_records_states);
    RUN_TEST(test_set_state_C1_sets_pwm_off);
    RUN_TEST(test_full_charge_cycle);
    RUN_TEST(test_actstart_to_A_on_disconnect);
    RUN_TEST(test_activation_mode_triggers_actstart);

    TEST_SUITE_RESULTS();
}
