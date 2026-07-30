#ifndef MQTT_PARSER_H
#define MQTT_PARSER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Parsed MQTT command — the result of parsing a topic+payload
typedef enum {
    MQTT_CMD_NONE = 0,
    MQTT_CMD_MODE,
    MQTT_CMD_CUSTOM_BUTTON,
    MQTT_CMD_CURRENT_OVERRIDE,
    MQTT_CMD_MAX_SUM_MAINS,
    MQTT_CMD_CP_PWM_OVERRIDE,
    MQTT_CMD_MAINS_METER,
    MQTT_CMD_EV_METER,
    MQTT_CMD_HOME_BATTERY_CURRENT,
    MQTT_CMD_REQUIRED_EVCCID,
    MQTT_CMD_COLOR,
    MQTT_CMD_CABLE_LOCK,
    MQTT_CMD_ENABLE_C2,
    MQTT_CMD_PRIO_STRATEGY,
    MQTT_CMD_ROTATION_INTERVAL,
    MQTT_CMD_IDLE_TIMEOUT,
    MQTT_CMD_MQTT_HEARTBEAT,
    MQTT_CMD_MQTT_CHANGE_ONLY,
    MQTT_CMD_DIAG_PROFILE,
    MQTT_CMD_MAINS_METER_TIMEOUT,
    MQTT_CMD_HOMEWIZARD_IP,
    MQTT_CMD_INITIAL_SOC,
    MQTT_CMD_FULL_SOC,
    MQTT_CMD_ENERGY_CAPACITY,
    MQTT_CMD_ENERGY_REQUEST,
    MQTT_CMD_EVCCID_SET,
    MQTT_CMD_CAPACITY_LIMIT,
    MQTT_CMD_MAX_CIRCUIT_MAINS,
    MQTT_CMD_CIRCUIT_METER,
    MQTT_CMD_RAMP_RATE_DIVISOR,
    MQTT_CMD_EMA_ALPHA,
    MQTT_CMD_SMART_DEADBAND,
    MQTT_CMD_MAX_RAMP_RATE,
    MQTT_CMD_OSCILLATION_BOOST_MAX,
    MQTT_CMD_IDIFF_EMA_WEIGHT,
    MQTT_CMD_LINKY_METER,
} mqtt_cmd_type_t;

// Mode values matching firmware MODE_NORMAL/MODE_SMART
#define MQTT_MODE_OFF     0xFF
#define MQTT_MODE_PAUSE   0xFE
#define MQTT_MODE_NORMAL  0
#define MQTT_MODE_SMART   1

// Color indices
#define MQTT_COLOR_OFF     0
#define MQTT_COLOR_NORMAL  1
#define MQTT_COLOR_SMART   2
#define MQTT_COLOR_CUSTOM  3

