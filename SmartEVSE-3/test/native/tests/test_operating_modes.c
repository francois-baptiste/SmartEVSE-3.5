/*
 * test_operating_modes.c - Normal / Smart / Solar mode behavior
 *
 * Tests how the operating mode affects current calculation,
 * regulation, and solar-specific stop/start timers.
 */

#include "test_framework.h"
#include "evse_types.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_charging_single(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = ctx.MaxCurrent * 10;
    ctx.Balanced[0] = ctx.MaxCurrent * 10;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    ctx.contactor1_state = true;
}

// ---- Normal mode tests ----

void test_normal_mode_uses_max_current(void) {
    setup_charging_single();
    ctx.Mode = MODE_NORMAL;
    evse_calc_balanced_current(&ctx, 0);
    // In normal standalone mode, IsetBalanced = ChargeCurrent
    TEST_ASSERT_EQUAL_INT(ctx.MaxCurrent * 10, ctx.IsetBalanced);
}

void test_normal_mode_ignores_mains(void) {
    setup_charging_single();
    ctx.Mode = MODE_NORMAL;
    ctx.MainsMeterImeasured = 300;  // High mains current
    evse_calc_balanced_current(&ctx, 0);
    // Normal mode should NOT reduce current based on mains
    TEST_ASSERT_EQUAL_INT(ctx.MaxCurrent * 10, ctx.IsetBalanced);
}

void test_normal_mode_respects_max_capacity(void) {
    setup_charging_single();
    ctx.Mode = MODE_NORMAL;
    ctx.MaxCapacity = 10;  // 10A capacity
    ctx.MaxCurrent = 16;   // 16A max
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(100, ctx.ChargeCurrent);  // Should use MaxCapacity
}

// ---- Smart mode tests ----

void test_smart_mode_respects_maxmains(void) {
    setup_charging_single();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 200;  // 20A on mains
    ctx.MaxMains = 25;              // 25A limit
    evse_calc_balanced_current(&ctx, 0);
    // IsetBalanced should be limited by MaxMains - Baseload
    int32_t expected_limit = (ctx.MaxMains * 10) - (200 - ctx.Balanced[0]);
    TEST_ASSERT_LESS_OR_EQUAL(expected_limit, ctx.IsetBalanced);
}

void test_smart_mode_slow_increase(void) {
    setup_charging_single();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 100;  // Low usage
    ctx.MaxMains = 25;
    int32_t initial = ctx.IsetBalanced;
    evse_calc_balanced_current(&ctx, 0);
    // Smart mode increases slowly (Idifference/4)
    // The increase should be present but conservative
    TEST_ASSERT_TRUE(ctx.IsetBalanced >= initial);
}

void test_smart_mode_fast_decrease(void) {
    setup_charging_single();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.IsetBalanced = 200;         // Currently set high
    ctx.MaxMains = 10;              // Low limit
    ctx.MainsMeterImeasured = 250;  // Way over limit -> negative Idifference
    evse_calc_balanced_current(&ctx, 0);
    // Should decrease rapidly (full Idifference, not /4)
    TEST_ASSERT_TRUE(ctx.IsetBalanced < 200);
}

// ---- Solar mode tests ----

