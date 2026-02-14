/*
 * test_modem_states.c - Modem / ISO15118 state transitions
 *
 * Tests the modem negotiation flow:
 *   MODEM_REQUEST -> MODEM_WAIT -> MODEM_DONE -> STATE_B
 *   MODEM_DENIED -> STATE_A
 */

#include "test_framework.h"
#include "evse_ctx.h"
#include "evse_state_machine.h"

static evse_ctx_t ctx;

static void setup_basic(void) {
    evse_init(&ctx, NULL);
    ctx.AccessStatus = ON;
    ctx.Mode = MODE_NORMAL;
}

// ---- MODEM_REQUEST ----

void test_modem_request_disconnects_pilot(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_FALSE(ctx.pilot_connected);
}

void test_modem_request_pwm_off(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_EQUAL_INT(1024, ctx.last_pwm_duty);
}

void test_modem_request_contactors_off(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

void test_modem_request_to_wait_on_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    // ToModemWaitStateTimer starts at 0, so next 1s tick moves to WAIT
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_WAIT, ctx.State);
}

void test_modem_request_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_WAIT ----

void test_modem_wait_5pct_duty(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_EQUAL_INT(51, ctx.last_pwm_duty);
}

void test_modem_wait_pilot_connected(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
}

void test_modem_wait_timer_set(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_EQUAL_INT(60, ctx.ToModemDoneStateTimer);
}

void test_modem_wait_to_done_after_timeout(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    // Count down 60 seconds
    for (int i = 0; i < 60; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_DONE, ctx.State);
}

void test_modem_wait_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_DONE ----

void test_modem_done_disconnects_pilot(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    TEST_ASSERT_FALSE(ctx.pilot_connected);
}

void test_modem_done_timer_set(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    TEST_ASSERT_EQUAL_INT(5, ctx.LeaveModemDoneStateTimer);
}

void test_modem_done_to_B_after_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    for (int i = 0; i < 5; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(1, ctx.ModemStage);  // Skip modem next time
}

void test_modem_done_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_DENIED ----

void test_modem_denied_to_A_after_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DENIED);
    ctx.LeaveModemDeniedStateTimer = 3;
    for (int i = 0; i < 3; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

void test_modem_denied_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DENIED);
    ctx.LeaveModemDeniedStateTimer = 10;
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- Full modem flow ----

void test_full_modem_flow(void) {
    setup_basic();
    // Start modem request
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_REQUEST, ctx.State);
    TEST_ASSERT_FALSE(ctx.pilot_connected);

    // Timer expires -> MODEM_WAIT
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_WAIT, ctx.State);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
    TEST_ASSERT_EQUAL_INT(51, ctx.last_pwm_duty);

    // Wait 60s -> MODEM_DONE
    for (int i = 0; i < 60; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_DONE, ctx.State);

    // Wait 5s -> STATE_B
    for (int i = 0; i < 5; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(1, ctx.ModemStage);
}

// ---- Main ----
int main(void) {
    TEST_SUITE_BEGIN("Modem / ISO15118 States");

    RUN_TEST(test_modem_request_disconnects_pilot);
    RUN_TEST(test_modem_request_pwm_off);
    RUN_TEST(test_modem_request_contactors_off);
    RUN_TEST(test_modem_request_to_wait_on_timer);
    RUN_TEST(test_modem_request_to_A_on_disconnect);
    RUN_TEST(test_modem_wait_5pct_duty);
    RUN_TEST(test_modem_wait_pilot_connected);
    RUN_TEST(test_modem_wait_timer_set);
    RUN_TEST(test_modem_wait_to_done_after_timeout);
    RUN_TEST(test_modem_wait_to_A_on_disconnect);
    RUN_TEST(test_modem_done_disconnects_pilot);
    RUN_TEST(test_modem_done_timer_set);
    RUN_TEST(test_modem_done_to_B_after_timer);
    RUN_TEST(test_modem_done_to_A_on_disconnect);
    RUN_TEST(test_modem_denied_to_A_after_timer);
    RUN_TEST(test_modem_denied_to_A_on_disconnect);
    RUN_TEST(test_full_modem_flow);

    TEST_SUITE_RESULTS();
}
