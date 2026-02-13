/*
 * test_power_availability.c - IsCurrentAvailable() checks
 *
 * Tests the multi-layer power availability gate:
 *   - MaxMains / MaxCircuit / MaxSumMains limits
 *   - Solar surplus requirements
 *   - OCPP current limit
 *   - Mode-specific behavior
 */

#include "test_framework.h"
#include "evse_types.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_normal_standalone(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.AccessStatus = ON;
    ctx.MinCurrent = MIN_CURRENT;
    ctx.MaxMains = MAX_MAINS;
    ctx.MaxCircuit = MAX_CIRCUIT;
}

// ---- Normal mode availability ----

void test_normal_mode_always_available(void) {
    setup_normal_standalone();
    // Normal mode doesn't check mains
    ctx.MainsMeterImeasured = 999;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_normal_mode_available_with_high_load(void) {
    setup_normal_standalone();
    ctx.MainsMeterImeasured = 400;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

// ---- Smart mode MaxMains ----

void test_smart_maxmains_allows_under_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.MaxMains = 25;             // 25A limit
    ctx.MainsMeterImeasured = 100; // 10A current load
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_smart_maxmains_blocks_over_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.MaxMains = 10;             // 10A limit
    ctx.MainsMeterImeasured = 200; // 20A current -> baseload 20A
    ctx.MinCurrent = 6;
    // Adding MinCurrent (6A) to 20A baseload = 26A > 10A limit
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

// ---- Smart mode MaxCircuit ----

void test_smart_maxcircuit_allows_under_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 1;  // Master, so MaxCircuit check applies
    ctx.MaxCircuit = 20;
    ctx.MaxMains = 40;  // High mains limit
    ctx.EVMeterImeasured = 50;
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_smart_maxcircuit_blocks_over_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.LoadBl = 1;
    ctx.MaxCircuit = 8;           // Very low circuit limit
    ctx.MaxMains = 40;
    ctx.EVMeterImeasured = 100;   // Already at 10A on circuit
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

// ---- MaxSumMains ----

void test_maxsummains_allows_under_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.MaxSumMains = 50;
    ctx.Isum = 100;  // 10A total across all phases
    ctx.MinCurrent = 6;
    ctx.MaxMains = 40;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_maxsummains_blocks_over_limit(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.MaxSumMains = 10;
    ctx.Isum = 200;  // Way over sum limit
    ctx.MinCurrent = 6;
    ctx.MaxMains = 40;
    ctx.MainsMeterImeasured = 50;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_maxsummains_zero_disables_check(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SMART;
    ctx.MaxSumMains = 0;  // Disabled
    ctx.Isum = 9999;      // Would exceed any limit
    ctx.MaxMains = 40;
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

// ---- Solar mode surplus ----

void test_solar_no_surplus_blocks(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 6;
    ctx.Isum = 0;  // No surplus
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_solar_surplus_allows(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 6;
    ctx.Isum = -80;  // 8A export
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_solar_insufficient_surplus_blocks(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 10;        // Need 10A surplus
    ctx.Isum = -80;               // Only 8A surplus
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_solar_with_active_evse_checks_fair_share(void) {
    setup_normal_standalone();
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 6;
    ctx.MinCurrent = 6;
    ctx.BalancedState[0] = STATE_C;
    ctx.Balanced[0] = 60;  // 6A charging
    ctx.Isum = 10;         // 1A import
    // One active EVSE at min current, trying to add another
    // Active * MinCurrent * 10 = 1 * 60 = 60, TotalCurrent = 60
    // Check: Isum > ImportCurrent*10 + TotalCurrent - ActiveEVSE * MinCurrent * 10
    // 10 > 0 + 60 - 60 = 0? Yes -> blocked
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

// ---- OCPP availability ----

void test_ocpp_limit_blocks_when_below_min(void) {
    setup_normal_standalone();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 4.0f;
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_ocpp_limit_allows_when_above_min(void) {
    setup_normal_standalone();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 10.0f;
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_ocpp_no_limit_allows(void) {
    setup_normal_standalone();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = -1.0f;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_ocpp_check_only_for_standalone(void) {
    setup_normal_standalone();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 3.0f;  // Below min
    ctx.MinCurrent = 6;
    ctx.LoadBl = 1;  // Master - OCPP check skipped for LoadBl != 0
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

// ---- PWM duty cycle conversion ----

void test_current_to_duty_6A(void) {
    // 60 (6A * 10) -> 60/0.6 = 100 -> 100 * 1024/1000 = 102
    uint32_t duty = evse_current_to_duty(60);
    TEST_ASSERT_EQUAL_INT(102, duty);
}

void test_current_to_duty_16A(void) {
    // 160 -> 160/0.6 = 266.67 -> 266 * 1024/1000 = 272
    uint32_t duty = evse_current_to_duty(160);
    TEST_ASSERT_TRUE(duty > 100 && duty < 600);
}

void test_current_to_duty_51A(void) {
    // 510 -> 510/0.6 = 850 -> 850 * 1024/1000 = 870
    uint32_t duty = evse_current_to_duty(510);
    TEST_ASSERT_TRUE(duty > 800 && duty < 1000);
}

void test_current_to_duty_high_range(void) {
    // 600 -> 600/2.5 + 640 = 880 -> 880 * 1024/1000 = 901
    uint32_t duty = evse_current_to_duty(600);
    TEST_ASSERT_TRUE(duty > 850 && duty < 1000);
}

void test_current_to_duty_80A(void) {
    // 800 -> 800/2.5 + 640 = 960 -> 960 * 1024/1000 = 983
    uint32_t duty = evse_current_to_duty(800);
    TEST_ASSERT_TRUE(duty > 950 && duty < 1024);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Power Availability");

    RUN_TEST(test_normal_mode_always_available);
    RUN_TEST(test_normal_mode_available_with_high_load);
    RUN_TEST(test_smart_maxmains_allows_under_limit);
    RUN_TEST(test_smart_maxmains_blocks_over_limit);
    RUN_TEST(test_smart_maxcircuit_allows_under_limit);
    RUN_TEST(test_smart_maxcircuit_blocks_over_limit);
    RUN_TEST(test_maxsummains_allows_under_limit);
    RUN_TEST(test_maxsummains_blocks_over_limit);
    RUN_TEST(test_maxsummains_zero_disables_check);
    RUN_TEST(test_solar_no_surplus_blocks);
    RUN_TEST(test_solar_surplus_allows);
    RUN_TEST(test_solar_insufficient_surplus_blocks);
    RUN_TEST(test_solar_with_active_evse_checks_fair_share);
    RUN_TEST(test_ocpp_limit_blocks_when_below_min);
    RUN_TEST(test_ocpp_limit_allows_when_above_min);
    RUN_TEST(test_ocpp_no_limit_allows);
    RUN_TEST(test_ocpp_check_only_for_standalone);
    RUN_TEST(test_current_to_duty_6A);
    RUN_TEST(test_current_to_duty_16A);
    RUN_TEST(test_current_to_duty_51A);
    RUN_TEST(test_current_to_duty_high_range);
    RUN_TEST(test_current_to_duty_80A);

    TEST_SUITE_RESULTS();
}
