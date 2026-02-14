/*
 * test_meter_recovery.c - Meter timeout and recovery sequences
 *
 * Tests:
 *   - CT_NOCOMM set then MainsMeterTimeout restored -> CT_NOCOMM cleared
 *   - EV_NOCOMM set then EVMeterTimeout restored -> EV_NOCOMM cleared
 *   - Both CT_NOCOMM and EV_NOCOMM simultaneously
 *   - Timeout during STATE_C triggers power unavailable
 *   - Timeout recovery allows resumption of charging
 *   - MainsMeter timeout on node (LoadBl > 1) vs master (LoadBl < 2)
 *   - EVMeterType=0 keeps resetting timeout (no EV meter installed)
 *   - Temperature error recovery with hysteresis boundary
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

/* ---- CT_NOCOMM set then restored ---- */

void test_ct_nocomm_set_then_restored(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.LoadBl = 0;  /* Master/standalone */

    /* Timeout reaches 0 -> CT_NOCOMM set */
    ctx.MainsMeterTimeout = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);

    /* Simulate communication restored: set timeout back to nonzero */
    ctx.MainsMeterTimeout = 5;
    evse_tick_1s(&ctx);
    /* CT_NOCOMM recovery check: if MainsMeterTimeout > 0, clear CT_NOCOMM */
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);
}

/* ---- EV_NOCOMM set then restored ---- */

void test_ev_nocomm_set_then_restored(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.EVMeterType = 1;

    /* Timeout reaches 0 -> EV_NOCOMM set */
    ctx.EVMeterTimeout = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & EV_NOCOMM) != 0);

    /* Simulate communication restored */
    ctx.EVMeterTimeout = 10;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & EV_NOCOMM);
}

/* ---- Both CT_NOCOMM and EV_NOCOMM simultaneously ---- */

void test_both_ct_and_ev_nocomm_simultaneously(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.EVMeterType = 1;
    ctx.LoadBl = 0;

    /* Both time out */
    ctx.MainsMeterTimeout = 0;
    ctx.EVMeterTimeout = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & EV_NOCOMM) != 0);

    /* Restore only mains meter */
    ctx.MainsMeterTimeout = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);
    /* EV_NOCOMM should still be set (EVMeterTimeout was decremented to 0 again
     * or was already 0). Actually EVMeterTimeout was set to 0, tick_1s doesn't
     * set it again because EVMeterType=1 and it's already timed out. The
     * EV_NOCOMM flag is already set, so the set code won't re-trigger (guard).
     * But EVMeterTimeout is 0, so recovery check (EVMeterTimeout > 0) fails. */
    TEST_ASSERT_TRUE((ctx.ErrorFlags & EV_NOCOMM) != 0);

    /* Now restore EV meter too */
    ctx.EVMeterTimeout = 10;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & EV_NOCOMM);
}

/* ---- Timeout during STATE_C triggers power unavailable ---- */

void test_mains_timeout_during_state_c(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.LoadBl = 0;
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_C);
    /* Make LESS_6A non-recoverable so the state stays */
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;

    ctx.MainsMeterTimeout = 0;
    evse_tick_1s(&ctx);

    /* CT_NOCOMM set + power unavailable: STATE_C -> STATE_C1 */
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

void test_ev_timeout_during_state_c(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.EVMeterType = 1;
    ctx.LoadBl = 0;
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_C);
    /* Make LESS_6A non-recoverable */
    ctx.MainsMeterImeasured = 300;
    ctx.MaxMains = 10;
    ctx.MainsMeterType = 1;

    ctx.EVMeterTimeout = 0;
    evse_tick_1s(&ctx);

    /* EV_NOCOMM set + power unavailable: STATE_C -> STATE_C1 */
    TEST_ASSERT_TRUE((ctx.ErrorFlags & EV_NOCOMM) != 0);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
}

/* ---- MainsMeter timeout on node (LoadBl > 1) ---- */

void test_mains_timeout_on_node(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;  /* Normal mode */
    ctx.LoadBl = 3;          /* Node */
    ctx.MainsMeterTimeout = 0;

    evse_tick_1s(&ctx);

    /* For nodes (LoadBl > 1), the timeout check does NOT have the
     * mode != MODE_NORMAL guard. It always sets CT_NOCOMM on timeout. */
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
}

