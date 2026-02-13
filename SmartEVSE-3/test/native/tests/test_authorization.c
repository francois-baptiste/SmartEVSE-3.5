/*
 * test_authorization.c - RFID / OCPP / Switch access control
 *
 * Tests the authorization gate:
 *   - AccessStatus (ON/OFF/PAUSE) gating transitions
 *   - setAccess() side effects (stop charging when access removed)
 *   - OCPP current limit blocking
 *   - RFID lock timer
 */

#include "test_framework.h"
#include "evse_types.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_basic(void) {
    evse_init(&ctx, NULL);
    ctx.Mode = MODE_NORMAL;
    ctx.LoadBl = 0;
    ctx.ChargeCurrent = 130;
}

// ---- setAccess tests ----

void test_set_access_on(void) {
    setup_basic();
    evse_set_access(&ctx, ON);
    TEST_ASSERT_EQUAL_INT(ON, ctx.AccessStatus);
}

void test_set_access_off(void) {
    setup_basic();
    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(OFF, ctx.AccessStatus);
}

void test_set_access_off_from_C_goes_C1(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_C);
    TEST_ASSERT_EQUAL_INT(STATE_C, ctx.State);

    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
    TEST_ASSERT_EQUAL_INT(OFF, ctx.AccessStatus);
}

void test_set_access_pause_from_C_goes_C1(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_C);

    evse_set_access(&ctx, PAUSE);
    TEST_ASSERT_EQUAL_INT(STATE_C1, ctx.State);
    TEST_ASSERT_EQUAL_INT(PAUSE, ctx.AccessStatus);
}

void test_set_access_off_from_B_goes_B1(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_B);

    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_set_access_off_from_modem_request_goes_B1(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_MODEM_REQUEST);

    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_set_access_off_from_modem_wait_goes_B1(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_MODEM_WAIT);

    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

void test_set_access_off_from_A_stays_A(void) {
    setup_basic();
    ctx.State = STATE_A;
    evse_set_access(&ctx, OFF);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_set_access_on_from_B1_does_not_auto_recover(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_B1);
    evse_set_access(&ctx, ON);
    // setAccess(ON) doesn't auto-recover state
    TEST_ASSERT_EQUAL_INT(STATE_B1, ctx.State);
}

// ---- OCPP authorization gating ----

void test_ocpp_blocks_current_availability(void) {
    setup_basic();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 3.0f;  // Below MinCurrent (6A)
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_ocpp_allows_when_limit_sufficient(void) {
    setup_basic();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = 10.0f;  // Above MinCurrent
    ctx.MinCurrent = 6;
    ctx.AccessStatus = ON;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_ocpp_negative_limit_ignored(void) {
    setup_basic();
    ctx.OcppMode = true;
    ctx.OcppCurrentLimit = -1.0f;  // Not set
    ctx.MinCurrent = 6;
    int result = evse_is_current_available(&ctx);
    TEST_ASSERT_EQUAL_INT(1, result);
}

// ---- RFID lock timer ----

// Original line 3090: AccessTimer starts on PILOT_12V (disconnect), not on connect
void test_access_timer_starts_on_rfid(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    ctx.RFIDReader = 2;
    ctx.AccessTimer = 0;

    // AccessTimer starts when EV disconnects (12V in STATE_A)
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(RFIDLOCKTIME, ctx.AccessTimer);
}

void test_access_timer_counts_down_in_state_A(void) {
    setup_basic();
    ctx.State = STATE_A;
    ctx.AccessStatus = ON;
    ctx.AccessTimer = 5;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(4, ctx.AccessTimer);
}

void test_access_timer_expires_turns_off(void) {
    setup_basic();
    ctx.State = STATE_A;
    ctx.AccessStatus = ON;
    ctx.AccessTimer = 1;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.AccessTimer);
    TEST_ASSERT_EQUAL_INT(OFF, ctx.AccessStatus);
}

void test_access_timer_cleared_when_not_in_A(void) {
    setup_basic();
    ctx.State = STATE_B;
    ctx.BalancedState[0] = STATE_B;
    ctx.AccessTimer = 30;
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(0, ctx.AccessTimer);
}

// ---- Access blocks state transition ----

void test_no_A_to_B_without_access(void) {
    setup_basic();
    ctx.AccessStatus = OFF;
    evse_tick_10ms(&ctx, PILOT_9V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_no_B_to_C_without_access(void) {
    setup_basic();
    ctx.AccessStatus = ON;
    evse_set_state(&ctx, STATE_B);
    ctx.DiodeCheck = 1;
    ctx.ChargeCurrent = ctx.MaxCurrent * 10;
    ctx.AccessStatus = OFF;  // Revoke access

    for (int i = 0; i < 55; i++) {
        evse_tick_10ms(&ctx, PILOT_6V);
    }
    TEST_ASSERT_NOT_EQUAL(STATE_C, ctx.State);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Authorization");

    RUN_TEST(test_set_access_on);
    RUN_TEST(test_set_access_off);
    RUN_TEST(test_set_access_off_from_C_goes_C1);
    RUN_TEST(test_set_access_pause_from_C_goes_C1);
    RUN_TEST(test_set_access_off_from_B_goes_B1);
    RUN_TEST(test_set_access_off_from_modem_request_goes_B1);
    RUN_TEST(test_set_access_off_from_modem_wait_goes_B1);
    RUN_TEST(test_set_access_off_from_A_stays_A);
    RUN_TEST(test_set_access_on_from_B1_does_not_auto_recover);
    RUN_TEST(test_ocpp_blocks_current_availability);
    RUN_TEST(test_ocpp_allows_when_limit_sufficient);
    RUN_TEST(test_ocpp_negative_limit_ignored);
    RUN_TEST(test_access_timer_starts_on_rfid);
    RUN_TEST(test_access_timer_counts_down_in_state_A);
    RUN_TEST(test_access_timer_expires_turns_off);
    RUN_TEST(test_access_timer_cleared_when_not_in_A);
    RUN_TEST(test_no_A_to_B_without_access);
    RUN_TEST(test_no_B_to_C_without_access);

    TEST_SUITE_RESULTS();
}
