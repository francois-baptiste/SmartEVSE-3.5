/*
 * test_phase_switching.c - Phase switching logic tests
 *
 * Tests evse_check_switching_phases() and phase switching behaviour
 * during state transitions (STATE_B entry, STATE_C entry).
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_base(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 3;
}

/* ---- AUTO + SMART: forces 3P ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-005
 * @scenario AUTO + SMART forces 3-phase when currently on 1 phase
 * @given The EVSE is in STATE_B with EnableC2=AUTO, MODE_SMART, and 1 phase
 * @when evse_check_switching_phases is called
 * @then Switching_Phases_C2 is set to GOING_TO_SWITCH_3P
 */
void test_check_auto_smart_forces_3p(void) {
    setup_base();
    ctx.EnableC2 = AUTO;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    evse_check_switching_phases(&ctx);
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_3P, ctx.Switching_Phases_C2);
}

/* ---- AUTO + SMART already 3P ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-006
 * @scenario AUTO + SMART already on 3 phases results in NO_SWITCH
 * @given The EVSE is in STATE_B with EnableC2=AUTO, MODE_SMART, and 3 phases
 * @when evse_check_switching_phases is called
 * @then Switching_Phases_C2 is NO_SWITCH (already three phase)
 */
void test_check_auto_smart_already_3p(void) {
    setup_base();
    ctx.EnableC2 = AUTO;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    evse_check_switching_phases(&ctx);
    TEST_ASSERT_EQUAL_INT(NO_SWITCH, ctx.Switching_Phases_C2);
}

/* ---- ALWAYS_OFF in STATE_A sets directly ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-007
 * @scenario ALWAYS_OFF in STATE_A sets Nr_Of_Phases_Charging directly to 1
 * @given The EVSE is in STATE_A with EnableC2=ALWAYS_OFF and 3 phases configured
 * @when evse_check_switching_phases is called
 * @then Nr_Of_Phases_Charging is set directly to 1 (no deferred switch needed)
 */
void test_check_always_off_in_state_a(void) {
    setup_base();
    ctx.EnableC2 = ALWAYS_OFF;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.State = STATE_A;
    ctx.BalancedState[0] = STATE_A;
    evse_check_switching_phases(&ctx);
    /* In STATE_A, should set Nr_Of_Phases directly */
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
}

/* ---- ALWAYS_OFF in STATE_B sets switching flag ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-008
 * @scenario ALWAYS_OFF in STATE_B sets deferred switching flag to 1P
 * @given The EVSE is in STATE_B with EnableC2=ALWAYS_OFF and 3 phases configured
 * @when evse_check_switching_phases is called
 * @then Switching_Phases_C2 is set to GOING_TO_SWITCH_1P (deferred until STATE_C entry)
 */
void test_check_always_off_in_state_b(void) {
    setup_base();
    ctx.EnableC2 = ALWAYS_OFF;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    evse_check_switching_phases(&ctx);
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_1P, ctx.Switching_Phases_C2);
}

/* ---- RESERVED_C2_2 (formerly SOLAR_OFF): always forces 3P now ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-009
 * @scenario RESERVED_C2_2 forces 3-phase charging regardless of mode
 * @given The EVSE is in STATE_B with EnableC2=RESERVED_C2_2 (Solar mode removed) and 1 phase
 * @when evse_check_switching_phases is called
 * @then Switching_Phases_C2 is set to GOING_TO_SWITCH_3P
 */
void test_check_reserved_c2_2_forces_3p(void) {
    setup_base();
    ctx.EnableC2 = RESERVED_C2_2;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    evse_check_switching_phases(&ctx);
    /* RESERVED_C2_2: force_single_phase always returns 0, so 3P */
    TEST_ASSERT_EQUAL_INT(GOING_TO_SWITCH_3P, ctx.Switching_Phases_C2);
}

/* ---- STATE_C applies 1P switch ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-011
 * @scenario STATE_C entry applies deferred 1P switch and opens contactor 2
 * @given Switching_Phases_C2 is GOING_TO_SWITCH_1P with EnableC2=ALWAYS_OFF
 * @when The state is set to STATE_C
 * @then Nr_Of_Phases_Charging is 1 and contactor2 is off (open)
 */
