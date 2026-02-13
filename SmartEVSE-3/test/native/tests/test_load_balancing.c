/*
 * test_load_balancing.c - Master/Node current distribution
 *
 * Tests CalcBalancedCurrent() with multiple EVSEs,
 * fair distribution, overload protection, and the
 * permission protocol (STATE_COMM_B/C).
 */

#include "test_framework.h"
#include "evse_types.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_master_two_evse(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 1;  // Master
    ctx.MaxCurrent = 16;
    ctx.MaxCapacity = 16;
    ctx.MinCurrent = 6;
    ctx.MaxCircuit = 32;
    ctx.MaxMains = 25;
    ctx.ChargeCurrent = 160;
    ctx.phasesLastUpdateFlag = true;

    // Two EVSEs charging
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedState[1] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.BalancedMax[1] = 160;
    ctx.Balanced[0] = 80;
    ctx.Balanced[1] = 80;
    ctx.Node[0].Online = 1;
    ctx.Node[1].Online = 1;
}

// ---- Distribution tests ----

void test_single_evse_gets_full_current(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;  // Standalone
    ctx.MaxCurrent = 16;
    ctx.MaxCapacity = 16;  // Match MaxCurrent
    ctx.ChargeCurrent = 160;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(160, ctx.IsetBalanced);
}

void test_two_evse_equal_distribution(void) {
    setup_master_two_evse();
    ctx.EVMeterImeasured = 160;  // Total measured = 160
    evse_calc_balanced_current(&ctx, 0);
    // Should distribute evenly
    TEST_ASSERT_EQUAL_INT(ctx.Balanced[0], ctx.Balanced[1]);
}

void test_two_evse_respects_max_circuit(void) {
    setup_master_two_evse();
    ctx.MaxCircuit = 16;  // Only 16A total for circuit
    ctx.EVMeterType = 1;
    ctx.EVMeterImeasured = 160;
    evse_calc_balanced_current(&ctx, 0);
    // Each should get at most ~8A (80 units)
    TEST_ASSERT_LESS_OR_EQUAL(100, ctx.Balanced[0]);
    TEST_ASSERT_LESS_OR_EQUAL(100, ctx.Balanced[1]);
}

void test_balanced_max_caps_individual(void) {
    setup_master_two_evse();
    // Note: BalancedMax[0] (master) gets overwritten by ChargeCurrent inside calc
    // Test capping on EVSE 1 (node) which retains its BalancedMax
    ctx.BalancedMax[1] = 60;   // EVSE 1 can only take 6A
    ctx.EVMeterImeasured = 0;
    ctx.IsetBalanced = 220;
    evse_calc_balanced_current(&ctx, 0);
    // EVSE 1 should be capped at its max
    TEST_ASSERT_LESS_OR_EQUAL(60, ctx.Balanced[1]);
}

// With no active EVSEs, IsetBalanced IS computed (from Mode/limits) but
// no distribution occurs. Timers are reset (NoCurrent=0, SolarStopTimer=0).
void test_no_active_evse_resets_timers(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 1;
    ctx.BalancedState[0] = STATE_A;
    ctx.BalancedState[1] = STATE_A;
    ctx.NoCurrent = 5;
    ctx.SolarStopTimer = 10;
    evse_calc_balanced_current(&ctx, 0);
    // No active EVSEs: timers are reset
    TEST_ASSERT_EQUAL_INT(0, ctx.NoCurrent);
    TEST_ASSERT_EQUAL_INT(0, ctx.SolarStopTimer);
}

void test_minimum_current_enforced(void) {
    setup_master_two_evse();
    ctx.MinCurrent = 6;
    ctx.IsetBalanced = 80;  // Only 80 = 8A total for 2 EVSEs
    ctx.EVMeterImeasured = 0;
    evse_calc_balanced_current(&ctx, 0);
    // Each EVSE should get at least MinCurrent
    for (int i = 0; i < 2; i++) {
        if (ctx.BalancedState[i] == STATE_C && ctx.Balanced[i] > 0) {
            TEST_ASSERT_TRUE(ctx.Balanced[i] >= ctx.MinCurrent * 10);
        }
    }
}

