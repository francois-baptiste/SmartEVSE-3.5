/*
 * pin_rate_limit.c — Rate limiter impl. See pin_rate_limit.h.
 */
#include "pin_rate_limit.h"

/* Escalating cooldown schedule, in milliseconds. Index = fail_count,
 * capped at the last entry once the counter grows beyond the table. */
static const uint32_t kCooldownMs[] = {
    0,                              /* 0 — never reached via record_failure */
    0,                              /* 1 — free */
    0,                              /* 2 — free */
    10UL * 1000UL,                  /* 3 — 10 s */
    60UL * 1000UL,                  /* 4 — 60 s */
    300UL * 1000UL,                 /* 5 — 5 min */
    1800UL * 1000UL                 /* 6+ — 30 min (cap) */
};
#define PIN_RL_MAX_INDEX ((uint16_t)(sizeof(kCooldownMs) / sizeof(kCooldownMs[0]) - 1))

static uint32_t cooldown_for_count(uint16_t fail_count) {
    if (fail_count > PIN_RL_MAX_INDEX) fail_count = PIN_RL_MAX_INDEX;
    return kCooldownMs[fail_count];
}

pin_rl_result_t pin_rl_check(pin_rate_limit_t *state, uint32_t now_ms) {
    if (!state) return PIN_RL_ALLOW;    /* Fail-open on bad arg — testable. */

    /* Long-idle auto-reset: if the last attempt (success or failure) was
     * more than PIN_RL_IDLE_RESET_MS ago, wipe the fail history so a
     * legitimate user coming back hours later gets a clean slate. Do NOT
     * auto-reset while an active cooldown is still in effect — that would
     * defeat the purpose of the cooldown. */
    if (state->cooldown_until_ms == 0 && state->last_attempt_ms != 0 &&
        (now_ms - state->last_attempt_ms) >= PIN_RL_IDLE_RESET_MS) {
        state->fail_count = 0;
    }

    if (state->cooldown_until_ms != 0) {
        /* Cooldown active — still holding? Unsigned wrap-safe compare:
         * (now - until) has the high bit set iff now < until. */
        if ((int32_t)(now_ms - state->cooldown_until_ms) < 0) {
            return PIN_RL_DENY_COOLDOWN;
        }
        /* Cooldown elapsed. Clear the sentinel so the next failure
         * re-arms from the current fail_count. */
        state->cooldown_until_ms = 0;
    }

    return PIN_RL_ALLOW;
}

void pin_rl_record_success(pin_rate_limit_t *state) {
    if (!state) return;
    state->fail_count = 0;
    state->cooldown_until_ms = 0;
    /* Keep last_attempt_ms so the idle-reset logic doesn't fire
     * spuriously on the next check. Not strictly needed (success
     * already clears fail_count) but keeps state consistent. */
}

void pin_rl_record_failure(pin_rate_limit_t *state, uint32_t now_ms) {
    if (!state) return;

    state->last_attempt_ms = now_ms;

    /* Saturate at UINT16_MAX to avoid wrap; the cooldown is capped at
     * kCooldownMs[max] regardless, so stopping the counter here is safe. */
    if (state->fail_count < 0xFFFFu) {
        state->fail_count++;
    }

    uint32_t cd = cooldown_for_count(state->fail_count);
    if (cd > 0) {
        state->cooldown_until_ms = now_ms + cd;
        /* Guard the zero-sentinel: if millis() wrapped such that
         * now_ms + cd == 0 exactly, bump by 1 so "cooldown active" is
         * distinguishable from "never armed". */
        if (state->cooldown_until_ms == 0) state->cooldown_until_ms = 1;
    }
}

uint32_t pin_rl_retry_after_seconds(const pin_rate_limit_t *state,
                                    uint32_t now_ms) {
    if (!state || state->cooldown_until_ms == 0) return 0;
    int32_t delta = (int32_t)(state->cooldown_until_ms - now_ms);
    if (delta <= 0) return 0;
    /* Round up to whole seconds so Retry-After never under-reports. */
    return (uint32_t)((delta + 999) / 1000);
}
