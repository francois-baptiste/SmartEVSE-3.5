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

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-001
 * @scenario Entering MODEM_REQUEST disconnects the pilot signal
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_REQUEST
 * @then pilot_connected is false
 */
void test_modem_request_disconnects_pilot(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_FALSE(ctx.pilot_connected);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-002
 * @scenario Entering MODEM_REQUEST sets PWM to off (+12V)
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_REQUEST
 * @then PWM duty is set to 1024 (off / +12V constant)
 */
void test_modem_request_pwm_off(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_EQUAL_INT(1024, ctx.last_pwm_duty);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-003
 * @scenario Entering MODEM_REQUEST ensures contactors are open
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_REQUEST
 * @then Both contactor1 and contactor2 are off (open)
 */
void test_modem_request_contactors_off(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    TEST_ASSERT_FALSE(ctx.contactor1_state);
    TEST_ASSERT_FALSE(ctx.contactor2_state);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-004
 * @scenario MODEM_REQUEST transitions to MODEM_WAIT after timer expires
 * @given The EVSE is in STATE_MODEM_REQUEST with ToModemWaitStateTimer=0
 * @when One second tick occurs
 * @then The state transitions to STATE_MODEM_WAIT
 */
void test_modem_request_to_wait_on_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    // ToModemWaitStateTimer starts at 0, so next 1s tick moves to WAIT
    evse_tick_1s(&ctx);
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_WAIT, ctx.State);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-005
 * @scenario Vehicle disconnect during MODEM_REQUEST returns to STATE_A
 * @given The EVSE is in STATE_MODEM_REQUEST
 * @when A 12V pilot signal is received (vehicle disconnected)
 * @then The state transitions to STATE_A
 */
void test_modem_request_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_REQUEST);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_WAIT ----

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-006
 * @scenario Entering MODEM_WAIT sets 5% PWM duty cycle for ISO15118 signalling
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_WAIT
 * @then PWM duty is set to 51 (5% duty cycle)
 */
void test_modem_wait_5pct_duty(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_EQUAL_INT(51, ctx.last_pwm_duty);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-007
 * @scenario Entering MODEM_WAIT reconnects the pilot signal
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_WAIT
 * @then pilot_connected is true
 */
void test_modem_wait_pilot_connected(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_TRUE(ctx.pilot_connected);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-008
 * @scenario Entering MODEM_WAIT sets ToModemDoneStateTimer to 60 seconds
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_WAIT
 * @then ToModemDoneStateTimer is set to 60
 */
void test_modem_wait_timer_set(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    TEST_ASSERT_EQUAL_INT(60, ctx.ToModemDoneStateTimer);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-009
 * @scenario MODEM_WAIT transitions to MODEM_DONE after 60-second timeout
 * @given The EVSE is in STATE_MODEM_WAIT with 60-second timer
 * @when 60 second ticks occur
 * @then The state transitions to STATE_MODEM_DONE
 */
void test_modem_wait_to_done_after_timeout(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    // Count down 60 seconds
    for (int i = 0; i < 60; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_MODEM_DONE, ctx.State);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-010
 * @scenario Vehicle disconnect during MODEM_WAIT returns to STATE_A
 * @given The EVSE is in STATE_MODEM_WAIT
 * @when A 12V pilot signal is received (vehicle disconnected)
 * @then The state transitions to STATE_A
 */
void test_modem_wait_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_WAIT);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_DONE ----

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-011
 * @scenario Entering MODEM_DONE disconnects the pilot signal
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_DONE
 * @then pilot_connected is false
 */
void test_modem_done_disconnects_pilot(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    TEST_ASSERT_FALSE(ctx.pilot_connected);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-012
 * @scenario Entering MODEM_DONE sets LeaveModemDoneStateTimer to 5 seconds
 * @given The EVSE is initialised with basic configuration
 * @when The state is set to STATE_MODEM_DONE
 * @then LeaveModemDoneStateTimer is set to 5
 */
void test_modem_done_timer_set(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    TEST_ASSERT_EQUAL_INT(5, ctx.LeaveModemDoneStateTimer);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-013
 * @scenario MODEM_DONE transitions to STATE_B after 5-second timer with ModemStage=1
 * @given The EVSE is in STATE_MODEM_DONE with 5-second timer
 * @when 5 second ticks occur
 * @then The state transitions to STATE_B and ModemStage is set to 1
 */
void test_modem_done_to_B_after_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    for (int i = 0; i < 5; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_B, ctx.State);
    TEST_ASSERT_EQUAL_INT(1, ctx.ModemStage);  // Skip modem next time
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-014
 * @scenario Vehicle disconnect during MODEM_DONE returns to STATE_A
 * @given The EVSE is in STATE_MODEM_DONE
 * @when A 12V pilot signal is received (vehicle disconnected)
 * @then The state transitions to STATE_A
 */
void test_modem_done_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DONE);
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- MODEM_DENIED ----

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-015
 * @scenario MODEM_DENIED transitions to STATE_A after timer expires
 * @given The EVSE is in STATE_MODEM_DENIED with LeaveModemDeniedStateTimer=3
 * @when 3 second ticks occur
 * @then The state transitions to STATE_A
 */
void test_modem_denied_to_A_after_timer(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DENIED);
    ctx.LeaveModemDeniedStateTimer = 3;
    for (int i = 0; i < 3; i++) {
        evse_tick_1s(&ctx);
    }
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-016
 * @scenario Vehicle disconnect during MODEM_DENIED returns to STATE_A
 * @given The EVSE is in STATE_MODEM_DENIED with timer still running
 * @when A 12V pilot signal is received (vehicle disconnected)
 * @then The state transitions to STATE_A
 */
void test_modem_denied_to_A_on_disconnect(void) {
    setup_basic();
    evse_set_state(&ctx, STATE_MODEM_DENIED);
    ctx.LeaveModemDeniedStateTimer = 10;
    evse_tick_10ms(&ctx, PILOT_12V);
    TEST_ASSERT_EQUAL_INT(STATE_A, ctx.State);
}

// ---- Full modem flow ----

/*
 * @feature Modem / ISO15118 Negotiation
 * @req REQ-MODEM-017
 * @scenario Full modem negotiation flow: REQUEST -> WAIT -> DONE -> STATE_B
 * @given The EVSE is initialised with basic configuration
 * @when The modem negotiation proceeds through all stages with timers expiring
 * @then The EVSE transitions REQUEST->WAIT->DONE->B with ModemStage=1 and correct PWM/pilot at each stage
 */
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
