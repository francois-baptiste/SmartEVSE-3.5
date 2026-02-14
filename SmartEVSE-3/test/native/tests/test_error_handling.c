/*
 * test_error_handling.c - Error flags, recovery, safety mechanisms
 *
 * Tests:
 *   - Error flag set/clear
 *   - ChargeDelay countdown
 *   - Temperature protection with hysteresis
 *   - Meter communication timeouts
 *   - LESS_6A auto-recovery
 *   - RCM fault handling
 *   - Power unavailable graceful shutdown
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_charging(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 0;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.contactor1_state = true;
}

// ---- Error flag management ----

void test_set_error_flags(void) {
    evse_init(&ctx, NULL);
    evse_set_error_flags(&ctx, TEMP_HIGH);
    TEST_ASSERT_EQUAL_INT(TEMP_HIGH, ctx.ErrorFlags & TEMP_HIGH);
}

void test_set_multiple_error_flags(void) {
    evse_init(&ctx, NULL);
    evse_set_error_flags(&ctx, TEMP_HIGH);
    evse_set_error_flags(&ctx, CT_NOCOMM);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
}

void test_clear_error_flags(void) {
    evse_init(&ctx, NULL);
    ctx.ErrorFlags = TEMP_HIGH | CT_NOCOMM;
    evse_clear_error_flags(&ctx, TEMP_HIGH);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & TEMP_HIGH);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
}

void test_clear_preserves_other_flags(void) {
    evse_init(&ctx, NULL);
    ctx.ErrorFlags = TEMP_HIGH | LESS_6A | CT_NOCOMM;
    evse_clear_error_flags(&ctx, LESS_6A);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & LESS_6A);
}

// ---- ChargeDelay countdown ----

void test_charge_delay_counts_down(void) {
    evse_init(&ctx, NULL);
    ctx.ChargeDelay = 10;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(9, ctx.ChargeDelay);
}

void test_charge_delay_stops_at_zero(void) {
    evse_init(&ctx, NULL);
    ctx.ChargeDelay = 1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.ChargeDelay);
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.ChargeDelay);
}

// Original line 3127-3128: ChargeDelay prevents A→B, goes to B1 instead
void test_charge_delay_blocks_A_to_B(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.ChargeDelay = 5;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

// ---- Temperature protection ----

void test_temp_high_triggers_error(void) {
    setup_charging();
    ctx.TempEVSE = 70;
    ctx.maxTemp = 65;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);
}

void test_temp_high_shuts_down_charging(void) {
    setup_charging();
    ctx.TempEVSE = 70;
    ctx.maxTemp = 65;
    evse_tick_1s(&ctx);
    // Should have called set_power_unavailable -> C1
    TEST_ASSERT_NOT_EQUAL(STATE_C, ctx.State);
}

void test_temp_recovery_with_hysteresis(void) {
    evse_init(&ctx, NULL);
    ctx.maxTemp = 65;
    ctx.ErrorFlags = TEMP_HIGH;

    // Still too hot (within 10 degrees)
    ctx.TempEVSE = 60;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);

    // Cooled down enough (below maxTemp - 10)
    ctx.TempEVSE = 50;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & TEMP_HIGH);
}

void test_temp_recovery_boundary(void) {
    evse_init(&ctx, NULL);
    ctx.maxTemp = 65;
    ctx.ErrorFlags = TEMP_HIGH;

    // Exactly at threshold: 65 - 10 = 55 — NOT below, so should NOT clear
    ctx.TempEVSE = 55;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);

    // One degree below threshold
    ctx.TempEVSE = 54;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & TEMP_HIGH);
}

// ---- Mains meter timeout ----

void test_mains_meter_timeout_sets_ct_nocomm(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterTimeout = 0;  // Already timed out
    ctx.LoadBl = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
}

void test_mains_meter_timeout_counts_down(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterTimeout = 5;
    ctx.LoadBl = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.MainsMeterTimeout);
}

void test_mains_meter_normal_mode_ignores_timeout(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterTimeout = 0;
    ctx.LoadBl = 0;
    evse_tick_1s(&ctx);
    // Normal mode - meter timeout should not set CT_NOCOMM
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);
}

void test_no_mains_meter_resets_timeout(void) {
    evse_init(&ctx, NULL);
    ctx.MainsMeterType = 0;
    ctx.MainsMeterTimeout = 3;
    ctx.LoadBl = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(COMM_TIMEOUT, ctx.MainsMeterTimeout);
}

// ---- EV meter timeout ----

void test_ev_meter_timeout_sets_ev_nocomm(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.EVMeterType = 1;
    ctx.EVMeterTimeout = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & EV_NOCOMM) != 0);
}

void test_no_ev_meter_resets_timeout(void) {
    evse_init(&ctx, NULL);
    ctx.EVMeterType = 0;
    ctx.EVMeterTimeout = 3;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(COMM_EVTIMEOUT, ctx.EVMeterTimeout);
}

// ---- CT_NOCOMM / EV_NOCOMM recovery ----

void test_ct_nocomm_recovers_on_communication(void) {
    evse_init(&ctx, NULL);
    ctx.ErrorFlags = CT_NOCOMM;
    ctx.MainsMeterTimeout = 5;  // Communication restored
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);
}

void test_ev_nocomm_recovers_on_communication(void) {
    evse_init(&ctx, NULL);
    ctx.ErrorFlags = EV_NOCOMM;
    ctx.EVMeterTimeout = 5;  // Communication restored
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & EV_NOCOMM);
}

// ---- LESS_6A auto-recovery ----

void test_less_6a_recovers_when_current_available(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.ErrorFlags = LESS_6A;
    ctx.AccessStatus = ON;
    evse_tick_1s(&ctx);
    // Normal mode: current is always available
    TEST_ASSERT_FALSE(ctx.ErrorFlags & LESS_6A);
}

void test_less_6a_stays_when_current_unavailable(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 0;
    ctx.ErrorFlags = LESS_6A;
    ctx.MaxMains = 5;
    ctx.MainsMeterImeasured = 200;  // Way over
    ctx.MinCurrent = 6;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & LESS_6A) != 0);
}

void test_less_6a_no_recovery_for_nodes(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 3;  // Node
    ctx.ErrorFlags = LESS_6A;
    evse_tick_1s(&ctx);
    // Nodes (LoadBl >= 2) don't auto-recover LESS_6A
    TEST_ASSERT_TRUE((ctx.ErrorFlags & LESS_6A) != 0);
}

// ---- Power unavailable graceful shutdown ----

void test_power_unavailable_from_C_goes_C1(void) {
    setup_charging();
    evse_set_power_unavailable(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

void test_power_unavailable_from_B_goes_B1(void) {
    evse_init(&ctx, NULL);
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    evse_set_power_unavailable(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_power_unavailable_from_A_stays_A(void) {
    evse_init(&ctx, NULL);
    ctx.State = STATE_A;
    evse_set_power_unavailable(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_power_unavailable_from_B1_stays_B1(void) {
    evse_init(&ctx, NULL);
    evse_set_state(&ctx, STATE_B1);
    evse_set_power_unavailable(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_power_unavailable_from_C1_stays_C1(void) {
    evse_init(&ctx, NULL);
    evse_set_state(&ctx, STATE_C1);
    evse_set_power_unavailable(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

// ---- Pilot disconnect/reconnect ----

void test_pilot_disconnect_on_B1_entry(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.PilotDisconnected = false;
    evse_set_state(&ctx, STATE_B1);
    TEST_ASSERT_TRUE(ctx.PilotDisconnected);
    TEST_ASSERT_FALSE(ctx.pilot_connected);
}

void test_pilot_reconnect_after_timer(void) {
    evse_init(&ctx, NULL);
    ctx.PilotDisconnectTime = 2;
    ctx.PilotDisconnected = true;
    ctx.pilot_connected = false;

    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(1, ctx.PilotDisconnectTime);
    TEST_ASSERT_TRUE(ctx.PilotDisconnected);

    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.PilotDisconnectTime);
    TEST_ASSERT_FALSE(ctx.PilotDisconnected);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
}

// ---- MaxSumMains timer ----

void test_maxsummains_timer_stops_charging(void) {
    setup_charging();
    ctx.MaxSumMainsTimer = 1;
    // Make current unavailable so LESS_6A persists after auto-recovery check
    ctx.MaxMains = 5;
    ctx.MainsMeterImeasured = 200;
    ctx.MinCurrent = 6;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.MaxSumMainsTimer);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & LESS_6A) != 0);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Error Handling & Safety");

    RUN_TEST(test_set_error_flags);
    RUN_TEST(test_set_multiple_error_flags);
    RUN_TEST(test_clear_error_flags);
    RUN_TEST(test_clear_preserves_other_flags);
    RUN_TEST(test_charge_delay_counts_down);
    RUN_TEST(test_charge_delay_stops_at_zero);
    RUN_TEST(test_charge_delay_blocks_A_to_B);
    RUN_TEST(test_temp_high_triggers_error);
    RUN_TEST(test_temp_high_shuts_down_charging);
    RUN_TEST(test_temp_recovery_with_hysteresis);
    RUN_TEST(test_temp_recovery_boundary);
    RUN_TEST(test_mains_meter_timeout_sets_ct_nocomm);
    RUN_TEST(test_mains_meter_timeout_counts_down);
    RUN_TEST(test_mains_meter_normal_mode_ignores_timeout);
    RUN_TEST(test_no_mains_meter_resets_timeout);
    RUN_TEST(test_ev_meter_timeout_sets_ev_nocomm);
    RUN_TEST(test_no_ev_meter_resets_timeout);
    RUN_TEST(test_ct_nocomm_recovers_on_communication);
    RUN_TEST(test_ev_nocomm_recovers_on_communication);
    RUN_TEST(test_less_6a_recovers_when_current_available);
    RUN_TEST(test_less_6a_stays_when_current_unavailable);
    RUN_TEST(test_less_6a_no_recovery_for_nodes);
    RUN_TEST(test_power_unavailable_from_C_goes_C1);
    RUN_TEST(test_power_unavailable_from_B_goes_B1);
    RUN_TEST(test_power_unavailable_from_A_stays_A);
    RUN_TEST(test_power_unavailable_from_B1_stays_B1);
    RUN_TEST(test_power_unavailable_from_C1_stays_C1);
    RUN_TEST(test_pilot_disconnect_on_B1_entry);
    RUN_TEST(test_pilot_reconnect_after_timer);
    RUN_TEST(test_maxsummains_timer_stops_charging);

    TEST_SUITE_RESULTS();
}
