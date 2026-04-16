/*
 * reconnect_backoff.h — exponential backoff for MQTT / WebSocket reconnects.
 *
 * Pure C, allocation-free, testable natively.
 *
 * Threat model (security finding M-6, CWE-799 — uncontrolled resource
 * consumption): a failing backend (broker offline, network partition,
 * DNS failure) currently triggers a constant 3-second reconnect storm
 * from the Mongoose MQTT timer. This wastes CPU, fills logs, and on a
 * shared upstream network can DoS the broker.
 *
 * Schedule:
 *   failure 1:  1 s before next attempt
 *   failure 2:  2 s
 *   failure 3:  4 s
 *   failure 4:  8 s
 *   failure 5: 16 s
 *   failure 6+: 30 s (capped)
 *
 *   On a successful connection, the failure counter is cleared and the
 *   next failure starts at 1 s again.
 */
#ifndef RECONNECT_BACKOFF_H
#define RECONNECT_BACKOFF_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t  consecutive_failures;  /* Saturating counter; capped internally. */
    uint32_t next_attempt_ms;       /* millis() at which next attempt is allowed. 0 = no backoff active. */
} reconnect_backoff_t;

/*
 * True when an attempt is allowed at the current millis() — either because
 * no backoff is active (clean state) or because the cooldown has elapsed.
 * Pure inspection; does not mutate state. The caller must call
 * reconnect_backoff_record_attempt() before actually attempting.
 */
bool reconnect_backoff_should_attempt(const reconnect_backoff_t *state, uint32_t now_ms);

/*
 * Mark that an attempt is being made now. Call this *before* the actual
 * connect call. If the caller skips this and just calls _record_failure /
 * _record_success the schedule still works; this exists for symmetry and
 * to allow future telemetry hooks.
 */
void reconnect_backoff_record_attempt(reconnect_backoff_t *state, uint32_t now_ms);

/*
 * Connection succeeded — reset counter and clear any pending cooldown.
 */
void reconnect_backoff_record_success(reconnect_backoff_t *state);

/*
 * Connection attempt failed — increment the counter (saturating) and
 * arm the next-attempt timestamp per the schedule above.
 */
void reconnect_backoff_record_failure(reconnect_backoff_t *state, uint32_t now_ms);

/*
 * Whole seconds remaining on the current cooldown, or 0 if none. Suitable
 * for log messages or status reporting; rounds up so 1 ms remaining shows
 * as 1 s, not 0 s.
 */
uint32_t reconnect_backoff_seconds_until_next(const reconnect_backoff_t *state,
                                              uint32_t now_ms);

#ifdef __cplusplus
}
#endif

#endif /* RECONNECT_BACKOFF_H */