void test_state_c_applies_1p_switch(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.EnableC2 = ALWAYS_OFF;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_1P;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

/* ---- STATE_C applies 3P switch ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-012
 * @scenario STATE_C entry applies deferred 3P switch and closes contactor 2
 * @given Switching_Phases_C2 is GOING_TO_SWITCH_3P with EnableC2=ALWAYS_ON
 * @when The state is set to STATE_C
 * @then Nr_Of_Phases_Charging is 3 and contactor2 is on (closed)
 */
void test_state_c_applies_3p_switch(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.EnableC2 = ALWAYS_ON;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_3P;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(3, ctx.Nr_Of_Phases_Charging);
    TEST_ASSERT_TRUE(ctx.contactor2_state);
}

/* ---- STATE_C resets Switching_Phases ---- */

/*
 * @feature Phase Switching
 * @req REQ-PHASE-013
 * @scenario STATE_C entry resets Switching_Phases_C2 to NO_SWITCH
 * @given Switching_Phases_C2 is GOING_TO_SWITCH_1P
 * @when The state is set to STATE_C
 * @then Switching_Phases_C2 is reset to NO_SWITCH
 */
void test_state_c_resets_switching(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_1P;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(NO_SWITCH, ctx.Switching_Phases_C2);
}

/* ==== Issue #20: Post-Phase-Switch Settling ==== */

/* ---- Phase switch resets IntTimer ---- */

/*
 * @feature Phase Switching
 * @req REQ-PH-024
 * @scenario Phase switch completion resets IntTimer for startup protection
 * @given The EVSE was charging on 3P with IntTimer=500 and switches to 1P
 * @when STATE_C is entered with Switching_Phases_C2 = GOING_TO_SWITCH_1P
 * @then Node[0].IntTimer is reset to 0 (new startup period begins)
 */
void test_phase_switch_resets_inttimer(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.EnableC2 = AUTO;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 3;
    ctx.Node[0].IntTimer = 500;  /* Deep into charge session */
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_1P;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(0, ctx.Node[0].IntTimer);
    TEST_ASSERT_EQUAL_INT(1, ctx.Nr_Of_Phases_Charging);
}

/*
 * @feature Phase Switching
 * @req REQ-PH-025
 * @scenario 3P upgrade also resets IntTimer
 * @given The EVSE was charging on 1P with IntTimer=300 and switches to 3P
 * @when STATE_C is entered with Switching_Phases_C2 = GOING_TO_SWITCH_3P
 * @then Node[0].IntTimer is reset to 0
 */
void test_3p_upgrade_resets_inttimer(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.EnableC2 = ALWAYS_ON;
    ctx.Mode = MODE_SMART;
    ctx.Nr_Of_Phases_Charging = 1;
    ctx.Node[0].IntTimer = 300;
    ctx.Switching_Phases_C2 = GOING_TO_SWITCH_3P;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(0, ctx.Node[0].IntTimer);
    TEST_ASSERT_EQUAL_INT(3, ctx.Nr_Of_Phases_Charging);
}

/*
 * @feature Phase Switching
 * @req REQ-PH-026
 * @scenario Normal STATE_C entry (no phase switch) does not reset IntTimer
 * @given The EVSE enters STATE_C without a phase switch (Switching_Phases_C2 = NO_SWITCH)
 * @when evse_set_state is called with STATE_C
 * @then Node[0].IntTimer is NOT reset (keeps previous value)
 */
void test_no_switch_preserves_inttimer(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_SMART;
    ctx.Node[0].IntTimer = 200;
    ctx.Switching_Phases_C2 = NO_SWITCH;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(200, ctx.Node[0].IntTimer);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("Phase Switching");

    RUN_TEST(test_check_auto_smart_forces_3p);
    RUN_TEST(test_check_auto_smart_already_3p);
    RUN_TEST(test_check_always_off_in_state_a);
    RUN_TEST(test_check_always_off_in_state_b);
    RUN_TEST(test_check_reserved_c2_2_forces_3p);
    RUN_TEST(test_state_c_applies_1p_switch);
    RUN_TEST(test_state_c_applies_3p_switch);
    RUN_TEST(test_state_c_resets_switching);

    /* Issue #20: Post-Phase-Switch Settling */
    RUN_TEST(test_phase_switch_resets_inttimer);
    RUN_TEST(test_3p_upgrade_resets_inttimer);
    RUN_TEST(test_no_switch_preserves_inttimer);

    TEST_SUITE_RESULTS();
}