void test_solar_current_available_requires_surplus(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 6;  // Need 6A surplus
    ctx.AccessStatus = ON;
    // No surplus (Isum = 0, StartCurrent*-10 = -60)
    ctx.Isum = 0;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_solar_current_available_with_surplus(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SOLAR;
    ctx.StartCurrent = 6;
    ctx.AccessStatus = ON;
    ctx.MinCurrent = MIN_CURRENT;
    // Strong surplus: Isum = -80 (8A export)
    ctx.Isum = -80;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_solar_fine_grained_increase(void) {
    setup_charging_single();
    ctx.Mode = MODE_SOLAR;
    ctx.MainsMeterType = 1;
    ctx.MaxMains = 25;
    ctx.ImportCurrent = 0;
    ctx.Isum = -20;  // 2A export surplus
    ctx.IsetBalanced = 100;
    ctx.MainsMeterImeasured = 50;
    evse_calc_balanced_current(&ctx, 0);
    // Solar should increase by small steps
    TEST_ASSERT_TRUE(ctx.IsetBalanced >= 100);
}

void test_solar_rapid_decrease_on_import(void) {
    setup_charging_single();
    ctx.Mode = MODE_SOLAR;
    ctx.MainsMeterType = 1;
    ctx.MaxMains = 25;
    ctx.ImportCurrent = 0;
    ctx.Isum = 50;  // 5A import, over threshold
    ctx.IsetBalanced = 100;
    ctx.MainsMeterImeasured = 50;
    evse_calc_balanced_current(&ctx, 0);
    // Solar should decrease quickly
    TEST_ASSERT_TRUE(ctx.IsetBalanced < 100);
}

void test_solar_import_current_offset(void) {
    setup_charging_single();
    ctx.Mode = MODE_SOLAR;
    ctx.MainsMeterType = 1;
    ctx.MaxMains = 25;
    ctx.ImportCurrent = 3;  // Allow 3A import
    ctx.Isum = 20;  // 2A import - within allowance
    ctx.IsetBalanced = 100;
    ctx.MainsMeterImeasured = 50;
    evse_calc_balanced_current(&ctx, 0);
    // IsumImport = 20 - 30 = -10, should increase
    TEST_ASSERT_TRUE(ctx.IsetBalanced >= 100);
}

// ---- Phase switching tests ----

void test_force_single_phase_not_present(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = NOT_PRESENT;
    TEST_ASSERT_EQUAL_INT(0, evse_force_single_phase(&ctx));
}

void test_force_single_phase_always_off(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = ALWAYS_OFF;
    TEST_ASSERT_EQUAL_INT(1, evse_force_single_phase(&ctx));
}

void test_force_single_phase_solar_off_in_solar_mode(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = SOLAR_OFF;
    ctx.Mode = MODE_SOLAR;
    TEST_ASSERT_EQUAL_INT(1, evse_force_single_phase(&ctx));
}

void test_force_single_phase_solar_off_in_smart_mode(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = SOLAR_OFF;
    ctx.Mode = MODE_SMART;
    TEST_ASSERT_EQUAL_INT(0, evse_force_single_phase(&ctx));
}

void test_force_single_phase_auto_c2_1p(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = AUTO_C2;
    ctx.Nr_Of_Phases_Charging = 1;
    TEST_ASSERT_EQUAL_INT(1, evse_force_single_phase(&ctx));
}

void test_force_single_phase_auto_c2_3p(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = AUTO_C2;
    ctx.Nr_Of_Phases_Charging = 3;
    TEST_ASSERT_EQUAL_INT(0, evse_force_single_phase(&ctx));
}

void test_force_single_phase_always_on(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = ALWAYS_ON;
    TEST_ASSERT_EQUAL_INT(0, evse_force_single_phase(&ctx));
}

void test_state_C_contactor2_off_when_single_phase(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = ALWAYS_OFF;  // Force single phase
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_TRUE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
}

void test_state_C_contactor2_on_when_three_phase(void) {
    evse_init(&ctx, NULL);
    ctx.EnableC2 = NOT_PRESENT;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_TRUE(ctx.contactor1_state);
    TEST_ASSERT_TRUE(ctx.contactor2_state);
    TEST_ASSERT_EQUAL_INT(3, ctx.Nr_Of_Phases_Charging);
}

void test_phase_switch_going_to_1p(void) {
    evse_init(&ctx, NULL);
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_1P;
    ctx.EnableC2 = AUTO_C2;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
    TEST_ASSERT_EQUAL_INT(NO_SWITCH, ctx.Switching_Phases_C2);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Operating Modes");

    RUN_TEST(test_normal_mode_uses_max_current);
    RUN_TEST(test_normal_mode_ignores_mains);
    RUN_TEST(test_normal_mode_respects_max_capacity);
    RUN_TEST(test_smart_mode_respects_maxmains);
    RUN_TEST(test_smart_mode_slow_increase);
    RUN_TEST(test_smart_mode_fast_decrease);
    RUN_TEST(test_solar_current_available_requires_surplus);
    RUN_TEST(test_solar_current_available_with_surplus);
    RUN_TEST(test_solar_fine_grained_increase);
    RUN_TEST(test_solar_rapid_decrease_on_import);
    RUN_TEST(test_solar_import_current_offset);
    RUN_TEST(test_force_single_phase_not_present);
    RUN_TEST(test_force_single_phase_always_off);
    RUN_TEST(test_force_single_phase_solar_off_in_solar_mode);
    RUN_TEST(test_force_single_phase_solar_off_in_smart_mode);
    RUN_TEST(test_force_single_phase_auto_c2_1p);
    RUN_TEST(test_force_single_phase_auto_c2_3p);
    RUN_TEST(test_force_single_phase_always_on);
    RUN_TEST(test_state_C_contactor2_off_when_single_phase);
    RUN_TEST(test_state_C_contactor2_on_when_three_phase);
    RUN_TEST(test_phase_switch_going_to_1p);

    TEST_SUITE_RESULTS();
}
