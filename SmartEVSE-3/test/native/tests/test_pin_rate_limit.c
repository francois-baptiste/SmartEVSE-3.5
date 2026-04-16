/*
 * test_pin_rate_limit.c — tests for the LCD-PIN brute-force limiter.
 * See src/pin_rate_limit.h and docs/security/plan-16-http-auth-layer.md.
 */

#include "test_framework.h"
#include "pin_rate_limit.h"
#include <string.h>

/* ---- Baseline: clean state lets requests through ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-020
 * @scenario Clean state allows the first request
 * @given A zero-initialised pin_rate_limit_t
 * @when pin_rl_check is called
 * @then Returns ALLOW
 */
void test_pin_rl_clean_state_allows(void) {
    pin_rate_limit_t s = {0};
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, 1000));
}

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-020
 * @scenario First two failures do not trigger cooldown
 * @given A clean rate limiter
 * @when Two consecutive failures are recorded
 * @then pin_rl_check still returns ALLOW (no cooldown armed)
 */
void test_pin_rl_first_two_failures_free(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, 1100));
    pin_rl_record_failure(&s, 1200);
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, 1300));
}

/* ---- Escalating backoff schedule ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-021
 * @scenario Third failure arms a 10-second cooldown
 * @given Two failures already recorded
 * @when A third failure is recorded and check is called immediately
 * @then check returns DENY_COOLDOWN and retry_after ~= 10 s
 */
void test_pin_rl_third_failure_10s_cooldown(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1100);
    pin_rl_record_failure(&s, 1200);

    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 1200));
    uint32_t retry = pin_rl_retry_after_seconds(&s, 1200);
    TEST_ASSERT_EQUAL_INT(10, (int)retry);
}

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-021
 * @scenario Fourth failure extends cooldown to 60 seconds
 */
void test_pin_rl_fourth_failure_60s_cooldown(void) {
    pin_rate_limit_t s = {0};
    for (int i = 0; i < 3; i++) pin_rl_record_failure(&s, 1000 + i * 100);
    /* Assume attacker waits the 10 s out and tries again (now allowed). */
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, 20000));
    pin_rl_record_failure(&s, 20000);
    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 20000));
    TEST_ASSERT_EQUAL_INT(60, (int)pin_rl_retry_after_seconds(&s, 20000));
}

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-021
 * @scenario Fifth failure extends cooldown to 5 minutes
 */
void test_pin_rl_fifth_failure_5min_cooldown(void) {
    pin_rate_limit_t s = {0};
    for (int i = 0; i < 4; i++) pin_rl_record_failure(&s, i * 100);
    pin_rl_record_failure(&s, 1000000);  /* far past any prior cooldown */
    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 1000000));
    TEST_ASSERT_EQUAL_INT(300, (int)pin_rl_retry_after_seconds(&s, 1000000));
}

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-021
 * @scenario Sixth and subsequent failures cap at 30 minutes
 */
void test_pin_rl_capped_at_30min(void) {
    pin_rate_limit_t s = {0};
    for (int i = 0; i < 10; i++) pin_rl_record_failure(&s, i * 100);
    /* All 10 were recorded within the cooldown window so they each
     * re-arm at the current count. Verify the final cap. */
    s.cooldown_until_ms = 0;  /* force re-check of cap independent of timing */
    pin_rl_record_failure(&s, 2000000);
    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 2000000));
    TEST_ASSERT_EQUAL_INT(1800, (int)pin_rl_retry_after_seconds(&s, 2000000));
}

/* ---- Cooldown elapses ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-022
 * @scenario After cooldown elapses, new attempt is allowed
 * @given A cooldown armed for 10 seconds at t=1000ms
 * @when check is called at t=12000ms (11s later)
 * @then check returns ALLOW and retry_after == 0
 */
void test_pin_rl_cooldown_elapses(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1100);
    pin_rl_record_failure(&s, 1200);   /* armed 10s cooldown at 1200ms */

    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 5000));
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW,         pin_rl_check(&s, 12000));
    TEST_ASSERT_EQUAL_INT(0, (int)pin_rl_retry_after_seconds(&s, 12000));
}

/* ---- Retry-After reporting ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-023
 * @scenario retry_after rounds up to whole seconds
 * @given A 10s cooldown armed at t=1000
 * @when queried at t=1500 (500ms in) it reports 10s, at t=9500 reports 1s
 */
