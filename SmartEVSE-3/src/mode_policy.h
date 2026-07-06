#ifndef MODE_POLICY_H
#define MODE_POLICY_H

/*
 * mode_policy.h — Pure C policy for enabling/disabling operating modes
 *
 * Backs the ModesDisabled setting: a bitmask that lets the user disable
 * the Smart and/or Solar operating modes from the web UI or LCD menu.
 * Normal mode can never be disabled — it is the safety fallback.
 *
 * Also provides the LCD status text ("SOLAR PAUSED", "NORMAL", ...) so the
 * mode/pause presentation logic is natively testable.
 *
 * No Arduino/ESP-IDF dependencies — compiles natively for the test suite.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Bit positions match the mode value: bit (1 << mode) disables that mode.
 * Bit 0 (Normal) is reserved and must stay 0. */
#define MODE_DISABLE_SMART   (1u << 1)   /* 1 << MODE_SMART */
#define MODE_DISABLE_SOLAR   (1u << 2)   /* 1 << MODE_SOLAR */
#define MODE_DISABLE_ALL     (MODE_DISABLE_SMART | MODE_DISABLE_SOLAR)

/* Returns true when switching to @mode is permitted under @disabled_mask.
 * Normal mode (0) is always permitted. Unknown modes are rejected. */
bool mode_policy_allowed(uint8_t mode, uint8_t disabled_mask);

/* Validate a ModesDisabled value received from HTTP/MQTT.
 * Only combinations of MODE_DISABLE_SMART and MODE_DISABLE_SOLAR are valid
 * (0, 2, 4 or 6). Returns true when valid. */
bool mode_policy_mask_valid(int value);

/* Reconcile the current mode with a (new) disabled mask.
 * Returns @mode unchanged when still allowed, MODE_NORMAL otherwise. */
uint8_t mode_policy_sanitize(uint8_t mode, uint8_t disabled_mask);

/* LCD '<' short-press toggle between Smart and Solar.
 * Returns the target mode, or @mode unchanged when the target is disabled
 * or when @mode is Normal (toggle only applies to Smart/Solar). */
uint8_t mode_policy_toggle_smart_solar(uint8_t mode, uint8_t disabled_mask);

/* Build the explicit mode/pause status text shown on the LCD.
 * @access_status: AccessStatus_t value (0=OFF, 1=ON, 2=PAUSE).
 * Produces "NORMAL", "SMART", "SOLAR" with " OFF" / " PAUSED" appended
 * when access is OFF/PAUSE. Always NUL-terminates. Returns the number of
 * characters that would have been written (snprintf semantics). */
int mode_policy_status_text(uint8_t mode, int access_status,
                            char *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* MODE_POLICY_H */
