/*
 * test_ocpp.c - OCPP edge cases for current limiting and mode behavior
 *
 * Tests:
 *   - OcppCurrentLimit at exact boundary values (equal to MinCurrent, MaxCurrent)
 *   - OcppMode with LoadBl != 0 (should be ignored per code)
 *   - OcppCurrentLimit interaction with OverrideCurrent
 *   - CPDutyOverride flag behavior
 *   - OcppCurrentLimit = 0.0 (should zero the current)
 *   - Negative OcppCurrentLimit (should be ignored, treated as no limit)
 *   - OCPP interaction with evse_is_current_available
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

/* Helper: set up a standalone EVSE in STATE_C with OCPP enabled */
static void setup_ocpp_charging(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;          /* Standalone */
    ctx.MaxCurrent = 16;
    ctx.MaxCapacity = 16;
    ctx.MinCurrent = 6;
    ctx.MaxCircuit = 32;
    ctx.MaxMains = 25;
    ctx.ChargeCurrent = 160;
    ctx.OcppMode = true;
    ctx.State = STATE_C;
    ctx.BalancedState[0] = STATE_C;
    ctx.BalancedMax[0] = 160;
    ctx.Balanced[0] = 160;
    ctx.phasesLastUpdateFlag = true;
}

/* ---- Boundary: OcppCurrentLimit == MinCurrent ---- */

void test_ocpp_limit_equal_to_mincurrent(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 6.0f;  /* Exactly MinCurrent */
    evse_calc_balanced_current(&ctx, 0);
    /* 6A is valid (>= MinCurrent), so ChargeCurrent should be 60 */
    TEST_ASSERT_EQUAL_INT(60, ctx.ChargeCurrent);
}

/* ---- Boundary: OcppCurrentLimit == MaxCurrent ---- */

void test_ocpp_limit_equal_to_maxcurrent(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 16.0f;  /* Exactly MaxCurrent */
    evse_calc_balanced_current(&ctx, 0);
    /* 16A == MaxCurrent, so no reduction: ChargeCurrent stays 160 */
    TEST_ASSERT_EQUAL_INT(160, ctx.ChargeCurrent);
}

/* ---- OcppCurrentLimit above MaxCurrent does not increase current ---- */

void test_ocpp_limit_above_maxcurrent_no_increase(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 32.0f;  /* Well above MaxCurrent of 16 */
    evse_calc_balanced_current(&ctx, 0);
    /* OCPP limit is higher than ChargeCurrent, so no capping: stays at MaxCurrent*10 */
    TEST_ASSERT_EQUAL_INT(160, ctx.ChargeCurrent);
}

/* ---- OcppMode with LoadBl != 0 (master or node): OCPP limit ignored ---- */

void test_ocpp_ignored_when_loadbl_master(void) {
    setup_ocpp_charging();
    ctx.LoadBl = 1;  /* Master in load-balanced setup */
    ctx.OcppCurrentLimit = 3.0f;  /* Below MinCurrent */
    ctx.MaxCircuit = 32;
    evse_calc_balanced_current(&ctx, 0);
    /* With LoadBl=1, OCPP limit check (!ctx->LoadBl) is false, so limit is ignored.
     * ChargeCurrent should be set from MaxCurrent, not zeroed. */
    TEST_ASSERT_EQUAL_INT(160, ctx.ChargeCurrent);
}

void test_ocpp_ignored_when_loadbl_node(void) {
    setup_ocpp_charging();
    ctx.LoadBl = 2;  /* Node */
    ctx.OcppCurrentLimit = 3.0f;  /* Below MinCurrent */
    evse_calc_balanced_current(&ctx, 0);
    /* OCPP check requires !ctx->LoadBl, so with LoadBl=2 the limit is ignored */
    TEST_ASSERT_EQUAL_INT(160, ctx.ChargeCurrent);
}

/* ---- OverrideCurrent takes precedence over OCPP limit ---- */

void test_override_current_overrides_ocpp(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 10.0f;  /* Would cap at 100 */
    ctx.OverrideCurrent = 80;      /* Override to 8A */
    evse_calc_balanced_current(&ctx, 0);
    /* OverrideCurrent is applied AFTER OCPP, and unconditionally sets ChargeCurrent */
    TEST_ASSERT_EQUAL_INT(80, ctx.ChargeCurrent);
}

void test_override_current_overrides_ocpp_zero(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 3.0f;   /* Below MinCurrent, would zero ChargeCurrent */
    ctx.OverrideCurrent = 120;     /* Override to 12A */
    evse_calc_balanced_current(&ctx, 0);
    /* OverrideCurrent is applied after OCPP zeroed ChargeCurrent, overriding it */
    TEST_ASSERT_EQUAL_INT(120, ctx.ChargeCurrent);
}

/* ---- OcppCurrentLimit = 0.0 should zero the current ---- */

void test_ocpp_limit_zero_zeros_current(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 0.0f;
    evse_calc_balanced_current(&ctx, 0);
    /* 0.0 < MinCurrent(6), so ChargeCurrent should be zeroed */
    TEST_ASSERT_EQUAL_INT(0, ctx.ChargeCurrent);
}

/* ---- Negative OcppCurrentLimit: treated as "no limit set" ---- */

void test_ocpp_negative_limit_no_restriction(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = -1.0f;  /* Default init value, means no limit */
    evse_calc_balanced_current(&ctx, 0);
    /* Negative limit means OCPP block is skipped (>= 0.0 check fails) */
    TEST_ASSERT_EQUAL_INT(160, ctx.ChargeCurrent);
}

/* ---- OCPP blocks current availability when limit < MinCurrent ---- */

void test_ocpp_blocks_current_available_at_zero(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 0.0f;
    int available = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, available);
}

/* ---- OCPP allows current availability when limit >= MinCurrent ---- */

void test_ocpp_allows_current_available_at_mincurrent(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = 6.0f;  /* Exactly MinCurrent */
    int available = evse_is_current_available(&ctx);
    /* 6.0 is NOT < MinCurrent(6), so the OCPP check passes */
    TEST_ASSERT_EQUAL_INT(1, available);
}

/* ---- OCPP current availability: negative limit is not blocking ---- */

void test_ocpp_negative_limit_allows_current_available(void) {
    setup_ocpp_charging();
    ctx.OcppCurrentLimit = -1.0f;
    int available = evse_is_current_available(&ctx);
    /* Negative: OcppCurrentLimit >= 0.0 is false, so OCPP check is skipped */
    TEST_ASSERT_EQUAL_INT(1, available);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("OCPP Edge Cases");

    RUN_TEST(test_ocpp_limit_equal_to_mincurrent);
    RUN_TEST(test_ocpp_limit_equal_to_maxcurrent);
    RUN_TEST(test_ocpp_limit_above_maxcurrent_no_increase);
    RUN_TEST(test_ocpp_ignored_when_loadbl_master);
    RUN_TEST(test_ocpp_ignored_when_loadbl_node);
    RUN_TEST(test_override_current_overrides_ocpp);
    RUN_TEST(test_override_current_overrides_ocpp_zero);
    RUN_TEST(test_ocpp_limit_zero_zeros_current);
    RUN_TEST(test_ocpp_negative_limit_no_restriction);
    RUN_TEST(test_ocpp_blocks_current_available_at_zero);
    RUN_TEST(test_ocpp_allows_current_available_at_mincurrent);
    RUN_TEST(test_ocpp_negative_limit_allows_current_available);

    TEST_SUITE_RESULTS();
}
