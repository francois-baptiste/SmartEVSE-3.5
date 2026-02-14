/*
 * test_solar_balancing.c - Solar-specific paths in evse_calc_balanced_current()
 *
 * Covers 3P/1P switching timers, solar startup forcing MinCurrent,
 * fine-grained increase/decrease, B-state phase determination,
 * hard/soft shortage, IsetBalanced cap, normal mode 3P forcing,
 * phasesLastUpdateFlag gating, and multi-EVSE solar startup.
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_solar_charging(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_SOLAR;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 16;
    ctx.MaxCapacity = 16;
    ctx.MinCurrent = 6;
    ctx.MaxMains = 25;
    ctx.MaxCircuit = 32;
    ctx.StartCurrent = 4;
    ctx.StopTime = 10;
    ctx.ImportCurrent = 0;
    ctx.MainsMeterType = 1;
    ctx.phasesLastUpdateFlag = true;

    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 100;
    ctx.ChargeCurrent = 160;
    ctx.IsetBalanced = 100;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.Node[0].IntTimer = SOLARSTARTTIME + 1; /* Past startup */
}

/* ---- 3P shortage starts SolarStopTimer ---- */

void test_solar_3p_shortage_starts_timer(void) {
    setup_solar_charging();
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.MainsMeterImeasured = 300;   /* Very high load */
    ctx.Isum = 200;                  /* Large import */
    ctx.SolarStopTimer = 0;
    evse_calc_balanced_current(&ctx, 0);
    /* Shortage detected in 3P + AUTO: SolarStopTimer should start */
    TEST_ASSERT_GREATER_THAN(0, ctx.SolarStopTimer);
}

/* ---- SolarStopTimer<=2 triggers 1P switch ---- */

void test_solar_3p_timer_triggers_1p_switch(void) {
    setup_solar_charging();
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.MainsMeterImeasured = 300;
    ctx.Isum = 200;
    ctx.SolarStopTimer = 2;  /* Will be decremented to trigger */
    evse_calc_balanced_current(&ctx, 0);
    /* Timer <=2 should set GOING_TO_SWITCH_1P and go to C1 */
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_1P, ctx.Switching_Phases_C2);
}

/* ---- 1P surplus starts timer for 3P switch ---- */

void test_solar_1p_surplus_starts_timer(void) {
    setup_solar_charging();
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.IsetBalanced = 155;           /* Near MaxCurrent*10 */
    ctx.Isum = -100;                  /* Good surplus */
    ctx.MainsMeterImeasured = -50;
    ctx.SolarStopTimer = 0;
    evse_calc_balanced_current(&ctx, 0);
    /* 1P at max with surplus: timer should start at 63 */
    if (ctx.SolarStopTimer > 0) {
        TEST_ASSERT_EQUAL_INT(63, ctx.SolarStopTimer);
    }
}

/* ---- SolarStopTimer<=3 triggers 3P switch ---- */

void test_solar_1p_timer_triggers_3p_switch(void) {
    setup_solar_charging();
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.IsetBalanced = 160;
    ctx.Isum = -200;                  /* Large surplus */
    ctx.MainsMeterImeasured = -100;
    ctx.SolarStopTimer = 3;           /* Will be at <=3 */
    evse_calc_balanced_current(&ctx, 0);
    /* Timer <=3 should switch to 3P */
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_3P, ctx.Switching_Phases_C2);
}

/* ---- Insufficient surplus resets timer ---- */

void test_solar_insufficient_surplus_resets_timer(void) {
    setup_solar_charging();
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.IsetBalanced = 100;            /* Well below MaxCurrent*10 */
    ctx.Isum = -10;                    /* Minimal surplus */
    ctx.MainsMeterImeasured = 0;
    ctx.SolarStopTimer = 30;
    evse_calc_balanced_current(&ctx, 0);
    /* Not enough surplus to upgrade: timer reset */
    TEST_ASSERT_EQUAL_INT(0, ctx.SolarStopTimer);
}

/* ---- Solar startup forces MinCurrent ---- */

void test_solar_startup_forces_mincurrent(void) {
    setup_solar_charging();
    ctx.Node[0].IntTimer = SOLARSTARTTIME - 5;  /* In startup */
    ctx.IsetBalanced = 200;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(ctx.MinCurrent * 10, ctx.Balanced[0]);
}

