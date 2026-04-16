/*
 * reconnect_backoff.c — see reconnect_backoff.h.
 */
#include "reconnect_backoff.h"

/* Indexed by consecutive_failures. Index 0 is unused (no backoff at zero
 * failures). Last entry is the cap and is reused for any larger count. */
static const uint32_t kBackoffMs[] = {
    0,                  /* 0 failures — unused */
    1UL * 1000UL,       /* 1 failure  → 1 s */
    2UL * 1000UL,       /* 2 failures → 2 s */
    4UL * 1000UL,       /* 3 failures → 4 s */
    8UL * 1000UL,       /* 4 failures → 8 s */
    16UL * 1000UL,      /* 5 failures → 16 s */
    30UL * 1000UL       /* 6+ failures → 30 s cap */
};
#define BACKOFF_TABLE_LEN ((uint8_t)(sizeof(kBackoffMs) / sizeof(kBackoffMs[0])))
#define BACKOFF_CAP_INDEX ((uint8_t)(BACKOFF_TABLE_LEN - 1))

static uint32_t backoff_for_count(uint8_t fail_count) {
    if (fail_count >= BACKOFF_TABLE_LEN) fail_count = BACKOFF_CAP_INDEX;
    return kBackoffMs[fail_count];
}

bool reconnect_backoff_should_attempt(const reconnect_backoff_t *state,
                                      uint32_t now_ms) {
    if (!state) return true;                            /* fail-open */
    if (state->next_attempt_ms == 0) return true;       /* no backoff active */
    /* Wrap-safe compare: (now - next) treated as signed; >=0 means now is at or past next. */
    return (int32_t)(now_ms - state->next_attempt_ms) >= 0;
}

void reconnect_backoff_record_attempt(reconnect_backoff_t *state,
                                      uint32_t now_ms) {
    (void)state;
    (void)now_ms;
    /* Currently a no-op; reserved for future telemetry. State changes
     * happen in record_success / record_failure based on the outcome. */
}

void reconnect_backoff_record_success(reconnect_backoff_t *state) {
    if (!state) return;
    state->consecutive_failures = 0;
    state->next_attempt_ms = 0;
}

void reconnect_backoff_record_failure(reconnect_backoff_t *state,
                                      uint32_t now_ms) {
    if (!state) return;

    /* Saturating increment to keep the counter sane even after extended
     * outages — the cap entry in kBackoffMs handles any value above the
     * table length anyway, but a clamp avoids debugger-confusing overflows. */
    if (state->consecutive_failures < 0xFFu) {
        state->consecutive_failures++;
    }

    uint32_t delay = backoff_for_count(state->consecutive_failures);
    state->next_attempt_ms = now_ms + delay;
    /* Guard the zero sentinel — if the addition wrapped to exactly 0, bump
     * to 1 so should_attempt() correctly recognises an active cooldown. */
    if (state->next_attempt_ms == 0) state->next_attempt_ms = 1;
}

uint32_t reconnect_backoff_seconds_until_next(const reconnect_backoff_t *state,
                                              uint32_t now_ms) {
    if (!state || state->next_attempt_ms == 0) return 0;
    int32_t delta = (int32_t)(state->next_attempt_ms - now_ms);
    if (delta <= 0) return 0;
    /* Round up to whole seconds so reports never under-promise the wait. */
    return (uint32_t)((delta + 999) / 1000);
}