void test_mod1_new_evse_recalculates(void) {
    setup_master_two_evse();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 100;  // 10A mains
    ctx.EVMeterImeasured = 80;
    int32_t before = ctx.IsetBalanced;
    evse_calc_balanced_current(&ctx, 1);  // mod=1, new EVSE joining
    // Should have recalculated from scratch
    TEST_ASSERT_NOT_EQUAL(before, ctx.IsetBalanced);
}

// ---- OCPP current limit ----

void test_ocpp_limit_reduces_charge_current(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 16;
    ctx.ChargeCurrent = 160;
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 10.0f;  // 10A limit
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_LESS_OR_EQUAL(100, ctx.ChargeCurrent);
}

void test_ocpp_limit_below_min_zeros_current(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 16;
    ctx.MinCurrent = 6;
    ctx.ChargeCurrent = 160;
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 3.0f;  // Below minimum
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(0, ctx.ChargeCurrent);
}

void test_override_current_takes_precedence(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 16;
    ctx.ChargeCurrent = 160;
    ctx.OverrideCurrent = 80;  // Override to 8A
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(80, ctx.ChargeCurrent);
}

// ---- Shortage detection ----

void test_shortage_increments_nocurrent(void) {
    setup_master_two_evse();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 250;  // Very high load
    ctx.MaxMains = 10;              // Very low limit
    ctx.IsetBalanced = 50;          // Not enough for 2 EVSEs at MinCurrent
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    // NoCurrent should increment due to shortage
    if (ctx.IsetBalanced < (int32_t)(2 * ctx.MinCurrent * 10)) {
        TEST_ASSERT_GREATER_THAN(0, ctx.NoCurrent);
    }
}

void test_no_shortage_clears_nocurrent(void) {
    setup_master_two_evse();
    ctx.Mode = MODE_SMART;
    ctx.NoCurrent = 5;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 50;   // Low load
    ctx.MaxMains = 32;              // High limit
    ctx.IsetBalanced = 200;
    evse_calc_balanced_current(&ctx, 0);
    if (ctx.IsetBalanced >= (int32_t)(2 * ctx.MinCurrent * 10)) {
        TEST_ASSERT_EQUAL_INT(0, ctx.NoCurrent);
    }
}

// ---- Grid relay ----

void test_grid_relay_limits_current(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 32;
    ctx.MinCurrent = 6;
    ctx.MaxMains = 40;
    ctx.ChargeCurrent = 320;
    ctx.GridRelayOpen = true;
    ctx.GridRelayMaxSumMains = 18;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 50;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 320;
    ctx.Balanced[0] = 320;
    ctx.IsetBalanced = 320;
    ctx.phasesLastUpdateFlag = true;

    evse_calc_balanced_current(&ctx, 0);
    // Grid relay should cap at GridRelayMaxSumMains / phases
    int32_t relay_limit = (ctx.GridRelayMaxSumMains * 10) / 3;
    TEST_ASSERT_LESS_OR_EQUAL(relay_limit, ctx.IsetBalanced);
}

// ---- Node communication state tests ----

void test_node_requests_comm_c(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 2;  // Node
    ctx.ChargeCurrent = 130;
    ctx.MaxCurrent = 13;
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;

    // 6V pilot for 500ms
    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    // Node should request COMM_C, not go directly to STATE_C
    TEST_ASSERT_EQUAL_INT(STATE_COMM_C, ctx.State);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Load Balancing");

    RUN_TEST(test_single_evse_gets_full_current);
    RUN_TEST(test_two_evse_equal_distribution);
    RUN_TEST(test_two_evse_respects_max_circuit);
    RUN_TEST(test_balanced_max_caps_individual);
    RUN_TEST(test_no_active_evse_resets_timers);
    RUN_TEST(test_minimum_current_enforced);
    RUN_TEST(test_mod1_new_evse_recalculates);
    RUN_TEST(test_ocpp_limit_reduces_charge_current);
    RUN_TEST(test_ocpp_limit_below_min_zeros_current);
    RUN_TEST(test_override_current_takes_precedence);
    RUN_TEST(test_shortage_increments_nocurrent);
    RUN_TEST(test_no_shortage_clears_nocurrent);
    RUN_TEST(test_grid_relay_limits_current);
    RUN_TEST(test_node_requests_comm_c);

    TEST_SUITE_RESULTS();
}