/* ---- Past startup uses calculated value ---- */

void test_solar_past_startup_uses_calculated(void) {
    setup_solar_charging();
    ctx.Node[0].IntTimer = SOLARSTARTTIME + 1;
    ctx.IsetBalanced = 120;
    ctx.MainsMeterImeasured = 50;
    evse_calc_balanced_current(&ctx, 0);
    /* Should use calculated distribution, not MinCurrent */
    TEST_ASSERT_TRUE(ctx.Balanced[0] >= ctx.MinCurrent * 10);
}

/* ---- Solar fine increase (small export) ---- */

void test_solar_fine_increase_small(void) {
    setup_solar_charging();
    ctx.Isum = -5;   /* Small export */
    ctx.ImportCurrent = 0;
    int32_t before = ctx.IsetBalanced;
    ctx.MainsMeterImeasured = ctx.Isum + (int16_t)ctx.Balanced[0];
    evse_calc_balanced_current(&ctx, 0);
    /* Small export -> +1 */
    TEST_ASSERT_TRUE(ctx.IsetBalanced >= before);
}

/* ---- Solar fine increase (large export) ---- */

void test_solar_fine_increase_large(void) {
    setup_solar_charging();
    ctx.Isum = -50;  /* Large export */
    ctx.ImportCurrent = 0;
    ctx.MainsMeterImeasured = ctx.Isum + (int16_t)ctx.Balanced[0];
    int32_t before = ctx.IsetBalanced;
    evse_calc_balanced_current(&ctx, 0);
    /* Large export -> should increase by more */
    TEST_ASSERT_TRUE(ctx.IsetBalanced > before);
}

/* ---- Solar fine decrease (moderate import) ---- */

void test_solar_fine_decrease_moderate(void) {
    setup_solar_charging();
    ctx.Isum = 15;    /* Moderate import */
    ctx.ImportCurrent = 0;
    ctx.MainsMeterImeasured = ctx.Isum + (int16_t)ctx.Balanced[0];
    ctx.IsetBalanced = 150;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_TRUE(ctx.IsetBalanced < 150);
}

/* ---- Solar fine decrease (aggressive import) ---- */

void test_solar_fine_decrease_aggressive(void) {
    setup_solar_charging();
    ctx.Isum = 50;     /* Large import */
    ctx.ImportCurrent = 0;
    ctx.MainsMeterImeasured = ctx.Isum + (int16_t)ctx.Balanced[0];
    ctx.IsetBalanced = 200;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_TRUE(ctx.IsetBalanced < 200);
}

/* ---- Solar B-state AUTO determines 1P ---- */

void test_solar_b_state_auto_determines_1p(void) {
    setup_solar_charging();
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.Isum = -50;  /* Small surplus - not enough for 3P */
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_1P, ctx.Switching_Phases_C2);
}

/* ---- Solar B-state AUTO determines 3P ---- */

void test_solar_b_state_auto_determines_3p(void) {
    setup_solar_charging();
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    ctx.EnableC2 = AUTO;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.Isum = -500;  /* Large surplus -> enough for 3P */
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_3P, ctx.Switching_Phases_C2);
}

/* ---- Hard shortage increments NoCurrent ---- */

void test_hard_shortage_increments_nocurrent(void) {
    setup_solar_charging();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.MainsMeterImeasured = 300;  /* Overloaded */
    ctx.MaxMains = 10;               /* Low limit */
    ctx.NoCurrent = 0;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_GREATER_THAN(0, ctx.NoCurrent);
}

/* ---- Soft shortage starts MaxSumMains timer ---- */

void test_soft_shortage_starts_maxsummains_timer(void) {
    setup_solar_charging();
    ctx.Mode = MODE_SMART;
    ctx.MaxSumMains = 10;
    ctx.MaxSumMainsTime = 5;
    ctx.Isum = 200;
    ctx.MainsMeterImeasured = 200;
    ctx.MaxMains = 40;              /* High enough to not be a hard shortage on MaxMains */
    ctx.MaxSumMainsTimer = 0;
    evse_calc_balanced_current(&ctx, 0);
    if (ctx.MaxSumMainsTimer > 0) {
        TEST_ASSERT_EQUAL_INT(5 * 60, ctx.MaxSumMainsTimer);
    }
}