void test_mains_timeout_master_normal_mode_ignored(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.MainsMeterType = 1;
    ctx.LoadBl = 0;  /* Standalone */
    ctx.MainsMeterTimeout = 0;

    evse_tick_1s(&ctx);

    /* For master/standalone (LoadBl < 2) with MainsMeterType set,
     * the timeout check has a Mode != MODE_NORMAL guard.
     * In MODE_NORMAL, CT_NOCOMM should NOT be set. */
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);
}

/* ---- EVMeterType=0 keeps resetting timeout ---- */

void test_no_ev_meter_resets_timeout_continuously(void) {
    evse_init(&ctx, NULL);
    ctx.EVMeterType = 0;

    /* Artificially lower timeout */
    ctx.EVMeterTimeout = 3;
    evse_tick_1s(&ctx);
    /* With no EV meter, timeout is reset to COMM_EVTIMEOUT every tick */
    TEST_ASSERT_EQUAL_INT(COMM_EVTIMEOUT, ctx.EVMeterTimeout);

    /* Even if we set it to 0, it gets reset */
    ctx.EVMeterTimeout = 0;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(COMM_EVTIMEOUT, ctx.EVMeterTimeout);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & EV_NOCOMM);
}

/* ---- No mains meter type and no LoadBl: timeout reset to COMM_TIMEOUT ---- */

void test_no_mains_meter_resets_timeout_continuously(void) {
    evse_init(&ctx, NULL);
    ctx.MainsMeterType = 0;
    ctx.LoadBl = 0;

    ctx.MainsMeterTimeout = 3;
    evse_tick_1s(&ctx);
    /* With no mains meter type and LoadBl=0, falls to else branch: reset */
    TEST_ASSERT_EQUAL_INT(COMM_TIMEOUT, ctx.MainsMeterTimeout);
}

/* ---- Temperature recovery boundary: exactly at threshold ---- */

void test_temp_recovery_exactly_at_boundary(void) {
    evse_init(&ctx, NULL);
    ctx.maxTemp = 65;
    ctx.ErrorFlags = TEMP_HIGH;

    /* At exactly maxTemp - 10 = 55: condition is TempEVSE < 55, which is false */
    ctx.TempEVSE = 55;
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & TEMP_HIGH) != 0);
}

void test_temp_recovery_one_below_boundary(void) {
    evse_init(&ctx, NULL);
    ctx.maxTemp = 65;
    ctx.ErrorFlags = TEMP_HIGH;

    /* At maxTemp - 10 - 1 = 54: condition is 54 < 55, which is true -> clears */
    ctx.TempEVSE = 54;
    evse_tick_1s(&ctx);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & TEMP_HIGH);
}

/* ---- Meter countdown sequence: verify tick-by-tick ---- */

void test_mains_meter_countdown_to_error(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_SMART;
    ctx.MainsMeterType = 1;
    ctx.LoadBl = 0;
    ctx.MainsMeterTimeout = 3;

    /* Tick 1: 3 -> 2 */
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(2, ctx.MainsMeterTimeout);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);

    /* Tick 2: 2 -> 1 */
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(1, ctx.MainsMeterTimeout);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);

    /* Tick 3: 1 -> 0 */
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.MainsMeterTimeout);
    TEST_ASSERT_FALSE(ctx.ErrorFlags & CT_NOCOMM);

    /* Tick 4: timeout == 0 and not yet flagged -> set CT_NOCOMM */
    evse_tick_1s(&ctx);
    TEST_ASSERT_TRUE((ctx.ErrorFlags & CT_NOCOMM) != 0);
}

/* ---- Main ---- */
int main(void) {
    TEST_SUITE_BEGIN("Meter Timeout Recovery Sequences");

    RUN_TEST(test_ct_nocomm_set_then_restored);
    RUN_TEST(test_ev_nocomm_set_then_restored);
    RUN_TEST(test_both_ct_and_ev_nocomm_simultaneously);
    RUN_TEST(test_mains_timeout_during_state_c);
    RUN_TEST(test_ev_timeout_during_state_c);
    RUN_TEST(test_mains_timeout_on_node);
    RUN_TEST(test_mains_timeout_master_normal_mode_ignored);
    RUN_TEST(test_no_ev_meter_resets_timeout_continuously);
    RUN_TEST(test_no_mains_meter_resets_timeout_continuously);
    RUN_TEST(test_temp_recovery_exactly_at_boundary);
    RUN_TEST(test_temp_recovery_one_below_boundary);
    RUN_TEST(test_mains_meter_countdown_to_error);

    TEST_SUITE_RESULTS();
}
