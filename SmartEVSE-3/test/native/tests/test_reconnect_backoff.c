/*
 * test_reconnect_backoff.c — tests for the MQTT/WebSocket reconnect backoff.
 * See src/reconnect_backoff.h.
 */
#include "test_framework.h"
#include "reconnect_backoff.h"

/* ---- Clean state ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-010
 * @scenario Clean state allows immediate attempt
 */
void test_clean_state_allows(void) {
    reconnect_backoff_t s = {0};
    TEST_ASSERT_TRUE(reconnect_backoff_should_attempt(&s, 1000));
    TEST_ASSERT_EQUAL_INT(0, (int)reconnect_backoff_seconds_until_next(&s, 1000));
}

/* ---- Schedule ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-011
 * @scenario First failure arms 1-second backoff
 */
void test_first_failure_1s(void) {
    reconnect_backoff_t s = {0};
    reconnect_backoff_record_failure(&s, 1000);
    TEST_ASSERT_FALSE(reconnect_backoff_should_attempt(&s, 1000));
    TEST_ASSERT_EQUAL_INT(1, (int)reconnect_backoff_seconds_until_next(&s, 1000));
    /* After 1s, attempt allowed. */
    TEST_ASSERT_TRUE(reconnect_backoff_should_attempt(&s, 2000));
}

/*
 * @feature Reconnect backoff
 * @req REQ-NET-011
 * @scenario Each subsequent failure doubles the backoff up to 30 s cap
 */
void test_doubling_schedule(void) {
    reconnect_backoff_t s = {0};
    /* Drive one failure at a time and check the cooldown each step. */
    const uint32_t expected[] = {1, 2, 4, 8, 16, 30, 30, 30};
    for (uint32_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        /* Use a millis() sequence comfortably past prior cooldowns. */
        uint32_t t = 1000000UL + i * 100000UL;
        reconnect_backoff_record_failure(&s, t);
        TEST_ASSERT_EQUAL_INT((int)expected[i],
            (int)reconnect_backoff_seconds_until_next(&s, t));
    }
}

/* ---- Success clears state ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-012
 * @scenario Success clears the failure counter and the cooldown
 */
void test_success_clears(void) {
    reconnect_backoff_t s = {0};
    reconnect_backoff_record_failure(&s, 1000);
    reconnect_backoff_record_failure(&s, 1000);
    reconnect_backoff_record_failure(&s, 1000);
    TEST_ASSERT_FALSE(reconnect_backoff_should_attempt(&s, 1500));
    reconnect_backoff_record_success(&s);
    TEST_ASSERT_TRUE(reconnect_backoff_should_attempt(&s, 1500));
    TEST_ASSERT_EQUAL_INT(0, (int)s.consecutive_failures);
    /* Next failure starts at 1 s again, not at the previous level. */
    reconnect_backoff_record_failure(&s, 5000);
    TEST_ASSERT_EQUAL_INT(1, (int)reconnect_backoff_seconds_until_next(&s, 5000));
}

/* ---- Cooldown elapses ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-013
 * @scenario After cooldown elapses, attempts allowed without state mutation
 * @given A 4-second cooldown after 3 failures
 * @when should_attempt is called past the cooldown deadline
 * @then Returns true; counter unchanged (only failure or success mutates)
 */
void test_cooldown_elapses(void) {
    reconnect_backoff_t s = {0};
    reconnect_backoff_record_failure(&s, 1000);
    reconnect_backoff_record_failure(&s, 1000);
    reconnect_backoff_record_failure(&s, 1000);   /* 4 s cooldown until 5000 */
    TEST_ASSERT_FALSE(reconnect_backoff_should_attempt(&s, 4000));
    TEST_ASSERT_TRUE(reconnect_backoff_should_attempt(&s, 5500));
    /* Counter not reset — that only happens on success. Schedule on next
     * failure escalates from 4 → 8 s. */
    TEST_ASSERT_EQUAL_INT(3, (int)s.consecutive_failures);
    reconnect_backoff_record_failure(&s, 5500);
    TEST_ASSERT_EQUAL_INT(8, (int)reconnect_backoff_seconds_until_next(&s, 5500));
}

/* ---- Rounding ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-014
 * @scenario seconds_until_next rounds up
 */
void test_seconds_rounds_up(void) {
    reconnect_backoff_t s = {0};
    reconnect_backoff_record_failure(&s, 1000);            /* cooldown 1000 → 2000 */
    TEST_ASSERT_EQUAL_INT(1, (int)reconnect_backoff_seconds_until_next(&s, 1000));
    /* 999 ms left → 1 s, not 0 s. */
    TEST_ASSERT_EQUAL_INT(1, (int)reconnect_backoff_seconds_until_next(&s, 1001));
    /* 1 ms left → 1 s. */
    TEST_ASSERT_EQUAL_INT(1, (int)reconnect_backoff_seconds_until_next(&s, 1999));
    /* Past deadline → 0 s. */
    TEST_ASSERT_EQUAL_INT(0, (int)reconnect_backoff_seconds_until_next(&s, 2500));
}

/* ---- NULL safety / fail-open ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-015
 * @scenario NULL state is safe and fails open
 */
void test_null_safe(void) {
    TEST_ASSERT_TRUE(reconnect_backoff_should_attempt(NULL, 1000));
    TEST_ASSERT_EQUAL_INT(0, (int)reconnect_backoff_seconds_until_next(NULL, 1000));
    /* These should not crash. */
    reconnect_backoff_record_attempt(NULL, 1000);
    reconnect_backoff_record_success(NULL);
    reconnect_backoff_record_failure(NULL, 1000);
}

/* ---- Counter saturation ---- */

/*
 * @feature Reconnect backoff
 * @req REQ-NET-016
 * @scenario consecutive_failures saturates at 0xFF
 */
void test_counter_saturates(void) {
    reconnect_backoff_t s = {0};
    s.consecutive_failures = 0xFFu;
    reconnect_backoff_record_failure(&s, 1000);
    TEST_ASSERT_EQUAL_INT(0xFFu, s.consecutive_failures);
    /* Cooldown is still the cap value (30 s). */
    TEST_ASSERT_EQUAL_INT(30, (int)reconnect_backoff_seconds_until_next(&s, 1000));
}

int main(void) {
    TEST_SUITE_BEGIN("Reconnect Backoff");

    RUN_TEST(test_clean_state_allows);

    RUN_TEST(test_first_failure_1s);
    RUN_TEST(test_doubling_schedule);

    RUN_TEST(test_success_clears);

    RUN_TEST(test_cooldown_elapses);

    RUN_TEST(test_seconds_rounds_up);

    RUN_TEST(test_null_safe);

    RUN_TEST(test_counter_saturates);

    TEST_SUITE_RESULTS();
}
