/*
 * mode_policy.c — Pure C policy for enabling/disabling operating modes
 *
 * See mode_policy.h for the API contract. Tested natively in
 * test/native/tests/test_mode_policy.c.
 */

#include "mode_policy.h"
#include <stdio.h>

/* Mode values mirror evse_ctx.h / main.h — kept local so this module has
 * no header dependencies beyond its own. */
#define MP_MODE_NORMAL 0
#define MP_MODE_SMART  1
#define MP_MODE_SOLAR  2

bool mode_policy_allowed(uint8_t mode, uint8_t disabled_mask) {
    if (mode == MP_MODE_NORMAL)
        return true;                       /* Normal is the safety fallback */
    if (mode != MP_MODE_SMART && mode != MP_MODE_SOLAR)
        return false;                      /* unknown mode */
    return (disabled_mask & (1u << mode)) == 0;
}

bool mode_policy_mask_valid(int value) {
    return value >= 0 && (value & ~(int)MODE_DISABLE_ALL) == 0;
}

uint8_t mode_policy_sanitize(uint8_t mode, uint8_t disabled_mask) {
    return mode_policy_allowed(mode, disabled_mask) ? mode : MP_MODE_NORMAL;
}

uint8_t mode_policy_toggle_smart_solar(uint8_t mode, uint8_t disabled_mask) {
    uint8_t target;

    if (mode == MP_MODE_SMART)
        target = MP_MODE_SOLAR;
    else if (mode == MP_MODE_SOLAR)
        target = MP_MODE_SMART;
    else
        return mode;                       /* toggle only applies to Smart/Solar */

    return mode_policy_allowed(target, disabled_mask) ? target : mode;
}

int mode_policy_status_text(uint8_t mode, int access_status,
                            char *buf, size_t size) {
    const char *name;
    const char *suffix;

    switch (mode) {
    case MP_MODE_NORMAL: name = "NORMAL"; break;
    case MP_MODE_SMART:  name = "SMART";  break;
    case MP_MODE_SOLAR:  name = "SOLAR";  break;
    default:             name = "?";      break;
    }

    switch (access_status) {
    case 0:  suffix = " OFF";    break;    /* AccessStatus OFF */
    case 2:  suffix = " PAUSED"; break;    /* AccessStatus PAUSE */
    default: suffix = "";        break;    /* ON */
    }

    return snprintf(buf, size, "%s%s", name, suffix);
}
