/*
 * test_tick_1s.c - Tests for the 1-second timer tick (evse_tick_1s)
 *
 * Covers solar stop timer, charge timers per node, mains meter timeout,
 * LESS_6A enforcement, MaxSumMains timer, access timer, EV meter timeout,
 * activation countdown, and charge delay interactions.
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_base(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
}

/* ---- SolarStopTimer ---- */

void test_solar_stop_timer_countdown(void) {
    setup_base();
    ctx.SolarStopTimer = 3;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(2, ctx.SolarStopTimer);
}

void test_solar_stop_timer_triggers_c1(void) {
    setup_base();
    /* Use SMART mode with high load so LESS_6A won't auto-recover */
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    evse_set_state(&ctx, STATE_C);
    /* Set timer AFTER set_state since STATE_C entry resets SolarStopTimer */
    ctx.SolarStopTimer = 1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & LESS_6A);
}

void test_solar_stop_timer_not_in_c(void) {
    setup_base();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    evse_set_state(&ctx, STATE_B);
    ctx.SolarStopTimer = 1;
    evse_tick_1s(&ctx);
    /* Not in STATE_C, so no C1 transition, but LESS_6A still set */
    TEST_ASSERT_NOT_EQUAL(STATE_C1, ctx.State);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & LESS_6A);
}

/* ---- Node charge timers ---- */

void test_node_charge_timer_increments(void) {
    setup_base();
    ctx.BalancedState[0] = STATE_C;
    ctx.Node[0].IntTimer = 5;
    ctx.Node[0].Timer = 100;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(6, ctx.Node[0].IntTimer);
    TEST_ASSERT_EQUAL_INT(101, ctx.Node[0].Timer);
}

void test_node_charge_timer_resets(void) {
    setup_base();
    ctx.BalancedState[0] = STATE_B;
    ctx.Node[0].IntTimer = 20;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.Node[0].IntTimer);
}

void test_multi_node_timers(void) {
    setup_base();
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedState[1] = STATE_B;
    ctx.BalancedState[2] = STATE_C;
    ctx.Node[0].IntTimer = 10;
    ctx.Node[1].IntTimer = 10;
    ctx.Node[2].IntTimer = 10;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(11, ctx.Node[0].IntTimer);
    TEST_ASSERT_EQUAL_INT(0, ctx.Node[1].IntTimer);
    TEST_ASSERT_EQUAL_INT(11, ctx.Node[2].IntTimer);
}

/* ---- MainsMeter timeout (node) ---- */

void test_mains_meter_timeout_node(void) {
    setup_base();
    ctx.LoadBl = 2;
    ctx.MainsMeterTimeout = 0;
    ctx.ErrorFlags = NO_ERROR;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & CT_NOCOMM);
}

void test_mains_meter_node_countdown(void) {
    setup_base();
    ctx.LoadBl = 3;
    ctx.MainsMeterTimeout = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.MainsMeterTimeout);
}

/* ---- LESS_6A enforcement ---- */

void test_less_6a_enforces_power_unavailable(void) {
    setup_base();
    /* Use SMART mode with high mains load so LESS_6A can't auto-recover */
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    evse_set_state(&ctx, STATE_C);
    ctx.ErrorFlags = LESS_6A;
    evse_tick_1s(&ctx);
    /* LESS_6A should cause transition from C to C1 via set_power_unavailable */
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

void test_less_6a_sets_charge_delay(void) {
    setup_base();
    /* Use SMART mode with high mains load so LESS_6A can't auto-recover */
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    ctx.ErrorFlags = LESS_6A;
    ctx.ChargeDelay = 0;
    ctx.State = STATE_B1;
    ctx.BalancedState[0] = STATE_B1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(CHARGEDELAY, ctx.ChargeDelay);
}

/* ---- MaxSumMains timer ---- */

void test_maxsummains_timer_countdown(void) {
    setup_base();
    ctx.MaxSumMainsTimer = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.MaxSumMainsTimer);
}

void test_maxsummains_timer_triggers_c1(void) {
    setup_base();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    evse_set_state(&ctx, STATE_C);
    /* Set timer AFTER set_state since STATE_C entry resets MaxSumMainsTimer */
    ctx.MaxSumMainsTimer = 1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & LESS_6A);
}

/* ---- AccessTimer ---- */

void test_access_timer_cleared_not_in_a(void) {
    setup_base();
    evse_set_state(&ctx, STATE_B);
    ctx.AccessTimer = 30;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.AccessTimer);
}

/* ---- EVMeter timeout ---- */

void test_ev_meter_timeout_countdown(void) {
    setup_base();
    ctx.EVMeterType = 1;
    ctx.EVMeterTimeout = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.EVMeterTimeout);
}

void test_ev_meter_timeout_triggers_error(void) {
    setup_base();
    ctx.EVMeterType = 1;
    ctx.EVMeterTimeout = 0;
    ctx.ErrorFlags = NO_ERROR;
    ctx.Mode = MODE_SMART;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE(ctx.ErrorFlags & EV_NOCOMM);
}

/* ---- Activation timer ---- */

void test_activation_timer_countdown(void) {
    setup_base();
    ctx.ActivationTimer = 3;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(2, ctx.ActivationTimer);
}

/* ---- ActivationMode countdown ---- */

void test_activation_mode_countdown(void) {
    setup_base();
    ctx.ActivationMode = 10;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(9, ctx.ActivationMode);
}

/* ---- ChargeDelay overridden by LESS_6A ---- */

void test_charge_delay_overridden_by_less_6a(void) {
    setup_base();
    /* Use SMART mode with high mains load so LESS_6A can't auto-recover */
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    ctx.ChargeDelay = 1;  /* Decrements to 0, then LESS_6A enforcement sets CHARGEDELAY */
    ctx.ErrorFlags = LESS_6A;
    ctx.State = STATE_B1;
    ctx.BalancedState[0] = STATE_B1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(CHARGEDELAY, ctx.ChargeDelay);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("Tick 1s");

    RUN_TEST(test_solar_stop_timer_countdown);
    RUN_TEST(test_solar_stop_timer_triggers_c1);
    RUN_TEST(test_solar_stop_timer_not_in_c);
    RUN_TEST(test_node_charge_timer_increments);
    RUN_TEST(test_node_charge_timer_resets);
    RUN_TEST(test_multi_node_timers);
    RUN_TEST(test_mains_meter_timeout_node);
    RUN_TEST(test_mains_meter_node_countdown);
    RUN_TEST(test_less_6a_enforces_power_unavailable);
    RUN_TEST(test_less_6a_sets_charge_delay);
    RUN_TEST(test_maxsummains_timer_countdown);
    RUN_TEST(test_maxsummains_timer_triggers_c1);
    RUN_TEST(test_access_timer_cleared_not_in_a);
    RUN_TEST(test_ev_meter_timeout_countdown);
    RUN_TEST(test_ev_meter_timeout_triggers_error);
    RUN_TEST(test_activation_timer_countdown);
    RUN_TEST(test_activation_mode_countdown);
    RUN_TEST(test_charge_delay_overridden_by_less_6a);

    TEST_SUITE_RESULTS();
}