typedef struct {
    mqtt_cmd_type_t cmd;
    union {
        uint8_t mode;                           // MQTT_CMD_MODE (MQTT_MODE_*)
        bool custom_button;                     // MQTT_CMD_CUSTOM_BUTTON
        uint16_t current_override;              // MQTT_CMD_CURRENT_OVERRIDE
        uint16_t max_sum_mains;                 // MQTT_CMD_MAX_SUM_MAINS
        int16_t cp_pwm;                         // MQTT_CMD_CP_PWM_OVERRIDE
        struct { int32_t L1, L2, L3; } mains_meter;
        struct { int32_t L1, L2, L3; int32_t W; int32_t Wh; } ev_meter;
        int16_t home_battery_current;           // MQTT_CMD_HOME_BATTERY_CURRENT
        char evccid[32];                        // MQTT_CMD_REQUIRED_EVCCID and MQTT_CMD_EVCCID_SET
        struct { uint8_t index; uint8_t r, g, b; } color; // MQTT_CMD_COLOR
        uint8_t cable_lock;                     // MQTT_CMD_CABLE_LOCK
        uint8_t enable_c2;                      // MQTT_CMD_ENABLE_C2
        uint8_t prio_strategy;                  // MQTT_CMD_PRIO_STRATEGY (0-2)
        uint16_t rotation_interval;             // MQTT_CMD_ROTATION_INTERVAL (0, 30-1440)
        uint16_t idle_timeout;                  // MQTT_CMD_IDLE_TIMEOUT (30-300)
        uint16_t mqtt_heartbeat;                // MQTT_CMD_MQTT_HEARTBEAT (10-300)
        bool mqtt_change_only;                  // MQTT_CMD_MQTT_CHANGE_ONLY (0/1)
        uint8_t diag_profile;                   // MQTT_CMD_DIAG_PROFILE (0-5)
        uint16_t mains_meter_timeout;           // MQTT_CMD_MAINS_METER_TIMEOUT (0, 10-3600)
        char homewizard_ip[16];                 // MQTT_CMD_HOMEWIZARD_IP (IPv4 or empty)
        int8_t initial_soc;                     // MQTT_CMD_INITIAL_SOC (-1 or 0-100)
        int8_t full_soc;                        // MQTT_CMD_FULL_SOC (-1 or 0-100)
        int32_t energy_capacity;                // MQTT_CMD_ENERGY_CAPACITY (-1 or 0-200000 Wh)
        int32_t energy_request;                 // MQTT_CMD_ENERGY_REQUEST (-1 or 0-200000 Wh)
        uint16_t capacity_limit;                // MQTT_CMD_CAPACITY_LIMIT (0=disabled, max 25000W)
        uint16_t max_circuit_mains;             // MQTT_CMD_MAX_CIRCUIT_MAINS (0-600)
        struct { int32_t L1, L2, L3; } circuit_meter; // MQTT_CMD_CIRCUIT_METER
        uint8_t ramp_rate_divisor;               // MQTT_CMD_RAMP_RATE_DIVISOR (1-20)
        uint8_t ema_alpha;                        // MQTT_CMD_EMA_ALPHA (0-100)
        uint8_t smart_deadband;                   // MQTT_CMD_SMART_DEADBAND (0-50)
        uint8_t max_ramp_rate;                     // MQTT_CMD_MAX_RAMP_RATE (0-100, 0=disabled)
        uint8_t oscillation_boost_max;             // MQTT_CMD_OSCILLATION_BOOST_MAX (0-20)
        uint8_t idiff_ema_weight;                  // MQTT_CMD_IDIFF_EMA_WEIGHT (1-4)
        struct {                                    // MQTT_CMD_LINKY_METER
            uint8_t is_hp;
            uint8_t is_hc;
            uint8_t is_power_overflow;
            float voltage_l1;
            float current_l1;
            float apparent_power;
            float active_energy_total;
            float contracted_power;
            float total_hp;
            float total_hc;
        } linky_meter;
    };
} mqtt_command_t;

// Linky-over-MQTT feed is considered stale (and MainsMeter.linky.available
// should be cleared) after this many seconds without a /Set/LinkyMeter message.
#define LINKY_MQTT_STALE_TIMEOUT_S 300

// EnableC2 string values for backwards-compatible parsing
#define MQTT_ENABLE_C2_COUNT 5
extern const char *mqtt_enable_c2_strings[MQTT_ENABLE_C2_COUNT];

// Parse a topic+payload into a structured command.
// prefix: the MQTT prefix (e.g. "SmartEVSE/123456")
// Returns true if a valid command was parsed, false if unrecognized/invalid.
bool mqtt_parse_command(const char *prefix, const char *topic,
                        const char *payload, mqtt_command_t *out);

// Parse "L1:L2:L3" mains meter format. Returns true on success.
bool mqtt_parse_mains_meter(const char *payload, int32_t *L1, int32_t *L2, int32_t *L3);

// Parse "L1:L2:L3:W:WH" EV meter format. Returns true on success.
bool mqtt_parse_ev_meter(const char *payload, int32_t *L1, int32_t *L2, int32_t *L3,
                         int32_t *W, int32_t *Wh);

// Parse "R,G,B" color format. Returns true on success.
bool mqtt_parse_rgb(const char *payload, uint8_t *r, uint8_t *g, uint8_t *b);

// Parse "is_hp:is_hc:is_power_overflow:voltage_l1:current_l1:apparent_power:
// active_energy_total:contracted_power:total_hp:total_hc" Linky telemetry feed
// (fed by an external MQTT bridge, e.g. a Linky teleinfo-to-MQTT gateway).
// Returns true on success.
bool mqtt_parse_linky_meter(const char *payload, uint8_t *is_hp, uint8_t *is_hc,
                            uint8_t *is_power_overflow, float *voltage_l1, float *current_l1,
                            float *apparent_power, float *active_energy_total,
                            float *contracted_power, float *total_hp, float *total_hc);

// Returns true if a Linky-over-MQTT feed with the given elapsed time since its
// last update should be considered stale (LINKY_MQTT_STALE_TIMEOUT_S).
bool mqtt_linky_meter_is_stale(uint32_t elapsed_s);

#ifdef __cplusplus
}
#endif

#endif
