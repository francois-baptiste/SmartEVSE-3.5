/*
 * test_tick_10ms.c - Tests for the 10ms timer tick (evse_tick_10ms)
 *
 * Covers pilot disconnect guards, RFID reader, capacity limits,
 * state B debounce, state C transitions, COMM states, activation,
 * and modem disconnect handling.
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_idle(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
}

static void setup_ready_to_charge(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.ChargeCurrent = 100;
    ctx.ModemStage = 1;
}

/* ---- Pilot disconnect guards ---- */

void test_pilot_disconnect_guards_reading(void) {
    setup_ready_to_charge();
    ctx.PilotDisconnected = true;
    ctx.PilotDisconnectTime = 3;
    /* With PilotDisconnected=true the 9V pilot should be ignored */
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_pilot_disconnect_clears_on_timer_zero(void) {
    setup_ready_to_charge();
    ctx.PilotDisconnected = true;
    ctx.PilotDisconnectTime = 0;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_FALSE(ctx.PilotDisconnected);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
}

/* ---- RFID reader ---- */

void test_rfid_reader_1_starts_access_timer(void) {
    setup_ready_to_charge();
    ctx.RFIDReader = 1;
    ctx.AccessTimer = 0;
    ctx.AccessStatus = ON;
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(RFIDLOCKTIME, ctx.AccessTimer);
}

/* ---- MaxCapacity limits ---- */

void test_maxcapacity_limits_charge_current(void) {
    setup_ready_to_charge();
    ctx.MaxCapacity = 8;   /* Less than MaxCurrent (13) */
    ctx.MaxCurrent = 13;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(80, ctx.ChargeCurrent);
}

void test_maxcapacity_default_uses_mincurrent(void) {
    setup_ready_to_charge();
    ctx.MaxCapacity = 16;  /* >= MaxCurrent (13) */
    ctx.MaxCurrent = 13;
    ctx.MinCurrent = 6;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(60, ctx.ChargeCurrent);
}

/* ---- A->B with no current ---- */

void test_less_6a_when_no_current_available(void) {
    setup_idle();
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 0;
    ctx.ModemStage = 1;
    ctx.MaxMains = 2;                /* Very low mains limit */
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 200;   /* Already overloaded */
    ctx.MinCurrent = 6;
    ctx.ChargeCurrent = 60;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & LESS_6A);
}

/* ---- STATE_B + 6V debounce ---- */

void test_b_6v_increments_state_timer(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.StateTimer = 0;
    evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_EQUAL_INT(1, ctx.StateTimer);
}

void test_b_9v_resets_state_timer(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.StateTimer = 30;
    ctx.ActivationMode = 255; /* prevent ACTSTART */
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(0, ctx.StateTimer);
}

void test_b_to_c_debounce_threshold(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    /* 50 ticks: should NOT yet transition */
    for (int i = 0; i < 50; i++)
        evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_NOT_EQUAL(STATE_C, ctx.State);
    /* 5 more ticks: now it should */
    for (int i = 0; i < 5; i++)
        evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
}

void test_b_to_c_requires_diode_and_no_errors(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.ErrorFlags = TEMP_HIGH; /* Error present */
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    for (int i = 0; i < 55; i++)
        evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_NOT_EQUAL(STATE_C, ctx.State);
}

/* ---- STATE_C transitions ---- */

void test_c_short_debounce(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    /* Less than 50 ticks of PILOT_SHORT: should stay in C */
    for (int i = 0; i < 45; i++)
        evse_tick_10ms(&ctx, PILOT_SHORT);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
    /* Push past 50: should transition to B */
    for (int i = 0; i < 10; i++)
        evse_tick_10ms(&ctx, PILOT_SHORT);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
}

void test_c_6v_no_transition(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_C);
    ctx.StateTimer = 20;
    evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);
    TEST_ASSERT_EQUAL_INT(0, ctx.StateTimer);
}

/* ---- COMM_B stays on 9V ---- */

