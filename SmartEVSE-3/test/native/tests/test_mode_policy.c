/*
 * test_mode_policy.c - Disabling operating modes + LCD mode/pause status text
 *
 * Covers the ModesDisabled bitmask policy (web UI / LCD option to disable
 * Smart mode) and the explicit mode + pause text shown on the LCD main
 * screen.
 */

#include "test_framework.h"
#include "mode_policy.h"
#include "evse_ctx.h"   /* MODE_NORMAL / MODE_SMART */

/* ---- mode_policy_allowed ---- */

/*
 * @feature Operating Modes
 * @req REQ-MODE-030
 * @scenario Normal mode is always allowed
 * @given ModesDisabled has every disable bit set
 * @when a switch to MODE_NORMAL is checked
 * @then the switch is allowed (Normal is the safety fallback)
 */
void test_normal_always_allowed(void) {
    TEST_ASSERT_TRUE(mode_policy_allowed(MODE_NORMAL, 0));
    TEST_ASSERT_TRUE(mode_policy_allowed(MODE_NORMAL, MODE_DISABLE_ALL));
    TEST_ASSERT_TRUE(mode_policy_allowed(MODE_NORMAL, 0xFF));
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-032
 * @scenario Smart mode rejected when disabled
 * @given ModesDisabled has the Smart bit set
 * @when a switch to MODE_SMART is checked
 * @then the switch is rejected
 */
void test_smart_disabled_rejected(void) {
    TEST_ASSERT_FALSE(mode_policy_allowed(MODE_SMART, MODE_DISABLE_SMART));
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-033
 * @scenario All modes allowed with empty mask
 * @given ModesDisabled is 0
 * @when switches to every mode are checked
 * @then Normal and Smart are allowed and unknown modes rejected
 */
void test_empty_mask_allows_all(void) {
    TEST_ASSERT_TRUE(mode_policy_allowed(MODE_NORMAL, 0));
    TEST_ASSERT_TRUE(mode_policy_allowed(MODE_SMART, 0));
    TEST_ASSERT_FALSE(mode_policy_allowed(2, 0));
    TEST_ASSERT_FALSE(mode_policy_allowed(255, 0));
}

/* ---- mode_policy_mask_valid ---- */

/*
 * @feature Operating Modes
 * @req REQ-MODE-034
 * @scenario ModesDisabled setting accepts only the Smart bit
 * @given values from HTTP POST /settings modes_disabled
 * @when the mask is validated
 * @then 0 and 2 are valid; odd values, >2 and negatives are rejected
 */
void test_mask_validation(void) {
    TEST_ASSERT_TRUE(mode_policy_mask_valid(0));
    TEST_ASSERT_TRUE(mode_policy_mask_valid(MODE_DISABLE_SMART));
    TEST_ASSERT_TRUE(mode_policy_mask_valid(MODE_DISABLE_ALL));
    TEST_ASSERT_FALSE(mode_policy_mask_valid(1));   /* would disable Normal */
    TEST_ASSERT_FALSE(mode_policy_mask_valid(3));
    TEST_ASSERT_FALSE(mode_policy_mask_valid(4));
    TEST_ASSERT_FALSE(mode_policy_mask_valid(-1));
    TEST_ASSERT_FALSE(mode_policy_mask_valid(256));
}

/* ---- mode_policy_sanitize ---- */

/*
 * @feature Operating Modes
 * @req REQ-MODE-035
 * @scenario Active mode falls back to Normal when it becomes disabled
 * @given the EVSE is in Smart mode
 * @when the user disables Smart mode
 * @then the sanitized mode is MODE_NORMAL
 */
void test_sanitize_falls_back_to_normal(void) {
    TEST_ASSERT_EQUAL_INT(MODE_NORMAL,
        mode_policy_sanitize(MODE_SMART, MODE_DISABLE_ALL));
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-036
 * @scenario Active mode preserved when still allowed
 * @given the EVSE is in Smart mode
 * @when no modes are disabled
 * @then the sanitized mode remains MODE_SMART
 */
void test_sanitize_keeps_allowed_mode(void) {
    TEST_ASSERT_EQUAL_INT(MODE_SMART, mode_policy_sanitize(MODE_SMART, 0));
    TEST_ASSERT_EQUAL_INT(MODE_NORMAL,
        mode_policy_sanitize(MODE_NORMAL, MODE_DISABLE_ALL));
}

/* ---- mode_policy_status_text ---- */

/*
 * @feature Operating Modes
 * @req REQ-MODE-039
 * @scenario LCD shows the active mode name explicitly
 * @given access is ON
 * @when the status text is built for each mode
 * @then it reads NORMAL or SMART
 */
void test_status_text_mode_names(void) {
    char buf[24];
    mode_policy_status_text(MODE_NORMAL, 1, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("NORMAL", buf);
    mode_policy_status_text(MODE_SMART, 1, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("SMART", buf);
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-040
 * @scenario LCD shows PAUSED next to the mode when charging is paused
 * @given access status is PAUSE (2)
 * @when the status text is built
 * @then the mode name is suffixed with PAUSED
 */
void test_status_text_paused(void) {
    char buf[24];
    mode_policy_status_text(MODE_SMART, 2, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("SMART PAUSED", buf);
    mode_policy_status_text(MODE_NORMAL, 2, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("NORMAL PAUSED", buf);
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-041
 * @scenario LCD shows OFF next to the mode when access is switched off
 * @given access status is OFF (0)
 * @when the status text is built
 * @then the mode name is suffixed with OFF
 */
void test_status_text_off(void) {
    char buf[24];
    mode_policy_status_text(MODE_SMART, 0, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("SMART OFF", buf);
}

/*
 * @feature Operating Modes
 * @req REQ-MODE-042
 * @scenario Status text never overflows a small buffer
 * @given a 7-byte destination buffer
 * @when a paused Smart status text is built
 * @then the output is truncated and NUL-terminated
 */
void test_status_text_truncation(void) {
    char buf[7];
    int n = mode_policy_status_text(MODE_SMART, 2, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("SMART ", buf);
    TEST_ASSERT_TRUE(n >= (int)sizeof(buf));   /* snprintf semantics */
    /* Unknown mode falls back to a safe placeholder */
    mode_policy_status_text(9, 1, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("?", buf);
}

int main(void) {
    printf("mode_policy tests\n");

    RUN_TEST(test_normal_always_allowed);
    RUN_TEST(test_smart_disabled_rejected);
    RUN_TEST(test_empty_mask_allows_all);
    RUN_TEST(test_mask_validation);
    RUN_TEST(test_sanitize_falls_back_to_normal);
    RUN_TEST(test_sanitize_keeps_allowed_mode);
    RUN_TEST(test_status_text_mode_names);
    RUN_TEST(test_status_text_paused);
    RUN_TEST(test_status_text_off);
    RUN_TEST(test_status_text_truncation);

    TEST_SUITE_RESULTS();
}
