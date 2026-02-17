/*
 * http_api.c — Pure C HTTP API validation logic
 *
 * Extracts parameter validation from handle_URI() POST /settings
 * so it can be tested natively without Mongoose or Arduino dependencies.
 */

#include "http_api.h"

#ifndef MIN_CURRENT
#define MIN_CURRENT 6
#endif

bool http_api_parse_color(int r_val, int g_val, int b_val,
                          uint8_t *r_out, uint8_t *g_out, uint8_t *b_out) {
    if (r_val < 0 || r_val > 255 || g_val < 0 || g_val > 255 || b_val < 0 || b_val > 255)
        return false;
    *r_out = (uint8_t)r_val;
    *g_out = (uint8_t)g_val;
    *b_out = (uint8_t)b_val;
    return true;
}

const char *http_api_validate_override_current(int value, int min_current,
                                               int max_current, int load_bl) {
    if (value == 0)
        return NULL; // zero always valid (disables override)
    if (load_bl >= 2)
        return "Value not allowed!"; // OverrideCurrent not possible on Slave
    if (value < (min_current * 10) || value > (max_current * 10))
        return "Value not allowed!";
    return NULL;
}

const char *http_api_validate_current_min(int value, int load_bl) {
    if (load_bl >= 2)
        return "Value not allowed!";
    if (value < MIN_CURRENT || value > 16)
        return "Value not allowed!";
    return NULL;
}

const char *http_api_validate_max_sum_mains(int value, int load_bl) {
    if (load_bl >= 2)
        return "Value not allowed!";
    if (value != 0 && (value < 10 || value > 600))
        return "Value not allowed!";
    return NULL;
}

const char *http_api_validate_stop_timer(int value) {
    if (value < 0 || value > 60)
        return "Value not allowed!";
    return NULL;
}

const char *http_api_validate_solar_start(int value) {
    if (value < 0 || value > 48)
        return "Value not allowed!";
    return NULL;
}

const char *http_api_validate_solar_max_import(int value) {
    if (value < 0 || value > 48)
        return "Value not allowed!";
    return NULL;
}

int http_api_validate_settings(const http_settings_request_t *req,
                               int min_current, int max_current,
                               int load_bl, int current_mode,
                               http_validation_error_t *errors, int max_errors) {
    int count = 0;

    if (req->has_current_min && count < max_errors) {
        const char *err = http_api_validate_current_min(req->current_min, load_bl);
        if (err) {
            errors[count].field = "current_min";
            errors[count].error = err;
            count++;
        }
    }

    if (req->has_max_sum_mains && count < max_errors) {
        const char *err = http_api_validate_max_sum_mains(req->max_sum_mains, load_bl);
        if (err) {
            errors[count].field = "current_max_sum_mains";
            errors[count].error = err;
            count++;
        }
    }

    if (req->has_stop_timer && count < max_errors) {
        const char *err = http_api_validate_stop_timer(req->stop_timer);
        if (err) {
            errors[count].field = "stop_timer";
            errors[count].error = err;
            count++;
        }
    }

    if (req->has_override_current && count < max_errors) {
        // Override current only valid in Normal or Smart mode
        if (current_mode == 0 || current_mode == 1) { // MODE_NORMAL=0, MODE_SMART=1
            const char *err = http_api_validate_override_current(
                req->override_current, min_current, max_current, load_bl);
            if (err) {
                errors[count].field = "override_current";
                errors[count].error = err;
                count++;
            }
        }
    }

    if (req->has_solar_start && count < max_errors) {
        const char *err = http_api_validate_solar_start(req->solar_start_current);
        if (err) {
            errors[count].field = "solar_start_current";
            errors[count].error = err;
            count++;
        }
    }

    if (req->has_solar_max_import && count < max_errors) {
        const char *err = http_api_validate_solar_max_import(req->solar_max_import);
        if (err) {
            errors[count].field = "solar_max_import";
            errors[count].error = err;
            count++;
        }
    }

    if (req->has_max_sum_mains_time && count < max_errors) {
        if (load_bl >= 2 || req->max_sum_mains_time < 0 || req->max_sum_mains_time > 60) {
            errors[count].field = "max_sum_mains_time";
            errors[count].error = "Value not allowed!";
            count++;
        }
    }

    if (req->has_lcd_lock && count < max_errors) {
        if (req->lcd_lock < 0 || req->lcd_lock > 1) {
            errors[count].field = "lcdlock";
            errors[count].error = "Value not allowed!";
            count++;
        }
    }

    if (req->has_cable_lock && count < max_errors) {
        if (req->cable_lock < 0 || req->cable_lock > 1) {
            errors[count].field = "cablelock";
            errors[count].error = "Value not allowed!";
            count++;
        }
    }

    return count;
}