void test_comm_b_stays_on_9v(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 2;
    ctx.ModemStage = 1;
    evse_set_state(&ctx, STATE_COMM_B);
    ctx.BalancedState[0] = STATE_COMM_B;
    /* 9V should NOT trigger A->B logic because State is COMM_B */
    evse_tick_10ms(&ctx, PILOT_9V);
    /* COMM_B with 9V, no error, no chargeDelay, but it's STATE_COMM_B so the
     * condition ctx.State != STATE_COMM_B prevents A->B. Should stay COMM_B or go B1. */
    TEST_ASSERT_NOT_EQUAL(STATE_B, ctx.State);
}

/* ---- Node B->COMM_C ---- */

void test_node_b_to_comm_c(void) {
    setup_idle();
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 2;
    ctx.ModemStage = 1;
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    for (int i = 0; i < 55; i++)
        evse_tick_10ms(&ctx, PILOT_6V);
    TEST_ASSERT_EQUAL_INT(STATE_COMM_C, ctx.State);
}

/* ---- A->B side effects ---- */

void test_a_to_b_sets_balanced_max(void) {
    setup_ready_to_charge();
    ctx.MaxCapacity = 10;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(100, ctx.BalancedMax[0]);
}

void test_a_to_b_sets_pwm_duty(void) {
    setup_ready_to_charge();
    evse_tick_10ms(&ctx, PILOT_9V);
    uint32_t expected = evse_current_to_duty(ctx.Balanced[0]);
    TEST_ASSERT_EQUAL_INT(expected, ctx.last_pwm_duty);
}

void test_a_to_b_sets_activation_mode_30(void) {
    setup_ready_to_charge();
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(30, ctx.ActivationMode);
    TEST_ASSERT_EQUAL_INT(0, ctx.AccessTimer);
}

/* ---- B1 with errors stays B1 on 9V ---- */

void test_b1_with_errors_stays_b1_on_9v(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_B1);
    ctx.PilotDisconnected = false;
    ctx.PilotDisconnectTime = 0;
    ctx.ErrorFlags = TEMP_HIGH;
    evse_tick_10ms(&ctx, PILOT_9V);
    /* Should go to B1 (already there) since errors present */
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

/* ---- Modem states to A on 12V ---- */

void test_modem_states_to_a_on_12v(void) {
    uint8_t modem_states[] = {STATE_MODEM_REQUEST, STATE_MODEM_WAIT,
                              STATE_MODEM_DONE, STATE_MODEM_DENIED};
    for (int i = 0; i < 4; i++) {
        setup_ready_to_charge();
        ctx.State = modem_states[i];
        ctx.BalancedState[0] = modem_states[i];
        evse_tick_10ms(&ctx, PILOT_12V);
        TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
    }
}

/* ---- ACTSTART to B when timer zero ---- */

void test_actstart_to_b_when_timer_zero(void) {
    setup_ready_to_charge();
    evse_set_state(&ctx, STATE_ACTSTART);
    ctx.ActivationTimer = 0;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(255, ctx.ActivationMode);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("Tick 10ms");

    RUN_TEST(test_pilot_disconnect_guards_reading);
    RUN_TEST(test_pilot_disconnect_clears_on_timer_zero);
    RUN_TEST(test_rfid_reader_1_starts_access_timer);
    RUN_TEST(test_maxcapacity_limits_charge_current);
    RUN_TEST(test_maxcapacity_default_uses_mincurrent);
    RUN_TEST(test_less_6a_when_no_current_available);
    RUN_TEST(test_b_6v_increments_state_timer);
    RUN_TEST(test_b_9v_resets_state_timer);
    RUN_TEST(test_b_to_c_debounce_threshold);
    RUN_TEST(test_b_to_c_requires_diode_and_no_errors);
    RUN_TEST(test_c_short_debounce);
    RUN_TEST(test_c_6v_no_transition);
    RUN_TEST(test_comm_b_stays_on_9v);
    RUN_TEST(test_node_b_to_comm_c);
    RUN_TEST(test_a_to_b_sets_balanced_max);
    RUN_TEST(test_a_to_b_sets_pwm_duty);
    RUN_TEST(test_a_to_b_sets_activation_mode_30);
    RUN_TEST(test_b1_with_errors_stays_b1_on_9v);
    RUN_TEST(test_modem_states_to_a_on_12v);
    RUN_TEST(test_actstart_to_b_when_timer_zero);

    TEST_SUITE_RESULTS();
}
