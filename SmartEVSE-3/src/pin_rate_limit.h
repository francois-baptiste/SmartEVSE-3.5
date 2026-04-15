/*
 * pin_rate_limit.h — Rate limiter for the /lcd-verify-password endpoint.
 *
 * Plan 16 Phase 2. Prevents brute-force of the 4-digit LCD PIN.
 *
 * Design:
 *   Pure C, no allocation, no platform deps — testable natively.
 *   Tracks consecutive failed attempts in a single struct. After a
 *   threshold, imposes an escalating cooldown during which further
 *   POSTs to /lcd-verify-password are rejected with 429 Retry-After.
 *   Successful verification resets the counter.
 *
 * Threat model:
 *   LAN attacker scripting POSTs to /lcd-verify-password, 4-digit
 *   PIN = 10,000 combinations. With this limiter, worst-case time
 *   to exhaust the space is on the order of months (see PR body
 *   for math), defeating practical brute-force.
 *
 * Non-goals:
 *   Per-source-IP tracking (global counter only, embedded RAM budget).
 *   Protection against distributed/parallel attacks (LAN trust model).
 */
#ifndef PIN_RATE_LIMIT_H
#define PIN_RATE_LIMIT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Internal state. Caller allocates (typically file-scope static).
 * Initialise with zero — {0} is a valid "no history" state.
 */
typedef struct {
    uint16_t fail_count;          /* Consecutive failed attempts (unbounded). */
    uint32_t last_attempt_ms;     /* millis() of last POST, 0 = never. */
    uint32_t cooldown_until_ms;   /* millis() when cooldown expires, 0 = none. */
} pin_rate_limit_t;

typedef enum {
    PIN_RL_ALLOW          = 0,    /* Accept the attempt. */
    PIN_RL_DENY_COOLDOWN  = 1     /* Reject with 429; caller reads retry_after. */
} pin_rl_result_t;

/* Reset counter when idle for this long (successful users shouldn't be
 * penalised for a stale failure from hours ago). */
#define PIN_RL_IDLE_RESET_MS  (10UL * 60UL * 1000UL)   /* 10 minutes */

/*
 * Check whether the current attempt is allowed. Does NOT mutate state
 * other than auto-resetting the fail counter after long idle. After
 * verification the caller MUST call pin_rl_record_success() or
 * pin_rl_record_failure() to keep the counter up to date.
 */
pin_rl_result_t pin_rl_check(pin_rate_limit_t *state, uint32_t now_ms);

/*
 * Record a successful PIN verification — clears the counter and
 * cooldown so the legitimate operator isn't penalised by past failures.
 */
void pin_rl_record_success(pin_rate_limit_t *state);

/*
 * Record a failed PIN verification — increments the counter and, once
 * past the first free attempts, arms an escalating cooldown window.
 * Backoff schedule (measured in seconds from now_ms):
 *     fail_count <= 2            : no cooldown
 *     fail_count == 3            : 10 s
 *     fail_count == 4            : 60 s
 *     fail_count == 5            : 300 s  (5 min)
 *     fail_count >= 6            : 1800 s (30 min, cap)
 */
void pin_rl_record_failure(pin_rate_limit_t *state, uint32_t now_ms);

/*
 * Seconds remaining on the active cooldown. Returns 0 when no cooldown
 * is active or it has already elapsed. Suitable for a Retry-After header.
 */
uint32_t pin_rl_retry_after_seconds(const pin_rate_limit_t *state,
                                    uint32_t now_ms);

#ifdef __cplusplus
}
#endif

#endif /* PIN_RATE_LIMIT_H */