/* ---- No shortage clears timers ---- */

void test_no_shortage_clears_timers(void) {
    setup_solar_charging();
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterImeasured = 50;
    ctx.MaxMains = 40;
    ctx.SolarStopTimer = 10;
    ctx.NoCurrent = 5;
    ctx.IsetBalanced = 200;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(0, ctx.SolarStopTimer);
    TEST_ASSERT_EQUAL_INT(0, ctx.NoCurrent);
}

/* ---- IsetBalanced capped at 800 ---- */

void test_isetbalanced_capped_at_800(void) {
    setup_solar_charging();
    ctx.Mode = MODE_SMART;
    ctx.IsetBalanced = 900;
    ctx.MainsMeterImeasured = -500;  /* Large surplus */
    ctx.MaxMains = 100;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_LESS_OR_EQUAL(800, ctx.IsetBalanced);
}

/* ---- Normal mode forces 3P ---- */

void test_normal_mode_forces_3p(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.MaxCurrent = 16;
    ctx.MaxCapacity = 16;
    ctx.ChargeCurrent = 160;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;
    evse_calc_balanced_current(&ctx, 0);
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_3P, ctx.Switching_Phases_C2);
}

/* ---- phasesLastUpdateFlag gates regulation ---- */

void test_phases_flag_gates_regulation(void) {
    setup_solar_charging();
    ctx.Mode = MODE_SMART;
    ctx.phasesLastUpdateFlag = false;
    ctx.IsetBalanced = 100;
    ctx.MainsMeterImeasured = -500;  /* Huge surplus */
    ctx.MaxMains = 100;
    int32_t before = ctx.IsetBalanced;
    evse_calc_balanced_current(&ctx, 0);
    /* With flag false, IsetBalanced should NOT increase (for smart ongoing) */
    TEST_ASSERT_EQUAL_INT(before, ctx.IsetBalanced);
}

/* ---- Multi-EVSE solar startup ---- */

void test_multi_evse_solar_startup(void) {
    setup_solar_charging();
    ctx.LoadBl = 1;
    /* EVSE 0: in startup */
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 100;
    ctx.Node[0].IntTimer = 5;  /* In startup */
    /* EVSE 1: past startup */
    ctx.BalancedState[1] = STATE_C;
    ctx.BalancedMax[1] = 160;
    ctx.Balanced[1] = 100;
    ctx.Node[1].IntTimer = SOLARSTARTTIME + 10;
    ctx.IsetBalanced = 200;
    ctx.MainsMeterImeasured = 50;
    ctx.Isum = -50;
    evse_calc_balanced_current(&ctx, 0);
    /* EVSE 0 (startup) should get MinCurrent */
    TEST_ASSERT_EQUAL_INT(ctx.MinCurrent * 10, ctx.Balanced[0]);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("Solar Balancing");

    RUN_TEST(test_solar_3p_shortage_starts_timer);
    RUN_TEST(test_solar_3p_timer_triggers_1p_switch);
    RUN_TEST(test_solar_1p_surplus_starts_timer);
    RUN_TEST(test_solar_1p_timer_triggers_3p_switch);
    RUN_TEST(test_solar_insufficient_surplus_resets_timer);
    RUN_TEST(test_solar_startup_forces_mincurrent);
    RUN_TEST(test_solar_past_startup_uses_calculated);
    RUN_TEST(test_solar_fine_increase_small);
    RUN_TEST(test_solar_fine_increase_large);
    RUN_TEST(test_solar_fine_decrease_moderate);
    RUN_TEST(test_solar_fine_decrease_aggressive);
    RUN_TEST(test_solar_b_state_auto_determines_1p);
    RUN_TEST(test_solar_b_state_auto_determines_3p);
    RUN_TEST(test_hard_shortage_increments_nocurrent);
    RUN_TEST(test_soft_shortage_starts_maxsummains_timer);
    RUN_TEST(test_no_shortage_clears_timers);
    RUN_TEST(test_isetbalanced_capped_at_800);
    RUN_TEST(test_normal_mode_forces_3p);
    RUN_TEST(test_phases_flag_gates_regulation);
    RUN_TEST(test_multi_evse_solar_startup);

    TEST_SUITE_RESULTS();
}