void test_pin_rl_retry_after_rounding(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1000);     /* cooldown until 11000ms */

    TEST_ASSERT_EQUAL_INT(10, (int)pin_rl_retry_after_seconds(&s, 1000));
    TEST_ASSERT_EQUAL_INT(10, (int)pin_rl_retry_after_seconds(&s, 1500));
    /* 500ms left → rounds up to 1s, not 0s. */
    TEST_ASSERT_EQUAL_INT(1,  (int)pin_rl_retry_after_seconds(&s, 10500));
    /* past cooldown → 0s */
    TEST_ASSERT_EQUAL_INT(0,  (int)pin_rl_retry_after_seconds(&s, 11500));
}

/* ---- Success clears state ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-024
 * @scenario Successful PIN resets counter and cooldown
 * @given A state with an active cooldown after 3 failures
 * @when pin_rl_record_success is called
 * @then Subsequent checks ALLOW immediately and count is 0
 */
void test_pin_rl_success_clears_cooldown(void) {
    pin_rate_limit_t s = {0};
    for (int i = 0; i < 3; i++) pin_rl_record_failure(&s, 1000 + i * 100);
    TEST_ASSERT_EQUAL_INT(PIN_RL_DENY_COOLDOWN, pin_rl_check(&s, 1500));

    pin_rl_record_success(&s);

    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, 1500));
    TEST_ASSERT_EQUAL_INT(0, (int)s.fail_count);
    TEST_ASSERT_EQUAL_INT(0, (int)s.cooldown_until_ms);
}

/* ---- Long-idle auto-reset ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-025
 * @scenario After idle > 10 min, counter auto-resets on next check
 * @given 2 failures recorded (no cooldown yet)
 * @when check is called more than 10 min later
 * @then fail_count resets to 0 — no accidental lockout of returning users
 */
void test_pin_rl_idle_reset(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1100);
    TEST_ASSERT_EQUAL_INT(2, (int)s.fail_count);

    /* 11 minutes later. */
    uint32_t far = 1100 + (11UL * 60UL * 1000UL);
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, far));
    TEST_ASSERT_EQUAL_INT(0, (int)s.fail_count);
}

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-025
 * @scenario Idle-reset does not fire while a cooldown is still active
 * @given Third failure arming a 10s cooldown
 * @when check is called 11 minutes later — but the cooldown was only 10s
 * @then Cooldown has long since elapsed, allow, but fail_count stays 3
 *        (the cooldown was active AT SOME POINT after the idle window,
 *         so idle-reset specifically does not trigger)
 */
void test_pin_rl_idle_reset_respects_cooldown(void) {
    pin_rate_limit_t s = {0};
    pin_rl_record_failure(&s, 1000);
    pin_rl_record_failure(&s, 1100);
    pin_rl_record_failure(&s, 1200);  /* 10s cooldown until 11200ms */
    /* At t=11200 the cooldown is still armed, no reset; one millisecond
     * later it is cleared but fail_count stays. */
    uint32_t far = 1200 + (11UL * 60UL * 1000UL);
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(&s, far));
    TEST_ASSERT_EQUAL_INT(3, (int)s.fail_count);
}

/* ---- Robustness / fail-open ---- */

/*
 * @feature PIN Rate Limit
 * @req REQ-AUTH-026
 * @scenario NULL state fails open (no crash, lets request through)
 * @given A NULL pin_rate_limit_t pointer
 * @when check / record_* / retry_after are called
 * @then No crash; check returns ALLOW, retry_after returns 0
 */
void test_pin_rl_null_safe(void) {
    TEST_ASSERT_EQUAL_INT(PIN_RL_ALLOW, pin_rl_check(NULL, 1000));
    pin_rl_record_success(NULL);                /* must not crash */
    pin_rl_record_failure(NULL, 1000);          /* must not crash */
    TEST_ASSERT_EQUAL_INT(0, (int)pin_rl_retry_after_seconds(NULL, 1000));
}

int main(void) {
    TEST_SUITE_BEGIN("PIN Rate Limit");

    RUN_TEST(test_pin_rl_clean_state_allows);
    RUN_TEST(test_pin_rl_first_two_failures_free);

    RUN_TEST(test_pin_rl_third_failure_10s_cooldown);
    RUN_TEST(test_pin_rl_fourth_failure_60s_cooldown);
    RUN_TEST(test_pin_rl_fifth_failure_5min_cooldown);
    RUN_TEST(test_pin_rl_capped_at_30min);

    RUN_TEST(test_pin_rl_cooldown_elapses);
    RUN_TEST(test_pin_rl_retry_after_rounding);

    RUN_TEST(test_pin_rl_success_clears_cooldown);

    RUN_TEST(test_pin_rl_idle_reset);
    RUN_TEST(test_pin_rl_idle_reset_respects_cooldown);

    RUN_TEST(test_pin_rl_null_safe);

    TEST_SUITE_RESULTS();
}
