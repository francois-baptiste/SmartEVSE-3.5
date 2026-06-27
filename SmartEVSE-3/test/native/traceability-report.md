# SmartEVSE-3 Traceability Report

**78 features** | **1187 scenarios** | **1187 with requirement IDs** | **100% coverage**

---

## Summary

| Feature | Scenarios | With Req ID | Coverage |
|---------|-----------|-------------|----------|
| API Mains Staleness Detection | 12 | 12 | 100% |
| HomeWizard P1 Manual IP Fallback | 3 | 3 | 100% |
| Authorization & Access Control | 22 | 22 | 100% |
| Bridge Transaction Integrity | 8 | 8 | 100% |
| Capacity Tariff Peak Tracking | 26 | 26 | 100% |
| Load Balancing — CAPACITY integration | 3 | 3 | 100% |
| CircuitMeter Subpanel Protection | 5 | 5 | 100% |
| Diagnostic Telemetry | 51 | 51 | 100% |
| Dual-EVSE Load Balancing | 23 | 23 | 100% |
| End-to-End Charging | 13 | 13 | 100% |
| Error Handling & Safety | 29 | 29 | 100% |
| Fidelity: DisconnectTimeCounter | 3 | 3 | 100% |
| Fidelity: PilotDisconnectTime | 2 | 2 | 100% |
| Fidelity: Fall-through behavior | 5 | 5 | 100% |
| Fidelity: ACTSTART no pilot check | 2 | 2 | 100% |
| Fidelity: Modem states not in tick_10ms | 1 | 1 | 100% |
| Fidelity: Handler ordering | 1 | 1 | 100% |
| Fidelity: Config field | 2 | 2 | 100% |
| HTTP API Color Parsing | 3 | 3 | 100% |
| HTTP API Input Validation | 24 | 24 | 100% |
| HTTP API Validation | 23 | 23 | 100% |
| HTTP API Settings Validation | 7 | 7 | 100% |
| EVCC IEC 61851 State Mapping | 11 | 11 | 100% |
| EVCC Charging Enabled | 3 | 3 | 100% |
| EVCC Phase Switch Validation | 7 | 7 | 100% |
| Unsigned firmware upload | 1 | 1 | 100% |
| HTTP Auth | 24 | 24 | 100% |
| LB Convergence | 47 | 47 | 100% |
| LED Status Indication | 15 | 15 | 100% |
| LED Color Configuration | 4 | 4 | 100% |
| LED Color — Public Scheme | 14 | 14 | 100% |
| Load Balancing | 18 | 18 | 100% |
| Meter Decoding | 36 | 36 | 100% |
| Meter Timeout & Recovery | 12 | 12 | 100% |
| Meter Telemetry | 13 | 13 | 100% |
| Metering Diagnostics | 7 | 7 | 100% |
| Modbus Frame Decoding | 15 | 15 | 100% |
| Modbus Frame Logging | 10 | 10 | 100% |
| Mode Synchronization | 8 | 8 | 100% |
| Modem / ISO15118 Negotiation | 29 | 29 | 100% |
| MQTT Command Parsing | 35 | 35 | 100% |
| MQTT Input Validation | 46 | 46 | 100% |
| MQTT Meter Parsing | 7 | 7 | 100% |
| MQTT Color Parsing | 4 | 4 | 100% |
| Solar Debug Telemetry | 10 | 10 | 100% |
| Capacity Tariff MQTT | 7 | 7 | 100% |
| MQTT Change-Only Publishing | 10 | 10 | 100% |
| MQTT SoC Parsing | 13 | 13 | 100% |
| MQTT SoC Input Validation | 13 | 13 | 100% |
| Multi-Node Load Balancing | 14 | 14 | 100% |
| Multi-Node Solar Charging | 24 | 24 | 100% |
| OCPP Current Limiting | 12 | 12 | 100% |
| OCPP Authorization | 22 | 22 | 100% |
| OCPP Connector State | 18 | 18 | 100% |
| OCPP Connector Lock | 11 | 11 | 100% |
| OCPP IEC 61851 Status Mapping | 11 | 11 | 100% |
| OCPP Load Balancing Exclusivity | 9 | 9 | 100% |
| OCPP Silence Detection | 10 | 10 | 100% |
| OCPP RFID Formatting | 9 | 9 | 100% |
| OCPP Settings Validation | 36 | 36 | 100% |
| OCPP Telemetry | 7 | 7 | 100% |
| Operating Modes | 21 | 21 | 100% |
| P1 Meter Parsing | 22 | 22 | 100% |
| Phase Switching | 26 | 26 | 100% |
| PIN Rate Limit | 12 | 12 | 100% |
| Power Availability | 22 | 22 | 100% |
| Reconnect backoff | 8 | 8 | 100% |
| Priority-Based Power Scheduling | 29 | 29 | 100% |
| Serial Message Parsing | 9 | 9 | 100% |
| Serial Input Validation | 10 | 10 | 100% |
| Battery Current Calculation | 7 | 7 | 100% |
| Current Sum Calculation | 5 | 5 | 100% |
| Charge Session Logging | 18 | 18 | 100% |
| Charge Session JSON Export | 7 | 7 | 100% |
| Solar Balancing | 49 | 49 | 100% |
| IEC 61851-1 State Transitions | 29 | 29 | 100% |
| 10ms Tick Processing | 20 | 20 | 100% |
| 1-Second Tick Processing | 23 | 23 | 100% |
| **TOTAL** | **1187** | **1187** | **100%** |

## API Mains Staleness Detection

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-020` | Staleness timer counts down each second and sets stale flag on expiry | `test_staleness_timer_countdown` | `test_api_staleness.c:1` |
| `REQ-MTR-021` | When API data goes stale, all phases fall back to MaxMains | `test_staleness_fallback_to_maxmains` | `test_api_staleness.c:58` |
| `REQ-MTR-022` | Stale flag is cleared when staleness timer is reset (data received) | `test_staleness_recovery_on_timer_reset` | `test_api_staleness.c:92` |
| `REQ-MTR-023` | Staleness check is skipped for non-API metering modes | `test_staleness_skipped_for_non_api` | `test_api_staleness.c:118` |
| `REQ-MTR-024` | Staleness detection is disabled when api_mains_timeout is 0 | `test_staleness_disabled_when_timeout_zero` | `test_api_staleness.c:142` |
| `REQ-MTR-025` | CT_NOCOMM is suppressed when API staleness detection is active | `test_ct_nocomm_suppressed_for_api_with_staleness` | `test_api_staleness.c:166` |
| `REQ-MTR-026` | CT_NOCOMM fires normally when staleness detection is disabled for API mode | `test_ct_nocomm_fires_when_staleness_disabled` | `test_api_staleness.c:190` |
| `REQ-MTR-027` | Stale flag is set only once, not repeatedly overwriting Irms each tick | `test_staleness_only_fires_once` | `test_api_staleness.c:214` |
| `REQ-MQTT-030` | Parse MainsMeterTimeout MQTT command with valid value | `test_mqtt_parse_staleness_timeout_valid` | `test_api_staleness.c:247` |
| `REQ-MQTT-031` | Parse MainsMeterTimeout MQTT command with 0 (disabled) | `test_mqtt_parse_staleness_timeout_disabled` | `test_api_staleness.c:262` |
| `REQ-MQTT-032` | Reject MainsMeterTimeout values outside valid range | `test_mqtt_parse_staleness_timeout_too_low` | `test_api_staleness.c:277` |
| `REQ-MQTT-033` | Reject MainsMeterTimeout values above maximum | `test_mqtt_parse_staleness_timeout_too_high` | `test_api_staleness.c:290` |

<details>
<summary>Detailed steps (12 scenarios)</summary>

### Staleness timer counts down each second and sets stale flag on expiry
**Requirement:** `REQ-MTR-020`

- **Given** EVSE in Smart mode with MainsMeterType=EM_API_METER and api_mains_timeout=3
- **When** 3 seconds elapse with no data update
- **Then** api_mains_stale is set to true

### When API data goes stale, all phases fall back to MaxMains
**Requirement:** `REQ-MTR-021`

- **Given** EVSE in Smart mode with API metering, MaxMains=25, current readings are 10A/phase
- **When** Staleness timer expires
- **Then** MainsMeterIrms for all 3 phases is set to MaxMains * 10 (250 dA)

### Stale flag is cleared when staleness timer is reset (data received)
**Requirement:** `REQ-MTR-022`

- **Given** EVSE in API mode with stale data (api_mains_stale=true, timer=0)
- **When** External code resets api_mains_staleness_timer to a positive value
- **Then** api_mains_stale is cleared on the next tick

### Staleness check is skipped for non-API metering modes
**Requirement:** `REQ-MTR-023`

- **Given** EVSE in Smart mode with MainsMeterType=1 (Sensorbox) and api_mains_timeout=120
- **When** Staleness timer is 0
- **Then** api_mains_stale remains false

### Staleness detection is disabled when api_mains_timeout is 0
**Requirement:** `REQ-MTR-024`

- **Given** EVSE in Smart mode with API metering and api_mains_timeout=0
- **When** Staleness timer reaches 0
- **Then** api_mains_stale remains false, normal CT_NOCOMM applies

### CT_NOCOMM is suppressed when API staleness detection is active
**Requirement:** `REQ-MTR-025`

- **Given** EVSE in Smart mode with API metering, staleness enabled, MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM is NOT set (staleness mechanism handles the timeout instead)

### CT_NOCOMM fires normally when staleness detection is disabled for API mode
**Requirement:** `REQ-MTR-026`

- **Given** EVSE in Smart mode with API metering, api_mains_timeout=0, MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM IS set (normal timeout behavior)

### Stale flag is set only once, not repeatedly overwriting Irms each tick
**Requirement:** `REQ-MTR-027`

- **Given** EVSE in API mode, already stale
- **When** Another tick occurs while stale
- **Then** Irms values are not overwritten again (flag already set)

### Parse MainsMeterTimeout MQTT command with valid value
**Requirement:** `REQ-MQTT-030`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MainsMeterTimeout with payload "120"
- **Then** Command type is MQTT_CMD_MAINS_METER_TIMEOUT with value 120

### Parse MainsMeterTimeout MQTT command with 0 (disabled)
**Requirement:** `REQ-MQTT-031`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MainsMeterTimeout with payload "0"
- **Then** Command type is MQTT_CMD_MAINS_METER_TIMEOUT with value 0

### Reject MainsMeterTimeout values outside valid range
**Requirement:** `REQ-MQTT-032`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MainsMeterTimeout with payload "5" (below minimum 10)
- **Then** Parsing returns false

### Reject MainsMeterTimeout values above maximum
**Requirement:** `REQ-MQTT-033`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MainsMeterTimeout with payload "4000" (above maximum 3600)
- **Then** Parsing returns false

</details>

---

## HomeWizard P1 Manual IP Fallback

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-034` | Parse HomeWizardIP MQTT command with valid IP | `test_mqtt_parse_homewizard_ip_valid` | `test_api_staleness.c:305` |
| `REQ-MQTT-035` | Parse HomeWizardIP with empty string clears manual IP (re-enable mDNS) | `test_mqtt_parse_homewizard_ip_empty` | `test_api_staleness.c:320` |
| `REQ-MQTT-036` | Reject HomeWizardIP that exceeds buffer size | `test_mqtt_parse_homewizard_ip_too_long` | `test_api_staleness.c:335` |

<details>
<summary>Detailed steps (3 scenarios)</summary>

### Parse HomeWizardIP MQTT command with valid IP
**Requirement:** `REQ-MQTT-034`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/HomeWizardIP with payload "192.168.1.50"
- **Then** Command type is MQTT_CMD_HOMEWIZARD_IP with the IP string

### Parse HomeWizardIP with empty string clears manual IP (re-enable mDNS)
**Requirement:** `REQ-MQTT-035`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/HomeWizardIP with empty payload
- **Then** Command type is MQTT_CMD_HOMEWIZARD_IP with empty string

### Reject HomeWizardIP that exceeds buffer size
**Requirement:** `REQ-MQTT-036`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/HomeWizardIP with a 16+ character payload
- **Then** Parsing returns false

</details>

---

## Authorization & Access Control

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-AUTH-001` | Setting access to ON stores the authorization status | `test_set_access_on` | `test_authorization.c:1` |
| `REQ-AUTH-002` | Setting access to OFF stores the authorization status | `test_set_access_off` | `test_authorization.c:40` |
| `REQ-AUTH-003` | Revoking access during charging suspends the session (C -> C1) | `test_set_access_off_from_C_goes_C1` | `test_authorization.c:54` |
| `REQ-AUTH-004` | Pausing access during charging suspends the session (C -> C1) | `test_set_access_pause_from_C_goes_C1` | `test_authorization.c:73` |
| `REQ-AUTH-005` | Revoking access in STATE_B moves to waiting state (B -> B1) | `test_set_access_off_from_B_goes_B1` | `test_authorization.c:91` |
| `REQ-AUTH-006` | Revoking access during modem request aborts to B1 | `test_set_access_off_from_modem_request_goes_B1` | `test_authorization.c:108` |
| `REQ-AUTH-007` | Revoking access during modem wait aborts to B1 | `test_set_access_off_from_modem_wait_goes_B1` | `test_authorization.c:125` |
| `REQ-AUTH-008` | Revoking access in STATE_A has no state transition side effect | `test_set_access_off_from_A_stays_A` | `test_authorization.c:142` |
| `REQ-AUTH-009` | Granting access in STATE_B1 does not auto-recover to STATE_B | `test_set_access_on_from_B1_does_not_auto_recover` | `test_authorization.c:157` |
| `REQ-AUTH-010` | OCPP current limit below MinCurrent blocks current availability | `test_ocpp_blocks_current_availability` | `test_authorization.c:175` |
| `REQ-AUTH-011` | OCPP current limit above MinCurrent allows current availability | `test_ocpp_allows_when_limit_sufficient` | `test_authorization.c:192` |
| `REQ-AUTH-012` | Negative OCPP current limit is ignored (not set) | `test_ocpp_negative_limit_ignored` | `test_authorization.c:210` |
| `REQ-AUTH-014` | Access timer counts down each second while in STATE_A | `test_access_timer_counts_down_in_state_A` | `test_authorization.c:229` |
| `REQ-AUTH-015` | Access timer expiry revokes authorization | `test_access_timer_expires_turns_off` | `test_authorization.c:266` |
| `REQ-AUTH-016` | Access timer is cleared when EVSE is not in STATE_A | `test_access_timer_cleared_when_not_in_A` | `test_authorization.c:284` |
| `REQ-AUTH-017` | No STATE_A to STATE_B transition without authorization | `test_no_A_to_B_without_access` | `test_authorization.c:303` |
| `REQ-AUTH-018` | No STATE_B to STATE_C transition after access revoked mid-session | `test_no_B_to_C_without_access` | `test_authorization.c:318` |
| `REQ-AUTH-019` | AccessStatus is cleared immediately when a charging session ends | `test_access_status_cleared_on_session_end` | `test_authorization.c:340` |
| `REQ-AUTH-020` | AccessStatus is cleared immediately when session ends from STATE_C1 | `test_access_status_cleared_on_session_end_from_c1` | `test_authorization.c:365` |
| `REQ-AUTH-021` | AccessStatus cleared on Tesla-style disconnect (C → B → A) | `test_access_status_cleared_on_tesla_disconnect_c_b_a` | `test_authorization.c:390` |
| `REQ-AUTH-022` | AccessStatus cleared on solar-stop disconnect (C1 → B1 → A) | `test_access_status_cleared_on_disconnect_from_b1` | `test_authorization.c:420` |
| `REQ-AUTH-023` | Tesla disconnect then new car + RFID swipe starts session correctly | `test_tesla_disconnect_then_new_car_rfid_starts_session` | `test_authorization.c:452` |

<details>
<summary>Detailed steps (22 scenarios)</summary>

### Setting access to ON stores the authorization status
**Requirement:** `REQ-AUTH-001`

- **Given** The EVSE is initialised in basic configuration
- **When** evse_set_access is called with ON
- **Then** AccessStatus is set to ON

### Setting access to OFF stores the authorization status
**Requirement:** `REQ-AUTH-002`

- **Given** The EVSE is initialised in basic configuration
- **When** evse_set_access is called with OFF
- **Then** AccessStatus is set to OFF

### Revoking access during charging suspends the session (C -> C1)
**Requirement:** `REQ-AUTH-003`

- **Given** The EVSE is in STATE_C (charging) with AccessStatus ON
- **When** evse_set_access is called with OFF
- **Then** The state transitions to STATE_C1 and AccessStatus is OFF

### Pausing access during charging suspends the session (C -> C1)
**Requirement:** `REQ-AUTH-004`

- **Given** The EVSE is in STATE_C (charging) with AccessStatus ON
- **When** evse_set_access is called with PAUSE
- **Then** The state transitions to STATE_C1 and AccessStatus is PAUSE

### Revoking access in STATE_B moves to waiting state (B -> B1)
**Requirement:** `REQ-AUTH-005`

- **Given** The EVSE is in STATE_B (connected) with AccessStatus ON
- **When** evse_set_access is called with OFF
- **Then** The state transitions to STATE_B1 (waiting)

### Revoking access during modem request aborts to B1
**Requirement:** `REQ-AUTH-006`

- **Given** The EVSE is in STATE_MODEM_REQUEST with AccessStatus ON
- **When** evse_set_access is called with OFF
- **Then** The state transitions to STATE_B1 (waiting)

### Revoking access during modem wait aborts to B1
**Requirement:** `REQ-AUTH-007`

- **Given** The EVSE is in STATE_MODEM_WAIT with AccessStatus ON
- **When** evse_set_access is called with OFF
- **Then** The state transitions to STATE_B1 (waiting)

### Revoking access in STATE_A has no state transition side effect
**Requirement:** `REQ-AUTH-008`

- **Given** The EVSE is in STATE_A (disconnected)
- **When** evse_set_access is called with OFF
- **Then** The state remains STATE_A

### Granting access in STATE_B1 does not auto-recover to STATE_B
**Requirement:** `REQ-AUTH-009`

- **Given** The EVSE is in STATE_B1 (waiting)
- **When** evse_set_access is called with ON
- **Then** The state remains STATE_B1 (no automatic recovery)

### OCPP current limit below MinCurrent blocks current availability
**Requirement:** `REQ-AUTH-010`

- **Given** OCPP mode is enabled with OcppCurrentLimit=3A and MinCurrent=6A
- **When** evse_is_current_available is called
- **Then** The function returns 0 (current not available)

### OCPP current limit above MinCurrent allows current availability
**Requirement:** `REQ-AUTH-011`

- **Given** OCPP mode is enabled with OcppCurrentLimit=10A and MinCurrent=6A
- **When** evse_is_current_available is called
- **Then** The function returns 1 (current available)

### Negative OCPP current limit is ignored (not set)
**Requirement:** `REQ-AUTH-012`

- **Given** OCPP mode is enabled with OcppCurrentLimit=-1 (unset)
- **When** evse_is_current_available is called
- **Then** The function returns 1 (limit not applied)

### Access timer counts down each second while in STATE_A
**Requirement:** `REQ-AUTH-014`

- **Given** The EVSE has AccessStatus ON, RFIDReader=2, and AccessTimer=0
- **Given** The EVSE is in STATE_A with AccessTimer=5
- **When** A 12V pilot signal is received (EV disconnects)
- **When** One second tick occurs
- **Then** AccessTimer is set to RFIDLOCKTIME
- **Then** AccessTimer decrements to 4

### Access timer expiry revokes authorization
**Requirement:** `REQ-AUTH-015`

- **Given** The EVSE is in STATE_A with AccessTimer=1 and AccessStatus ON
- **When** One second tick occurs (timer reaches 0)
- **Then** AccessStatus is set to OFF (authorization revoked)

### Access timer is cleared when EVSE is not in STATE_A
**Requirement:** `REQ-AUTH-016`

- **Given** The EVSE is in STATE_B with AccessTimer=30
- **When** One second tick occurs
- **Then** AccessTimer is reset to 0

### No STATE_A to STATE_B transition without authorization
**Requirement:** `REQ-AUTH-017`

- **Given** The EVSE is in STATE_A with AccessStatus OFF
- **When** A 9V pilot signal is received (vehicle connected)
- **Then** The state remains STATE_A (transition blocked)

### No STATE_B to STATE_C transition after access revoked mid-session
**Requirement:** `REQ-AUTH-018`

- **Given** The EVSE is in STATE_B with DiodeCheck passed but AccessStatus revoked to OFF
- **When** A 6V pilot signal is sustained for 500ms
- **Then** The state does NOT transition to STATE_C

### AccessStatus is cleared immediately when a charging session ends
**Requirement:** `REQ-AUTH-019`

- **Given** EVSE is in STATE_C with AccessStatus ON and RFID reader enabled (EnableOne)
- **When** PILOT_12V is received (car disconnects — e.g. Tesla door handle)
- **Then** AccessStatus is OFF and AccessTimer is 0 immediately upon transition to STATE_A

### AccessStatus is cleared immediately when session ends from STATE_C1
**Requirement:** `REQ-AUTH-020`

- **Given** EVSE is in STATE_C1 (winding down charge) with AccessStatus ON
- **When** PILOT_12V is received (car disconnects during C1 wind-down)
- **Then** AccessStatus is OFF and AccessTimer is 0 on transition to STATE_A

### AccessStatus cleared on Tesla-style disconnect (C → B → A)
**Requirement:** `REQ-AUTH-021`

- **Given** EVSE is in STATE_C with AccessStatus ON and RFID reader enabled
- **When** Car transitions to STATE_B (CP → 9V), then to STATE_A (CP → 12V)
- **Then** AccessStatus is OFF and AccessTimer is 0 upon reaching STATE_A

### AccessStatus cleared on solar-stop disconnect (C1 → B1 → A)
**Requirement:** `REQ-AUTH-022`

- **Given** EVSE is in STATE_B1 (transitioned from C1 after solar stop) with AccessStatus ON
- **When** Pilot disconnect timer expires, then car disconnects (CP → 12V)
- **Then** AccessStatus is OFF and AccessTimer is 0 upon reaching STATE_A

### Tesla disconnect then new car + RFID swipe starts session correctly
**Requirement:** `REQ-AUTH-023`

- **Given** EVSE charged Car A in STATE_C, RFIDReader=EnableOne, AccessStatus=ON
- **When** Car A does Tesla-style disconnect (C→B→A), Car B plugs in, user swipes RFID
- **Then** Car B is blocked until RFID swipe, then RFID swipe sets AccessStatus ON and charging starts

</details>

---

## Bridge Transaction Integrity

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SM-100` | Bridge lock/unlock API is callable | `test_bridge_lock_unlock_callable` | `test_bridge_transaction.c:1` |
| `REQ-AUTH-024` | AccessTimer counts down to zero over 60 sequential tick_1s calls | `test_access_timer_full_countdown` | `test_bridge_transaction.c:54` |
| `REQ-AUTH-025` | AccessTimer countdown survives interleaved tick_10ms calls | `test_access_timer_survives_interleaved_ticks` | `test_bridge_transaction.c:83` |
| `REQ-AUTH-026` | AccessTimer is not re-armed after expiry | `test_access_timer_not_rearmed_after_expiry` | `test_bridge_transaction.c:123` |
| `REQ-AUTH-027` | OCPP setAccess(ON) triggers A→B transition on next tick_10ms | `test_set_access_on_enables_a_to_b` | `test_bridge_transaction.c:153` |
| `REQ-AUTH-028` | AccessStatus ON persists through multiple tick_10ms cycles | `test_access_status_persists_through_ticks` | `test_bridge_transaction.c:181` |
| `REQ-AUTH-029` | Full OCPP charge cycle: authorize → charge → disconnect → new authorize | `test_ocpp_full_cycle_two_users` | `test_bridge_transaction.c:205` |
| `REQ-AUTH-030` | AccessTimer full countdown with interleaved 10ms ticks (real timing) | `test_access_timer_real_world_timing` | `test_bridge_transaction.c:277` |

<details>
<summary>Detailed steps (8 scenarios)</summary>

### Bridge lock/unlock API is callable
**Requirement:** `REQ-SM-100`

- **Given** The test environment (native build, no FreeRTOS)
- **When** evse_bridge_lock and evse_bridge_unlock are called
- **Then** They complete without error (no-ops in native builds)

### AccessTimer counts down to zero over 60 sequential tick_1s calls
**Requirement:** `REQ-AUTH-024`

- **Given** EVSE in STATE_A with AccessStatus ON and AccessTimer armed to 60
- **When** tick_1s is called 60 times (simulating 60 seconds with no concurrent interference)
- **Then** AccessTimer reaches 0 and AccessStatus is set to OFF

### AccessTimer countdown survives interleaved tick_10ms calls
**Requirement:** `REQ-AUTH-025`

- **Given** EVSE in STATE_A with AccessTimer=2, pilot at 12V
- **When** tick_10ms and tick_1s are called in alternating sequence
- **Then** AccessTimer still reaches 0 and AccessStatus is cleared

### AccessTimer is not re-armed after expiry
**Requirement:** `REQ-AUTH-026`

- **Given** EVSE in STATE_A after AccessTimer just expired (AccessStatus=OFF, AccessTimer=0)
- **When** tick_10ms runs with PILOT_12V
- **Then** AccessTimer stays 0 (re-arm requires AccessStatus==ON)

### OCPP setAccess(ON) triggers A→B transition on next tick_10ms
**Requirement:** `REQ-AUTH-027`

- **Given** EVSE in STATE_A with AccessStatus=OFF, car plugged in (pilot 9V)
- **When** setAccess(ON) is called, then tick_10ms runs
- **Then** State transitions from A to B (AccessStatus=ON enables the transition)

### AccessStatus ON persists through multiple tick_10ms cycles
**Requirement:** `REQ-AUTH-028`

- **Given** EVSE in STATE_B with AccessStatus=ON (car connected, authorized)
- **When** tick_10ms is called repeatedly with PILOT_9V
- **Then** AccessStatus remains ON (not corrupted by tick processing)

### Full OCPP charge cycle: authorize → charge → disconnect → new authorize
**Requirement:** `REQ-AUTH-029`

- **Given** EVSE idle in STATE_A, OCPP mode, car not connected
- **When** First user charges and disconnects, then second user plugs in and authorizes
- **Then** Second user's authorization succeeds and A→B transition occurs

### AccessTimer full countdown with interleaved 10ms ticks (real timing)
**Requirement:** `REQ-AUTH-030`

- **Given** EVSE in STATE_A, AccessStatus=ON, AccessTimer=60, pilot 12V
- **When** 60 rounds of (100x tick_10ms + 1x tick_1s) simulate real-world timing
- **Then** AccessTimer reaches 0 and AccessStatus transitions to OFF

</details>

---

## Capacity Tariff Peak Tracking

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-CAP-001` | Basic 15-minute window averaging at constant power | `test_capacity_basic_window_avg` | `test_capacity_peak.c:1` |
| `REQ-CAP-002` | Variable power within a single window | `test_capacity_variable_power_window` | `test_capacity_peak.c:53` |
| `REQ-CAP-003` | Monthly peak tracks highest window | `test_capacity_monthly_peak_tracking` | `test_capacity_peak.c:78` |
| `REQ-CAP-004` | Month rollover resets monthly peak | `test_capacity_month_rollover` | `test_capacity_peak.c:109` |
| `REQ-CAP-005` | Headroom calculation mid-window | `test_capacity_headroom_mid_window` | `test_capacity_peak.c:141` |
| `REQ-CAP-006` | Headroom to deciamps conversion for 3-phase | `test_capacity_headroom_to_da_3phase` | `test_capacity_peak.c:158` |
| `REQ-CAP-007` | Headroom to deciamps conversion for 1-phase | `test_capacity_headroom_to_da_1phase` | `test_capacity_peak.c:185` |
| `REQ-CAP-008` | Disabled when limit equals zero | `test_capacity_disabled_returns_max_headroom` | `test_capacity_peak.c:199` |
| `REQ-CAP-009` | JSON output contains all key fields | `test_capacity_json_output` | `test_capacity_peak.c:219` |
| `REQ-CAP-010` | Negative power from solar export is averaged correctly | `test_capacity_negative_power_solar` | `test_capacity_peak.c:248` |
| `REQ-CAP-011` | Zero-length buffer returns -1 | `test_capacity_json_zero_buffer` | `test_capacity_peak.c:274` |
| `REQ-CAP-012` | NULL state returns -1 for JSON and 0 for getters | `test_capacity_null_state` | `test_capacity_peak.c:288` |
| `REQ-CAP-013` | Headroom to deciamps with zero phases returns zero | `test_capacity_headroom_to_da_zero_phases` | `test_capacity_peak.c:307` |
| `REQ-CAP-014` | JSON with NULL buffer returns -1 | `test_capacity_json_null_buffer` | `test_capacity_peak.c:320` |
| `REQ-CAP-015` | JSON with too-small buffer returns -1 | `test_capacity_json_small_buffer` | `test_capacity_peak.c:334` |
| `REQ-CAP-016` | Year rollover also resets monthly peak | `test_capacity_year_rollover` | `test_capacity_peak.c:349` |
| `REQ-CAP-017` | Window not valid until first window completes | `test_capacity_window_not_valid_initially` | `test_capacity_peak.c:372` |
| `REQ-CAP-018` | Headroom decreases as window fills with high power | `test_capacity_headroom_decreases_with_high_power` | `test_capacity_peak.c:392` |
| `REQ-CAP-020` | IsetBalanced clamped by capacity headroom guard rail | `test_capacity_headroom_clamps_iset_balanced` | `test_capacity_sm.c:1` |
| `REQ-CAP-021` | Unconstrained when headroom is INT16_MAX (default) | `test_capacity_unconstrained_at_int16_max` | `test_capacity_sm.c:77` |
| `REQ-CAP-022` | Negative headroom clamps IsetBalanced and triggers shortage | `test_capacity_negative_headroom_clamps_down` | `test_capacity_sm.c:119` |
| `REQ-CAP-023` | Capacity headroom is tighter constraint than MaxSumMains | `test_capacity_headroom_tighter_than_max_sum_mains` | `test_capacity_sm.c:133` |
| `REQ-CAP-024` | evse_init sets CapacityHeadroom_da to INT16_MAX by default | `test_capacity_init_default` | `test_capacity_sm.c:159` |
| `REQ-CAP-025` | Capacity headroom clamps IsetBalanced when new EVSE joins in smart mode | `test_capacity_headroom_master_new_evse` | `test_capacity_sm.c:196` |
| `REQ-CAP-026` | Single-phase charging gets full headroom on one phase | `test_capacity_headroom_single_phase` | `test_capacity_sm.c:283` |
| `REQ-CAP-027` | Moderate capacity headroom allows charging above minimum | `test_capacity_moderate_headroom` | `test_capacity_sm.c:307` |

<details>
<summary>Detailed steps (26 scenarios)</summary>

### Basic 15-minute window averaging at constant power
**Requirement:** `REQ-CAP-001`

- **Given** A capacity state initialized with limit 5000W
- **When** 900 ticks of capacity_tick_1s with constant 3000W
- **Then** window_avg_w equals 3000 and headroom reflects remaining capacity

### Variable power within a single window
**Requirement:** `REQ-CAP-002`

- **Given** A capacity state with limit 5000W
- **When** 450 ticks at 2000W followed by 450 ticks at 4000W
- **Then** window_avg_w equals 3000

### Monthly peak tracks highest window
**Requirement:** `REQ-CAP-003`

- **Given** A fresh capacity state in month 3
- **When** Three windows complete with averages 3000W, 5000W, 4000W
- **Then** monthly_peak_w equals 5000

### Month rollover resets monthly peak
**Requirement:** `REQ-CAP-004`

- **Given** A state with monthly_peak_w of 5000 in month 3
- **When** capacity_tick_1s is called with month 4
- **Then** monthly_peak_w resets to 0 and new tracking begins

### Headroom calculation mid-window
**Requirement:** `REQ-CAP-005`

- **Given** A capacity state with limit 5000W, mid-window at 450s with running avg 3500W
- **When** capacity_get_headroom_w is called
- **Then** Headroom reflects how much more can be consumed in remaining window time

### Headroom to deciamps conversion for 3-phase
**Requirement:** `REQ-CAP-006`

- **Given** A headroom of 2300W
- **When** capacity_headroom_to_da is called with 3 phases
- **Then** Returns 33 deciamps (2300 * 10 / (230 * 3) = 33.3 -> 33)

### Headroom to deciamps conversion for 1-phase
**Requirement:** `REQ-CAP-007`

- **Given** A headroom of 2300W
- **When** capacity_headroom_to_da is called with 1 phase
- **Then** Returns 100 deciamps (2300 * 10 / 230 = 100)

### Disabled when limit equals zero
**Requirement:** `REQ-CAP-008`

- **Given** A capacity state with limit_w set to 0
- **When** capacity_get_headroom_w is called
- **Then** Returns INT32_MAX indicating no constraint

### JSON output contains all key fields
**Requirement:** `REQ-CAP-009`

- **Given** A state with valid window and peak data
- **When** capacity_to_json is called
- **Then** JSON contains limit_w, window_avg_w, monthly_peak_w, headroom_w

### Negative power from solar export is averaged correctly
**Requirement:** `REQ-CAP-010`

- **Given** A capacity state with limit 5000W
- **When** 900 ticks with -1000W (net solar export)
- **Then** window_avg_w equals -1000 and headroom is limit + 1000 = 6000

### Zero-length buffer returns -1
**Requirement:** `REQ-CAP-011`

- **Given** A valid capacity state
- **When** capacity_to_json is called with bufsz 0
- **Then** Returns -1

### NULL state returns -1 for JSON and 0 for getters
**Requirement:** `REQ-CAP-012`

- **Given** A NULL state pointer
- **When** capacity_to_json and getter functions are called
- **Then** JSON returns -1, getters return 0

### Headroom to deciamps with zero phases returns zero
**Requirement:** `REQ-CAP-013`

- **Given** A headroom value
- **When** capacity_headroom_to_da is called with 0 phases
- **Then** Returns 0

### JSON with NULL buffer returns -1
**Requirement:** `REQ-CAP-014`

- **Given** A valid capacity state
- **When** capacity_to_json is called with NULL buffer
- **Then** Returns -1

### JSON with too-small buffer returns -1
**Requirement:** `REQ-CAP-015`

- **Given** A valid capacity state
- **When** capacity_to_json is called with a very small buffer
- **Then** Returns -1 (truncation detected)

### Year rollover also resets monthly peak
**Requirement:** `REQ-CAP-016`

- **Given** A state with peak in month 12 year_offset 2
- **When** tick is called with month 1 year_offset 3
- **Then** Monthly peak resets to 0

### Window not valid until first window completes
**Requirement:** `REQ-CAP-017`

- **Given** A freshly initialized capacity state
- **When** Only 100 ticks have elapsed (no complete window)
- **Then** window_valid is 0 and window_avg_w is 0

### Headroom decreases as window fills with high power
**Requirement:** `REQ-CAP-018`

- **Given** A capacity state with limit 5000W
- **When** Power consumption exceeds limit for first half of window
- **Then** Headroom in second half is reduced to compensate

### IsetBalanced clamped by capacity headroom guard rail
**Requirement:** `REQ-CAP-020`

- **Given** ctx already charging at 160 deciamps, CapacityHeadroom_da=30 (3.0A total)
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced is clamped to at most 30/3=10 deciamps per phase by guard rail

### Unconstrained when headroom is INT16_MAX (default)
**Requirement:** `REQ-CAP-021`

- **Given** ctx already charging at 160 deciamps with CapacityHeadroom_da = INT16_MAX
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced is not reduced by capacity headroom

### Negative headroom clamps IsetBalanced and triggers shortage
**Requirement:** `REQ-CAP-022`

- **Given** ctx already charging with CapacityHeadroom_da = -50 (over capacity limit)
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced is clamped to MinCurrent floor (shortage path)

### Capacity headroom is tighter constraint than MaxSumMains
**Requirement:** `REQ-CAP-023`

- **Given** MaxSumMains=75A, CapacityHeadroom_da=30 (3.0A), charging at 160 deciamps
- **When** evse_calc_balanced_current runs
- **Then** CapacityHeadroom wins as the tighter constraint, IsetBalanced reduced

### evse_init sets CapacityHeadroom_da to INT16_MAX by default
**Requirement:** `REQ-CAP-024`

- **Given** A freshly initialized evse_ctx_t
- **When** evse_init is called
- **Then** CapacityHeadroom_da equals INT16_MAX (unconstrained)

### Capacity headroom clamps IsetBalanced when new EVSE joins in smart mode
**Requirement:** `REQ-CAP-025`

- **Given** Master (LoadBl=1) in smart mode with CapacityHeadroom_da=60 and a new EVSE joining
- **When** evse_calc_balanced_current runs with mod=1
- **Then** IsetBalanced is clamped by capacity headroom

### Single-phase charging gets full headroom on one phase
**Requirement:** `REQ-CAP-026`

- **Given** ctx charging at 160 deciamps, CapacityHeadroom_da=120, forced single-phase
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced clamped to 120/1=120 deciamps (not 120/3=40)

### Moderate capacity headroom allows charging above minimum
**Requirement:** `REQ-CAP-027`

- **Given** ctx charging with CapacityHeadroom_da=240 (24.0A total, 8A/phase)
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced is between MinCurrent and the headroom-per-phase limit

</details>

---

## Load Balancing — CAPACITY integration

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LB-170` | MaxSumMains does NOT overwrite tighter per-phase MaxMains limit | `test_capacity_a54b07f_maxsummains_does_not_overwrite_tighter_maxmains` | `test_capacity_sm.c:329` |
| `REQ-LB-171` | MaxSumMains IS the binding constraint when it is tighter per-phase | `test_capacity_a54b07f_maxsummains_binds_when_tighter` | `test_capacity_sm.c:367` |
| `REQ-LB-172` | LimitedByMaxSumMains flag still set when MaxSumMains exceeded | `test_capacity_a54b07f_exceeded_still_flagged` | `test_capacity_sm.c:393` |

<details>
<summary>Detailed steps (3 scenarios)</summary>

### MaxSumMains does NOT overwrite tighter per-phase MaxMains limit
**Requirement:** `REQ-LB-170`

- **Given** MaxMains=10A (tight), MaxSumMains=75A (generous), charging at 160 dA
- **When** evse_calc_balanced_current runs
- **Then** IsetBalanced respects the MaxMains-based per-phase limit;

### MaxSumMains IS the binding constraint when it is tighter per-phase
**Requirement:** `REQ-LB-171`

- **Given** MaxMains=32A (generous per-phase), MaxSumMains=30A (sum = 10A/phase equiv.)
- **When** evse_calc_balanced_current runs
- **Then** MaxSumMains wins — Idifference narrowed by the per-phase equivalent (30/3=10 dA)

### LimitedByMaxSumMains flag still set when MaxSumMains exceeded
**Requirement:** `REQ-LB-172`

- **Given** ExcessMaxSumMains < 0 (MaxSumMains already exceeded)
- **When** evse_calc_balanced_current runs
- **Then** The MaxSumMainsTimer path is armed (LimitedByMaxSumMains semantics preserved)

</details>

---

## CircuitMeter Subpanel Protection

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-CIR-001` | Circuit current limiting clamps IsetBalanced on new EVSE join | `test_circuit_limiting_active` | `test_circuit_meter.c:1` |
| `REQ-CIR-002` | Circuit meter disabled has no effect on IsetBalanced | `test_circuit_meter_disabled` | `test_circuit_meter.c:82` |
| `REQ-CIR-003` | Circuit overload triggers hard shortage and increments NoCurrent | `test_circuit_overload` | `test_circuit_meter.c:104` |
| `REQ-CIR-004` | Circuit headroom tighter than MaxMains — circuit wins | `test_circuit_tighter_than_maxmains` | `test_circuit_meter.c:126` |
| `REQ-CIR-005` | Default initialization sets circuit meter fields to zero | `test_circuit_meter_init_defaults` | `test_circuit_meter.c:163` |

<details>
<summary>Detailed steps (5 scenarios)</summary>

### Circuit current limiting clamps IsetBalanced on new EVSE join
**Requirement:** `REQ-CIR-001`

- **Given** MaxCircuitMains=25A, CircuitMeterImeasured=200dA (20A), new EVSE joining (mod=1)
- **When** evse_calc_balanced_current() runs with mod=1 in smart mode
- **Then** IsetBalanced is clamped by circuit headroom below the unconstrained value

### Circuit meter disabled has no effect on IsetBalanced
**Requirement:** `REQ-CIR-002`

- **Given** MaxCircuitMains=0 (disabled), new EVSE joining (mod=1)
- **When** evse_calc_balanced_current() runs in smart mode
- **Then** IsetBalanced is determined only by MaxMains and MaxCircuit limits

### Circuit overload triggers hard shortage and increments NoCurrent
**Requirement:** `REQ-CIR-003`

- **Given** MaxCircuitMains=25A and CircuitMeterImeasured=260dA (26A, over limit)
- **When** evse_calc_balanced_current() runs with mod=1
- **Then** NoCurrent is incremented due to hard shortage from circuit overload

### Circuit headroom tighter than MaxMains — circuit wins
**Requirement:** `REQ-CIR-004`

- **Given** MaxMains=40A (plenty of headroom) but MaxCircuitMains=12A with 60dA measured
- **When** evse_calc_balanced_current() runs with mod=1
- **Then** IsetBalanced is limited by circuit headroom, not MaxMains

### Default initialization sets circuit meter fields to zero
**Requirement:** `REQ-CIR-005`

- **Given** A freshly initialized evse_ctx_t
- **When** evse_init() is called
- **Then** MaxCircuitMains and CircuitMeterImeasured are both 0

</details>

---

## Diagnostic Telemetry

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-E2E-049` | Modbus event ring initializes empty and disabled | `test_mb_init` | `test_diag_modbus.c:1` |
| `REQ-E2E-049` | Disabled ring rejects records | `test_mb_disabled_rejects` | `test_diag_modbus.c:27` |
| `REQ-E2E-049` | Record and read a single event | `test_mb_record_and_read` | `test_diag_modbus.c:42` |
| `REQ-E2E-049` | Ring wraps around after 32 events | `test_mb_wrap_around` | `test_diag_modbus.c:68` |
| `REQ-E2E-049` | Reset clears all events | `test_mb_reset` | `test_diag_modbus.c:95` |
| `REQ-E2E-049` | Error events record error code | `test_mb_error_event` | `test_diag_modbus.c:118` |
| `REQ-E2E-049` | Event struct is exactly 8 bytes | `test_mb_event_size` | `test_diag_modbus.c:139` |
| `REQ-E2E-049` | NULL ring pointer is safe for all operations | `test_mb_null_safety` | `test_diag_modbus.c:152` |
| `REQ-E2E-050` | Create synthetic capture with known parameters | `test_synthetic_capture` | `test_diag_replay.c:1` |
| `REQ-E2E-050` | Load capture from serialized binary buffer | `test_load_from_serialized_buffer` | `test_diag_replay.c:40` |
| `REQ-E2E-050` | Load from buffer detects corrupt magic | `test_load_corrupt_magic` | `test_diag_replay.c:84` |
| `REQ-E2E-050` | Load from NULL buffer is safe | `test_load_null_safe` | `test_diag_replay.c:101` |
| `REQ-E2E-050` | Synthetic capture with zero count fails | `test_synthetic_zero_count` | `test_diag_replay.c:115` |
| `REQ-E2E-051` | Replay snapshots into evse_ctx_t and verify field mapping | `test_replay_field_mapping` | `test_diag_replay.c:130` |
| `REQ-E2E-051` | Replay sequence tracks state transitions across snapshots | `test_replay_state_transitions` | `test_diag_replay.c:180` |
| `REQ-E2E-051` | Advisory replay detects solar current oscillation pattern | `test_replay_solar_oscillation_detection` | `test_diag_replay.c:207` |
| `REQ-E2E-051` | Round-trip: serialize ring → load → compare snapshots | `test_roundtrip_serialize_load` | `test_diag_replay.c:239` |
| `REQ-E2E-040` | Ring buffer initializes with zero entries | `test_ring_init` | `test_diag_telemetry.c:1` |
| `REQ-E2E-040` | Ring buffer init with NULL pointer is safe | `test_ring_init_null` | `test_diag_telemetry.c:58` |
| `REQ-E2E-041` | Push a single snapshot and read it back | `test_push_and_read_single` | `test_diag_telemetry.c:75` |
| `REQ-E2E-041` | Push fills buffer to capacity | `test_push_fills_to_capacity` | `test_diag_telemetry.c:98` |
| `REQ-E2E-042` | Ring buffer wraps around, overwriting oldest entries | `test_wrap_around` | `test_diag_telemetry.c:130` |
| `REQ-E2E-042` | Read with smaller output buffer than ring count | `test_read_partial` | `test_diag_telemetry.c:162` |
| `REQ-E2E-043` | Reset clears all entries but preserves capacity | `test_reset` | `test_diag_telemetry.c:192` |
| `REQ-E2E-043` | Reset with NULL is safe | `test_reset_null` | `test_diag_telemetry.c:223` |
| `REQ-E2E-044` | Frozen ring rejects new pushes | `test_frozen_rejects_push` | `test_diag_telemetry.c:239` |
| `REQ-E2E-044` | Unfreezing allows pushes again | `test_unfreeze_allows_push` | `test_diag_telemetry.c:268` |
| `REQ-E2E-044` | Frozen ring still allows reads | `test_frozen_allows_read` | `test_diag_telemetry.c:297` |
| `REQ-E2E-045` | Setting GENERAL profile sets divider to 1 | `test_profile_general` | `test_diag_telemetry.c:324` |
| `REQ-E2E-045` | Setting FAST profile sets divider to 1 (sampled from 100ms tick) | `test_profile_fast` | `test_diag_telemetry.c:343` |
| `REQ-E2E-045` | Setting OFF profile prevents pushes | `test_profile_off_rejects_push` | `test_diag_telemetry.c:362` |
| `REQ-E2E-045` | Setting profile resets tick counter | `test_profile_resets_tick_counter` | `test_diag_telemetry.c:382` |
| `REQ-E2E-046` | Tick with divider=1 returns true every call | `test_tick_divider_1` | `test_diag_telemetry.c:403` |
| `REQ-E2E-046` | Tick with divider=10 returns true every 10th call | `test_tick_divider_10` | `test_diag_telemetry.c:423` |
| `REQ-E2E-046` | Tick with OFF profile always returns false | `test_tick_off_profile` | `test_diag_telemetry.c:449` |
| `REQ-E2E-040` | diag_snapshot_t is exactly 64 bytes | `test_snapshot_size` | `test_diag_telemetry.c:469` |
| `REQ-E2E-047` | Serialize empty ring produces valid header with zero snapshots | `test_serialize_empty` | `test_diag_telemetry.c:484` |
| `REQ-E2E-047` | Serialize ring with entries produces correct binary | `test_serialize_with_data` | `test_diag_telemetry.c:518` |
| `REQ-E2E-047` | Serialize returns 0 when buffer is too small | `test_serialize_buffer_too_small` | `test_diag_telemetry.c:551` |
| `REQ-E2E-047` | Serialized data has valid CRC32 | `test_serialize_crc_valid` | `test_diag_telemetry.c:574` |
| `REQ-E2E-047` | CRC32 of empty data returns initial value | `test_crc32_empty` | `test_diag_telemetry.c:607` |
| `REQ-E2E-047` | CRC32 of known data matches expected value | `test_crc32_known_value` | `test_diag_telemetry.c:621` |
| `REQ-E2E-041` | Push with NULL snapshot is safe | `test_push_null_snap` | `test_diag_telemetry.c:639` |
| `REQ-E2E-041` | Read from empty ring returns 0 | `test_read_empty` | `test_diag_telemetry.c:658` |
| `REQ-E2E-042` | Wrap-around preserves all snapshot fields | `test_wrap_preserves_fields` | `test_diag_telemetry.c:677` |
| `REQ-E2E-047` | File header struct is 34 bytes | `test_file_header_size` | `test_diag_telemetry.c:723` |
| `REQ-E2E-048` | DiagProfile set to general via MQTT | `test_diag_profile_general` | `test_mqtt_parser.c:948` |
| `REQ-E2E-048` | DiagProfile set to solar via MQTT | `test_diag_profile_solar` | `test_mqtt_parser.c:962` |
| `REQ-E2E-048` | DiagProfile set to off via MQTT | `test_diag_profile_off` | `test_mqtt_parser.c:976` |
| `REQ-E2E-048` | DiagProfile set via numeric value | `test_diag_profile_numeric` | `test_mqtt_parser.c:990` |
| `REQ-E2E-048` | DiagProfile rejects invalid payload | `test_diag_profile_invalid` | `test_mqtt_parser.c:1004` |

<details>
<summary>Detailed steps (51 scenarios)</summary>

### Modbus event ring initializes empty and disabled
**Requirement:** `REQ-E2E-049`

- **Given** A diag_mb_ring_t
- **When** diag_mb_init is called
- **Then** count is 0, head is 0, enabled is false

### Disabled ring rejects records
**Requirement:** `REQ-E2E-049`

- **Given** An initialized but disabled Modbus ring
- **When** diag_mb_record is called
- **Then** count stays 0

### Record and read a single event
**Requirement:** `REQ-E2E-049`

- **Given** An enabled Modbus ring
- **When** One SENT event is recorded
- **Then** diag_mb_read returns 1 event with correct fields

### Ring wraps around after 32 events
**Requirement:** `REQ-E2E-049`

- **Given** An enabled Modbus ring
- **When** 35 events are recorded
- **Then** count is 32 and oldest 3 events are overwritten

### Reset clears all events
**Requirement:** `REQ-E2E-049`

- **Given** A ring with 5 events
- **When** diag_mb_reset is called
- **Then** count is 0 and read returns 0

### Error events record error code
**Requirement:** `REQ-E2E-049`

- **Given** An enabled Modbus ring
- **When** An ERROR event with error code 0xE2 is recorded
- **Then** The event has event_type ERROR and error_code 0xE2

### Event struct is exactly 8 bytes
**Requirement:** `REQ-E2E-049`

- **Given** The diag_mb_event_t struct
- **When** sizeof is checked
- **Then** The size is 8 bytes

### NULL ring pointer is safe for all operations
**Requirement:** `REQ-E2E-049`

- **Given** A NULL ring pointer
- **When** init, record, read, reset, enable are called
- **Then** No crash occurs

### Create synthetic capture with known parameters
**Requirement:** `REQ-E2E-050`

- **Given** A request for 10 snapshots starting at uptime 1000
- **When** diag_create_synthetic is called with GENERAL profile
- **Then** 10 snapshots are created with timestamps 1000..1009

### Load capture from serialized binary buffer
**Requirement:** `REQ-E2E-050`

- **Given** A ring buffer with 3 snapshots serialized to binary
- **When** diag_load_buffer is called
- **Then** All 3 snapshots are loaded with correct timestamps and CRC is valid

### Load from buffer detects corrupt magic
**Requirement:** `REQ-E2E-050`

- **Given** A binary buffer with invalid magic bytes
- **When** diag_load_buffer is called
- **Then** Returns false

### Load from NULL buffer is safe
**Requirement:** `REQ-E2E-050`

- **Given** NULL data pointer
- **When** diag_load_buffer is called
- **Then** Returns false without crash

### Synthetic capture with zero count fails
**Requirement:** `REQ-E2E-050`

- **Given** A request for 0 snapshots
- **When** diag_create_synthetic is called
- **Then** Returns false

### Replay snapshots into evse_ctx_t and verify field mapping
**Requirement:** `REQ-E2E-051`

- **Given** A synthetic capture with 5 snapshots containing known current values
- **When** Each snapshot's fields are mapped to evse_ctx_t
- **Then** The ctx fields match the snapshot values

### Replay sequence tracks state transitions across snapshots
**Requirement:** `REQ-E2E-051`

- **Given** A capture with STATE_A→STATE_B→STATE_C→STATE_C→STATE_C transition
- **When** Snapshots are replayed in sequence
- **Then** Each snapshot's state matches the expected transition

### Advisory replay detects solar current oscillation pattern
**Requirement:** `REQ-E2E-051`

- **Given** A capture with charge_current oscillating between 0 and 80
- **When** Snapshots are analyzed for oscillation
- **Then** The oscillation is detected (>2 zero-crossings in the window)

### Round-trip: serialize ring → load → compare snapshots
**Requirement:** `REQ-E2E-051`

- **Given** A ring buffer with 4 snapshots serialized to binary
- **When** The binary is loaded back via diag_load_buffer
- **Then** All snapshot fields match the originals exactly

### Ring buffer initializes with zero entries
**Requirement:** `REQ-E2E-040`

- **Given** A diag_ring_t and a buffer of 8 slots
- **When** diag_ring_init is called
- **Then** count is 0, head is 0, profile is OFF, frozen is false

### Ring buffer init with NULL pointer is safe
**Requirement:** `REQ-E2E-040`

- **Given** A NULL ring pointer
- **When** diag_ring_init is called with NULL
- **Then** No crash occurs

### Push a single snapshot and read it back
**Requirement:** `REQ-E2E-041`

- **Given** An initialized ring with GENERAL profile and capacity 8
- **When** One snapshot with timestamp=42 is pushed
- **Then** diag_ring_read returns 1 snapshot with timestamp=42

### Push fills buffer to capacity
**Requirement:** `REQ-E2E-041`

- **Given** An initialized ring with capacity 4 and GENERAL profile
- **When** 4 snapshots are pushed (timestamps 10,20,30,40)
- **Then** count is 4 and read returns all 4 in chronological order

### Ring buffer wraps around, overwriting oldest entries
**Requirement:** `REQ-E2E-042`

- **Given** An initialized ring with capacity 4 and GENERAL profile
- **When** 6 snapshots are pushed (timestamps 1..6)
- **Then** count stays at 4 and read returns timestamps 3,4,5,6 (oldest overwritten)

### Read with smaller output buffer than ring count
**Requirement:** `REQ-E2E-042`

- **Given** A ring with 4 entries
- **When** diag_ring_read is called with max_count=2
- **Then** Only the 2 oldest snapshots are returned

### Reset clears all entries but preserves capacity
**Requirement:** `REQ-E2E-043`

- **Given** A ring with 3 entries and capacity 8
- **When** diag_ring_reset is called
- **Then** count is 0, head is 0, capacity is still 8, profile is OFF

### Reset with NULL is safe
**Requirement:** `REQ-E2E-043`

- **Given** A NULL ring pointer
- **When** diag_ring_reset is called
- **Then** No crash occurs

### Frozen ring rejects new pushes
**Requirement:** `REQ-E2E-044`

- **Given** A ring with 2 entries and GENERAL profile, then frozen
- **When** A new snapshot is pushed
- **Then** count remains 2 (push rejected)

### Unfreezing allows pushes again
**Requirement:** `REQ-E2E-044`

- **Given** A frozen ring with 2 entries
- **When** The ring is unfrozen and a snapshot is pushed
- **Then** count increases to 3

### Frozen ring still allows reads
**Requirement:** `REQ-E2E-044`

- **Given** A frozen ring with 2 entries
- **When** diag_ring_read is called
- **Then** Both entries are returned correctly

### Setting GENERAL profile sets divider to 1
**Requirement:** `REQ-E2E-045`

- **Given** An initialized ring
- **When** diag_set_profile is called with DIAG_PROFILE_GENERAL
- **Then** profile is GENERAL and sample_divider is 1

### Setting FAST profile sets divider to 1 (sampled from 100ms tick)
**Requirement:** `REQ-E2E-045`

- **Given** An initialized ring
- **When** diag_set_profile is called with DIAG_PROFILE_FAST
- **Then** profile is FAST and sample_divider is 1

### Setting OFF profile prevents pushes
**Requirement:** `REQ-E2E-045`

- **Given** An initialized ring with OFF profile
- **When** A snapshot is pushed
- **Then** count remains 0 (push rejected)

### Setting profile resets tick counter
**Requirement:** `REQ-E2E-045`

- **Given** A ring with tick_counter at 5
- **When** diag_set_profile is called
- **Then** tick_counter is reset to 0

### Tick with divider=1 returns true every call
**Requirement:** `REQ-E2E-046`

- **Given** A ring with GENERAL profile (divider=1)
- **When** diag_ring_tick is called 3 times
- **Then** All 3 calls return true

### Tick with divider=10 returns true every 10th call
**Requirement:** `REQ-E2E-046`

- **Given** A ring with sample_divider manually set to 10
- **When** diag_ring_tick is called 20 times
- **Then** Returns true on calls 10 and 20 only

### Tick with OFF profile always returns false
**Requirement:** `REQ-E2E-046`

- **Given** A ring with OFF profile
- **When** diag_ring_tick is called
- **Then** Returns false

### diag_snapshot_t is exactly 64 bytes
**Requirement:** `REQ-E2E-040`

- **Given** The diag_snapshot_t struct definition
- **When** sizeof is checked
- **Then** The size is exactly 64 bytes

### Serialize empty ring produces valid header with zero snapshots
**Requirement:** `REQ-E2E-047`

- **Given** An initialized ring with GENERAL profile and 0 entries
- **When** diag_ring_serialize is called
- **Then** Output contains valid header with count=0 and CRC32

### Serialize ring with entries produces correct binary
**Requirement:** `REQ-E2E-047`

- **Given** A ring with 2 snapshots (timestamps 100, 200)
- **When** diag_ring_serialize is called
- **Then** Output contains header + 2 snapshots + CRC32

### Serialize returns 0 when buffer is too small
**Requirement:** `REQ-E2E-047`

- **Given** A ring with 2 snapshots
- **When** diag_ring_serialize is called with a 10-byte buffer
- **Then** Returns 0 (insufficient space)

### Serialized data has valid CRC32
**Requirement:** `REQ-E2E-047`

- **Given** A ring with 1 snapshot serialized to binary
- **When** CRC32 is computed over header+snapshots and compared to stored CRC
- **Then** The CRC values match

### CRC32 of empty data returns initial value
**Requirement:** `REQ-E2E-047`

- **Given** An empty byte array
- **When** diag_crc32 is called with length 0
- **Then** Returns 0 (CRC of empty data)

### CRC32 of known data matches expected value
**Requirement:** `REQ-E2E-047`

- **Given** The string "123456789"
- **When** diag_crc32 is computed
- **Then** Returns 0xCBF43926 (standard CRC32 test vector)

### Push with NULL snapshot is safe
**Requirement:** `REQ-E2E-041`

- **Given** An initialized ring with GENERAL profile
- **When** diag_ring_push is called with NULL snapshot pointer
- **Then** No crash, count stays 0

### Read from empty ring returns 0
**Requirement:** `REQ-E2E-041`

- **Given** An initialized ring with 0 entries
- **When** diag_ring_read is called
- **Then** Returns 0

### Wrap-around preserves all snapshot fields
**Requirement:** `REQ-E2E-042`

- **Given** A ring with capacity 2 and GENERAL profile
- **When** 3 snapshots are pushed with distinct state and current fields
- **Then** The surviving 2 snapshots have all fields intact

### File header struct is 34 bytes
**Requirement:** `REQ-E2E-047`

- **Given** The diag_file_header_t struct definition
- **When** sizeof is checked
- **Then** The size is exactly 34 bytes

### DiagProfile set to general via MQTT
**Requirement:** `REQ-E2E-048`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/DiagProfile with payload "general"
- **Then** The parser returns true with diag_profile = 1

### DiagProfile set to solar via MQTT
**Requirement:** `REQ-E2E-048`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/DiagProfile with payload "solar"
- **Then** The parser returns true with diag_profile = 2

### DiagProfile set to off via MQTT
**Requirement:** `REQ-E2E-048`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/DiagProfile with payload "off"
- **Then** The parser returns true with diag_profile = 0

### DiagProfile set via numeric value
**Requirement:** `REQ-E2E-048`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/DiagProfile with payload "5"
- **Then** The parser returns true with diag_profile = 5 (FAST)

### DiagProfile rejects invalid payload
**Requirement:** `REQ-E2E-048`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/DiagProfile with payload "invalid"
- **Then** The parser returns false

</details>

---

## Dual-EVSE Load Balancing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-DUAL-S1A` | Both EVSEs get equal share of MaxCircuit in Normal mode | `test_s1_both_start_equal_split` | `test_dual_evse.c:1` |
| `REQ-DUAL-S1B` | IsetBalanced equals MaxCircuit * 10 in Normal mode | `test_s1_isetbalanced_equals_max_circuit` | `test_dual_evse.c:67` |
| `REQ-DUAL-S1C` | EV meter baseload reduces available current | `test_s1_ev_meter_baseload` | `test_dual_evse.c:85` |
| `REQ-DUAL-S2A` | Master reduces current when slave joins | `test_s2_slave_joins_master_reduces` | `test_dual_evse.c:112` |
| `REQ-DUAL-S2B` | Slave node sends COMM_B on car connect | `test_s2_slave_sends_comm_b` | `test_dual_evse.c:145` |
| `REQ-DUAL-S3A` | MaxCircuit reduction redistributes current equally | `test_s3_maxcircuit_reduction` | `test_dual_evse.c:170` |
| `REQ-DUAL-S3B` | MaxCircuit at exactly 2 * MinCurrent gives each MinCurrent | `test_s3_maxcircuit_to_mincurrent` | `test_dual_evse.c:191` |
| `REQ-DUAL-S4A` | Slave disconnects, master gets capped at BalancedMax | `test_s4_slave_disconnects` | `test_dual_evse.c:215` |
| `REQ-DUAL-S4B` | Master with higher MaxCurrent gets more after slave disconnect | `test_s4_master_absorbs_full_capacity` | `test_dual_evse.c:240` |
| `REQ-DUAL-S5A` | Smart mode: new EVSE joining recalculates from mains headroom | `test_s5_smart_mode_new_join` | `test_dual_evse.c:273` |
| `REQ-DUAL-S5B` | Smart mode: surplus increases IsetBalanced gradually | `test_s5_smart_surplus_increases` | `test_dual_evse.c:297` |
| `REQ-DUAL-S5C` | Smart mode: overload decreases IsetBalanced immediately | `test_s5_smart_overload_decreases` | `test_dual_evse.c:321` |
| `REQ-DUAL-S6A` | Solar mode: both EVSEs in startup get MinCurrent | `test_s6_solar_both_in_startup` | `test_dual_evse.c:348` |
| `REQ-DUAL-S6B` | Solar mode: insufficient solar starts SolarStopTimer | `test_s6_solar_insufficient_starts_timer` | `test_dual_evse.c:376` |
| `REQ-DUAL-S7A` | Zero available power pauses all EVSEs via priority scheduling | `test_s7_mincurrent_violation` | `test_dual_evse.c:412` |
| `REQ-DUAL-S7B` | Exactly 2 * MinCurrent — no shortage | `test_s7_barely_enough` | `test_dual_evse.c:440` |
| `REQ-DUAL-S8A` | Slave error → master absorbs capacity | `test_s8_slave_error_master_absorbs` | `test_dual_evse.c:465` |
| `REQ-DUAL-S8B` | Slave recovers, current redistributed | `test_s8_slave_recovers` | `test_dual_evse.c:488` |
| `REQ-DUAL-S9A` | MaxSumMains overridden Idifference limits IsetBalanced | `test_s9_maxsummains_limits` | `test_dual_evse.c:520` |
| `REQ-DUAL-S9B` | MaxSumMains timer expiry stops charging | `test_s9_maxsummains_timer_expiry` | `test_dual_evse.c:550` |
| `REQ-DUAL-S10A` | Normal mode forces 3P when currently on 1P | `test_s10_normal_forces_3p` | `test_dual_evse.c:582` |
| `REQ-DUAL-S10B` | STATE_C entry applies 1P switch | `test_s10_state_c_applies_1p` | `test_dual_evse.c:601` |
| `REQ-DUAL-S10C` | Smart mode with AUTO forces back to 3P | `test_s10_smart_auto_forces_3p` | `test_dual_evse.c:621` |

<details>
<summary>Detailed steps (23 scenarios)</summary>

### Both EVSEs get equal share of MaxCircuit in Normal mode
**Requirement:** `REQ-DUAL-S1A`

- **Given** Two EVSEs both in STATE_C, Normal mode, MaxCircuit=32A
- **When** evse_calc_balanced_current(mod=1) is called
- **Then** Each EVSE gets 160 (16A), equal split of 320 IsetBalanced

### IsetBalanced equals MaxCircuit * 10 in Normal mode
**Requirement:** `REQ-DUAL-S1B`

- **Given** Two EVSEs in Normal mode
- **When** evse_calc_balanced_current(mod=1)
- **Then** IsetBalanced = MaxCircuit * 10 = 320

### EV meter baseload reduces available current
**Requirement:** `REQ-DUAL-S1C`

- **Given** Two EVSEs, EV meter reads 200 (other loads on circuit)
- **When** evse_calc_balanced_current(mod=1)
- **Then** IsetBalanced reduced by baseload

### Master reduces current when slave joins
**Requirement:** `REQ-DUAL-S2A`

- **Given** Master alone at 160, slave not active
- **When** Slave enters STATE_C and calc runs with mod=1
- **Then** Both get equal share (160 each with MaxCircuit=32)

### Slave node sends COMM_B on car connect
**Requirement:** `REQ-DUAL-S2B`

- **Given** Slave EVSE (LoadBl=2) in STATE_A with 9V pilot
- **When** tick_10ms with PILOT_9V
- **Then** Transitions to STATE_COMM_B (requests master permission)

### MaxCircuit reduction redistributes current equally
**Requirement:** `REQ-DUAL-S3A`

- **Given** Both at 160 with MaxCircuit=32
- **When** MaxCircuit reduced to 20
- **Then** Each gets 100 (200 / 2)

### MaxCircuit at exactly 2 * MinCurrent gives each MinCurrent
**Requirement:** `REQ-DUAL-S3B`

- **Given** Both in STATE_C, MaxCircuit=12
- **When** evse_calc_balanced_current
- **Then** Each gets exactly 60 (MinCurrent * 10)

### Slave disconnects, master gets capped at BalancedMax
**Requirement:** `REQ-DUAL-S4A`

- **Given** Both at 160, slave disconnects (STATE_A)
- **When** Recalculation runs
- **Then** Master gets BalancedMax[0]=160, slave gets 0

### Master with higher MaxCurrent gets more after slave disconnect
**Requirement:** `REQ-DUAL-S4B`

- **Given** Master MaxCurrent=32, MaxCircuit=40, slave disconnects
- **When** Recalculation with mod=0
- **Then** Master gets up to 320 (BalancedMax[0]=ChargeCurrent=320)

### Smart mode: new EVSE joining recalculates from mains headroom
**Requirement:** `REQ-DUAL-S5A`

- **Given** Master in MODE_SMART, both in STATE_C, MaxMains=32A
- **When** evse_calc_balanced_current(mod=1)
- **Then** IsetBalanced based on (MaxMains*10) - Baseload

### Smart mode: surplus increases IsetBalanced gradually
**Requirement:** `REQ-DUAL-S5B`

- **Given** MODE_SMART, low mains load, IsetBalanced=200
- **When** evse_calc_balanced_current(mod=0)
- **Then** IsetBalanced increases by Idifference/4

### Smart mode: overload decreases IsetBalanced immediately
**Requirement:** `REQ-DUAL-S5C`

- **Given** MODE_SMART, high mains load
- **When** evse_calc_balanced_current(mod=0)
- **Then** IsetBalanced decreases by full Idifference

### Solar mode: both EVSEs in startup get MinCurrent
**Requirement:** `REQ-DUAL-S6A`

- **Given** MODE_SOLAR, both in STATE_C with IntTimer < SOLARSTARTTIME
- **When** evse_calc_balanced_current
- **Then** Both receive exactly MinCurrent * 10 = 60

### Solar mode: insufficient solar starts SolarStopTimer
**Requirement:** `REQ-DUAL-S6B`

- **Given** MODE_SOLAR, high grid import, past startup
- **When** evse_calc_balanced_current
- **Then** SolarStopTimer is set

### Zero available power pauses all EVSEs via priority scheduling
**Requirement:** `REQ-DUAL-S7A`

- **Given** Smart mode, MaxMains=5A, heavy mains load (IsetBalanced drops to 0)
- **When** evse_calc_balanced_current
- **Then** Both EVSEs paused (Balanced=0), NoCurrent increments (true hard shortage)

### Exactly 2 * MinCurrent — no shortage
**Requirement:** `REQ-DUAL-S7B`

- **Given** Normal mode, MaxCircuit=12
- **When** evse_calc_balanced_current
- **Then** Each gets 60, NoCurrent stays 0

### Slave error → master absorbs capacity
**Requirement:** `REQ-DUAL-S8A`

- **Given** Both at 160 each, slave enters B1
- **When** Recalculation
- **Then** Master gets 160 (capped by BalancedMax)

### Slave recovers, current redistributed
**Requirement:** `REQ-DUAL-S8B`

- **Given** Master alone at 160, slave re-enters STATE_C
- **When** evse_calc_balanced_current(mod=1)
- **Then** Both get equal share

### MaxSumMains overridden Idifference limits IsetBalanced
**Requirement:** `REQ-DUAL-S9A`

- **Given** MODE_SMART, MaxSumMains=30, Isum close to limit
- **When** evse_calc_balanced_current(mod=0)
- **Then** IsetBalanced constrained by MaxSumMains

### MaxSumMains timer expiry stops charging
**Requirement:** `REQ-DUAL-S9B`

- **Given** STATE_C with MaxSumMainsTimer=1
- **When** evse_tick_1s (timer expires)
- **Then** C → C1, LESS_6A set

### Normal mode forces 3P when currently on 1P
**Requirement:** `REQ-DUAL-S10A`

- **Given** Normal mode, Nr_Of_Phases_Charging=1
- **When** evse_calc_balanced_current
- **Then** Switching_Phases_C2 = GOING_TO_SWITCH_3P

### STATE_C entry applies 1P switch
**Requirement:** `REQ-DUAL-S10B`

- **Given** Switching_Phases_C2=GOING_TO_SWITCH_1P, EnableC2=ALWAYS_OFF
- **When** evse_set_state(STATE_C)
- **Then** Nr_Of_Phases_Charging=1, contactor2 off

### Smart mode with AUTO forces back to 3P
**Requirement:** `REQ-DUAL-S10C`

- **Given** MODE_SMART, EnableC2=AUTO, Nr_Of_Phases_Charging=1
- **When** evse_check_switching_phases
- **Then** Switching_Phases_C2 = GOING_TO_SWITCH_3P

</details>

---

## End-to-End Charging

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-E2E-001` | Complete standalone charge cycle with DiodeCheck | `test_e2e_standalone_happy_path` | `test_e2e_charging.c:1` |
| `REQ-E2E-002` | Slave EVSE full charge cycle with master handshake | `test_e2e_slave_happy_path` | `test_e2e_charging.c:99` |
| `REQ-E2E-003` | OCPP grants access mid-session, car starts charging | `test_e2e_ocpp_authorization_flow` | `test_e2e_charging.c:152` |
| `REQ-E2E-004` | OCPP denied — car connects but stays in STATE_A | `test_e2e_ocpp_denied_stays_in_a` | `test_e2e_charging.c:200` |
| `REQ-E2E-005` | Two full charge cycles — verify no stale state leaks | `test_e2e_reconnect_after_disconnect` | `test_e2e_charging.c:224` |
| `REQ-E2E-006` | Temperature spike during STATE_C, recovery after cooldown | `test_e2e_temp_error_during_charge` | `test_e2e_charging.c:283` |
| `REQ-E2E-007` | Meter communication lost during STATE_C | `test_e2e_ct_nocomm_during_charge` | `test_e2e_charging.c:322` |
| `REQ-E2E-008` | TEMP_HIGH + CT_NOCOMM simultaneously during charge | `test_e2e_multiple_errors_during_charge` | `test_e2e_charging.c:359` |
| `REQ-E2E-009` | 6V pilot without DiodeCheck does not transition to STATE_C | `test_e2e_no_charge_without_diode` | `test_e2e_charging.c:397` |
| `REQ-E2E-010` | ChargeDelay > 0 blocks A→B transition, sends to B1 | `test_e2e_charge_delay_blocks_charging` | `test_e2e_charging.c:424` |
| `REQ-E2E-011` | StateTimer is properly reset between charge sessions | `test_e2e_state_timer_reset_on_c_to_b` | `test_e2e_charging.c:450` |
| `REQ-E2E-012` | Power unavailable during charge suspends charging | `test_e2e_power_unavailable_c_to_c1_to_b1` | `test_e2e_charging.c:492` |
| `REQ-E2E-013` | Reconnect after Tesla-style disconnect requires fresh RFID swipe | `test_e2e_rfid_reconnect_after_tesla_disconnect` | `test_e2e_charging.c:522` |

<details>
<summary>Detailed steps (13 scenarios)</summary>

### Complete standalone charge cycle with DiodeCheck
**Requirement:** `REQ-E2E-001`

- **Given** Standalone EVSE, authorized, Normal mode
- **When** Car connects (9V) → DiodeCheck (DIODE) → requests charge (6V) → stops (9V) → disconnects (12V)
- **Then** Full cycle: A → B → (DiodeCheck) → C → B → A with correct contactor states

### Slave EVSE full charge cycle with master handshake
**Requirement:** `REQ-E2E-002`

- **Given** Slave EVSE (LoadBl=2), authorized
- **When** Car connects → COMM_B → master approves → B → DiodeCheck → 6V → COMM_C → master approves → C → disconnect
- **Then** Full slave cycle: A → COMM_B → COMM_B_OK → B → COMM_C → COMM_C_OK → C → B → A

### OCPP grants access mid-session, car starts charging
**Requirement:** `REQ-E2E-003`

- **Given** Standalone EVSE with OcppMode=true, AccessStatus=OFF
- **When** Car connects, OCPP grants access, car charges, OCPP revokes
- **Then** A (blocked) → A (OCPP grants) → B → C → C1 (revoked) → B1

### OCPP denied — car connects but stays in STATE_A
**Requirement:** `REQ-E2E-004`

- **Given** OCPP mode with AccessStatus=OFF
- **When** Car repeatedly presents 9V pilot
- **Then** State stays A for 100+ ticks

### Two full charge cycles — verify no stale state leaks
**Requirement:** `REQ-E2E-005`

- **Given** Standalone EVSE
- **When** First cycle: connect → charge → disconnect. Second cycle: connect → charge → disconnect.
- **Then** Both cycles complete successfully, all state is clean between them

### Temperature spike during STATE_C, recovery after cooldown
**Requirement:** `REQ-E2E-006`

- **Given** EVSE charging in STATE_C
- **When** Temperature exceeds maxTemp, then cools below hysteresis
- **Then** C → C1 → B1 (TEMP_HIGH), cooldown clears error

### Meter communication lost during STATE_C
**Requirement:** `REQ-E2E-007`

- **Given** EVSE charging in Smart mode with MainsMeter
- **When** Meter timeout reaches 0
- **Then** CT_NOCOMM set, power unavailable, C → C1

### TEMP_HIGH + CT_NOCOMM simultaneously during charge
**Requirement:** `REQ-E2E-008`

- **Given** EVSE charging in Smart mode
- **When** Temperature spikes AND meter fails at same time
- **Then** Both errors set, both must clear for full recovery

### 6V pilot without DiodeCheck does not transition to STATE_C
**Requirement:** `REQ-E2E-009`

- **Given** EVSE in STATE_B, DiodeCheck=0
- **When** 55 ticks of 6V pilot
- **Then** State stays STATE_B (DiodeCheck blocks B→C)

### ChargeDelay > 0 blocks A→B transition, sends to B1
**Requirement:** `REQ-E2E-010`

- **Given** Standalone EVSE with ChargeDelay=10
- **When** Car connects (9V)
- **Then** Goes to B1 (not B), must wait for delay to expire

### StateTimer is properly reset between charge sessions
**Requirement:** `REQ-E2E-011`

- **Given** EVSE in STATE_C with accumulated StateTimer
- **When** Car stops (9V → B), then requests charge again (6V)
- **Then** Debounce starts from 0, requiring full 500ms

### Power unavailable during charge suspends charging
**Requirement:** `REQ-E2E-012`

- **Given** EVSE charging in STATE_C
- **When** evse_set_power_unavailable is called
- **Then** C → C1 (PWM off) → B1 (contactors open after C1Timer)

### Reconnect after Tesla-style disconnect requires fresh RFID swipe
**Requirement:** `REQ-E2E-013`

- **Given** EVSE charging in STATE_C, RFIDReader=EnableOne, AccessStatus=ON
- **When** Car disconnects (CP → 12V), then reconnects within RFIDLOCKTIME seconds
- **Then** Auto A→B is blocked (AccessStatus cleared on disconnect); new RFID swipe restarts session

</details>

---

## Error Handling & Safety

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-ERR-001` | Setting an error flag stores it in ErrorFlags | `test_set_error_flags` | `test_error_handling.c:1` |
| `REQ-ERR-002` | Multiple error flags can be set simultaneously | `test_set_multiple_error_flags` | `test_error_handling.c:46` |
| `REQ-ERR-003` | Clearing an error flag removes only the specified flag | `test_clear_error_flags` | `test_error_handling.c:62` |
| `REQ-ERR-004` | Clearing one flag preserves all other active flags | `test_clear_preserves_other_flags` | `test_error_handling.c:78` |
| `REQ-ERR-005` | ChargeDelay decrements each second | `test_charge_delay_counts_down` | `test_error_handling.c:97` |
| `REQ-ERR-006` | ChargeDelay does not underflow past zero | `test_charge_delay_stops_at_zero` | `test_error_handling.c:112` |
| `REQ-ERR-008` | Temperature exceeding maxTemp triggers TEMP_HIGH error | `test_temp_high_triggers_error` | `test_error_handling.c:129` |
| `REQ-ERR-009` | Overtemperature shuts down active charging session | `test_temp_high_shuts_down_charging` | `test_error_handling.c:165` |
| `REQ-ERR-010` | Temperature recovery requires 10-degree hysteresis below maxTemp | `test_temp_recovery_with_hysteresis` | `test_error_handling.c:182` |
| `REQ-ERR-011` | Temperature recovery boundary: exactly at threshold does not clear | `test_temp_recovery_boundary` | `test_error_handling.c:206` |
| `REQ-ERR-012` | Mains meter communication timeout sets CT_NOCOMM error | `test_mains_meter_timeout_sets_ct_nocomm` | `test_error_handling.c:232` |
| `REQ-ERR-013` | Mains meter timeout counter decrements each second | `test_mains_meter_timeout_counts_down` | `test_error_handling.c:250` |
| `REQ-ERR-014` | Normal mode ignores mains meter timeout (no CT_NOCOMM) | `test_mains_meter_normal_mode_ignores_timeout` | `test_error_handling.c:268` |
| `REQ-ERR-015` | No mains meter configured resets timeout to COMM_TIMEOUT | `test_no_mains_meter_resets_timeout` | `test_error_handling.c:287` |
| `REQ-ERR-016` | EV meter communication timeout sets EV_NOCOMM error | `test_ev_meter_timeout_sets_ev_nocomm` | `test_error_handling.c:306` |
| `REQ-ERR-017` | No EV meter configured resets timeout to COMM_EVTIMEOUT | `test_no_ev_meter_resets_timeout` | `test_error_handling.c:323` |
| `REQ-ERR-018` | CT_NOCOMM error clears when mains meter communication resumes | `test_ct_nocomm_recovers_on_communication` | `test_error_handling.c:341` |
| `REQ-ERR-019` | EV_NOCOMM error clears when EV meter communication resumes | `test_ev_nocomm_recovers_on_communication` | `test_error_handling.c:357` |
| `REQ-ERR-020` | LESS_6A error auto-recovers when sufficient current becomes available | `test_less_6a_recovers_when_current_available` | `test_error_handling.c:375` |
| `REQ-ERR-021` | LESS_6A error persists when current is still unavailable | `test_less_6a_stays_when_current_unavailable` | `test_error_handling.c:394` |
| `REQ-ERR-022` | Node EVSEs (LoadBl >= 2) do not auto-recover LESS_6A | `test_less_6a_no_recovery_for_nodes` | `test_error_handling.c:414` |
| `REQ-ERR-023` | Power unavailable during charging suspends to STATE_C1 | `test_power_unavailable_from_C_goes_C1` | `test_error_handling.c:434` |
| `REQ-ERR-024` | Power unavailable in STATE_B moves to waiting state B1 | `test_power_unavailable_from_B_goes_B1` | `test_error_handling.c:448` |
| `REQ-ERR-025` | Power unavailable in STATE_A has no effect | `test_power_unavailable_from_A_stays_A` | `test_error_handling.c:464` |
| `REQ-ERR-026` | Power unavailable in STATE_B1 remains in B1 (already waiting) | `test_power_unavailable_from_B1_stays_B1` | `test_error_handling.c:479` |
| `REQ-ERR-027` | Power unavailable in STATE_C1 remains in C1 (already suspended) | `test_power_unavailable_from_C1_stays_C1` | `test_error_handling.c:494` |
| `REQ-ERR-028` | Entering STATE_B1 disconnects pilot when authorized | `test_pilot_disconnect_on_B1_entry` | `test_error_handling.c:511` |
| `REQ-ERR-029` | Pilot reconnects after PilotDisconnectTime expires | `test_pilot_reconnect_after_timer` | `test_error_handling.c:528` |
| `REQ-ERR-030` | MaxSumMains timer expiry stops charging with LESS_6A error | `test_maxsummains_timer_stops_charging` | `test_error_handling.c:560` |

<details>
<summary>Detailed steps (29 scenarios)</summary>

### Setting an error flag stores it in ErrorFlags
**Requirement:** `REQ-ERR-001`

- **Given** The EVSE is initialised with no errors
- **When** evse_set_error_flags is called with TEMP_HIGH
- **Then** TEMP_HIGH bit is set in ErrorFlags

### Multiple error flags can be set simultaneously
**Requirement:** `REQ-ERR-002`

- **Given** The EVSE is initialised with no errors
- **When** evse_set_error_flags is called with TEMP_HIGH then CT_NOCOMM
- **Then** Both TEMP_HIGH and CT_NOCOMM bits are set in ErrorFlags

### Clearing an error flag removes only the specified flag
**Requirement:** `REQ-ERR-003`

- **Given** The EVSE has TEMP_HIGH and CT_NOCOMM error flags set
- **When** evse_clear_error_flags is called with TEMP_HIGH
- **Then** TEMP_HIGH is cleared but CT_NOCOMM remains set

### Clearing one flag preserves all other active flags
**Requirement:** `REQ-ERR-004`

- **Given** The EVSE has TEMP_HIGH, LESS_6A, and CT_NOCOMM error flags set
- **When** evse_clear_error_flags is called with LESS_6A
- **Then** TEMP_HIGH and CT_NOCOMM remain set, LESS_6A is cleared

### ChargeDelay decrements each second
**Requirement:** `REQ-ERR-005`

- **Given** The EVSE has ChargeDelay set to 10
- **When** One second tick occurs
- **Then** ChargeDelay decrements to 9

### ChargeDelay does not underflow past zero
**Requirement:** `REQ-ERR-006`

- **Given** The EVSE has ChargeDelay set to 1
- **When** Two second ticks occur
- **Then** ChargeDelay reaches 0 and stays at 0

### Temperature exceeding maxTemp triggers TEMP_HIGH error
**Requirement:** `REQ-ERR-008`

- **Given** The EVSE is in STATE_A with ChargeDelay=5 and AccessStatus ON
- **Given** The EVSE is charging with TempEVSE=70 and maxTemp=65
- **When** A 9V pilot signal is received (vehicle connected)
- **When** One second tick occurs
- **Then** The state transitions to STATE_B1 instead of STATE_B
- **Then** TEMP_HIGH error flag is set in ErrorFlags

### Overtemperature shuts down active charging session
**Requirement:** `REQ-ERR-009`

- **Given** The EVSE is in STATE_C (charging) with TempEVSE=70 and maxTemp=65
- **When** One second tick occurs triggering temperature protection
- **Then** The state transitions out of STATE_C (charging suspended)

### Temperature recovery requires 10-degree hysteresis below maxTemp
**Requirement:** `REQ-ERR-010`

- **Given** The EVSE has TEMP_HIGH error with maxTemp=65
- **When** Temperature drops to 60 (within hysteresis) then to 50 (below threshold)
- **Then** TEMP_HIGH persists at 60 but clears at 50 (below maxTemp-10)

### Temperature recovery boundary: exactly at threshold does not clear
**Requirement:** `REQ-ERR-011`

- **Given** The EVSE has TEMP_HIGH error with maxTemp=65
- **When** Temperature is exactly 55 (maxTemp-10) then drops to 54
- **Then** TEMP_HIGH persists at 55 but clears at 54 (strictly below threshold)

### Mains meter communication timeout sets CT_NOCOMM error
**Requirement:** `REQ-ERR-012`

- **Given** The EVSE is in MODE_SMART with MainsMeterTimeout=0 (timed out)
- **When** One second tick occurs
- **Then** CT_NOCOMM error flag is set

### Mains meter timeout counter decrements each second
**Requirement:** `REQ-ERR-013`

- **Given** The EVSE is in MODE_SMART with MainsMeterTimeout=5
- **When** One second tick occurs
- **Then** MainsMeterTimeout decrements to 4

### Normal mode ignores mains meter timeout (no CT_NOCOMM)
**Requirement:** `REQ-ERR-014`

- **Given** The EVSE is in MODE_NORMAL with MainsMeterTimeout=0
- **When** One second tick occurs
- **Then** CT_NOCOMM error flag is NOT set

### No mains meter configured resets timeout to COMM_TIMEOUT
**Requirement:** `REQ-ERR-015`

- **Given** The EVSE has MainsMeterType=0 (no meter) with MainsMeterTimeout=3
- **When** One second tick occurs
- **Then** MainsMeterTimeout is reset to COMM_TIMEOUT

### EV meter communication timeout sets EV_NOCOMM error
**Requirement:** `REQ-ERR-016`

- **Given** The EVSE has EVMeterType=1 with EVMeterTimeout=0 (timed out)
- **When** One second tick occurs
- **Then** EV_NOCOMM error flag is set

### No EV meter configured resets timeout to COMM_EVTIMEOUT
**Requirement:** `REQ-ERR-017`

- **Given** The EVSE has EVMeterType=0 (no meter) with EVMeterTimeout=3
- **When** One second tick occurs
- **Then** EVMeterTimeout is reset to COMM_EVTIMEOUT

### CT_NOCOMM error clears when mains meter communication resumes
**Requirement:** `REQ-ERR-018`

- **Given** The EVSE has CT_NOCOMM error with MainsMeterTimeout=5 (restored)
- **When** One second tick occurs
- **Then** CT_NOCOMM error flag is cleared

### EV_NOCOMM error clears when EV meter communication resumes
**Requirement:** `REQ-ERR-019`

- **Given** The EVSE has EV_NOCOMM error with EVMeterTimeout=5 (restored)
- **When** One second tick occurs
- **Then** EV_NOCOMM error flag is cleared

### LESS_6A error auto-recovers when sufficient current becomes available
**Requirement:** `REQ-ERR-020`

- **Given** The EVSE is in MODE_NORMAL standalone with LESS_6A error and AccessStatus ON
- **When** One second tick occurs (normal mode always has current available)
- **Then** LESS_6A error flag is cleared

### LESS_6A error persists when current is still unavailable
**Requirement:** `REQ-ERR-021`

- **Given** The EVSE is in MODE_SMART with LESS_6A error and mains heavily loaded
- **When** One second tick occurs
- **Then** LESS_6A error flag remains set

### Node EVSEs (LoadBl >= 2) do not auto-recover LESS_6A
**Requirement:** `REQ-ERR-022`

- **Given** The EVSE is configured as a node (LoadBl=3) with LESS_6A error
- **When** One second tick occurs
- **Then** LESS_6A error flag remains set (nodes rely on master for recovery)

### Power unavailable during charging suspends to STATE_C1
**Requirement:** `REQ-ERR-023`

- **Given** The EVSE is in STATE_C (charging)
- **When** evse_set_power_unavailable is called
- **Then** The state transitions to STATE_C1 (charging suspended)

### Power unavailable in STATE_B moves to waiting state B1
**Requirement:** `REQ-ERR-024`

- **Given** The EVSE is in STATE_B (connected)
- **When** evse_set_power_unavailable is called
- **Then** The state transitions to STATE_B1 (waiting)

### Power unavailable in STATE_A has no effect
**Requirement:** `REQ-ERR-025`

- **Given** The EVSE is in STATE_A (disconnected)
- **When** evse_set_power_unavailable is called
- **Then** The state remains STATE_A

### Power unavailable in STATE_B1 remains in B1 (already waiting)
**Requirement:** `REQ-ERR-026`

- **Given** The EVSE is in STATE_B1 (waiting)
- **When** evse_set_power_unavailable is called
- **Then** The state remains STATE_B1

### Power unavailable in STATE_C1 remains in C1 (already suspended)
**Requirement:** `REQ-ERR-027`

- **Given** The EVSE is in STATE_C1 (charging suspended)
- **When** evse_set_power_unavailable is called
- **Then** The state remains STATE_C1

### Entering STATE_B1 disconnects pilot when authorized
**Requirement:** `REQ-ERR-028`

- **Given** The EVSE has AccessStatus ON and PilotDisconnected is false
- **When** The state is set to STATE_B1
- **Then** PilotDisconnected is true and pilot_connected is false

### Pilot reconnects after PilotDisconnectTime expires
**Requirement:** `REQ-ERR-029`

- **Given** The EVSE has PilotDisconnectTime=2 with pilot disconnected
- **When** Two second ticks occur
- **Then** PilotDisconnected is cleared and pilot_connected is restored

### MaxSumMains timer expiry stops charging with LESS_6A error
**Requirement:** `REQ-ERR-030`

- **Given** The EVSE is charging with MaxSumMainsTimer=1 and mains heavily loaded
- **When** One second tick occurs (timer expires)
- **Then** The state transitions to STATE_C1 and LESS_6A error flag is set

</details>

---

## Fidelity: DisconnectTimeCounter

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D1A` | Module tick_1s does not increment DisconnectTimeCounter | `test_fid_disconnect_counter_not_in_module` | `test_fidelity.c:1` |
| `REQ-FID-D1B` | Module correctly sets counter via set_state for STATE_A | `test_fid_disconnect_counter_starts_on_state_a` | `test_fidelity.c:59` |
| `REQ-FID-D1C` | Module disables counter on MODEM_REQUEST entry | `test_fid_disconnect_counter_disabled_on_modem_request` | `test_fidelity.c:75` |

<details>
<summary>Detailed steps (3 scenarios)</summary>

### Module tick_1s does not increment DisconnectTimeCounter
**Requirement:** `REQ-FID-D1A`

- **Given** ModemEnabled=true, DisconnectTimeCounter=0
- **When** tick_1s is called
- **Then** Counter stays 0 (firmware wrapper handles increment + pilot check)

### Module correctly sets counter via set_state for STATE_A
**Requirement:** `REQ-FID-D1B`

- **Given** ModemEnabled=true, DisconnectTimeCounter=-1
- **When** evse_set_state to STATE_A
- **Then** Counter is set to 0 (start counting)

### Module disables counter on MODEM_REQUEST entry
**Requirement:** `REQ-FID-D1C`

- **Given** DisconnectTimeCounter=5
- **When** evse_set_state to STATE_MODEM_REQUEST
- **Then** Counter is set to -1 (disabled)

</details>

---

## Fidelity: PilotDisconnectTime

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D2A` | tick_1s only decrements timer, does not reconnect | `test_fid_pilot_disconnect_no_reconnect_in_tick_1s` | `test_fidelity.c:95` |
| `REQ-FID-D2B` | tick_10ms reconnects when PilotDisconnectTime reaches 0 | `test_fid_pilot_disconnect_reconnects_in_tick_10ms` | `test_fidelity.c:116` |

<details>
<summary>Detailed steps (2 scenarios)</summary>

### tick_1s only decrements timer, does not reconnect
**Requirement:** `REQ-FID-D2A`

- **Given** PilotDisconnectTime=1, PilotDisconnected=true
- **When** tick_1s is called (timer reaches 0)
- **Then** PilotDisconnected is still true (reconnect happens in tick_10ms)

### tick_10ms reconnects when PilotDisconnectTime reaches 0
**Requirement:** `REQ-FID-D2B`

- **Given** PilotDisconnected=true, PilotDisconnectTime=0, State=B1
- **When** tick_10ms is called with PILOT_9V
- **Then** PilotDisconnected=false, pilot_connected=true

</details>

---

## Fidelity: Fall-through behavior

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D3A` | COMM_B_OK transitions to STATE_B and B handler runs same tick | `test_fid_comm_b_ok_falls_through_to_b_handler` | `test_fidelity.c:141` |
| `REQ-FID-D3B` | COMM_B_OK → B → 12V disconnect in same tick | `test_fid_comm_b_ok_to_b_then_disconnect` | `test_fidelity.c:161` |
| `REQ-FID-D4A` | A→B transition allows B handler to run and detect PILOT_DIODE | `test_fid_a_to_b_falls_through_to_b_handler` | `test_fidelity.c:183` |
| `REQ-FID-D5A` | COMM_C_OK transitions to STATE_C and C handler runs same tick | `test_fid_comm_c_ok_falls_through_to_c_handler` | `test_fidelity.c:208` |
| `REQ-FID-D5B` | COMM_C_OK → C → immediate 12V disconnect in same tick | `test_fid_comm_c_ok_to_c_then_disconnect` | `test_fidelity.c:230` |

<details>
<summary>Detailed steps (5 scenarios)</summary>

### COMM_B_OK transitions to STATE_B and B handler runs same tick
**Requirement:** `REQ-FID-D3A`

- **Given** State=COMM_B_OK, DiodeCheck=0
- **When** tick_10ms with PILOT_DIODE
- **Then** State=STATE_B, and DiodeCheck=1 (B handler fired in same tick)

### COMM_B_OK → B → 12V disconnect in same tick
**Requirement:** `REQ-FID-D3B`

- **Given** State=COMM_B_OK
- **When** tick_10ms with PILOT_12V
- **Then** State=STATE_A (B handler detects disconnect in same tick)

### A→B transition allows B handler to run and detect PILOT_DIODE
**Requirement:** `REQ-FID-D4A`

- **Given** State=STATE_A, PILOT_DIODE would trigger A→B on 9V but we pass 9V
- **When** tick_10ms with PILOT_9V in STATE_A with access
- **Then** State=STATE_B, ActivationMode=30, and StateTimer reset to 0

### COMM_C_OK transitions to STATE_C and C handler runs same tick
**Requirement:** `REQ-FID-D5A`

- **Given** State=COMM_C_OK
- **When** tick_10ms with PILOT_6V
- **Then** State=STATE_C, StateTimer=0 (C handler's else resets StateTimer)

### COMM_C_OK → C → immediate 12V disconnect in same tick
**Requirement:** `REQ-FID-D5B`

- **Given** State=COMM_C_OK
- **When** tick_10ms with PILOT_12V
- **Then** State=STATE_A (C handler detects disconnect immediately)

</details>

---

## Fidelity: ACTSTART no pilot check

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D6A` | ACTSTART ignores PILOT_12V (original has no pilot check here) | `test_fid_actstart_no_pilot_12v_check` | `test_fidelity.c:252` |
| `REQ-FID-D6B` | ACTSTART timer expiry leads to STATE_B (B handler is before ACTSTART | `test_fid_actstart_timer_then_disconnect` | `test_fidelity.c:270` |

<details>
<summary>Detailed steps (2 scenarios)</summary>

### ACTSTART ignores PILOT_12V (original has no pilot check here)
**Requirement:** `REQ-FID-D6A`

- **Given** State=ACTSTART with timer running (3 seconds)
- **When** tick_10ms with PILOT_12V
- **Then** State stays ACTSTART (timer must expire → B → detects 12V → A)

### ACTSTART timer expiry leads to STATE_B (B handler is before ACTSTART
**Requirement:** `REQ-FID-D6B`

- **Given** State=ACTSTART, ActivationTimer=0
- **When** tick_10ms with PILOT_12V, then another tick_10ms with PILOT_12V
- **Then** First tick: ACTSTART → B. Second tick: B → A (12V detected)

</details>

---

## Fidelity: Modem states not in tick_10ms

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D7A` | Modem states are invisible to tick_10ms | `test_fid_modem_states_invisible_to_tick_10ms` | `test_fidelity.c:299` |

<details>
<summary>Detailed steps (1 scenarios)</summary>

### Modem states are invisible to tick_10ms
**Requirement:** `REQ-FID-D7A`

- **Given** EVSE in each modem state
- **When** tick_10ms with any pilot value
- **Then** State does not change (modem managed entirely by tick_1s)

</details>

---

## Fidelity: Handler ordering

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-D8A` | B→ACTSTART falls through to ACTSTART handler in same tick | `test_fid_b_to_actstart_falls_through` | `test_fidelity.c:327` |

<details>
<summary>Detailed steps (1 scenarios)</summary>

### B→ACTSTART falls through to ACTSTART handler in same tick
**Requirement:** `REQ-FID-D8A`

- **Given** State=STATE_B, ActivationMode=0 (expired)
- **When** tick_10ms with PILOT_9V
- **Then** State=STATE_ACTSTART, ActivationTimer=3

</details>

---

## Fidelity: Config field

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-FID-CFG-A` | Socket mode (Config=0) caps ChargeCurrent by MaxCapacity | `test_fid_config_socket_caps_by_maxcapacity` | `test_fidelity.c:351` |
| `REQ-FID-CFG-B` | Fixed cable mode (Config=1) does NOT cap by MaxCapacity | `test_fid_config_fixed_cable_no_maxcapacity_cap` | `test_fidelity.c:372` |

<details>
<summary>Detailed steps (2 scenarios)</summary>

### Socket mode (Config=0) caps ChargeCurrent by MaxCapacity
**Requirement:** `REQ-FID-CFG-A`

- **Given** Config=0, MaxCurrent=25, MaxCapacity=16, STATE_C
- **When** calc_balanced_current is called
- **Then** ChargeCurrent=160 (capped by MaxCapacity)

### Fixed cable mode (Config=1) does NOT cap by MaxCapacity
**Requirement:** `REQ-FID-CFG-B`

- **Given** Config=1, MaxCurrent=25, MaxCapacity=16, STATE_C
- **When** calc_balanced_current is called
- **Then** ChargeCurrent=250 (MaxCurrent * 10, not capped)

</details>

---

## HTTP API Color Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-001` | Valid RGB color values are accepted | `test_color_valid` | `test_http_api.c:1` |
| `REQ-API-001` | Zero RGB values are accepted | `test_color_zero` | `test_http_api.c:31` |
| `REQ-API-001` | Maximum RGB values are accepted | `test_color_max` | `test_http_api.c:42` |

<details>
<summary>Detailed steps (3 scenarios)</summary>

### Valid RGB color values are accepted
**Requirement:** `REQ-API-001`

- **Given** Integer values for R, G, B
- **When** All values are in 0..255
- **Then** http_api_parse_color returns true with correct output

### Zero RGB values are accepted
**Requirement:** `REQ-API-001`


### Maximum RGB values are accepted
**Requirement:** `REQ-API-001`


</details>

---

## HTTP API Input Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-002` | RGB value above 255 is rejected | `test_color_out_of_range` | `test_http_api.c:53` |
| `REQ-API-002` | Negative RGB value is rejected | `test_color_negative` | `test_http_api.c:63` |
| `REQ-API-004` | Override current below minimum is rejected | `test_override_current_below_min` | `test_http_api.c:112` |
| `REQ-API-004` | Override current above maximum is rejected | `test_override_current_above_max` | `test_http_api.c:121` |
| `REQ-API-004` | Override current on slave is rejected | `test_override_current_slave` | `test_http_api.c:130` |
| `REQ-API-005` | Current min below 6A is rejected | `test_current_min_too_low` | `test_http_api.c:159` |
| `REQ-API-005` | Current min above 16A is rejected | `test_current_min_too_high` | `test_http_api.c:168` |
| `REQ-API-005` | Current min on slave is rejected | `test_current_min_slave` | `test_http_api.c:177` |
| `REQ-API-006` | Max sum mains between 1-9 is rejected | `test_max_sum_mains_gap` | `test_http_api.c:215` |
| `REQ-API-006` | Max sum mains above 600 is rejected | `test_max_sum_mains_too_high` | `test_http_api.c:224` |
| `REQ-API-006` | Max sum mains on slave is rejected | `test_max_sum_mains_slave` | `test_http_api.c:233` |
| `REQ-API-007` | Stop timer above 60 is rejected | `test_stop_timer_too_high` | `test_http_api.c:262` |
| `REQ-API-007` | Negative stop timer is rejected | `test_stop_timer_negative` | `test_http_api.c:271` |
| `REQ-API-008` | Solar start current above 48 is rejected | `test_solar_start_too_high` | `test_http_api.c:300` |
| `REQ-API-009` | Solar max import above 48 is rejected | `test_solar_import_too_high` | `test_http_api.c:320` |
| `REQ-API-011` | PrioStrategy value 3 is rejected | `test_prio_strategy_too_high` | `test_http_api.c:361` |
| `REQ-API-011` | PrioStrategy negative value is rejected | `test_prio_strategy_negative` | `test_http_api.c:370` |
| `REQ-API-011` | PrioStrategy on slave is rejected | `test_prio_strategy_slave` | `test_http_api.c:379` |
| `REQ-API-012` | RotationInterval in gap (1-29) is rejected | `test_rotation_interval_gap` | `test_http_api.c:423` |
| `REQ-API-012` | RotationInterval above maximum is rejected | `test_rotation_interval_too_high` | `test_http_api.c:432` |
| `REQ-API-012` | RotationInterval on slave is rejected | `test_rotation_interval_slave` | `test_http_api.c:441` |
| `REQ-API-013` | IdleTimeout below minimum (29) is rejected | `test_idle_timeout_too_low` | `test_http_api.c:482` |
| `REQ-API-013` | IdleTimeout above maximum (301) is rejected | `test_idle_timeout_too_high` | `test_http_api.c:491` |
| `REQ-API-013` | IdleTimeout on slave is rejected | `test_idle_timeout_slave` | `test_http_api.c:500` |

<details>
<summary>Detailed steps (24 scenarios)</summary>

### RGB value above 255 is rejected
**Requirement:** `REQ-API-002`


### Negative RGB value is rejected
**Requirement:** `REQ-API-002`


### Override current below minimum is rejected
**Requirement:** `REQ-API-004`


### Override current above maximum is rejected
**Requirement:** `REQ-API-004`


### Override current on slave is rejected
**Requirement:** `REQ-API-004`


### Current min below 6A is rejected
**Requirement:** `REQ-API-005`


### Current min above 16A is rejected
**Requirement:** `REQ-API-005`


### Current min on slave is rejected
**Requirement:** `REQ-API-005`


### Max sum mains between 1-9 is rejected
**Requirement:** `REQ-API-006`


### Max sum mains above 600 is rejected
**Requirement:** `REQ-API-006`


### Max sum mains on slave is rejected
**Requirement:** `REQ-API-006`


### Stop timer above 60 is rejected
**Requirement:** `REQ-API-007`


### Negative stop timer is rejected
**Requirement:** `REQ-API-007`


### Solar start current above 48 is rejected
**Requirement:** `REQ-API-008`


### Solar max import above 48 is rejected
**Requirement:** `REQ-API-009`


### PrioStrategy value 3 is rejected
**Requirement:** `REQ-API-011`


### PrioStrategy negative value is rejected
**Requirement:** `REQ-API-011`


### PrioStrategy on slave is rejected
**Requirement:** `REQ-API-011`

- **Given** A slave EVSE (load_bl=2)
- **When** prio_strategy is 0 (valid value)
- **Then** Validation fails because slaves cannot set scheduling

### RotationInterval in gap (1-29) is rejected
**Requirement:** `REQ-API-012`


### RotationInterval above maximum is rejected
**Requirement:** `REQ-API-012`


### RotationInterval on slave is rejected
**Requirement:** `REQ-API-012`


### IdleTimeout below minimum (29) is rejected
**Requirement:** `REQ-API-013`


### IdleTimeout above maximum (301) is rejected
**Requirement:** `REQ-API-013`


### IdleTimeout on slave is rejected
**Requirement:** `REQ-API-013`


</details>

---

## HTTP API Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-003` | Override current zero is always valid (disables override) | `test_override_current_zero` | `test_http_api.c:75` |
| `REQ-API-003` | Override current within range is valid | `test_override_current_valid` | `test_http_api.c:84` |
| `REQ-API-003` | Override current at minimum boundary is valid | `test_override_current_at_min` | `test_http_api.c:94` |
| `REQ-API-003` | Override current at maximum boundary is valid | `test_override_current_at_max` | `test_http_api.c:103` |
| `REQ-API-005` | Current min at boundary (6A) is valid | `test_current_min_valid` | `test_http_api.c:141` |
| `REQ-API-005` | Current min at 16A is valid | `test_current_min_max` | `test_http_api.c:150` |
| `REQ-API-006` | Max sum mains zero disables limit | `test_max_sum_mains_zero` | `test_http_api.c:188` |
| `REQ-API-006` | Max sum mains at minimum (10A) is valid | `test_max_sum_mains_min` | `test_http_api.c:197` |
| `REQ-API-006` | Max sum mains at maximum (600A) is valid | `test_max_sum_mains_max` | `test_http_api.c:206` |
| `REQ-API-007` | Stop timer at zero is valid | `test_stop_timer_zero` | `test_http_api.c:244` |
| `REQ-API-007` | Stop timer at max (60) is valid | `test_stop_timer_max` | `test_http_api.c:253` |
| `REQ-API-008` | Solar start current at 0 is valid | `test_solar_start_zero` | `test_http_api.c:282` |
| `REQ-API-008` | Solar start current at 48 is valid | `test_solar_start_max` | `test_http_api.c:291` |
| `REQ-API-009` | Solar max import at 0 is valid | `test_solar_import_zero` | `test_http_api.c:311` |
| `REQ-API-011` | PrioStrategy MODBUS_ADDR (0) is valid on master | `test_prio_strategy_valid_0` | `test_http_api.c:331` |
| `REQ-API-011` | PrioStrategy FIRST_CONNECTED (1) is valid | `test_prio_strategy_valid_1` | `test_http_api.c:343` |
| `REQ-API-011` | PrioStrategy LAST_CONNECTED (2) is valid | `test_prio_strategy_valid_2` | `test_http_api.c:352` |
| `REQ-API-012` | RotationInterval 0 (disabled) is valid | `test_rotation_interval_zero` | `test_http_api.c:393` |
| `REQ-API-012` | RotationInterval at minimum (30) is valid | `test_rotation_interval_min` | `test_http_api.c:405` |
| `REQ-API-012` | RotationInterval at maximum (1440) is valid | `test_rotation_interval_max` | `test_http_api.c:414` |
| `REQ-API-013` | IdleTimeout at minimum (30) is valid | `test_idle_timeout_min` | `test_http_api.c:452` |
| `REQ-API-013` | IdleTimeout at default (60) is valid | `test_idle_timeout_default` | `test_http_api.c:464` |
| `REQ-API-013` | IdleTimeout at maximum (300) is valid | `test_idle_timeout_max` | `test_http_api.c:473` |

<details>
<summary>Detailed steps (23 scenarios)</summary>

### Override current zero is always valid (disables override)
**Requirement:** `REQ-API-003`


### Override current within range is valid
**Requirement:** `REQ-API-003`


### Override current at minimum boundary is valid
**Requirement:** `REQ-API-003`


### Override current at maximum boundary is valid
**Requirement:** `REQ-API-003`


### Current min at boundary (6A) is valid
**Requirement:** `REQ-API-005`


### Current min at 16A is valid
**Requirement:** `REQ-API-005`


### Max sum mains zero disables limit
**Requirement:** `REQ-API-006`


### Max sum mains at minimum (10A) is valid
**Requirement:** `REQ-API-006`


### Max sum mains at maximum (600A) is valid
**Requirement:** `REQ-API-006`


### Stop timer at zero is valid
**Requirement:** `REQ-API-007`


### Stop timer at max (60) is valid
**Requirement:** `REQ-API-007`


### Solar start current at 0 is valid
**Requirement:** `REQ-API-008`


### Solar start current at 48 is valid
**Requirement:** `REQ-API-008`


### Solar max import at 0 is valid
**Requirement:** `REQ-API-009`


### PrioStrategy MODBUS_ADDR (0) is valid on master
**Requirement:** `REQ-API-011`

- **Given** A master EVSE (load_bl=0)
- **When** prio_strategy is 0
- **Then** Validation passes

### PrioStrategy FIRST_CONNECTED (1) is valid
**Requirement:** `REQ-API-011`


### PrioStrategy LAST_CONNECTED (2) is valid
**Requirement:** `REQ-API-011`


### RotationInterval 0 (disabled) is valid
**Requirement:** `REQ-API-012`

- **Given** A master EVSE (load_bl=0)
- **When** rotation_interval is 0
- **Then** Validation passes

### RotationInterval at minimum (30) is valid
**Requirement:** `REQ-API-012`


### RotationInterval at maximum (1440) is valid
**Requirement:** `REQ-API-012`


### IdleTimeout at minimum (30) is valid
**Requirement:** `REQ-API-013`

- **Given** A master EVSE (load_bl=0)
- **When** idle_timeout is 30
- **Then** Validation passes

### IdleTimeout at default (60) is valid
**Requirement:** `REQ-API-013`


### IdleTimeout at maximum (300) is valid
**Requirement:** `REQ-API-013`


</details>

---

## HTTP API Settings Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-010` | Valid settings request passes validation | `test_validate_settings_valid` | `test_http_api.c:511` |
| `REQ-API-010` | Invalid current_min in combined request | `test_validate_settings_invalid_min` | `test_http_api.c:532` |
| `REQ-API-010` | Multiple invalid fields | `test_validate_settings_multiple_errors` | `test_http_api.c:549` |
| `REQ-API-010` | Empty request passes validation | `test_validate_settings_empty` | `test_http_api.c:567` |
| `REQ-API-010` | Slave restrictions applied | `test_validate_settings_slave_restrictions` | `test_http_api.c:581` |
| `REQ-API-014` | Valid scheduling settings in combined request | `test_validate_settings_scheduling_valid` | `test_http_api.c:597` |
| `REQ-API-014` | Invalid scheduling settings on slave | `test_validate_settings_scheduling_slave` | `test_http_api.c:620` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Valid settings request passes validation
**Requirement:** `REQ-API-010`

- **Given** A settings request with valid current_min and override_current
- **When** Validated against current limits
- **Then** No errors are returned

### Invalid current_min in combined request
**Requirement:** `REQ-API-010`


### Multiple invalid fields
**Requirement:** `REQ-API-010`


### Empty request passes validation
**Requirement:** `REQ-API-010`


### Slave restrictions applied
**Requirement:** `REQ-API-010`


### Valid scheduling settings in combined request
**Requirement:** `REQ-API-014`

- **Given** A settings request with valid scheduling fields
- **When** Validated on master (load_bl=1)
- **Then** No errors are returned

### Invalid scheduling settings on slave
**Requirement:** `REQ-API-014`

- **Given** A settings request with scheduling fields
- **When** Validated on slave (load_bl=2)
- **Then** All three scheduling fields produce errors

</details>

---

## EVCC IEC 61851 State Mapping

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-020` | STATE_A maps to IEC 61851 state A (standby) | `test_iec61851_state_a` | `test_http_api.c:645` |
| `REQ-API-020` | STATE_B maps to IEC 61851 state B (vehicle detected) | `test_iec61851_state_b` | `test_http_api.c:657` |
| `REQ-API-020` | STATE_C maps to IEC 61851 state C (charging) | `test_iec61851_state_c` | `test_http_api.c:669` |
| `REQ-API-020` | STATE_D maps to IEC 61851 state D (ventilation required) | `test_iec61851_state_d` | `test_http_api.c:681` |
| `REQ-API-021` | STATE_B1 maps to IEC 61851 state B (connected, EVSE not ready) | `test_iec61851_state_b1` | `test_http_api.c:693` |
| `REQ-API-021` | STATE_C1 maps to IEC 61851 state C (charge stopping) | `test_iec61851_state_c1` | `test_http_api.c:705` |
| `REQ-API-021` | Communication and modem states map to B (connected) | `test_iec61851_comm_modem_states` | `test_http_api.c:717` |
| `REQ-API-022` | Modem denied maps to E (error) | `test_iec61851_modem_denied` | `test_http_api.c:736` |
| `REQ-API-022` | Hard error flags override state to E (error) | `test_iec61851_hard_error_overrides_state` | `test_http_api.c:748` |
| `REQ-API-022` | Soft errors (LESS_6A, NO_SUN) do NOT override state | `test_iec61851_soft_errors_no_override` | `test_http_api.c:763` |
| `REQ-API-023` | NOSTATE and unknown values map to F (not available) | `test_iec61851_nostate_and_unknown` | `test_http_api.c:777` |

<details>
<summary>Detailed steps (11 scenarios)</summary>

### STATE_A maps to IEC 61851 state A (standby)
**Requirement:** `REQ-API-020`

- **Given** The EVSE is in STATE_A with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'A'

### STATE_B maps to IEC 61851 state B (vehicle detected)
**Requirement:** `REQ-API-020`

- **Given** The EVSE is in STATE_B with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'B'

### STATE_C maps to IEC 61851 state C (charging)
**Requirement:** `REQ-API-020`

- **Given** The EVSE is in STATE_C with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'C'

### STATE_D maps to IEC 61851 state D (ventilation required)
**Requirement:** `REQ-API-020`

- **Given** The EVSE is in STATE_D with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'D'

### STATE_B1 maps to IEC 61851 state B (connected, EVSE not ready)
**Requirement:** `REQ-API-021`

- **Given** The EVSE is in STATE_B1 (no PWM signal) with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'B' because the vehicle is connected

### STATE_C1 maps to IEC 61851 state C (charge stopping)
**Requirement:** `REQ-API-021`

- **Given** The EVSE is in STATE_C1 (stopping) with no errors
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'C' because charging session is still active

### Communication and modem states map to B (connected)
**Requirement:** `REQ-API-021`

- **Given** The EVSE is in various communication/modem states
- **When** evse_state_to_iec61851 is called for each
- **Then** All return 'B' because the vehicle is connected but not yet charging

### Modem denied maps to E (error)
**Requirement:** `REQ-API-022`

- **Given** The EVSE is in STATE_MODEM_DENIED
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'E' because access was denied

### Hard error flags override state to E (error)
**Requirement:** `REQ-API-022`

- **Given** The EVSE is in STATE_C (charging) with RCM_TRIPPED error
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'E' because a hard error takes priority

### Soft errors (LESS_6A, NO_SUN) do NOT override state
**Requirement:** `REQ-API-022`

- **Given** The EVSE is in STATE_C with LESS_6A or STATE_A with NO_SUN
- **When** evse_state_to_iec61851 is called
- **Then** It returns the state-based letter, not 'E'

### NOSTATE and unknown values map to F (not available)
**Requirement:** `REQ-API-023`

- **Given** The EVSE is in NOSTATE or an unrecognized state value
- **When** evse_state_to_iec61851 is called
- **Then** It returns 'F' indicating EVSE not available

</details>

---

## EVCC Charging Enabled

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-025` | STATE_C means charging is enabled | `test_charging_enabled_state_c` | `test_http_api.c:792` |
| `REQ-API-025` | STATE_C1 means charging is enabled (stopping phase) | `test_charging_enabled_state_c1` | `test_http_api.c:804` |
| `REQ-API-025` | Non-charging states return false | `test_charging_enabled_non_charging_states` | `test_http_api.c:816` |

<details>
<summary>Detailed steps (3 scenarios)</summary>

### STATE_C means charging is enabled
**Requirement:** `REQ-API-025`

- **Given** The EVSE is in STATE_C (charging)
- **When** evse_charging_enabled is called
- **Then** It returns true

### STATE_C1 means charging is enabled (stopping phase)
**Requirement:** `REQ-API-025`

- **Given** The EVSE is in STATE_C1 (charge stopping)
- **When** evse_charging_enabled is called
- **Then** It returns true because energy is still being delivered

### Non-charging states return false
**Requirement:** `REQ-API-025`

- **Given** The EVSE is in STATE_A, STATE_B, or other non-charging states
- **When** evse_charging_enabled is called
- **Then** It returns false

</details>

---

## EVCC Phase Switch Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-024` | Valid 1-phase switch request on standalone with C2 contactor | `test_phase_switch_valid_1p` | `test_http_api.c:838` |
| `REQ-API-024` | Valid 3-phase switch request on master with C2 contactor | `test_phase_switch_valid_3p` | `test_http_api.c:851` |
| `REQ-API-025` | Invalid phase count (2) is rejected | `test_phase_switch_invalid_phase_count` | `test_http_api.c:864` |
| `REQ-API-025` | Phase switch rejected when C2 contactor not present | `test_phase_switch_no_c2_hardware` | `test_http_api.c:877` |
| `REQ-API-025` | Phase switch rejected on slave node | `test_phase_switch_slave_rejected` | `test_http_api.c:890` |
| `REQ-API-025` | Phase switch with zero phases is rejected | `test_phase_switch_zero_phases` | `test_http_api.c:903` |
| `REQ-API-024` | Phase switch valid with all non-NOT_PRESENT EnableC2 values | `test_phase_switch_all_c2_configs` | `test_http_api.c:916` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Valid 1-phase switch request on standalone with C2 contactor
**Requirement:** `REQ-API-024`

- **Given** A standalone EVSE (load_bl=0) with EnableC2=AUTO
- **When** A phase switch to 1 phase is requested
- **Then** Validation passes (returns NULL)

### Valid 3-phase switch request on master with C2 contactor
**Requirement:** `REQ-API-024`

- **Given** A master EVSE (load_bl=1) with EnableC2=ALWAYS_ON
- **When** A phase switch to 3 phases is requested
- **Then** Validation passes (returns NULL)

### Invalid phase count (2) is rejected
**Requirement:** `REQ-API-025`

- **Given** A standalone EVSE with EnableC2=AUTO
- **When** A phase switch to 2 phases is requested
- **Then** Validation fails with error message

### Phase switch rejected when C2 contactor not present
**Requirement:** `REQ-API-025`

- **Given** An EVSE with EnableC2=NOT_PRESENT (no C2 hardware)
- **When** A phase switch to 1 phase is requested
- **Then** Validation fails because hardware cannot switch phases

### Phase switch rejected on slave node
**Requirement:** `REQ-API-025`

- **Given** A slave EVSE (load_bl=2) with EnableC2=AUTO
- **When** A phase switch to 3 phases is requested
- **Then** Validation fails because slaves cannot initiate phase switching

### Phase switch with zero phases is rejected
**Requirement:** `REQ-API-025`

- **Given** A standalone EVSE with EnableC2=AUTO
- **When** A phase switch to 0 phases is requested
- **Then** Validation fails

### Phase switch valid with all non-NOT_PRESENT EnableC2 values
**Requirement:** `REQ-API-024`

- **Given** A standalone EVSE with various EnableC2 settings (ALWAYS_OFF, SOLAR_OFF, ALWAYS_ON, AUTO)
- **When** A phase switch to 1 phase is requested
- **Then** Validation passes for all C2 configurations that have hardware present

</details>

---

## Unsigned firmware upload

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-API-020` | Unsigned upload gate always allows regardless of build type or PIN | `test_unsigned_upload_always_allowed` | `test_http_api.c:938` |

<details>
<summary>Detailed steps (1 scenarios)</summary>

### Unsigned upload gate always allows regardless of build type or PIN
**Requirement:** `REQ-API-020`

- **Given** Any combination of build type, PIN, and PIN-verified state
- **When** /update receives an unsigned firmware.bin
- **Then** http_api_allow_unsigned_upload returns true unconditionally

</details>

---

## HTTP Auth

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-AUTH-001` | AuthMode=OFF allows any request (no PIN, no Origin) | `test_auth_off_allows_unauthenticated` | `test_http_auth.c:1` |
| `REQ-AUTH-001` | AuthMode=OFF allows request with foreign Origin (no CSRF check) | `test_auth_off_allows_foreign_origin` | `test_http_auth.c:27` |
| `REQ-AUTH-001` | AuthMode=OFF + lcd_pin=0 still allows (legacy upgrade path) | `test_auth_off_allows_when_pin_zero` | `test_http_auth.c:38` |
| `REQ-AUTH-002` | AuthMode=REQUIRED denies request without PIN verification | `test_auth_required_denies_unauth` | `test_http_auth.c:54` |
| `REQ-AUTH-002` | AuthMode=REQUIRED allows PIN-verified request | `test_auth_required_allows_authed` | `test_http_auth.c:65` |
| `REQ-AUTH-003` | Authenticated session expires after HTTP_AUTH_SESSION_TIMEOUT_MS idle | `test_auth_session_expires` | `test_http_auth.c:79` |
| `REQ-AUTH-003` | Authenticated session still valid just before the timeout boundary | `test_auth_session_just_before_timeout` | `test_http_auth.c:91` |
| `REQ-AUTH-003` | Session with zero timestamp is treated as "never set" (defensive) | `test_auth_session_zero_ts_does_not_expire` | `test_http_auth.c:103` |
| `REQ-AUTH-004` | Missing Origin header allowed (non-browser integration) | `test_auth_no_origin_allowed` | `test_http_auth.c:115` |
| `REQ-AUTH-004` | Matching Origin allowed | `test_auth_matching_origin_allowed` | `test_http_auth.c:126` |
| `REQ-AUTH-004` | Matching hostname in origin allowed | `test_auth_matching_hostname_origin_allowed` | `test_http_auth.c:137` |
| `REQ-AUTH-004` | Foreign Origin blocked as CSRF | `test_auth_foreign_origin_blocked` | `test_http_auth.c:148` |
| `REQ-AUTH-004` | Origin with unexpected scheme blocked | `test_auth_origin_bad_scheme_blocked` | `test_http_auth.c:159` |
| `REQ-AUTH-004` | https:// Origin matching device IP allowed | `test_auth_https_matching_origin_allowed` | `test_http_auth.c:170` |
| `REQ-AUTH-005` | Unauth + foreign Origin reports UNAUTH first (PIN check precedes CSRF) | `test_auth_unauth_precedes_csrf` | `test_http_auth.c:183` |
| `REQ-AUTH-006` | AuthMode=REQUIRED with no PIN configured denies unauthenticated request | `test_auth_required_no_pin_configured_denies` | `test_http_auth.c:202` |
| `REQ-AUTH-006` | AuthMode=REQUIRED with no PIN configured ignores LCDPasswordOK=true | `test_auth_required_no_pin_denies_even_if_flag_set` | `test_http_auth.c:216` |
| `REQ-AUTH-007` | Attacker subdomain that suffixes the device mDNS host is rejected | `test_auth_csrf_substring_suffix_rejected` | `test_http_auth.c:240` |
| `REQ-AUTH-007` | Attacker IP-suffix domain (nip.io-style) is rejected | `test_auth_csrf_ip_suffix_rejected` | `test_http_auth.c:255` |
| `REQ-AUTH-007` | Attacker domain that prefixes the device host is rejected | `test_auth_csrf_substring_prefix_rejected` | `test_http_auth.c:270` |
| `REQ-AUTH-007` | Origin that embeds device host in userinfo/path is rejected | `test_auth_csrf_host_in_path_rejected` | `test_http_auth.c:285` |
| `REQ-AUTH-007` | Case-insensitive host match accepted (DNS labels are case-insensitive) | `test_auth_csrf_case_insensitive_match_allowed` | `test_http_auth.c:300` |
| `REQ-AUTH-007` | Matching host with explicit port accepted | `test_auth_csrf_matching_host_with_port_allowed` | `test_http_auth.c:315` |
| `REQ-AUTH-007` | Matching host with trailing slash accepted | `test_auth_csrf_matching_host_with_trailing_slash_allowed` | `test_http_auth.c:330` |

<details>
<summary>Detailed steps (24 scenarios)</summary>

### AuthMode=OFF allows any request (no PIN, no Origin)
**Requirement:** `REQ-AUTH-001`


### AuthMode=OFF allows request with foreign Origin (no CSRF check)
**Requirement:** `REQ-AUTH-001`


### AuthMode=OFF + lcd_pin=0 still allows (legacy upgrade path)
**Requirement:** `REQ-AUTH-001`

- **Given** Legacy installation with AuthMode never enabled and no PIN set
- **When** Any request arrives
- **Then** Allow — backward compat preserved regardless of PIN provisioning

### AuthMode=REQUIRED denies request without PIN verification
**Requirement:** `REQ-AUTH-002`


### AuthMode=REQUIRED allows PIN-verified request
**Requirement:** `REQ-AUTH-002`


### Authenticated session expires after HTTP_AUTH_SESSION_TIMEOUT_MS idle
**Requirement:** `REQ-AUTH-003`


### Authenticated session still valid just before the timeout boundary
**Requirement:** `REQ-AUTH-003`


### Session with zero timestamp is treated as "never set" (defensive)
**Requirement:** `REQ-AUTH-003`


### Missing Origin header allowed (non-browser integration)
**Requirement:** `REQ-AUTH-004`


### Matching Origin allowed
**Requirement:** `REQ-AUTH-004`


### Matching hostname in origin allowed
**Requirement:** `REQ-AUTH-004`


### Foreign Origin blocked as CSRF
**Requirement:** `REQ-AUTH-004`


### Origin with unexpected scheme blocked
**Requirement:** `REQ-AUTH-004`


### https:// Origin matching device IP allowed
**Requirement:** `REQ-AUTH-004`


### Unauth + foreign Origin reports UNAUTH first (PIN check precedes CSRF)
**Requirement:** `REQ-AUTH-005`


### AuthMode=REQUIRED with no PIN configured denies unauthenticated request
**Requirement:** `REQ-AUTH-006`

- **Given** AuthMode=REQUIRED, lcd_pin=0, lcd_password_ok=false
- **When** A request arrives at a require_auth-gated endpoint
- **Then** Return DENY_UNAUTH — auth is not reachable until a PIN is provisioned

### AuthMode=REQUIRED with no PIN configured ignores LCDPasswordOK=true
**Requirement:** `REQ-AUTH-006`

- **Given** Somehow lcd_password_ok=true (bug, stale state, or bypass attempt) but lcd_pin=0
- **When** A request arrives at a require_auth-gated endpoint
- **Then** Return DENY_UNAUTH — a cleared PIN must invalidate any cached auth

### Attacker subdomain that suffixes the device mDNS host is rejected
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "smartevse-1234.local", admin has a live session
- **When** Origin is "http://smartevse-1234.local.evil.com"
- **Then** DENY_CSRF — the host must match exactly, not just be a substring

### Attacker IP-suffix domain (nip.io-style) is rejected
**Requirement:** `REQ-AUTH-007`

- **Given** Device IP is 192.168.1.50
- **When** Origin is "http://192.168.1.50.nip.io"
- **Then** DENY_CSRF

### Attacker domain that prefixes the device host is rejected
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "smartevse.local"
- **When** Origin is "http://evil.smartevse.local" (subdomain of attacker-owned TLD)
- **Then** DENY_CSRF

### Origin that embeds device host in userinfo/path is rejected
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "smartevse.local"
- **When** Origin is "http://evil.com/smartevse.local" (host portion is "evil.com")
- **Then** DENY_CSRF — only the hostname portion of the Origin is compared

### Case-insensitive host match accepted (DNS labels are case-insensitive)
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "smartevse-1234.local"
- **When** Origin is "http://SmartEVSE-1234.LOCAL"
- **Then** ALLOW

### Matching host with explicit port accepted
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "192.168.1.50"
- **When** Origin is "http://192.168.1.50:80"
- **Then** ALLOW

### Matching host with trailing slash accepted
**Requirement:** `REQ-AUTH-007`

- **Given** Device host is "smartevse.local"
- **When** Origin is "http://smartevse.local/" (browsers don't send this, but be safe)
- **Then** ALLOW

</details>

---

## LB Convergence

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LB-020` | Standalone Smart mode converges to target within 20 cycles | `test_smart_standalone_converges_to_target` | `test_lb_convergence.c:1` |
| `REQ-LB-021` | Smart mode converges monotonically when starting below target | `test_smart_standalone_monotonic_increase` | `test_lb_convergence.c:166` |
| `REQ-LB-022` | Smart mode recovers when mains load increases mid-session | `test_smart_standalone_recovers_from_load_increase` | `test_lb_convergence.c:199` |
| `REQ-LB-023` | Smart mode recovers when mains load decreases mid-session | `test_smart_standalone_recovers_from_load_decrease` | `test_lb_convergence.c:221` |
| `REQ-LB-024` | Two EVSEs in Normal mode converge to equal distribution | `test_two_evse_normal_converges_equal` | `test_lb_convergence.c:246` |
| `REQ-LB-025` | Two EVSEs in Smart mode converge to fair sharing | `test_two_evse_smart_converges_fair` | `test_lb_convergence.c:294` |
| `REQ-LB-026` | Four EVSEs in Smart mode converge with sufficient headroom | `test_four_evse_smart_converges` | `test_lb_convergence.c:316` |
| `REQ-LB-027` | Third EVSE joining mid-session causes redistribution | `test_third_evse_joining_reconverges` | `test_lb_convergence.c:343` |
| `REQ-LB-028` | EVSE disconnecting causes fair redistribution to remaining | `test_evse_disconnect_reconverges` | `test_lb_convergence.c:382` |
| `REQ-LB-029` | MaxMains limits total EVSE allocation in Smart mode | `test_maxmains_caps_convergence` | `test_lb_convergence.c:414` |
| `REQ-LB-030` | Tight capacity with 4 EVSEs triggers priority scheduling | `test_tight_capacity_four_evse_priority` | `test_lb_convergence.c:436` |
| `REQ-LB-031` | Hard shortage with single EVSE triggers NoCurrent | `test_hard_shortage_standalone_triggers_nocurrent` | `test_lb_convergence.c:463` |
| `REQ-LB-032` | MaxCircuit limits per-EVSE allocation independently of MaxMains | `test_maxcircuit_limits_convergence` | `test_lb_convergence.c:481` |
| `REQ-LB-033` | MaxSumMains limit overrides MaxMains when configured | `test_maxsummains_constrains_convergence` | `test_lb_convergence.c:499` |
| `REQ-LB-034` | Solar mode converges to export surplus | `test_solar_standalone_converges_to_surplus` | `test_lb_convergence.c:522` |
| `REQ-LB-035` | Solar mode with ImportCurrent allows partial grid import | `test_solar_import_current_allows_grid_use` | `test_lb_convergence.c:541` |
| `REQ-LB-036` | Converged Smart mode EVSE remains stable (no oscillation) | `test_smart_stability_no_oscillation` | `test_lb_convergence.c:564` |
| `REQ-LB-037` | Two-EVSE Smart mode remains stable after convergence | `test_two_evse_stability_no_oscillation` | `test_lb_convergence.c:595` |
| `REQ-LB-038` | Oscillation detection increments OscillationCount on sign flip | `test_oscillation_detected_on_sign_flip` | `test_lb_convergence.c:632` |
| `REQ-LB-039` | Adaptive gain increases effective divisor during oscillation | `test_adaptive_gain_reduces_step_during_oscillation` | `test_lb_convergence.c:669` |
| `REQ-LB-040` | OscillationCount decays when no sign flip occurs | `test_oscillation_count_decays_when_stable` | `test_lb_convergence.c:703` |
| `REQ-LB-041` | Adaptive gain improves convergence under alternating load | `test_adaptive_gain_dampens_noisy_load` | `test_lb_convergence.c:732` |
| `REQ-LB-042` | Normal mode is unaffected by adaptive gain | `test_normal_mode_no_adaptive_gain` | `test_lb_convergence.c:766` |
| `REQ-LB-043` | EMA filter smooths Idifference spikes | `test_ema_filter_smooths_spike` | `test_lb_convergence.c:803` |
| `REQ-LB-044` | EMA filter preserves convergence (no regression) | `test_ema_filter_still_converges` | `test_lb_convergence.c:834` |
| `REQ-LB-045` | EMA filter reduces peak-to-peak swing under noisy measurements | `test_ema_filter_reduces_noise_swing` | `test_lb_convergence.c:853` |
| `REQ-LB-046` | EMA filter tracks sustained load change within 10 cycles | `test_ema_filter_tracks_sustained_change` | `test_lb_convergence.c:883` |
| `REQ-LB-047` | Distribution smoothing clamps per-EVSE current change | `test_distribution_smoothing_clamps_increase` | `test_lb_convergence.c:914` |
| `REQ-LB-048` | Distribution smoothing clamps per-EVSE current decrease | `test_distribution_smoothing_clamps_decrease` | `test_lb_convergence.c:944` |
| `REQ-LB-049` | Distribution smoothing is skipped for mod=1 (new EVSE joining) | `test_distribution_smoothing_skipped_on_mod1` | `test_lb_convergence.c:973` |
| `REQ-LB-050` | Distribution smoothing still converges within 20 cycles | `test_distribution_smoothing_still_converges` | `test_lb_convergence.c:1007` |
| `REQ-LB-051` | BalancedPrev tracks previous cycle values | `test_balanced_prev_tracks_previous` | `test_lb_convergence.c:1026` |
| `REQ-LB-052` | LB diagnostic snapshot populated after regulation cycle | `test_lb_diag_snapshot_populated` | `test_lb_convergence.c:1058` |
| `REQ-LB-053` | LB diagnostic captures shortage state | `test_lb_diag_captures_shortage` | `test_lb_convergence.c:1076` |
| `REQ-LB-054` | LB diagnostic captures oscillation count | `test_lb_diag_captures_oscillation` | `test_lb_convergence.c:1094` |
| `REQ-LB-055` | LB diagnostic captures delta clamping state | `test_lb_diag_captures_delta_clamped` | `test_lb_convergence.c:1116` |
| `REQ-LB-056` | Eight EVSEs in Normal mode receive fair distribution | `test_eight_evse_normal_fair` | `test_lb_convergence.c:1147` |
| `REQ-LB-057` | Eight EVSEs in Smart mode converge with sufficient headroom | `test_eight_evse_smart_converges` | `test_lb_convergence.c:1188` |
| `REQ-LB-058` | Eight EVSEs with varying BalancedMax distribute fairly | `test_eight_evse_varying_max` | `test_lb_convergence.c:1214` |
| `REQ-LB-059` | Eight EVSEs: sequential join cycle | `test_eight_evse_sequential_join` | `test_lb_convergence.c:1259` |
| `REQ-LB-060` | Eight EVSEs: sequential leave cycle | `test_eight_evse_sequential_leave` | `test_lb_convergence.c:1304` |
| `REQ-LB-061` | Eight EVSEs under tight capacity: priority scheduling | `test_eight_evse_tight_capacity_priority` | `test_lb_convergence.c:1330` |
| `REQ-LB-062` | EVSE converges with 2-cycle vehicle response delay | `test_vehicle_response_delay_converges` | `test_lb_convergence.c:1359` |
| `REQ-LB-063` | Vehicle lag with noise does not cause LESS_6A error | `test_vehicle_response_stable_with_noise` | `test_lb_convergence.c:1426` |
| `REQ-LB-064` | Two EVSEs converge with vehicle response model | `test_two_evse_vehicle_response_converges` | `test_lb_convergence.c:1452` |
| `REQ-LB-065` | Vehicle response model with load step recovers | `test_vehicle_response_load_step_recovery` | `test_lb_convergence.c:1475` |
| `REQ-LB-066` | Heavy measurement noise with vehicle lag doesn't cause NoCurrent | `test_vehicle_response_noise_no_false_shortage` | `test_lb_convergence.c:1498` |

<details>
<summary>Detailed steps (47 scenarios)</summary>

### Standalone Smart mode converges to target within 20 cycles
**Requirement:** `REQ-LB-020`

- **Given** A standalone EVSE in Smart mode with 25A mains limit and 50dA baseload
- **When** 20 regulation cycles are simulated with meter feedback
- **Then** IsetBalanced stabilizes within 5 deciamps of the expected target (200dA)

### Smart mode converges monotonically when starting below target
**Requirement:** `REQ-LB-021`

- **Given** A standalone EVSE in Smart mode starting at MinCurrent (60dA) with headroom
- **When** 10 regulation cycles are simulated
- **Then** IsetBalanced increases each cycle (monotonic convergence upward)

### Smart mode recovers when mains load increases mid-session
**Requirement:** `REQ-LB-022`

- **Given** A standalone EVSE converged to 200dA with 5A baseload
- **When** Baseload suddenly increases by 100dA (10A) reducing available capacity
- **Then** After 20 more cycles, IsetBalanced settles near the new target (100dA)

### Smart mode recovers when mains load decreases mid-session
**Requirement:** `REQ-LB-023`

- **Given** A standalone EVSE converged with 15A baseload
- **When** Baseload drops by 100dA (10A) increasing available capacity
- **Then** After 20 more cycles, IsetBalanced settles near the new higher target

### Two EVSEs in Normal mode converge to equal distribution
**Requirement:** `REQ-LB-024`

- **Given** Master with 2 EVSEs in Normal mode, MaxCircuit=32A, no baseload
- **When** 5 regulation cycles are simulated
- **Then** Both EVSEs receive equal current within 1 deciamp

### Two EVSEs in Smart mode converge to fair sharing
**Requirement:** `REQ-LB-025`

- **Given** Master with 2 EVSEs in Smart mode, 25A mains limit, 5A baseload
- **When** 20 regulation cycles are simulated with meter feedback
- **Then** Both EVSEs receive current within 5dA of each other

### Four EVSEs in Smart mode converge with sufficient headroom
**Requirement:** `REQ-LB-026`

- **Given** Master with 4 EVSEs in Smart mode, 50A mains limit, 5A baseload
- **When** 30 regulation cycles are simulated with meter feedback
- **Then** All 4 EVSEs receive current within 10dA of each other

### Third EVSE joining mid-session causes redistribution
**Requirement:** `REQ-LB-027`

- **Given** Master with 2 EVSEs converged in Smart mode
- **When** A third EVSE starts charging (mod=1) and 20 more cycles run
- **Then** All 3 EVSEs converge to fair sharing within 10dA

### EVSE disconnecting causes fair redistribution to remaining
**Requirement:** `REQ-LB-028`

- **Given** Master with 3 EVSEs converged in Smart mode
- **When** EVSE 2 disconnects and 20 more cycles run
- **Then** Remaining 2 EVSEs converge to fair sharing, each getting more than before

### MaxMains limits total EVSE allocation in Smart mode
**Requirement:** `REQ-LB-029`

- **Given** Standalone EVSE in Smart mode, MaxMains=10A, 5A baseload
- **When** 20 regulation cycles are simulated
- **Then** IsetBalanced converges to MinCurrent (60dA) since available (50dA) < MinCurrent

### Tight capacity with 4 EVSEs triggers priority scheduling
**Requirement:** `REQ-LB-030`

- **Given** Master with 4 EVSEs, only enough power for 2 at MinCurrent
- **When** 10 regulation cycles are simulated
- **Then** NoCurrent stays at 0 (priority scheduling handles shortage gracefully)

### Hard shortage with single EVSE triggers NoCurrent
**Requirement:** `REQ-LB-031`

- **Given** Standalone EVSE in Smart mode, mains heavily overloaded
- **When** Multiple regulation cycles are simulated with baseload exceeding MaxMains
- **Then** NoCurrent counter increments indicating sustained shortage

### MaxCircuit limits per-EVSE allocation independently of MaxMains
**Requirement:** `REQ-LB-032`

- **Given** Standalone EVSE in Smart mode, MaxCircuit=10A, MaxMains=50A, 3A baseload
- **When** 20 regulation cycles are simulated
- **Then** Balanced[0] does not exceed MaxCircuit*10 (100dA)

### MaxSumMains limit overrides MaxMains when configured
**Requirement:** `REQ-LB-033`

- **Given** Standalone EVSE in Smart mode with MaxSumMains=15A
- **When** 20 regulation cycles are simulated with Isum near the limit
- **Then** IsetBalanced is constrained by MaxSumMains, not just MaxMains

### Solar mode converges to export surplus
**Requirement:** `REQ-LB-034`

- **Given** Standalone EVSE in Solar mode, large export (Isum negative)
- **When** 30 regulation cycles are simulated with meter feedback
- **Then** IsetBalanced increases to absorb available solar surplus

### Solar mode with ImportCurrent allows partial grid import
**Requirement:** `REQ-LB-035`

- **Given** Standalone EVSE in Solar mode with ImportCurrent=6A
- **When** 30 regulation cycles run with modest solar export
- **Then** EVSE charges above pure-solar level due to allowed import

### Converged Smart mode EVSE remains stable (no oscillation)
**Requirement:** `REQ-LB-036`

- **Given** A standalone EVSE converged in Smart mode
- **When** 20 additional regulation cycles run with constant conditions
- **Then** IsetBalanced varies by no more than 5dA across all cycles

### Two-EVSE Smart mode remains stable after convergence
**Requirement:** `REQ-LB-037`

- **Given** Master with 2 EVSEs converged in Smart mode
- **When** 20 additional regulation cycles run with constant conditions
- **Then** Balanced[0] and Balanced[1] each vary by no more than 5dA

### Oscillation detection increments OscillationCount on sign flip
**Requirement:** `REQ-LB-038`

- **Given** Standalone EVSE in Smart mode with alternating positive/negative Idifference
- **When** Regulation cycles produce sign flips in Idifference
- **Then** OscillationCount increments, indicating detected oscillation

### Adaptive gain increases effective divisor during oscillation
**Requirement:** `REQ-LB-039`

- **Given** Standalone EVSE in Smart mode with OscillationCount > 0
- **When** Regulation cycle runs with positive Idifference
- **Then** IsetBalanced increases by less than Idifference/RampRateDivisor

### OscillationCount decays when no sign flip occurs
**Requirement:** `REQ-LB-040`

- **Given** Standalone EVSE in Smart mode with OscillationCount = 5
- **When** Multiple consecutive regulation cycles have same-sign Idifference
- **Then** OscillationCount decays back toward 0

### Adaptive gain improves convergence under alternating load
**Requirement:** `REQ-LB-041`

- **Given** Standalone EVSE in Smart mode with alternating baseload (simulating noisy grid)
- **When** 40 regulation cycles are simulated with alternating +-20dA baseload noise
- **Then** IsetBalanced peak-to-peak oscillation is less than 30dA (dampened)

### Normal mode is unaffected by adaptive gain
**Requirement:** `REQ-LB-042`

- **Given** Standalone EVSE in Normal mode
- **When** Regulation cycles run
- **Then** OscillationCount remains 0 (adaptive gain only applies to Smart/Solar)

### EMA filter smooths Idifference spikes
**Requirement:** `REQ-LB-043`

- **Given** Standalone EVSE in Smart mode converged at stable load
- **When** A single large Idifference spike occurs (sudden mains change)
- **Then** The filtered Idifference used for regulation is less than the raw spike

### EMA filter preserves convergence (no regression)
**Requirement:** `REQ-LB-044`

- **Given** Standalone EVSE in Smart mode with EMA filtering active
- **When** 30 regulation cycles run
- **Then** IsetBalanced converges to target within 10 dA (may be slower but still converges)

### EMA filter reduces peak-to-peak swing under noisy measurements
**Requirement:** `REQ-LB-045`

- **Given** Standalone EVSE in Smart mode converged
- **When** 40 cycles with +-30dA measurement noise are simulated
- **Then** Peak-to-peak IsetBalanced swing is at most 30dA (~50% of raw 60dA noise)

### EMA filter tracks sustained load change within 10 cycles
**Requirement:** `REQ-LB-046`

- **Given** Standalone EVSE in Smart mode converged at 5A baseload
- **When** Baseload increases permanently by 100dA (10A)
- **Then** After 10 cycles, IsetBalanced has moved at least 50% toward new target

### Distribution smoothing clamps per-EVSE current change
**Requirement:** `REQ-LB-047`

- **Given** Master with 2 EVSEs in Smart mode, converged to 100dA each
- **When** IsetBalanced suddenly jumps to 320dA (large headroom increase)
- **Then** Each EVSE Balanced[] changes by at most MAX_DELTA_PER_CYCLE (30dA) per cycle

### Distribution smoothing clamps per-EVSE current decrease
**Requirement:** `REQ-LB-048`

- **Given** Master with 2 EVSEs in Smart mode, converged to 200dA each
- **When** IsetBalanced suddenly drops (mains overloaded)
- **Then** Each EVSE Balanced[] decreases by at most MAX_DELTA_PER_CYCLE per cycle

### Distribution smoothing is skipped for mod=1 (new EVSE joining)
**Requirement:** `REQ-LB-049`

- **Given** Master with 2 EVSEs, EVSE 1 just joined with mod=1
- **When** Balanced current is calculated with mod=1
- **Then** Balanced[] values are NOT clamped (full redistribution allowed)

### Distribution smoothing still converges within 20 cycles
**Requirement:** `REQ-LB-050`

- **Given** Master with 2 EVSEs in Smart mode, starting from MinCurrent
- **When** 20 regulation cycles with distribution smoothing
- **Then** Both EVSEs converge to fair sharing within 10dA

### BalancedPrev tracks previous cycle values
**Requirement:** `REQ-LB-051`

- **Given** Master with 2 EVSEs after a regulation cycle
- **When** A second regulation cycle runs
- **Then** BalancedPrev[] matches the Balanced[] values from the previous cycle

### LB diagnostic snapshot populated after regulation cycle
**Requirement:** `REQ-LB-052`

- **Given** Master with 2 EVSEs in Smart mode after regulation
- **When** evse_calc_balanced_current completes
- **Then** lb_diag contains correct IsetBalanced, ActiveEVSE, and Balanced[] values

### LB diagnostic captures shortage state
**Requirement:** `REQ-LB-053`

- **Given** Master with 4 EVSEs in Smart mode under hard shortage
- **When** Regulation cycle detects insufficient power
- **Then** lb_diag.Shortage is true and lb_diag.NoCurrent > 0

### LB diagnostic captures oscillation count
**Requirement:** `REQ-LB-054`

- **Given** Standalone EVSE with OscillationCount elevated
- **When** Regulation cycle completes
- **Then** lb_diag.OscillationCount matches ctx.OscillationCount

### LB diagnostic captures delta clamping state
**Requirement:** `REQ-LB-055`

- **Given** Master with 2 EVSEs where distribution smoothing will clamp
- **When** Large current change triggers clamping
- **Then** lb_diag.DeltaClamped is true

### Eight EVSEs in Normal mode receive fair distribution
**Requirement:** `REQ-LB-056`

- **Given** Master with 8 EVSEs all in STATE_C, MaxCircuit=64A
- **When** Regulation cycles complete
- **Then** All 8 EVSEs receive equal current (80dA = 8A each)

### Eight EVSEs in Smart mode converge with sufficient headroom
**Requirement:** `REQ-LB-057`

- **Given** Master with 8 EVSEs in Smart mode, 80A mains, 5A baseload
- **When** 40 regulation cycles are simulated
- **Then** All 8 EVSEs receive current within 10dA of each other

### Eight EVSEs with varying BalancedMax distribute fairly
**Requirement:** `REQ-LB-058`

- **Given** Master with 8 EVSEs, each with different BalancedMax (60-320dA)
- **When** Regulation cycles complete in Normal mode
- **Then** Each EVSE is capped at its BalancedMax, total equals IsetBalanced

### Eight EVSEs: sequential join cycle
**Requirement:** `REQ-LB-059`

- **Given** Master starts with 2 EVSEs, then adds one per cycle up to 8
- **When** Each new EVSE joins with mod=1 followed by 5 regulation cycles
- **Then** After all 8 are active, distribution is fair within 10dA

### Eight EVSEs: sequential leave cycle
**Requirement:** `REQ-LB-060`

- **Given** Master with 8 EVSEs converged in Smart mode
- **When** EVSEs disconnect one by one (7 down to 2)
- **Then** Remaining EVSEs get progressively more current

### Eight EVSEs under tight capacity: priority scheduling
**Requirement:** `REQ-LB-061`

- **Given** Master with 8 EVSEs, only enough power for 3 at MinCurrent
- **When** Regulation cycles run
- **Then** At most 3 EVSEs are active, others are paused, NoCurrent stays 0

### EVSE converges with 2-cycle vehicle response delay
**Requirement:** `REQ-LB-062`

- **Given** Standalone EVSE in Smart mode with simulated vehicle response lag
- **When** 80 regulation cycles with vehicle response model
- **Then** IsetBalanced converges to target within 30dA despite lag

### Vehicle lag with noise does not cause LESS_6A error
**Requirement:** `REQ-LB-063`

- **Given** Standalone EVSE with vehicle response model and 5dA noise
- **When** 40 cycles run after convergence
- **Then** No LESS_6A error is triggered and EVSE keeps charging

### Two EVSEs converge with vehicle response model
**Requirement:** `REQ-LB-064`

- **Given** Master with 2 EVSEs, both with vehicle response lag
- **When** 80 regulation cycles with vehicle response simulation
- **Then** Both EVSEs receive equal current and are above MinCurrent

### Vehicle response model with load step recovers
**Requirement:** `REQ-LB-065`

- **Given** Standalone EVSE converged with vehicle model
- **When** Baseload suddenly increases by 100dA
- **Then** After 30 cycles with vehicle lag, IsetBalanced settles near new target

### Heavy measurement noise with vehicle lag doesn't cause NoCurrent
**Requirement:** `REQ-LB-066`

- **Given** Standalone EVSE with vehicle model and 10dA measurement noise
- **When** 50 regulation cycles run
- **Then** NoCurrent stays below NoCurrentThreshold (no false LESS_6A errors)

</details>

---

## LED Status Indication

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LED-001` | RCM tripped error produces red flashing pattern on ESP32 | `test_error_rcm_tripped_esp32` | `test_led_color.c:1` |
| `REQ-LED-001` | CT_NOCOMM error shows red flashing | `test_error_ct_nocomm` | `test_led_color.c:82` |
| `REQ-LED-001` | TEMP_HIGH error shows red flashing | `test_error_temp_high` | `test_led_color.c:105` |
| `REQ-LED-001` | CH32 RCM mismatch with no test counter shows error | `test_error_ch32_rcm_mismatch` | `test_led_color.c:126` |
| `REQ-LED-001` | CH32 RCM test in progress does not show error flash | `test_no_error_ch32_rcm_test_active` | `test_led_color.c:149` |
| `REQ-LED-002` | Access OFF shows off color | `test_access_off_default` | `test_led_color.c:181` |
| `REQ-LED-002` | MODEM_DENIED state shows off color | `test_modem_denied_shows_off` | `test_led_color.c:224` |
| `REQ-LED-003` | Solar mode with charge delay shows slow blink | `test_waiting_solar_blink` | `test_led_color.c:247` |
| `REQ-LED-003` | Smart mode waiting shows smart color blink | `test_waiting_smart_color` | `test_led_color.c:271` |
| `REQ-LED-005` | State A shows dimmed LED | `test_state_a_dimmed` | `test_led_color.c:320` |
| `REQ-LED-005` | State B shows full brightness LED | `test_state_b_full_brightness` | `test_led_color.c:340` |
| `REQ-LED-005` | State B1 shows full brightness (same as B) | `test_state_b1_full_brightness` | `test_led_color.c:359` |
| `REQ-LED-005` | State B sets led_count to 128 for smooth C transition | `test_state_b_sets_count_128` | `test_led_color.c:378` |
| `REQ-LED-006` | State C shows breathing animation | `test_state_c_breathing` | `test_led_color.c:395` |
| `REQ-LED-006` | State C Solar mode has slower breathing | `test_state_c_solar_slower` | `test_led_color.c:418` |

<details>
<summary>Detailed steps (15 scenarios)</summary>

### RCM tripped error produces red flashing pattern on ESP32
**Requirement:** `REQ-LED-001`

- **Given** ErrorFlags has RCM_TRIPPED set on ESP32 platform
- **When** led_compute_color is called repeatedly
- **Then** LED alternates between red and off

### CT_NOCOMM error shows red flashing
**Requirement:** `REQ-LED-001`

- **Given** ErrorFlags has CT_NOCOMM set
- **When** led_compute_color is called multiple times
- **Then** LED flashes red

### TEMP_HIGH error shows red flashing
**Requirement:** `REQ-LED-001`

- **Given** ErrorFlags has TEMP_HIGH set
- **When** led_compute_color is called
- **Then** LED flashes red

### CH32 RCM mismatch with no test counter shows error
**Requirement:** `REQ-LED-001`

- **Given** CH32 platform with RCM_TRIPPED set but not RCM_TEST, counter=0
- **When** led_compute_color is called
- **Then** LED shows red (error condition)

### CH32 RCM test in progress does not show error flash
**Requirement:** `REQ-LED-001`

- **Given** CH32 platform with RCM_TRIPPED set, counter > 0 (test running)
- **When** led_compute_color is called
- **Then** LED does NOT show rapid red error flash (enters waiting blink instead)

### Access OFF shows off color
**Requirement:** `REQ-LED-002`

- **Given** Access status is OFF, no custom button
- **When** led_compute_color is called
- **Then** LED shows ColorOff values

### MODEM_DENIED state shows off color
**Requirement:** `REQ-LED-002`

- **Given** State is STATE_MODEM_DENIED, access ON
- **When** led_compute_color is called
- **Then** LED shows ColorOff values (same as access OFF)

### Solar mode with charge delay shows slow blink
**Requirement:** `REQ-LED-003`

- **Given** Solar mode, ChargeDelay > 0, no errors
- **When** led_compute_color is called repeatedly
- **Then** LED blinks with solar color (orange)

### Smart mode waiting shows smart color blink
**Requirement:** `REQ-LED-003`

- **Given** Smart mode, ChargeDelay > 0
- **When** led_compute_color is called when LED is on
- **Then** Color matches ColorSmart

### State A shows dimmed LED
**Requirement:** `REQ-LED-005`

- **Given** State A, Normal mode, no errors
- **When** led_compute_color is called
- **Then** LED shows dimmed green (STATE_A_LED_BRIGHTNESS)

### State B shows full brightness LED
**Requirement:** `REQ-LED-005`

- **Given** State B, Normal mode, no errors
- **When** led_compute_color is called
- **Then** LED shows full brightness green

### State B1 shows full brightness (same as B)
**Requirement:** `REQ-LED-005`

- **Given** State B1, Normal mode
- **When** led_compute_color is called
- **Then** LED shows full brightness green

### State B sets led_count to 128 for smooth C transition
**Requirement:** `REQ-LED-005`

- **Given** State B entered
- **When** led_compute_color is called
- **Then** led_count is set to 128

### State C shows breathing animation
**Requirement:** `REQ-LED-006`

- **Given** State C, Normal mode
- **When** led_compute_color is called multiple times
- **Then** LED brightness varies (breathing effect)

### State C Solar mode has slower breathing
**Requirement:** `REQ-LED-006`

- **Given** State C, Solar mode
- **When** led_compute_color is called
- **Then** led_count increments by 1 per call (vs 2 for other modes)

</details>

---

## LED Color Configuration

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LED-004` | Custom button active when access OFF shows custom color | `test_access_off_custom_button` | `test_led_color.c:204` |
| `REQ-LED-004` | Custom button waiting shows custom color | `test_waiting_custom_button` | `test_led_color.c:294` |
| `REQ-LED-004` | Solar mode State A shows solar orange (dimmed) | `test_state_a_solar_color` | `test_led_color.c:445` |
| `REQ-LED-004` | Custom button overrides mode color in State B | `test_state_b_custom_override` | `test_led_color.c:466` |

<details>
<summary>Detailed steps (4 scenarios)</summary>

### Custom button active when access OFF shows custom color
**Requirement:** `REQ-LED-004`

- **Given** Access OFF and CustomButton is true
- **When** led_compute_color is called
- **Then** LED shows ColorCustom values

### Custom button waiting shows custom color
**Requirement:** `REQ-LED-004`

- **Given** Custom button active, ChargeDelay > 0
- **When** led_compute_color is called when LED is on
- **Then** Color matches ColorCustom

### Solar mode State A shows solar orange (dimmed)
**Requirement:** `REQ-LED-004`

- **Given** State A, Solar mode
- **When** led_compute_color is called
- **Then** LED shows orange tint at STATE_A brightness

### Custom button overrides mode color in State B
**Requirement:** `REQ-LED-004`

- **Given** State B, Normal mode, CustomButton true
- **When** led_compute_color is called
- **Then** LED shows custom blue at full brightness

</details>

---

## LED Color — Public Scheme

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LED-100` | RFID read grey flash wins over all other signals | `test_public_rfid_flash_priority` | `test_led_color.c:498` |
| `REQ-LED-100` | Authorized-grant green flash | `test_public_tx_authorized_green` | `test_led_color.c:518` |
| `REQ-LED-100` | Authorization-rejected red flash | `test_public_tx_rejected_red` | `test_led_color.c:536` |
| `REQ-LED-100` | Auth-timeout red flash | `test_public_tx_timeout_red` | `test_led_color.c:554` |
| `REQ-LED-101` | Reserved ChargePoint status → orange | `test_public_reserved_orange` | `test_led_color.c:572` |
| `REQ-LED-101` | Unavailable ChargePoint status → red | `test_public_unavailable_red` | `test_led_color.c:590` |
| `REQ-LED-101` | Faulted ChargePoint status → red | `test_public_faulted_red` | `test_led_color.c:608` |
| `REQ-LED-102` | Waiting / ChargeDelay → slow orange blink (bright phase) | `test_public_waiting_orange_bright` | `test_led_color.c:626` |
| `REQ-LED-102` | Waiting / ChargeDelay → slow orange blink (dark phase) | `test_public_waiting_orange_dark` | `test_led_color.c:644` |
| `REQ-LED-103` | STATE_A → green (dimmed) = Available | `test_public_state_a_green_dim` | `test_led_color.c:662` |
| `REQ-LED-103` | STATE_B → blue static = EV connected | `test_public_state_b_blue_static` | `test_led_color.c:680` |
| `REQ-LED-103` | STATE_B1 and STATE_MODEM_* also → blue static | `test_public_state_b1_blue_static` | `test_led_color.c:699` |
| `REQ-LED-103` | STATE_C → blue fading (animation advances) | `test_public_state_c_blue_fading` | `test_led_color.c:717` |
| `REQ-LED-104` | Default/unknown state with no signals → all off | `test_public_unknown_state_off` | `test_led_color.c:739` |

<details>
<summary>Detailed steps (14 scenarios)</summary>

### RFID read grey flash wins over all other signals
**Requirement:** `REQ-LED-100`

- **Given** rfid_read_flash true, other flashes also asserted
- **When** led_public_compute is called
- **Then** Returns grey (128,128,128) — highest priority in the decision tree

### Authorized-grant green flash
**Requirement:** `REQ-LED-100`

- **Given** tx_authorized_flash true, no higher-priority signal
- **When** led_public_compute is called
- **Then** Returns green (0,255,0)

### Authorization-rejected red flash
**Requirement:** `REQ-LED-100`

- **Given** tx_rejected_flash true
- **When** led_public_compute is called
- **Then** Returns red (255,0,0)

### Auth-timeout red flash
**Requirement:** `REQ-LED-100`

- **Given** tx_timeout_flash true
- **When** led_public_compute is called
- **Then** Returns red (255,0,0)

### Reserved ChargePoint status → orange
**Requirement:** `REQ-LED-101`

- **Given** cp_status = LED_CP_STATUS_RESERVED, no flashes
- **When** led_public_compute is called
- **Then** Returns orange (255,128,0)

### Unavailable ChargePoint status → red
**Requirement:** `REQ-LED-101`

- **Given** cp_status = LED_CP_STATUS_UNAVAILABLE
- **When** led_public_compute is called
- **Then** Returns red (255,0,0)

### Faulted ChargePoint status → red
**Requirement:** `REQ-LED-101`

- **Given** cp_status = LED_CP_STATUS_FAULTED
- **When** led_public_compute is called
- **Then** Returns red (255,0,0)

### Waiting / ChargeDelay → slow orange blink (bright phase)
**Requirement:** `REQ-LED-102`

- **Given** charge_delay set, led_count seeded past 230
- **When** led_public_compute is called
- **Then** Returns orange at waiting brightness (R=WAITING_LED_BRIGHTNESS, G=R/2, B=0)

### Waiting / ChargeDelay → slow orange blink (dark phase)
**Requirement:** `REQ-LED-102`

- **Given** error flag set, led_count seeded so post-increment is <= 230
- **When** led_public_compute is called
- **Then** Returns (0,0,0) — dark part of the blink

### STATE_A → green (dimmed) = Available
**Requirement:** `REQ-LED-103`

- **Given** state = STATE_A, no flashes, no waiting
- **When** led_public_compute is called
- **Then** Returns (0, STATE_A_LED_BRIGHTNESS, 0)

### STATE_B → blue static = EV connected
**Requirement:** `REQ-LED-103`

- **Given** state = STATE_B
- **When** led_public_compute is called
- **Then** Returns (0, 0, STATE_B_LED_BRIGHTNESS) and seeds led_count=128

### STATE_B1 and STATE_MODEM_* also → blue static
**Requirement:** `REQ-LED-103`

- **Given** state = STATE_B1
- **When** led_public_compute is called
- **Then** Returns (0, 0, STATE_B_LED_BRIGHTNESS)

### STATE_C → blue fading (animation advances)
**Requirement:** `REQ-LED-103`

- **Given** state = STATE_C, led_count incremented across calls
- **When** led_public_compute is called twice
- **Then** Both outputs have R=0, G=0, B>0 and led_count advances

### Default/unknown state with no signals → all off
**Requirement:** `REQ-LED-104`

- **Given** Default snapshot, state is unknown value
- **When** led_public_compute is called
- **Then** Returns (0,0,0) — falls off the decision tree

</details>

---

## Load Balancing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LB-001` | Single standalone EVSE receives full MaxCurrent allocation | `test_single_evse_gets_full_current` | `test_load_balancing.c:1` |
| `REQ-LB-002` | Two EVSEs receive equal current distribution | `test_two_evse_equal_distribution` | `test_load_balancing.c:66` |
| `REQ-LB-003` | Two EVSEs respect MaxCircuit total capacity limit | `test_two_evse_respects_max_circuit` | `test_load_balancing.c:82` |
| `REQ-LB-004` | Individual EVSE BalancedMax caps its current allocation | `test_balanced_max_caps_individual` | `test_load_balancing.c:101` |
| `REQ-LB-006` | Each active EVSE receives at least MinCurrent | `test_minimum_current_enforced` | `test_load_balancing.c:121` |
| `REQ-LB-007` | New EVSE joining (mod=1) triggers full recalculation | `test_mod1_new_evse_recalculates` | `test_load_balancing.c:167` |
| `REQ-LB-008` | OCPP current limit reduces ChargeCurrent below MaxCurrent | `test_ocpp_limit_reduces_charge_current` | `test_load_balancing.c:189` |
| `REQ-LB-009` | OCPP current limit below MinCurrent zeros out ChargeCurrent | `test_ocpp_limit_below_min_zeros_current` | `test_load_balancing.c:215` |
| `REQ-LB-010` | OverrideCurrent takes precedence over calculated ChargeCurrent | `test_override_current_takes_precedence` | `test_load_balancing.c:242` |
| `REQ-LB-011` | Current shortage increments NoCurrent counter | `test_shortage_increments_nocurrent` | `test_load_balancing.c:269` |
| `REQ-LB-012` | No current shortage decays NoCurrent counter | `test_no_shortage_clears_nocurrent` | `test_load_balancing.c:293` |
| `REQ-LB-013` | Open grid relay caps IsetBalanced at GridRelayMaxSumMains per phase | `test_grid_relay_limits_current` | `test_load_balancing.c:317` |
| `REQ-LB-014` | Node EVSE requests COMM_C instead of transitioning directly to STATE_C | `test_node_requests_comm_c` | `test_load_balancing.c:353` |
| `REQ-LB-F1A` | Socket mode (Config=0) caps ChargeCurrent by MaxCapacity | `test_config_socket_caps_by_maxcapacity` | `test_load_balancing.c:381` |
| `REQ-LB-F1B` | Fixed Cable mode (Config=1) does NOT cap by MaxCapacity | `test_config_fixed_cable_no_maxcapacity_cap` | `test_load_balancing.c:408` |
| `REQ-LB-080` | Surplus handout with zero uncapped EVSEs does not crash | `test_handout_surplus_zero_uncapped_no_crash` | `test_load_balancing.c:437` |
| `REQ-LB-081` | Balanced current with zero active EVSEs does not divide by zero | `test_balanced_current_zero_active_no_crash` | `test_load_balancing.c:479` |
| `REQ-LB-082` | NoCurrent counter saturates at 255 instead of wrapping to 0 | `test_nocurrent_saturates_at_255` | `test_load_balancing.c:516` |

<details>
<summary>Detailed steps (18 scenarios)</summary>

### Single standalone EVSE receives full MaxCurrent allocation
**Requirement:** `REQ-LB-001`

- **Given** A standalone EVSE (LoadBl=0) in STATE_C with MaxCurrent=16A
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced is set to 160 (16A in tenths)

### Two EVSEs receive equal current distribution
**Requirement:** `REQ-LB-002`

- **Given** Two EVSEs are charging as master (LoadBl=1) with equal BalancedMax
- **When** evse_calc_balanced_current is called
- **Then** Both EVSEs receive equal Balanced current allocations

### Two EVSEs respect MaxCircuit total capacity limit
**Requirement:** `REQ-LB-003`

- **Given** Two EVSEs are charging with MaxCircuit=16A total
- **When** evse_calc_balanced_current is called
- **Then** Each EVSE receives at most half the circuit capacity

### Individual EVSE BalancedMax caps its current allocation
**Requirement:** `REQ-LB-004`

- **Given** Two EVSEs are charging with EVSE 1 having BalancedMax=60 (6A)
- **When** evse_calc_balanced_current is called
- **Then** EVSE 1 Balanced is capped at its BalancedMax of 60

### Each active EVSE receives at least MinCurrent
**Requirement:** `REQ-LB-006`

- **Given** Two EVSEs are both in STATE_A (disconnected) as master
- **Given** Two EVSEs are charging with MinCurrent=6A and limited total capacity
- **When** evse_calc_balanced_current is called
- **When** evse_calc_balanced_current is called
- **Then** NoCurrent and SolarStopTimer are reset to 0
- **Then** Each charging EVSE with non-zero allocation gets at least MinCurrent*10

### New EVSE joining (mod=1) triggers full recalculation
**Requirement:** `REQ-LB-007`

- **Given** Two EVSEs in MODE_SMART with existing current distribution
- **When** evse_calc_balanced_current is called with mod=1 (new EVSE joining)
- **Then** IsetBalanced is recalculated from scratch (different from previous value)

### OCPP current limit reduces ChargeCurrent below MaxCurrent
**Requirement:** `REQ-LB-008`

- **Given** A standalone EVSE with OcppCurrentLimit=10A and MaxCurrent=16A
- **When** evse_calc_balanced_current is called
- **Then** ChargeCurrent is capped at 100 (10A in tenths) or below

### OCPP current limit below MinCurrent zeros out ChargeCurrent
**Requirement:** `REQ-LB-009`

- **Given** A standalone EVSE with OcppCurrentLimit=3A and MinCurrent=6A
- **When** evse_calc_balanced_current is called
- **Then** ChargeCurrent is set to 0 (below minimum, cannot charge)

### OverrideCurrent takes precedence over calculated ChargeCurrent
**Requirement:** `REQ-LB-010`

- **Given** A standalone EVSE with OverrideCurrent=80 (8A) and MaxCurrent=16A
- **When** evse_calc_balanced_current is called
- **Then** ChargeCurrent is set to 80 (override value)

### Current shortage increments NoCurrent counter
**Requirement:** `REQ-LB-011`

- **Given** Two EVSEs in MODE_SMART with mains heavily loaded and low MaxMains
- **When** evse_calc_balanced_current is called with insufficient capacity
- **Then** NoCurrent counter is incremented above 0

### No current shortage decays NoCurrent counter
**Requirement:** `REQ-LB-012`

- **Given** Two EVSEs in MODE_SMART with low mains load and high MaxMains
- **When** evse_calc_balanced_current is called with sufficient capacity
- **Then** NoCurrent counter decays by 1 (gradual recovery)

### Open grid relay caps IsetBalanced at GridRelayMaxSumMains per phase
**Requirement:** `REQ-LB-013`

- **Given** A standalone EVSE in MODE_SMART with GridRelayOpen=true and 3 phases
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced is capped at GridRelayMaxSumMains*10/3

### Node EVSE requests COMM_C instead of transitioning directly to STATE_C
**Requirement:** `REQ-LB-014`

- **Given** The EVSE is configured as a node (LoadBl=2) in STATE_B with DiodeCheck passed
- **When** A 6V pilot signal is sustained for 500ms (vehicle requests charge)
- **Then** The state transitions to STATE_COMM_C (requesting master permission to charge)

### Socket mode (Config=0) caps ChargeCurrent by MaxCapacity
**Requirement:** `REQ-LB-F1A`

- **Given** Config=0 (Socket), MaxCurrent=25, MaxCapacity=16, STATE_C
- **When** evse_calc_balanced_current is called
- **Then** ChargeCurrent is capped at 160 (MaxCapacity * 10)

### Fixed Cable mode (Config=1) does NOT cap by MaxCapacity
**Requirement:** `REQ-LB-F1B`

- **Given** Config=1 (Fixed Cable), MaxCurrent=25, MaxCapacity=16, STATE_C
- **When** evse_calc_balanced_current is called
- **Then** ChargeCurrent is 250 (MaxCurrent * 10), not capped by MaxCapacity

### Surplus handout with zero uncapped EVSEs does not crash
**Requirement:** `REQ-LB-080`

- **Given** Master with 2 EVSEs in shortage, all EVSEs already at BalancedMax (capped)
- **When** evse_calc_balanced_current triggers priority scheduling with surplus
- **Then** No division by zero occurs and function completes safely

### Balanced current with zero active EVSEs does not divide by zero
**Requirement:** `REQ-LB-081`

- **Given** All EVSEs in STATE_A (no active chargers)
- **When** evse_calc_balanced_current is called
- **Then** No division by zero occurs; Balanced[] values remain at zero

### NoCurrent counter saturates at 255 instead of wrapping to 0
**Requirement:** `REQ-LB-082`

- **Given** NoCurrent is at 254, standalone EVSE in shortage
- **When** evse_calc_balanced_current detects shortage twice
- **Then** NoCurrent reaches 255 and stays there (does not wrap to 0)

</details>

---

## Meter Decoding

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-040` | Register size returns correct byte count per data type | `test_register_size` | `test_meter_decode.c:1` |
| `REQ-MTR-041` | HBF_HWF INT32: big-endian 0x00000064 decodes to 100 | `test_combine_hbf_hwf_int32` | `test_meter_decode.c:41` |
| `REQ-MTR-042` | HBF_HWF INT16: big-endian 0x00C8 decodes to 200 | `test_combine_hbf_hwf_int16` | `test_meter_decode.c:56` |
| `REQ-MTR-043` | HBF_HWF FLOAT32: big-endian IEEE 754 42.5f decodes correctly | `test_combine_hbf_hwf_float32` | `test_meter_decode.c:71` |
| `REQ-MTR-044` | LBF_LWF INT32: little-endian 0x64000000 in bytes decodes to 100 | `test_combine_lbf_lwf_int32` | `test_meter_decode.c:90` |
| `REQ-MTR-045` | LBF_LWF INT16: little-endian 0xC800 in bytes decodes to 200 | `test_combine_lbf_lwf_int16` | `test_meter_decode.c:105` |
| `REQ-MTR-046` | HBF_LWF INT32: word-swapped big-endian decodes correctly | `test_combine_hbf_lwf_int32` | `test_meter_decode.c:122` |
| `REQ-MTR-047` | LBF_HWF INT32: word-swapped little-endian decodes correctly | `test_combine_lbf_hwf_int32` | `test_meter_decode.c:145` |
| `REQ-MTR-048` | INT32 with zero divisor returns raw value | `test_decode_int32_divisor_zero` | `test_meter_decode.c:166` |
| `REQ-MTR-049` | INT32 with positive divisor divides by power of 10 | `test_decode_int32_positive_divisor` | `test_meter_decode.c:183` |
| `REQ-MTR-050` | INT32 with negative divisor multiplies by power of 10 | `test_decode_int32_negative_divisor` | `test_meter_decode.c:199` |
| `REQ-MTR-051` | INT16 positive value with divisor | `test_decode_int16_positive` | `test_meter_decode.c:218` |
| `REQ-MTR-052` | INT16 sign extension: negative value 0xFFCE = -50 | `test_decode_int16_sign_extension` | `test_meter_decode.c:235` |
| `REQ-MTR-053` | FLOAT32 with zero divisor returns truncated integer | `test_decode_float32_divisor_zero` | `test_meter_decode.c:254` |
| `REQ-MTR-054` | FLOAT32 with negative divisor: multiply 2.345 by 1000 | `test_decode_float32_negative_divisor` | `test_meter_decode.c:271` |
| `REQ-MTR-055` | FLOAT32 with positive divisor: divide 23450.0 by 10 | `test_decode_float32_positive_divisor` | `test_meter_decode.c:288` |
| `REQ-MTR-056` | Index parameter selects correct register from buffer | `test_decode_index_offset` | `test_meter_decode.c:307` |
| `REQ-MTR-057` | INT16 index offset uses 2-byte stride | `test_decode_int16_index_offset` | `test_meter_decode.c:333` |
| `REQ-MTR-058` | Negative INT32 value decodes correctly | `test_decode_int32_negative` | `test_meter_decode.c:357` |
| `REQ-MTR-059` | Negative FLOAT32 value decodes correctly | `test_decode_float32_negative` | `test_meter_decode.c:376` |
| `REQ-MTR-060` | NULL buffer returns invalid result | `test_decode_null_buffer` | `test_meter_decode.c:395` |
| `REQ-MTR-061` | Invalid datatype returns invalid result | `test_decode_invalid_datatype` | `test_meter_decode.c:409` |
| `REQ-MTR-062` | Divisor out of pow10 range returns invalid result | `test_decode_divisor_out_of_range` | `test_meter_decode.c:424` |
| `REQ-MTR-063` | NULL pointer to meter_combine_bytes does not crash | `test_combine_null_safety` | `test_meter_decode.c:439` |
| `REQ-MTR-064` | Phoenix Contact meter HBF_LWF INT32 current reading | `test_phoenix_contact_current` | `test_meter_decode.c:458` |
| `REQ-MTR-065` | Eastron SDM630 HBF_HWF FLOAT32 current reading | `test_eastron_float_current` | `test_meter_decode.c:477` |
| `REQ-MTR-066` | Orno WE-517 3-phase current reading at register 0x0C | `test_orno3p_current` | `test_meter_decode.c:496` |
| `REQ-MTR-067` | Orno WE-517 total active power reading | `test_orno3p_power` | `test_meter_decode.c:522` |
| `REQ-MTR-068` | Orno WE-517 import energy reading in kWh | `test_orno3p_energy` | `test_meter_decode.c:539` |
| `REQ-MTR-069` | Orno WE-517 negative power during export (solar feed-in) | `test_orno3p_negative_power` | `test_meter_decode.c:557` |
| `REQ-MTR-087` | INT8_MIN divisor (-128) is rejected to avoid negation UB | `test_decode_divisor_int8_min` | `test_meter_decode.c:576` |
| `REQ-MTR-088` | FLOAT32 NaN value from corrupt meter data is rejected | `test_decode_float32_nan_rejected` | `test_meter_decode.c:591` |
| `REQ-MTR-089` | FLOAT32 Infinity value from corrupt meter data is rejected | `test_decode_float32_inf_rejected` | `test_meter_decode.c:607` |
| `REQ-MTR-090` | INT32 multiplication overflow is detected and rejected | `test_decode_int32_multiply_overflow` | `test_meter_decode.c:623` |
| `REQ-MTR-091` | INT32 multiplication that fits is still accepted | `test_decode_int32_multiply_max_valid` | `test_meter_decode.c:640` |
| `REQ-MTR-092` | Negative INT32 multiplication overflow is detected | `test_decode_int32_negative_multiply_overflow` | `test_meter_decode.c:657` |

<details>
<summary>Detailed steps (36 scenarios)</summary>

### Register size returns correct byte count per data type
**Requirement:** `REQ-MTR-040`

- **Given** The three supported data types
- **When** meter_register_size is called for each
- **Then** INT16 returns 2, INT32 returns 4, FLOAT32 returns 4

### HBF_HWF INT32: big-endian 0x00000064 decodes to 100
**Requirement:** `REQ-MTR-041`

- **Given** 4 bytes in big-endian order representing value 100
- **When** meter_combine_bytes is called with ENDIANNESS_HBF_HWF, INT32
- **Then** Output equals 100

### HBF_HWF INT16: big-endian 0x00C8 decodes to 200
**Requirement:** `REQ-MTR-042`

- **Given** 2 bytes in big-endian order representing value 200
- **When** meter_combine_bytes is called with ENDIANNESS_HBF_HWF, INT16
- **Then** Output equals 200

### HBF_HWF FLOAT32: big-endian IEEE 754 42.5f decodes correctly
**Requirement:** `REQ-MTR-043`

- **Given** 4 bytes representing float 42.5 in big-endian
- **When** meter_combine_bytes is called with ENDIANNESS_HBF_HWF, FLOAT32
- **Then** Output float equals 42.5

### LBF_LWF INT32: little-endian 0x64000000 in bytes decodes to 100
**Requirement:** `REQ-MTR-044`

- **Given** 4 bytes in little-endian order representing value 100
- **When** meter_combine_bytes is called with ENDIANNESS_LBF_LWF, INT32
- **Then** Output equals 100

### LBF_LWF INT16: little-endian 0xC800 in bytes decodes to 200
**Requirement:** `REQ-MTR-045`

- **Given** 2 bytes in little-endian order representing value 200
- **When** meter_combine_bytes is called with ENDIANNESS_LBF_LWF, INT16
- **Then** Output equals 200

### HBF_LWF INT32: word-swapped big-endian decodes correctly
**Requirement:** `REQ-MTR-046`

- **Given** 4 bytes: low word [0x00, 0x01] then high word [0x00, 0x00] = value 1
- **When** meter_combine_bytes is called with ENDIANNESS_HBF_LWF, INT32
- **Then** Output equals 1

### LBF_HWF INT32: word-swapped little-endian decodes correctly
**Requirement:** `REQ-MTR-047`

- **Given** 4 bytes: high word [0x00, 0x00] then low word [0x64, 0x00] = value 100
- **When** meter_combine_bytes is called with ENDIANNESS_LBF_HWF, INT32
- **Then** Output equals 100

### INT32 with zero divisor returns raw value
**Requirement:** `REQ-MTR-048`

- **Given** Big-endian INT32 buffer with value 12345
- **When** meter_decode_value is called with divisor=0
- **Then** Result value is 12345

### INT32 with positive divisor divides by power of 10
**Requirement:** `REQ-MTR-049`

- **Given** Big-endian INT32 buffer with value 12345
- **When** meter_decode_value is called with divisor=2 (divide by 100)
- **Then** Result value is 123

### INT32 with negative divisor multiplies by power of 10
**Requirement:** `REQ-MTR-050`

- **Given** Big-endian INT32 buffer with value 42
- **When** meter_decode_value is called with divisor=-3 (multiply by 1000)
- **Then** Result value is 42000

### INT16 positive value with divisor
**Requirement:** `REQ-MTR-051`

- **Given** Big-endian INT16 buffer with value 2500
- **When** meter_decode_value is called with divisor=1 (divide by 10)
- **Then** Result value is 250

### INT16 sign extension: negative value 0xFFCE = -50
**Requirement:** `REQ-MTR-052`

- **Given** Big-endian INT16 buffer with value -50 (0xFFCE)
- **When** meter_decode_value is called with divisor=0
- **Then** Result value is -50 (sign-extended to 32-bit)

### FLOAT32 with zero divisor returns truncated integer
**Requirement:** `REQ-MTR-053`

- **Given** Big-endian FLOAT32 buffer with value 230.5
- **When** meter_decode_value is called with divisor=0
- **Then** Result value is 230 (truncated from 230.5)

### FLOAT32 with negative divisor: multiply 2.345 by 1000
**Requirement:** `REQ-MTR-054`

- **Given** Big-endian FLOAT32 buffer with value 2.345
- **When** meter_decode_value is called with divisor=-3 (multiply by 1000)
- **Then** Result value is 2345

### FLOAT32 with positive divisor: divide 23450.0 by 10
**Requirement:** `REQ-MTR-055`

- **Given** Big-endian FLOAT32 buffer with value 23450.0
- **When** meter_decode_value is called with divisor=1 (divide by 10)
- **Then** Result value is 2345

### Index parameter selects correct register from buffer
**Requirement:** `REQ-MTR-056`

- **Given** A buffer with 3 INT32 values in big-endian: [100, 200, 300]
- **When** meter_decode_value is called with index=0, 1, and 2
- **Then** Returns 100, 200, 300 respectively

### INT16 index offset uses 2-byte stride
**Requirement:** `REQ-MTR-057`

- **Given** A buffer with 3 INT16 values in big-endian: [10, 20, 30]
- **When** meter_decode_value is called with index=0, 1, and 2
- **Then** Returns 10, 20, 30 respectively

### Negative INT32 value decodes correctly
**Requirement:** `REQ-MTR-058`

- **Given** Big-endian INT32 buffer with value -1000 (0xFFFFFC18)
- **When** meter_decode_value is called with divisor=0
- **Then** Result value is -1000

### Negative FLOAT32 value decodes correctly
**Requirement:** `REQ-MTR-059`

- **Given** Big-endian FLOAT32 buffer with value -5.0
- **When** meter_decode_value is called with divisor=0
- **Then** Result value is -5

### NULL buffer returns invalid result
**Requirement:** `REQ-MTR-060`

- **Given** A NULL buffer pointer
- **When** meter_decode_value is called
- **Then** Result valid is 0

### Invalid datatype returns invalid result
**Requirement:** `REQ-MTR-061`

- **Given** A valid buffer but datatype=METER_DATATYPE_MAX (out of range)
- **When** meter_decode_value is called
- **Then** Result valid is 0

### Divisor out of pow10 range returns invalid result
**Requirement:** `REQ-MTR-062`

- **Given** A valid buffer with divisor=10 (exceeds pow10_table size)
- **When** meter_decode_value is called
- **Then** Result valid is 0

### NULL pointer to meter_combine_bytes does not crash
**Requirement:** `REQ-MTR-063`

- **Given** NULL out and buf pointers
- **When** meter_combine_bytes is called
- **Then** No crash occurs

### Phoenix Contact meter HBF_LWF INT32 current reading
**Requirement:** `REQ-MTR-064`

- **Given** Phoenix Contact response with current 23.12A encoded as 23120 mA in HBF_LWF INT32
- **When** meter_decode_value is called with divisor=3 (divide by 1000 to get 0.1A units)
- **Then** Result value is 23 (23.12A in deciAmpere after /1000 = 23)

### Eastron SDM630 HBF_HWF FLOAT32 current reading
**Requirement:** `REQ-MTR-065`

- **Given** Eastron response with 16.5A encoded as IEEE 754 float in HBF_HWF
- **When** meter_decode_value is called with divisor=-3 (multiply by 1000 for mA)
- **Then** Result value is 16500 (mA)

### Orno WE-517 3-phase current reading at register 0x0C
**Requirement:** `REQ-MTR-066`

- **Given** Orno response with 3 phase currents [8.5A, 12.3A, 6.7A] as FLOAT32 HBF_HWF
- **When** meter_decode_value is called for indices 0, 1, 2 with divisor=0
- **Then** Returns 8, 12, 6 (truncated integer amps)

### Orno WE-517 total active power reading
**Requirement:** `REQ-MTR-067`

- **Given** Orno response with total power 3456.7W as FLOAT32 HBF_HWF at register 0x1C
- **When** meter_decode_value is called with divisor=0
- **Then** Returns 3456

### Orno WE-517 import energy reading in kWh
**Requirement:** `REQ-MTR-068`

- **Given** Orno response with 1234.567 kWh as FLOAT32 HBF_HWF at register 0x0100
- **When** meter_decode_value is called with divisor=-3 (multiply by 1000 to get Wh)
- **Then** Returns 1234567 (Wh)

### Orno WE-517 negative power during export (solar feed-in)
**Requirement:** `REQ-MTR-069`

- **Given** Orno response with -1500.0W as FLOAT32 HBF_HWF
- **When** meter_decode_value is called with divisor=0
- **Then** Returns -1500

### INT8_MIN divisor (-128) is rejected to avoid negation UB
**Requirement:** `REQ-MTR-087`

- **Given** A valid buffer and divisor=-128 (INT8_MIN)
- **When** meter_decode_value is called
- **Then** Result is invalid because -128 is outside pow10 table range

### FLOAT32 NaN value from corrupt meter data is rejected
**Requirement:** `REQ-MTR-088`

- **Given** Buffer containing IEEE 754 NaN bit pattern (0x7FC00000)
- **When** meter_decode_value is called with FLOAT32 datatype
- **Then** Result is invalid

### FLOAT32 Infinity value from corrupt meter data is rejected
**Requirement:** `REQ-MTR-089`

- **Given** Buffer containing IEEE 754 +Infinity bit pattern (0x7F800000)
- **When** meter_decode_value is called with FLOAT32 datatype
- **Then** Result is invalid

### INT32 multiplication overflow is detected and rejected
**Requirement:** `REQ-MTR-090`

- **Given** Buffer with INT32 value near INT32_MAX/1000 and divisor=-3
- **When** meter_decode_value is called
- **Then** Result is invalid because value * 1000 would overflow int32_t

### INT32 multiplication that fits is still accepted
**Requirement:** `REQ-MTR-091`

- **Given** Buffer with INT32 value 2147483 and divisor=-3
- **When** meter_decode_value is called
- **Then** Result is valid with value 2147483000

### Negative INT32 multiplication overflow is detected
**Requirement:** `REQ-MTR-092`

- **Given** Buffer with large negative INT32 value and divisor=-3
- **When** meter_decode_value is called
- **Then** Result is invalid because value * 1000 would overflow

</details>

---

## Meter Timeout & Recovery

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-METER-001` | CT_NOCOMM error is set on timeout and cleared when communication restores | `test_ct_nocomm_set_then_restored` | `test_meter_recovery.c:1` |
| `REQ-METER-002` | EV_NOCOMM error is set on timeout and cleared when communication restores | `test_ev_nocomm_set_then_restored` | `test_meter_recovery.c:51` |
| `REQ-METER-003` | Both CT_NOCOMM and EV_NOCOMM can be set simultaneously and recover independently | `test_both_ct_and_ev_nocomm_simultaneously` | `test_meter_recovery.c:77` |
| `REQ-METER-004` | Mains meter timeout during STATE_C triggers transition to STATE_C1 | `test_mains_timeout_during_state_c` | `test_meter_recovery.c:118` |
| `REQ-METER-005` | EV meter timeout during STATE_C triggers transition to STATE_C1 | `test_ev_timeout_during_state_c` | `test_meter_recovery.c:145` |
| `REQ-METER-006` | MainsMeter timeout on node sets CT_NOCOMM regardless of operating mode | `test_mains_timeout_on_node` | `test_meter_recovery.c:175` |
| `REQ-METER-007` | MainsMeter timeout on standalone in Normal mode does not set CT_NOCOMM | `test_mains_timeout_master_normal_mode_ignored` | `test_meter_recovery.c:196` |
| `REQ-METER-008` | No EV meter installed continuously resets EVMeterTimeout to COMM_EVTIMEOUT | `test_no_ev_meter_resets_timeout_continuously` | `test_meter_recovery.c:221` |
| `REQ-METER-009` | No mains meter type and standalone resets MainsMeterTimeout to COMM_TIMEOUT | `test_no_mains_meter_resets_timeout_continuously` | `test_meter_recovery.c:248` |
| `REQ-METER-010` | Temperature recovery requires strictly below hysteresis boundary | `test_temp_recovery_exactly_at_boundary` | `test_meter_recovery.c:269` |
| `REQ-METER-011` | Temperature recovery clears TEMP_HIGH when one degree below hysteresis boundary | `test_temp_recovery_one_below_boundary` | `test_meter_recovery.c:288` |
| `REQ-METER-012` | Mains meter countdown sequence from 3 to 0 then CT_NOCOMM on next tick | `test_mains_meter_countdown_to_error` | `test_meter_recovery.c:309` |

<details>
<summary>Detailed steps (12 scenarios)</summary>

### CT_NOCOMM error is set on timeout and cleared when communication restores
**Requirement:** `REQ-METER-001`

- **Given** EVSE is in Smart mode standalone with MainsMeterType=1 and MainsMeterTimeout=0
- **When** A 1-second tick sets CT_NOCOMM, then MainsMeterTimeout is restored to 5 and another tick occurs
- **Then** CT_NOCOMM is set after the first tick and cleared after the second tick

### EV_NOCOMM error is set on timeout and cleared when communication restores
**Requirement:** `REQ-METER-002`

- **Given** EVSE is in Smart mode with EVMeterType=1 and EVMeterTimeout=0
- **When** A 1-second tick sets EV_NOCOMM, then EVMeterTimeout is restored to 10 and another tick occurs
- **Then** EV_NOCOMM is set after the first tick and cleared after the second tick

### Both CT_NOCOMM and EV_NOCOMM can be set simultaneously and recover independently
**Requirement:** `REQ-METER-003`

- **Given** EVSE is in Smart mode with both MainsMeterTimeout=0 and EVMeterTimeout=0
- **When** Both timeouts expire, then mains meter is restored first, then EV meter is restored
- **Then** Each NOCOMM flag is set and cleared independently as its respective meter recovers

### Mains meter timeout during STATE_C triggers transition to STATE_C1
**Requirement:** `REQ-METER-004`

- **Given** EVSE is in Smart mode standalone in STATE_C with high mains load and MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM is set and EVSE transitions from STATE_C to STATE_C1 (charging suspended)

### EV meter timeout during STATE_C triggers transition to STATE_C1
**Requirement:** `REQ-METER-005`

- **Given** EVSE is in Smart mode standalone in STATE_C with EVMeterType=1 and EVMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** EV_NOCOMM is set and EVSE transitions from STATE_C to STATE_C1 (charging suspended)

### MainsMeter timeout on node sets CT_NOCOMM regardless of operating mode
**Requirement:** `REQ-METER-006`

- **Given** EVSE is a node (LoadBl=3) in Normal mode with MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM is set because nodes do not have the MODE_NORMAL guard for timeout checks

### MainsMeter timeout on standalone in Normal mode does not set CT_NOCOMM
**Requirement:** `REQ-METER-007`

- **Given** EVSE is standalone (LoadBl=0) in MODE_NORMAL with MainsMeterType=1 and MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM is not set because the MODE_NORMAL guard skips the timeout check for master/standalone

### No EV meter installed continuously resets EVMeterTimeout to COMM_EVTIMEOUT
**Requirement:** `REQ-METER-008`

- **Given** EVSE has EVMeterType=0 (no EV meter installed) with EVMeterTimeout artificially lowered
- **When** 1-second ticks occur even with EVMeterTimeout set to 0
- **Then** EVMeterTimeout is always reset to COMM_EVTIMEOUT and EV_NOCOMM is never set

### No mains meter type and standalone resets MainsMeterTimeout to COMM_TIMEOUT
**Requirement:** `REQ-METER-009`

- **Given** EVSE has MainsMeterType=0 and LoadBl=0 with MainsMeterTimeout artificially lowered to 3
- **When** A 1-second tick occurs
- **Then** MainsMeterTimeout is reset to COMM_TIMEOUT because no mains meter is configured

### Temperature recovery requires strictly below hysteresis boundary
**Requirement:** `REQ-METER-010`

- **Given** EVSE has TEMP_HIGH error with maxTemp=65 and TempEVSE=55 (exactly at maxTemp-10)
- **When** A 1-second tick occurs
- **Then** TEMP_HIGH error remains set because recovery requires TempEVSE < (maxTemp - 10), not <=

### Temperature recovery clears TEMP_HIGH when one degree below hysteresis boundary
**Requirement:** `REQ-METER-011`

- **Given** EVSE has TEMP_HIGH error with maxTemp=65 and TempEVSE=54 (one below maxTemp-10)
- **When** A 1-second tick occurs
- **Then** TEMP_HIGH error is cleared because 54 < 55 (maxTemp - 10) satisfies the recovery condition

### Mains meter countdown sequence from 3 to 0 then CT_NOCOMM on next tick
**Requirement:** `REQ-METER-012`

- **Given** EVSE is in Smart mode standalone with MainsMeterType=1 and MainsMeterTimeout=3
- **When** Four consecutive 1-second ticks occur decrementing the timeout
- **Then** CT_NOCOMM remains clear during countdown (3 to 0) and is set on the tick after reaching 0

</details>

---

## Meter Telemetry

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-001` | Initialization zeros all counters and metadata | `test_init_zeros_all` | `test_meter_telemetry.c:1` |
| `REQ-MTR-002` | Configure sets meter type and address for a slot | `test_configure_sets_type_and_address` | `test_meter_telemetry.c:50` |
| `REQ-MTR-003` | Each counter increments independently | `test_increment_counters_independently` | `test_meter_telemetry.c:71` |
| `REQ-MTR-004` | Counters on different slots are independent | `test_slots_are_independent` | `test_meter_telemetry.c:98` |
| `REQ-MTR-005` | Counter saturates at UINT32_MAX instead of wrapping | `test_counter_saturates_at_max` | `test_meter_telemetry.c:124` |
| `REQ-MTR-006` | Reset slot zeros counters but preserves type and address | `test_reset_slot_preserves_config` | `test_meter_telemetry.c:147` |
| `REQ-MTR-007` | Reset all zeros counters on every slot but preserves each slot's config | `test_reset_all_preserves_config` | `test_meter_telemetry.c:172` |
| `REQ-MTR-008` | Out-of-range slot returns NULL and does not crash | `test_out_of_range_slot_safe` | `test_meter_telemetry.c:200` |
| `REQ-MTR-009` | Error rate is zero when no requests have been sent | `test_error_rate_zero_requests` | `test_meter_telemetry.c:227` |
| `REQ-MTR-010` | Error rate calculated correctly from CRC errors and timeouts | `test_error_rate_mixed_errors` | `test_meter_telemetry.c:240` |
| `REQ-MTR-011` | Error rate caps at 100% when errors exceed requests | `test_error_rate_caps_at_100` | `test_meter_telemetry.c:257` |
| `REQ-MTR-012` | Error rate for out-of-range slot returns 0 | `test_error_rate_invalid_slot` | `test_meter_telemetry.c:273` |
| `REQ-MTR-013` | All functions handle NULL pointer without crashing | `test_null_pointer_safety` | `test_meter_telemetry.c:288` |

<details>
<summary>Detailed steps (13 scenarios)</summary>

### Initialization zeros all counters and metadata
**Requirement:** `REQ-MTR-001`

- **Given** An uninitialized meter_telemetry_t struct
- **When** meter_telemetry_init is called
- **Then** All counters, meter types, and addresses are zero

### Configure sets meter type and address for a slot
**Requirement:** `REQ-MTR-002`

- **Given** An initialized telemetry struct
- **When** meter_telemetry_configure is called with type=4 (Eastron3P) and address=10
- **Then** The slot reflects the configured type and address

### Each counter increments independently
**Requirement:** `REQ-MTR-003`

- **Given** An initialized telemetry struct with mains slot configured
- **When** request, response, crc_error, and timeout are each incremented different numbers of times
- **Then** Each counter reflects only its own increments

### Counters on different slots are independent
**Requirement:** `REQ-MTR-004`

- **Given** An initialized telemetry struct with mains and EV slots configured
- **When** Mains slot gets 5 requests and EV slot gets 2 requests
- **Then** Each slot reflects only its own request count

### Counter saturates at UINT32_MAX instead of wrapping
**Requirement:** `REQ-MTR-005`

- **Given** A telemetry struct with request_count set to UINT32_MAX - 1
- **When** request is incremented twice
- **Then** Counter reaches UINT32_MAX and stays there

### Reset slot zeros counters but preserves type and address
**Requirement:** `REQ-MTR-006`

- **Given** A mains slot with type=4, address=10, and non-zero counters
- **When** meter_telemetry_reset_slot is called
- **Then** All counters are zero but meter_type=4 and meter_address=10 are preserved

### Reset all zeros counters on every slot but preserves each slot's config
**Requirement:** `REQ-MTR-007`

- **Given** Mains and EV slots are configured with non-zero counters
- **When** meter_telemetry_reset_all is called
- **Then** All counters are zero and both slots retain their type and address

### Out-of-range slot returns NULL and does not crash
**Requirement:** `REQ-MTR-008`

- **Given** An initialized telemetry struct
- **When** get, increment, configure, and reset are called with slot=METER_TELEMETRY_MAX_METERS
- **Then** get returns NULL and no crash occurs

### Error rate is zero when no requests have been sent
**Requirement:** `REQ-MTR-009`

- **Given** An initialized telemetry struct with zero request count
- **When** meter_telemetry_error_rate is called
- **Then** Returns 0

### Error rate calculated correctly from CRC errors and timeouts
**Requirement:** `REQ-MTR-010`

- **Given** 100 requests with 3 CRC errors and 7 timeouts
- **When** meter_telemetry_error_rate is called
- **Then** Returns 10 (10%)

### Error rate caps at 100% when errors exceed requests
**Requirement:** `REQ-MTR-011`

- **Given** 10 requests with 15 timeout errors (more errors than requests due to counter manipulation)
- **When** meter_telemetry_error_rate is called
- **Then** Returns 100 (capped)

### Error rate for out-of-range slot returns 0
**Requirement:** `REQ-MTR-012`

- **Given** An initialized telemetry struct
- **When** meter_telemetry_error_rate is called with an invalid slot
- **Then** Returns 0

### All functions handle NULL pointer without crashing
**Requirement:** `REQ-MTR-013`

- **Given** A NULL meter_telemetry_t pointer
- **When** All API functions are called with NULL
- **Then** No crash occurs, get returns NULL, error_rate returns 0

</details>

---

## Metering Diagnostics

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-030` | All diagnostic counters are zero after initialization | `test_counters_zero_after_init` | `test_metering_diagnostics.c:1` |
| `REQ-MTR-031` | meter_timeout_count increments when CT_NOCOMM is set | `test_timeout_count_increments_on_ct_nocomm` | `test_metering_diagnostics.c:37` |
| `REQ-MTR-032` | meter_timeout_count increments for node (LoadBl > 1) | `test_timeout_count_increments_on_node_ct_nocomm` | `test_metering_diagnostics.c:59` |
| `REQ-MTR-033` | meter_recovery_count increments when CT_NOCOMM clears | `test_recovery_count_increments` | `test_metering_diagnostics.c:80` |
| `REQ-MTR-034` | api_stale_count increments when API data goes stale | `test_api_stale_count_increments` | `test_metering_diagnostics.c:109` |
| `REQ-MTR-035` | Counters accumulate across multiple events | `test_counters_are_cumulative` | `test_metering_diagnostics.c:135` |
| `REQ-MTR-036` | meter_timeout_count does NOT increment when CT_NOCOMM is suppressed for API mode | `test_timeout_count_not_incremented_when_suppressed` | `test_metering_diagnostics.c:172` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### All diagnostic counters are zero after initialization
**Requirement:** `REQ-MTR-030`

- **Given** A freshly initialized EVSE context
- **When** evse_init completes
- **Then** meter_timeout_count, meter_recovery_count, and api_stale_count are all 0

### meter_timeout_count increments when CT_NOCOMM is set
**Requirement:** `REQ-MTR-031`

- **Given** EVSE in Smart mode with MainsMeterType=1 and MainsMeterTimeout=0
- **When** A 1-second tick triggers CT_NOCOMM
- **Then** meter_timeout_count increments by 1

### meter_timeout_count increments for node (LoadBl > 1)
**Requirement:** `REQ-MTR-032`

- **Given** EVSE as node with LoadBl=2 and MainsMeterTimeout=0
- **When** A 1-second tick triggers CT_NOCOMM
- **Then** meter_timeout_count increments by 1

### meter_recovery_count increments when CT_NOCOMM clears
**Requirement:** `REQ-MTR-033`

- **Given** EVSE with CT_NOCOMM set and MainsMeterTimeout restored to >0
- **When** A 1-second tick clears CT_NOCOMM
- **Then** meter_recovery_count increments by 1

### api_stale_count increments when API data goes stale
**Requirement:** `REQ-MTR-034`

- **Given** EVSE in API mode with staleness timer about to expire
- **When** Timer reaches 0
- **Then** api_stale_count increments by 1

### Counters accumulate across multiple events
**Requirement:** `REQ-MTR-035`

- **Given** EVSE that has already had one timeout and recovery
- **When** Another timeout and recovery cycle occurs
- **Then** Counters show 2 timeouts and 2 recoveries

### meter_timeout_count does NOT increment when CT_NOCOMM is suppressed for API mode
**Requirement:** `REQ-MTR-036`

- **Given** EVSE in API mode with staleness enabled and MainsMeterTimeout=0
- **When** A 1-second tick occurs (CT_NOCOMM suppressed)
- **Then** meter_timeout_count remains 0

</details>

---

## Modbus Frame Decoding

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-020` | Frame init zeros all fields and sets Type to MODBUS_INVALID | `test_frame_init` | `test_modbus_decode.c:1` |
| `REQ-MTR-021` | FC04 read input register request is parsed correctly | `test_fc04_read_request` | `test_modbus_decode.c:53` |
| `REQ-MTR-022` | FC03 read holding register request is parsed the same as FC04 | `test_fc03_read_request` | `test_modbus_decode.c:74` |
| `REQ-MTR-023` | FC04 response with 4 bytes of data is parsed correctly | `test_fc04_response` | `test_modbus_decode.c:95` |
| `REQ-MTR-024` | FC06 write single register as initial request (no pending request) | `test_fc06_as_request` | `test_modbus_decode.c:129` |
| `REQ-MTR-025` | FC06 echo treated as response when matching pending request | `test_fc06_as_response` | `test_modbus_decode.c:150` |
| `REQ-MTR-026` | FC06 to broadcast address is always treated as request | `test_fc06_broadcast_is_request` | `test_modbus_decode.c:174` |
| `REQ-MTR-027` | FC10 response (6 bytes) is parsed correctly | `test_fc10_response` | `test_modbus_decode.c:195` |
| `REQ-MTR-028` | FC10 request with data payload is parsed correctly | `test_fc10_request_with_data` | `test_modbus_decode.c:213` |
| `REQ-MTR-029` | 3-byte exception frame is parsed correctly | `test_exception_frame` | `test_modbus_decode.c:241` |
| `REQ-MTR-030` | Buffer too short (< 3 bytes) results in MODBUS_INVALID | `test_too_short_buffer` | `test_modbus_decode.c:262` |
| `REQ-MTR-031` | 4-byte buffer (between exception and minimum data) results in MODBUS_INVALID | `test_four_byte_buffer_invalid` | `test_modbus_decode.c:278` |
| `REQ-MTR-032` | FC04 response with mismatched byte count results in MODBUS_INVALID | `test_fc04_response_length_mismatch` | `test_modbus_decode.c:294` |
| `REQ-MTR-033` | NULL pointer arguments do not crash | `test_null_safety` | `test_modbus_decode.c:311` |
| `REQ-MTR-034` | Unknown function code results in MODBUS_INVALID | `test_unknown_function_code` | `test_modbus_decode.c:330` |

<details>
<summary>Detailed steps (15 scenarios)</summary>

### Frame init zeros all fields and sets Type to MODBUS_INVALID
**Requirement:** `REQ-MTR-020`

- **Given** An uninitialized modbus_frame_t
- **When** modbus_frame_init is called
- **Then** All fields are zero and Type is MODBUS_INVALID

### FC04 read input register request is parsed correctly
**Requirement:** `REQ-MTR-021`

- **Given** A 6-byte FC04 request: address=0x0A, register=0x0006, count=12
- **When** modbus_decode is called
- **Then** Type=MODBUS_REQUEST, Address=0x0A, Function=0x04, Register=0x0006, RegisterCount=12

### FC03 read holding register request is parsed the same as FC04
**Requirement:** `REQ-MTR-022`

- **Given** A 6-byte FC03 request: address=0x01, register=0x5B0C, count=16
- **When** modbus_decode is called
- **Then** Type=MODBUS_REQUEST, Function=0x03, Register=0x5B0C, RegisterCount=16

### FC04 response with 4 bytes of data is parsed correctly
**Requirement:** `REQ-MTR-023`

- **Given** A FC04 response: address=0x0A, bytecount=4, data=[0x00,0x64,0x00,0xC8]
- **When** modbus_decode is called with a pending request for register 0x0006
- **Then** Type=MODBUS_RESPONSE, DataLength=4, Register=0x0006, Data points to payload

### FC06 write single register as initial request (no pending request)
**Requirement:** `REQ-MTR-024`

- **Given** A 6-byte FC06 packet: address=0x02, register=0x0100, value=0x0020
- **When** modbus_decode is called with no pending request
- **Then** Type=MODBUS_REQUEST, Register=0x0100, Value=0x0020

### FC06 echo treated as response when matching pending request
**Requirement:** `REQ-MTR-025`

- **Given** A 6-byte FC06 packet with a pending request matching address and function
- **When** modbus_decode is called
- **Then** Type=MODBUS_RESPONSE (disambiguated from MODBUS_OK)

### FC06 to broadcast address is always treated as request
**Requirement:** `REQ-MTR-026`

- **Given** A 6-byte FC06 packet to broadcast address 0x09 with matching pending request
- **When** modbus_decode is called
- **Then** Type=MODBUS_REQUEST (broadcast is never a response)

### FC10 response (6 bytes) is parsed correctly
**Requirement:** `REQ-MTR-027`

- **Given** A 6-byte FC10 response: address=0x01, register=0x0020, count=8
- **When** modbus_decode is called
- **Then** Type=MODBUS_RESPONSE, Register=0x0020, RegisterCount=8

### FC10 request with data payload is parsed correctly
**Requirement:** `REQ-MTR-028`

- **Given** An FC10 request: address=0x09, register=0x0020, count=2, bytecount=4, data=[0x00,0x3C,0x00,0x50]
- **When** modbus_decode is called
- **Then** Type=MODBUS_REQUEST, DataLength=4, Data points to the 4-byte payload

### 3-byte exception frame is parsed correctly
**Requirement:** `REQ-MTR-029`

- **Given** A 3-byte exception: address=0x0A, function=0x84, exception=0x02
- **When** modbus_decode is called
- **Then** Type=MODBUS_EXCEPTION, Exception=0x02

### Buffer too short (< 3 bytes) results in MODBUS_INVALID
**Requirement:** `REQ-MTR-030`

- **Given** A 2-byte buffer
- **When** modbus_decode is called
- **Then** Type=MODBUS_INVALID

### 4-byte buffer (between exception and minimum data) results in MODBUS_INVALID
**Requirement:** `REQ-MTR-031`

- **Given** A 4-byte buffer that is neither an exception nor a valid data packet
- **When** modbus_decode is called
- **Then** Type=MODBUS_INVALID

### FC04 response with mismatched byte count results in MODBUS_INVALID
**Requirement:** `REQ-MTR-032`

- **Given** A FC04 response where bytecount (10) does not match actual data length
- **When** modbus_decode is called
- **Then** Type=MODBUS_INVALID because DataLength != len - 3

### NULL pointer arguments do not crash
**Requirement:** `REQ-MTR-033`

- **Given** NULL frame or buffer pointer
- **When** modbus_decode is called
- **Then** No crash occurs

### Unknown function code results in MODBUS_INVALID
**Requirement:** `REQ-MTR-034`

- **Given** A 6-byte frame with function code 0x01 (read coils, not supported)
- **When** modbus_decode is called
- **Then** Type=MODBUS_INVALID

</details>

---

## Modbus Frame Logging

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-090` | Init zeros all ring buffer fields | `test_log_init` | `test_modbus_log.c:1` |
| `REQ-MTR-091` | Append and retrieve a single entry | `test_log_single_entry` | `test_modbus_log.c:42` |
| `REQ-MTR-092` | Multiple entries maintain chronological order | `test_log_order` | `test_modbus_log.c:68` |
| `REQ-MTR-093` | Ring buffer wraps around and overwrites oldest entries | `test_log_wraparound` | `test_modbus_log.c:90` |
| `REQ-MTR-094` | Ring buffer at exactly MODBUS_LOG_SIZE entries | `test_log_exact_fill` | `test_modbus_log.c:123` |
| `REQ-MTR-095` | Clear resets count but preserves total_logged | `test_log_clear` | `test_modbus_log.c:150` |
| `REQ-MTR-096` | Clear then refill works correctly | `test_log_clear_then_refill` | `test_modbus_log.c:173` |
| `REQ-MTR-097` | Out-of-range index returns NULL | `test_log_out_of_range` | `test_modbus_log.c:201` |
| `REQ-MTR-098` | All functions handle NULL pointer without crashing | `test_log_null_safety` | `test_modbus_log.c:221` |
| `REQ-MTR-099` | TX, RX, and ERR direction values are stored correctly | `test_log_directions` | `test_modbus_log.c:241` |

<details>
<summary>Detailed steps (10 scenarios)</summary>

### Init zeros all ring buffer fields
**Requirement:** `REQ-MTR-090`

- **Given** An uninitialized modbus_log_t
- **When** modbus_log_init is called
- **Then** count=0, head=0, total_logged=0

### Append and retrieve a single entry
**Requirement:** `REQ-MTR-091`

- **Given** An initialized ring buffer
- **When** One entry is appended with timestamp=1000, addr=0x0A, func=0x04, reg=0x0006
- **Then** count=1, get(0) returns the entry with correct fields

### Multiple entries maintain chronological order
**Requirement:** `REQ-MTR-092`

- **Given** An initialized ring buffer
- **When** 3 entries are appended with timestamps 100, 200, 300
- **Then** get(0) returns t=100, get(1) returns t=200, get(2) returns t=300

### Ring buffer wraps around and overwrites oldest entries
**Requirement:** `REQ-MTR-093`

- **Given** An initialized ring buffer
- **When** MODBUS_LOG_SIZE + 5 entries are appended
- **Then** count equals MODBUS_LOG_SIZE, oldest entries are overwritten

### Ring buffer at exactly MODBUS_LOG_SIZE entries
**Requirement:** `REQ-MTR-094`

- **Given** An initialized ring buffer
- **When** Exactly MODBUS_LOG_SIZE entries are appended
- **Then** count equals MODBUS_LOG_SIZE, all entries accessible in order

### Clear resets count but preserves total_logged
**Requirement:** `REQ-MTR-095`

- **Given** A ring buffer with 10 entries
- **When** modbus_log_clear is called
- **Then** count=0, total_logged=10, get(0) returns NULL

### Clear then refill works correctly
**Requirement:** `REQ-MTR-096`

- **Given** A ring buffer that was filled, cleared, then has 3 new entries
- **When** Entries are read
- **Then** count=3, entries reflect only the new data, total includes both batches

### Out-of-range index returns NULL
**Requirement:** `REQ-MTR-097`

- **Given** A ring buffer with 3 entries
- **When** get is called with index=3 and index=MODBUS_LOG_SIZE
- **Then** Both return NULL

### All functions handle NULL pointer without crashing
**Requirement:** `REQ-MTR-098`

- **Given** NULL modbus_log_t pointer
- **When** All API functions are called with NULL
- **Then** No crash, count returns 0, get returns NULL, total returns 0

### TX, RX, and ERR direction values are stored correctly
**Requirement:** `REQ-MTR-099`

- **Given** An initialized ring buffer
- **When** Three entries with different directions are appended
- **Then** Each entry reflects its correct direction

</details>

---

## Mode Synchronization

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MODE-SYNC-001` | SOLAR_OFF: switching to Solar requires single-phase (evse_force_single_phase) | `test_solar_off_forces_single_phase_in_solar` | `test_mode_sync.c:1` |
| `REQ-MODE-SYNC-002` | SOLAR_OFF: Smart mode allows three-phase | `test_solar_off_allows_3p_in_smart` | `test_mode_sync.c:72` |
| `REQ-MODE-SYNC-003` | State C entry with SOLAR_OFF in Solar mode opens C2 contactor | `test_state_c_entry_solar_off_opens_c2` | `test_mode_sync.c:89` |
| `REQ-MODE-SYNC-004` | Clearing LESS_6A on switch to Smart (via evse_clear_error_flags) | `test_clear_less6a_on_mode_switch` | `test_mode_sync.c:118` |
| `REQ-MODE-SYNC-005` | SolarStopTimer persists if mode switch misses setMode | `test_raw_mode_assign_leaves_timer_stale` | `test_mode_sync.c:136` |
| `REQ-MODE-SYNC-006` | SolarStopTimer cleared when setMode side effects applied | `test_setmode_clears_timer` | `test_mode_sync.c:157` |
| `REQ-MODE-SYNC-007` | Smart→Solar mid-charge: regulation switches to solar algorithm | `test_mid_charge_smart_to_solar` | `test_mode_sync.c:187` |
| `REQ-MODE-SYNC-008` | Solar→Normal mid-charge: all EVSEs get full current | `test_mid_charge_solar_to_normal` | `test_mode_sync.c:225` |

<details>
<summary>Detailed steps (8 scenarios)</summary>

### SOLAR_OFF: switching to Solar requires single-phase (evse_force_single_phase)
**Requirement:** `REQ-MODE-SYNC-001`

- **Given** EVSE in Smart mode charging on 3 phases, EnableC2=SOLAR_OFF
- **When** Mode is set to Solar and evse_check_switching_phases is called
- **Then** evse_force_single_phase returns true (C2 must be off in Solar mode)

### SOLAR_OFF: Smart mode allows three-phase
**Requirement:** `REQ-MODE-SYNC-002`

- **Given** EVSE with EnableC2=SOLAR_OFF in Smart mode
- **When** evse_force_single_phase is checked
- **Then** Returns false (C2 allowed in non-Solar modes with SOLAR_OFF)

### State C entry with SOLAR_OFF in Solar mode opens C2 contactor
**Requirement:** `REQ-MODE-SYNC-003`

- **Given** EVSE with EnableC2=SOLAR_OFF, Mode=Solar, entering STATE_C
- **When** evse_set_state(ctx, STATE_C) is called
- **Then** contactor2 is off (single-phase charging)

### Clearing LESS_6A on switch to Smart (via evse_clear_error_flags)
**Requirement:** `REQ-MODE-SYNC-004`

- **Given** EVSE with LESS_6A error set from solar shortage
- **When** evse_clear_error_flags clears LESS_6A (as setMode does for Smart)
- **Then** ErrorFlags no longer has LESS_6A set

### SolarStopTimer persists if mode switch misses setMode
**Requirement:** `REQ-MODE-SYNC-005`

- **Given** EVSE with SolarStopTimer=300, mode changes to Smart
- **When** Only Mode variable is assigned (simulating SETITEM bug)
- **Then** SolarStopTimer remains at 300 (stale — not cleared)

### SolarStopTimer cleared when setMode side effects applied
**Requirement:** `REQ-MODE-SYNC-006`

- **Given** EVSE with SolarStopTimer=300, mode changes to Smart
- **When** setMode side effects are applied (timer reset to 0)
- **Then** SolarStopTimer is 0

### Smart→Solar mid-charge: regulation switches to solar algorithm
**Requirement:** `REQ-MODE-SYNC-007`

- **Given** EVSE charging in Smart mode with mains headroom available
- **When** Mode is changed to Solar and evse_calc_balanced_current is called
- **Then** Solar fine regulation is applied (IsetBalanced changes differently)

### Solar→Normal mid-charge: all EVSEs get full current
**Requirement:** `REQ-MODE-SYNC-008`

- **Given** Master with 2 EVSEs in Solar mode with shortage
- **When** Mode is changed to Normal
- **Then** Both EVSEs get full current (Normal ignores solar/mains constraints)

</details>

---

## Modem / ISO15118 Negotiation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MODEM-001` | Entering MODEM_REQUEST disconnects the pilot signal | `test_modem_request_disconnects_pilot` | `test_modem_states.c:1` |
| `REQ-MODEM-002` | Entering MODEM_REQUEST sets PWM to off (+12V) | `test_modem_request_pwm_off` | `test_modem_states.c:38` |
| `REQ-MODEM-003` | Entering MODEM_REQUEST ensures contactors are open | `test_modem_request_contactors_off` | `test_modem_states.c:52` |
| `REQ-MODEM-004` | MODEM_REQUEST transitions to MODEM_WAIT after timer expires | `test_modem_request_to_wait_on_timer` | `test_modem_states.c:67` |
| `REQ-MODEM-005` | Modem states are NOT handled in tick_10ms (original behavior) | `test_modem_request_to_A_on_disconnect` | `test_modem_states.c:83` |
| `REQ-MODEM-006` | Entering MODEM_WAIT sets 5% PWM duty cycle for ISO15118 signalling | `test_modem_wait_5pct_duty` | `test_modem_states.c:100` |
| `REQ-MODEM-007` | Entering MODEM_WAIT reconnects the pilot signal | `test_modem_wait_pilot_connected` | `test_modem_states.c:114` |
| `REQ-MODEM-008` | Entering MODEM_WAIT sets ToModemDoneStateTimer to 60 seconds | `test_modem_wait_timer_set` | `test_modem_states.c:128` |
| `REQ-MODEM-009` | MODEM_WAIT transitions to MODEM_DONE after 60-second timeout | `test_modem_wait_to_done_after_timeout` | `test_modem_states.c:142` |
| `REQ-MODEM-010` | MODEM_WAIT is NOT handled in tick_10ms (original behavior) | `test_modem_wait_to_A_on_disconnect` | `test_modem_states.c:160` |
| `REQ-MODEM-011` | Entering MODEM_DONE disconnects the pilot signal | `test_modem_done_disconnects_pilot` | `test_modem_states.c:177` |
| `REQ-MODEM-012` | Entering MODEM_DONE sets LeaveModemDoneStateTimer to 5 seconds | `test_modem_done_timer_set` | `test_modem_states.c:191` |
| `REQ-MODEM-013` | MODEM_DONE transitions to STATE_B after 5-second timer with ModemStage=1 | `test_modem_done_to_B_after_timer` | `test_modem_states.c:205` |
| `REQ-MODEM-014` | MODEM_DONE is NOT handled in tick_10ms (original behavior) | `test_modem_done_to_A_on_disconnect` | `test_modem_states.c:223` |
| `REQ-MODEM-015` | MODEM_DENIED transitions to STATE_A after timer expires | `test_modem_denied_to_A_after_timer` | `test_modem_states.c:240` |
| `REQ-MODEM-016` | MODEM_DENIED is NOT handled in tick_10ms (original behavior) | `test_modem_denied_to_A_on_disconnect` | `test_modem_states.c:258` |
| `REQ-MODEM-M1A` | MODEM_WAIT timer=1 does not transition immediately on decrement | `test_modem_wait_timer_1_no_immediate_transition` | `test_modem_states.c:276` |
| `REQ-MODEM-M1B` | MODEM_DONE timer=1 does not transition immediately on decrement | `test_modem_done_timer_1_no_immediate_transition` | `test_modem_states.c:299` |
| `REQ-MODEM-M1C` | MODEM_DENIED timer=1 does not transition immediately on decrement | `test_modem_denied_timer_1_no_immediate_transition` | `test_modem_states.c:320` |
| `REQ-MODEM-M2A` | DisconnectTimeCounter starts on STATE_A entry when modem enabled | `test_disconnect_counter_starts_on_state_a` | `test_modem_states.c:343` |
| `REQ-MODEM-M2B` | DisconnectTimeCounter disabled on MODEM_REQUEST entry | `test_disconnect_counter_disabled_on_modem_request` | `test_modem_states.c:358` |
| `REQ-MODEM-M2C` | DisconnectTimeCounter disabled on MODEM_DONE entry | `test_disconnect_counter_disabled_on_modem_done` | `test_modem_states.c:373` |
| `REQ-MODEM-M2D` | DisconnectTimeCounter is NOT incremented in tick_1s (handled by firmware wrapper) | `test_disconnect_counter_increments_in_tick_1s` | `test_modem_states.c:388` |
| `REQ-MODEM-M2E` | DisconnectTimeCounter does not increment when disabled (-1) | `test_disconnect_counter_stays_disabled` | `test_modem_states.c:403` |
| `REQ-MODEM-EVCCID-001` | Empty RequiredEVCCID allows any vehicle | `test_evccid_empty_required_allows_any` | `test_modem_states.c:420` |
| `REQ-MODEM-EVCCID-002` | Matching EVCCID passes validation | `test_evccid_matching_passes` | `test_modem_states.c:441` |
| `REQ-MODEM-EVCCID-003` | Mismatched EVCCID triggers MODEM_DENIED | `test_evccid_mismatch_denied` | `test_modem_states.c:462` |
| `REQ-MODEM-EVCCID-004` | Full flow: EVCCID mismatch → DENIED → timeout → STATE_A | `test_evccid_mismatch_full_flow_to_a` | `test_modem_states.c:485` |
| `REQ-MODEM-017` | Full modem negotiation flow: REQUEST -> WAIT -> DONE -> STATE_B | `test_full_modem_flow` | `test_modem_states.c:515` |

<details>
<summary>Detailed steps (29 scenarios)</summary>

### Entering MODEM_REQUEST disconnects the pilot signal
**Requirement:** `REQ-MODEM-001`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_REQUEST
- **Then** pilot_connected is false

### Entering MODEM_REQUEST sets PWM to off (+12V)
**Requirement:** `REQ-MODEM-002`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_REQUEST
- **Then** PWM duty is set to 1024 (off / +12V constant)

### Entering MODEM_REQUEST ensures contactors are open
**Requirement:** `REQ-MODEM-003`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_REQUEST
- **Then** Both contactor1 and contactor2 are off (open)

### MODEM_REQUEST transitions to MODEM_WAIT after timer expires
**Requirement:** `REQ-MODEM-004`

- **Given** The EVSE is in STATE_MODEM_REQUEST with ToModemWaitStateTimer=0
- **When** One second tick occurs
- **Then** The state transitions to STATE_MODEM_WAIT

### Modem states are NOT handled in tick_10ms (original behavior)
**Requirement:** `REQ-MODEM-005`

- **Given** The EVSE is in STATE_MODEM_REQUEST
- **When** A 12V pilot signal is received during tick_10ms
- **Then** The state stays MODEM_REQUEST (modem is managed only by tick_1s timers)

### Entering MODEM_WAIT sets 5% PWM duty cycle for ISO15118 signalling
**Requirement:** `REQ-MODEM-006`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_WAIT
- **Then** PWM duty is set to 51 (5% duty cycle)

### Entering MODEM_WAIT reconnects the pilot signal
**Requirement:** `REQ-MODEM-007`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_WAIT
- **Then** pilot_connected is true

### Entering MODEM_WAIT sets ToModemDoneStateTimer to 60 seconds
**Requirement:** `REQ-MODEM-008`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_WAIT
- **Then** ToModemDoneStateTimer is set to 60

### MODEM_WAIT transitions to MODEM_DONE after 60-second timeout
**Requirement:** `REQ-MODEM-009`

- **Given** The EVSE is in STATE_MODEM_WAIT with 60-second timer
- **When** 61 second ticks occur (60 to decrement to 0, 1 more to fire transition)
- **Then** The state transitions to STATE_MODEM_DONE

### MODEM_WAIT is NOT handled in tick_10ms (original behavior)
**Requirement:** `REQ-MODEM-010`

- **Given** The EVSE is in STATE_MODEM_WAIT
- **When** A 12V pilot signal is received during tick_10ms
- **Then** The state stays MODEM_WAIT (modem is managed only by tick_1s timers)

### Entering MODEM_DONE disconnects the pilot signal
**Requirement:** `REQ-MODEM-011`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_DONE
- **Then** pilot_connected is false

### Entering MODEM_DONE sets LeaveModemDoneStateTimer to 5 seconds
**Requirement:** `REQ-MODEM-012`

- **Given** The EVSE is initialised with basic configuration
- **When** The state is set to STATE_MODEM_DONE
- **Then** LeaveModemDoneStateTimer is set to 5

### MODEM_DONE transitions to STATE_B after 5-second timer with ModemStage=1
**Requirement:** `REQ-MODEM-013`

- **Given** The EVSE is in STATE_MODEM_DONE with 5-second timer
- **When** 6 second ticks occur (5 to decrement to 0, 1 more to fire transition)
- **Then** The state transitions to STATE_B and ModemStage is set to 1

### MODEM_DONE is NOT handled in tick_10ms (original behavior)
**Requirement:** `REQ-MODEM-014`

- **Given** The EVSE is in STATE_MODEM_DONE
- **When** A 12V pilot signal is received during tick_10ms
- **Then** The state stays MODEM_DONE (modem is managed only by tick_1s timers)

### MODEM_DENIED transitions to STATE_A after timer expires
**Requirement:** `REQ-MODEM-015`

- **Given** The EVSE is in STATE_MODEM_DENIED with LeaveModemDeniedStateTimer=3
- **When** 4 second ticks occur (3 to decrement to 0, 1 more to fire transition)
- **Then** The state transitions to STATE_A

### MODEM_DENIED is NOT handled in tick_10ms (original behavior)
**Requirement:** `REQ-MODEM-016`

- **Given** The EVSE is in STATE_MODEM_DENIED with timer still running
- **When** A 12V pilot signal is received during tick_10ms
- **Then** The state stays MODEM_DENIED (modem is managed only by tick_1s timers)

### MODEM_WAIT timer=1 does not transition immediately on decrement
**Requirement:** `REQ-MODEM-M1A`

- **Given** EVSE is in STATE_MODEM_WAIT with ToModemDoneStateTimer=1
- **When** One second tick occurs (timer decrements to 0)
- **When** Another second tick occurs (timer is now 0, else branch fires)
- **Then** The EVSE stays in STATE_MODEM_WAIT (does not yet transition to MODEM_DONE)
- **Then** The EVSE transitions to STATE_MODEM_DONE

### MODEM_DONE timer=1 does not transition immediately on decrement
**Requirement:** `REQ-MODEM-M1B`

- **Given** EVSE is in STATE_MODEM_DONE with LeaveModemDoneStateTimer=1
- **When** One second tick occurs (timer decrements to 0)
- **When** Another second tick occurs
- **Then** The EVSE stays in STATE_MODEM_DONE
- **Then** The EVSE transitions to STATE_B (EVCCID accepted)

### MODEM_DENIED timer=1 does not transition immediately on decrement
**Requirement:** `REQ-MODEM-M1C`

- **Given** EVSE is in STATE_MODEM_DENIED with LeaveModemDeniedStateTimer=1
- **When** One second tick occurs (timer decrements to 0)
- **When** Another second tick occurs
- **Then** The EVSE stays in STATE_MODEM_DENIED
- **Then** The EVSE transitions to STATE_A

### DisconnectTimeCounter starts on STATE_A entry when modem enabled
**Requirement:** `REQ-MODEM-M2A`

- **Given** ModemEnabled=true, DisconnectTimeCounter=-1 (disabled)
- **When** State is set to STATE_A
- **Then** DisconnectTimeCounter is set to 0 (started)

### DisconnectTimeCounter disabled on MODEM_REQUEST entry
**Requirement:** `REQ-MODEM-M2B`

- **Given** DisconnectTimeCounter=5 (running)
- **When** State is set to STATE_MODEM_REQUEST
- **Then** DisconnectTimeCounter is set to -1 (disabled)

### DisconnectTimeCounter disabled on MODEM_DONE entry
**Requirement:** `REQ-MODEM-M2C`

- **Given** DisconnectTimeCounter=5 (running)
- **When** State is set to STATE_MODEM_DONE
- **Then** DisconnectTimeCounter is set to -1 (disabled)

### DisconnectTimeCounter is NOT incremented in tick_1s (handled by firmware wrapper)
**Requirement:** `REQ-MODEM-M2D`

- **Given** ModemEnabled=true, DisconnectTimeCounter=0
- **When** tick_1s occurs
- **Then** DisconnectTimeCounter stays 0 (firmware wrapper handles increment + pilot check)

### DisconnectTimeCounter does not increment when disabled (-1)
**Requirement:** `REQ-MODEM-M2E`

- **Given** ModemEnabled=true, DisconnectTimeCounter=-1
- **When** tick_1s occurs
- **Then** DisconnectTimeCounter remains -1

### Empty RequiredEVCCID allows any vehicle
**Requirement:** `REQ-MODEM-EVCCID-001`

- **Given** MODEM_DONE, LeaveModemDoneStateTimer expired, RequiredEVCCID=""
- **When** tick_1s processes MODEM_DONE timer expiry
- **Then** Transitions to STATE_B with ModemStage=1

### Matching EVCCID passes validation
**Requirement:** `REQ-MODEM-EVCCID-002`

- **Given** MODEM_DONE, timer expired, RequiredEVCCID matches EVCCID
- **When** tick_1s processes timer expiry
- **Then** Transitions to STATE_B with ModemStage=1

### Mismatched EVCCID triggers MODEM_DENIED
**Requirement:** `REQ-MODEM-EVCCID-003`

- **Given** MODEM_DONE, timer expired, RequiredEVCCID != EVCCID
- **When** tick_1s processes timer expiry
- **Then** Transitions to MODEM_DENIED, ModemStage=0, LeaveModemDeniedStateTimer=60

### Full flow: EVCCID mismatch → DENIED → timeout → STATE_A
**Requirement:** `REQ-MODEM-EVCCID-004`

- **Given** Modem flow reaches MODEM_DONE with wrong EVCCID
- **When** Timer expires and EVCCID doesn't match, then DENIED timer expires
- **Then** MODEM_DENIED → STATE_A after 60+1 seconds

### Full modem negotiation flow: REQUEST -> WAIT -> DONE -> STATE_B
**Requirement:** `REQ-MODEM-017`

- **Given** The EVSE is initialised with basic configuration
- **When** The modem negotiation proceeds through all stages with timers expiring
- **Then** The EVSE transitions REQUEST->WAIT->DONE->B with ModemStage=1 and correct PWM/pilot at each stage

</details>

---

## MQTT Command Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-001` | Set mode to Normal via MQTT | `test_mode_normal` | `test_mqtt_parser.c:1` |
| `REQ-MQTT-001` | Set mode to Solar via MQTT | `test_mode_solar` | `test_mqtt_parser.c:32` |
| `REQ-MQTT-001` | Set mode to Smart via MQTT | `test_mode_smart` | `test_mqtt_parser.c:43` |
| `REQ-MQTT-001` | Set mode to Off via MQTT | `test_mode_off` | `test_mqtt_parser.c:54` |
| `REQ-MQTT-001` | Set mode to Pause via MQTT | `test_mode_pause` | `test_mqtt_parser.c:65` |
| `REQ-MQTT-003` | CustomButton set to On | `test_custom_button_on` | `test_mqtt_parser.c:90` |
| `REQ-MQTT-003` | CustomButton set to Off | `test_custom_button_off` | `test_mqtt_parser.c:101` |
| `REQ-MQTT-006` | CP PWM override normal mode (-1) | `test_cp_pwm_normal` | `test_mqtt_parser.c:192` |
| `REQ-MQTT-006` | CP PWM override disconnect (0) | `test_cp_pwm_disconnect` | `test_mqtt_parser.c:203` |
| `REQ-MQTT-006` | CP PWM override max value (1024) | `test_cp_pwm_max` | `test_mqtt_parser.c:213` |
| `REQ-MQTT-009` | Home battery current set | `test_home_battery_current` | `test_mqtt_parser.c:370` |
| `REQ-MQTT-009` | Home battery current negative (discharging) | `test_home_battery_current_negative` | `test_mqtt_parser.c:381` |
| `REQ-MQTT-011` | Cable lock enabled | `test_cable_lock_enable` | `test_mqtt_parser.c:473` |
| `REQ-MQTT-011` | Cable lock disabled | `test_cable_lock_disable` | `test_mqtt_parser.c:484` |
| `REQ-MQTT-011` | Cable lock any non-"1" disables | `test_cable_lock_any_other` | `test_mqtt_parser.c:494` |
| `REQ-MQTT-012` | EnableC2 numeric value | `test_enable_c2_numeric` | `test_mqtt_parser.c:506` |
| `REQ-MQTT-012` | EnableC2 string value | `test_enable_c2_string` | `test_mqtt_parser.c:517` |
| `REQ-MQTT-013` | RequiredEVCCID set | `test_required_evccid` | `test_mqtt_parser.c:547` |
| `REQ-MQTT-015` | PrioStrategy set to MODBUS_ADDR (0) via MQTT | `test_prio_strategy_modbus_addr` | `test_mqtt_parser.c:570` |
| `REQ-MQTT-015` | PrioStrategy set to FIRST_CONNECTED (1) | `test_prio_strategy_first_connected` | `test_mqtt_parser.c:584` |
| `REQ-MQTT-015` | PrioStrategy set to LAST_CONNECTED (2) | `test_prio_strategy_last_connected` | `test_mqtt_parser.c:594` |
| `REQ-MQTT-016` | RotationInterval set to 0 (disabled) via MQTT | `test_rotation_interval_zero` | `test_mqtt_parser.c:627` |
| `REQ-MQTT-016` | RotationInterval set to minimum (30 minutes) | `test_rotation_interval_min` | `test_mqtt_parser.c:641` |
| `REQ-MQTT-016` | RotationInterval set to maximum (1440 minutes = 24h) | `test_rotation_interval_max` | `test_mqtt_parser.c:651` |
| `REQ-MQTT-017` | IdleTimeout set to minimum (30 seconds) via MQTT | `test_idle_timeout_min` | `test_mqtt_parser.c:684` |
| `REQ-MQTT-017` | IdleTimeout set to default (60 seconds) | `test_idle_timeout_default` | `test_mqtt_parser.c:698` |
| `REQ-MQTT-017` | IdleTimeout set to maximum (300 seconds) | `test_idle_timeout_max` | `test_mqtt_parser.c:708` |
| `REQ-MQTT-023` | MQTTHeartbeat set to valid value via MQTT | `test_mqtt_heartbeat_valid` | `test_mqtt_parser.c:824` |
| `REQ-MQTT-024` | MQTTChangeOnly enabled via MQTT with payload "1" | `test_mqtt_change_only_enable` | `test_mqtt_parser.c:864` |
| `REQ-MQTT-024` | MQTTChangeOnly disabled via MQTT with payload "0" | `test_mqtt_change_only_disable` | `test_mqtt_parser.c:878` |
| `REQ-CIR-010` | Set MaxCircuitMains to valid value via MQTT | `test_max_circuit_mains_valid` | `test_mqtt_parser.c:1193` |
| `REQ-CIR-010` | Set MaxCircuitMains to zero (disable) via MQTT | `test_max_circuit_mains_zero` | `test_mqtt_parser.c:1207` |
| `REQ-CIR-010` | Set MaxCircuitMains to boundary max (600) via MQTT | `test_max_circuit_mains_max` | `test_mqtt_parser.c:1221` |
| `REQ-CIR-011` | Set CircuitMeter API feed via MQTT with L1:L2:L3 format | `test_circuit_meter_valid` | `test_mqtt_parser.c:1261` |
| `REQ-CIR-011` | CircuitMeter API feed with negative values (export) | `test_circuit_meter_negative` | `test_mqtt_parser.c:1277` |

<details>
<summary>Detailed steps (35 scenarios)</summary>

### Set mode to Normal via MQTT
**Requirement:** `REQ-MQTT-001`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/Mode with payload "Normal"
- **Then** Command type is MQTT_CMD_MODE with mode MQTT_MODE_NORMAL

### Set mode to Solar via MQTT
**Requirement:** `REQ-MQTT-001`


### Set mode to Smart via MQTT
**Requirement:** `REQ-MQTT-001`


### Set mode to Off via MQTT
**Requirement:** `REQ-MQTT-001`


### Set mode to Pause via MQTT
**Requirement:** `REQ-MQTT-001`


### CustomButton set to On
**Requirement:** `REQ-MQTT-003`


### CustomButton set to Off
**Requirement:** `REQ-MQTT-003`


### CP PWM override normal mode (-1)
**Requirement:** `REQ-MQTT-006`


### CP PWM override disconnect (0)
**Requirement:** `REQ-MQTT-006`


### CP PWM override max value (1024)
**Requirement:** `REQ-MQTT-006`


### Home battery current set
**Requirement:** `REQ-MQTT-009`


### Home battery current negative (discharging)
**Requirement:** `REQ-MQTT-009`


### Cable lock enabled
**Requirement:** `REQ-MQTT-011`


### Cable lock disabled
**Requirement:** `REQ-MQTT-011`


### Cable lock any non-"1" disables
**Requirement:** `REQ-MQTT-011`


### EnableC2 numeric value
**Requirement:** `REQ-MQTT-012`


### EnableC2 string value
**Requirement:** `REQ-MQTT-012`


### RequiredEVCCID set
**Requirement:** `REQ-MQTT-013`


### PrioStrategy set to MODBUS_ADDR (0) via MQTT
**Requirement:** `REQ-MQTT-015`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/PrioStrategy with payload "0"
- **Then** Command type is MQTT_CMD_PRIO_STRATEGY with value 0

### PrioStrategy set to FIRST_CONNECTED (1)
**Requirement:** `REQ-MQTT-015`


### PrioStrategy set to LAST_CONNECTED (2)
**Requirement:** `REQ-MQTT-015`


### RotationInterval set to 0 (disabled) via MQTT
**Requirement:** `REQ-MQTT-016`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/RotationInterval with payload "0"
- **Then** Command type is MQTT_CMD_ROTATION_INTERVAL with value 0

### RotationInterval set to minimum (30 minutes)
**Requirement:** `REQ-MQTT-016`


### RotationInterval set to maximum (1440 minutes = 24h)
**Requirement:** `REQ-MQTT-016`


### IdleTimeout set to minimum (30 seconds) via MQTT
**Requirement:** `REQ-MQTT-017`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/IdleTimeout with payload "30"
- **Then** Command type is MQTT_CMD_IDLE_TIMEOUT with value 30

### IdleTimeout set to default (60 seconds)
**Requirement:** `REQ-MQTT-017`


### IdleTimeout set to maximum (300 seconds)
**Requirement:** `REQ-MQTT-017`


### MQTTHeartbeat set to valid value via MQTT
**Requirement:** `REQ-MQTT-023`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTHeartbeat with payload "60"
- **Then** Command type is MQTT_CMD_MQTT_HEARTBEAT with mqtt_heartbeat = 60

### MQTTChangeOnly enabled via MQTT with payload "1"
**Requirement:** `REQ-MQTT-024`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTChangeOnly with payload "1"
- **Then** Command type is MQTT_CMD_MQTT_CHANGE_ONLY with mqtt_change_only = true

### MQTTChangeOnly disabled via MQTT with payload "0"
**Requirement:** `REQ-MQTT-024`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTChangeOnly with payload "0"
- **Then** Command type is MQTT_CMD_MQTT_CHANGE_ONLY with mqtt_change_only = false

### Set MaxCircuitMains to valid value via MQTT
**Requirement:** `REQ-CIR-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MaxCircuitMains with payload "25"
- **Then** Command type is MQTT_CMD_MAX_CIRCUIT_MAINS with value 25

### Set MaxCircuitMains to zero (disable) via MQTT
**Requirement:** `REQ-CIR-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MaxCircuitMains with payload "0"
- **Then** Command type is MQTT_CMD_MAX_CIRCUIT_MAINS with value 0

### Set MaxCircuitMains to boundary max (600) via MQTT
**Requirement:** `REQ-CIR-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MaxCircuitMains with payload "600"
- **Then** Command type is MQTT_CMD_MAX_CIRCUIT_MAINS with value 600

### Set CircuitMeter API feed via MQTT with L1:L2:L3 format
**Requirement:** `REQ-CIR-011`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CircuitMeter with payload "100:200:150"
- **Then** Command type is MQTT_CMD_CIRCUIT_METER with parsed phase currents

### CircuitMeter API feed with negative values (export)
**Requirement:** `REQ-CIR-011`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CircuitMeter with payload "-50:100:-25"
- **Then** Command type is MQTT_CMD_CIRCUIT_METER with correct phase currents

</details>

---

## MQTT Input Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-002` | Invalid mode string is rejected | `test_mode_invalid` | `test_mqtt_parser.c:76` |
| `REQ-MQTT-004` | Current override with valid value | `test_current_override_valid` | `test_mqtt_parser.c:114` |
| `REQ-MQTT-004` | Current override zero resets override | `test_current_override_zero` | `test_mqtt_parser.c:128` |
| `REQ-MQTT-004` | Current override with max value | `test_current_override_max` | `test_mqtt_parser.c:139` |
| `REQ-MQTT-005` | Max sum mains valid value | `test_max_sum_mains_valid` | `test_mqtt_parser.c:151` |
| `REQ-MQTT-005` | Max sum mains zero disables | `test_max_sum_mains_zero` | `test_mqtt_parser.c:162` |
| `REQ-MQTT-005` | Max sum mains below minimum rejected | `test_max_sum_mains_below_min` | `test_mqtt_parser.c:172` |
| `REQ-MQTT-005` | Max sum mains above maximum rejected | `test_max_sum_mains_above_max` | `test_mqtt_parser.c:181` |
| `REQ-MQTT-006` | CP PWM override out of range rejected | `test_cp_pwm_out_of_range` | `test_mqtt_parser.c:223` |
| `REQ-MQTT-006` | CP PWM override below -1 rejected | `test_cp_pwm_below_neg1` | `test_mqtt_parser.c:232` |
| `REQ-MQTT-007` | Mains meter out of range rejected (>2000) | `test_mains_meter_out_of_range` | `test_mqtt_parser.c:272` |
| `REQ-MQTT-007` | Mains meter out of range rejected (<-2000) | `test_mains_meter_out_of_range_neg` | `test_mqtt_parser.c:282` |
| `REQ-MQTT-007` | Mains meter missing fields rejected | `test_mains_meter_missing_fields` | `test_mqtt_parser.c:292` |
| `REQ-MQTT-008` | EV meter partial data rejected | `test_ev_meter_partial` | `test_mqtt_parser.c:345` |
| `REQ-MQTT-010` | RGB color out of range rejected | `test_rgb_out_of_range` | `test_mqtt_parser.c:406` |
| `REQ-MQTT-010` | RGB color negative rejected | `test_rgb_negative` | `test_mqtt_parser.c:416` |
| `REQ-MQTT-010` | RGB color missing component rejected | `test_rgb_missing` | `test_mqtt_parser.c:426` |
| `REQ-MQTT-012` | EnableC2 out of range rejected | `test_enable_c2_out_of_range` | `test_mqtt_parser.c:527` |
| `REQ-MQTT-012` | EnableC2 invalid string rejected | `test_enable_c2_invalid_string` | `test_mqtt_parser.c:536` |
| `REQ-MQTT-013` | RequiredEVCCID too long rejected | `test_required_evccid_too_long` | `test_mqtt_parser.c:558` |
| `REQ-MQTT-015` | PrioStrategy value 3 is rejected (out of range) | `test_prio_strategy_out_of_range` | `test_mqtt_parser.c:604` |
| `REQ-MQTT-015` | PrioStrategy negative value is rejected | `test_prio_strategy_negative` | `test_mqtt_parser.c:616` |
| `REQ-MQTT-016` | RotationInterval in gap (1-29) is rejected | `test_rotation_interval_gap` | `test_mqtt_parser.c:661` |
| `REQ-MQTT-016` | RotationInterval above maximum is rejected | `test_rotation_interval_too_high` | `test_mqtt_parser.c:673` |
| `REQ-MQTT-017` | IdleTimeout below minimum (29) is rejected | `test_idle_timeout_too_low` | `test_mqtt_parser.c:718` |
| `REQ-MQTT-017` | IdleTimeout above maximum (301) is rejected | `test_idle_timeout_too_high` | `test_mqtt_parser.c:730` |
| `REQ-MQTT-017` | IdleTimeout zero is rejected (minimum is 30) | `test_idle_timeout_zero` | `test_mqtt_parser.c:739` |
| `REQ-MQTT-005` | Max sum mains at lower boundary (10) is accepted | `test_max_sum_mains_boundary_10` | `test_mqtt_parser.c:750` |
| `REQ-MQTT-005` | Max sum mains at upper boundary (600) is accepted | `test_max_sum_mains_boundary_600` | `test_mqtt_parser.c:764` |
| `REQ-MQTT-004` | Negative current override is accepted (atoi converts, no range check) | `test_current_override_negative` | `test_mqtt_parser.c:778` |
| `REQ-MQTT-002` | Empty payload is rejected for Mode command | `test_empty_payload_mode_rejected` | `test_mqtt_parser.c:810` |
| `REQ-MQTT-023` | MQTTHeartbeat below minimum (9) is rejected | `test_mqtt_heartbeat_too_low` | `test_mqtt_parser.c:838` |
| `REQ-MQTT-023` | MQTTHeartbeat above maximum (301) is rejected | `test_mqtt_heartbeat_too_high` | `test_mqtt_parser.c:850` |
| `REQ-MQTT-024` | MQTTChangeOnly rejects invalid payload | `test_mqtt_change_only_invalid` | `test_mqtt_parser.c:892` |
| `REQ-MQTT-025` | Mains meter boundary value +2000 (200A exactly) is accepted | `test_mains_meter_boundary_positive` | `test_mqtt_parser.c:1018` |
| `REQ-MQTT-025` | Mains meter boundary value -2000 (-200A exactly) is accepted | `test_mains_meter_boundary_negative` | `test_mqtt_parser.c:1032` |
| `REQ-MQTT-026` | EV meter power exceeding 100kW is rejected | `test_ev_meter_power_too_high` | `test_mqtt_parser.c:1046` |
| `REQ-MQTT-026` | EV meter negative power exceeding -100kW is rejected | `test_ev_meter_power_too_low` | `test_mqtt_parser.c:1059` |
| `REQ-MQTT-027` | EV meter energy exceeding 1TWh is rejected | `test_ev_meter_energy_too_high` | `test_mqtt_parser.c:1072` |
| `REQ-MQTT-026` | EV meter power at boundary 100000W (100kW) is accepted | `test_ev_meter_power_boundary_accepted` | `test_mqtt_parser.c:1085` |
| `REQ-CIR-010` | Reject MaxCircuitMains below minimum (1-9 range) | `test_max_circuit_mains_below_min` | `test_mqtt_parser.c:1235` |
| `REQ-CIR-010` | Reject MaxCircuitMains above maximum | `test_max_circuit_mains_above_max` | `test_mqtt_parser.c:1247` |
| `REQ-CIR-011` | Reject CircuitMeter with out of range values | `test_circuit_meter_out_of_range` | `test_mqtt_parser.c:1293` |
| `REQ-CIR-011` | Reject CircuitMeter with missing fields | `test_circuit_meter_missing_fields` | `test_mqtt_parser.c:1305` |
| `REQ-MQTT-014` | Unrecognized topic returns false | `test_unrecognized_topic` | `test_mqtt_parser.c:1319` |
| `REQ-MQTT-014` | Wrong prefix returns false | `test_wrong_prefix` | `test_mqtt_parser.c:1328` |

<details>
<summary>Detailed steps (46 scenarios)</summary>

### Invalid mode string is rejected
**Requirement:** `REQ-MQTT-002`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/Mode with payload "Invalid"
- **Then** The parser returns false

### Current override with valid value
**Requirement:** `REQ-MQTT-004`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CurrentOverride with payload "100"
- **Then** Command has current_override = 100

### Current override zero resets override
**Requirement:** `REQ-MQTT-004`


### Current override with max value
**Requirement:** `REQ-MQTT-004`


### Max sum mains valid value
**Requirement:** `REQ-MQTT-005`


### Max sum mains zero disables
**Requirement:** `REQ-MQTT-005`


### Max sum mains below minimum rejected
**Requirement:** `REQ-MQTT-005`


### Max sum mains above maximum rejected
**Requirement:** `REQ-MQTT-005`


### CP PWM override out of range rejected
**Requirement:** `REQ-MQTT-006`


### CP PWM override below -1 rejected
**Requirement:** `REQ-MQTT-006`


### Mains meter out of range rejected (>2000)
**Requirement:** `REQ-MQTT-007`


### Mains meter out of range rejected (<-2000)
**Requirement:** `REQ-MQTT-007`


### Mains meter missing fields rejected
**Requirement:** `REQ-MQTT-007`


### EV meter partial data rejected
**Requirement:** `REQ-MQTT-008`


### RGB color out of range rejected
**Requirement:** `REQ-MQTT-010`


### RGB color negative rejected
**Requirement:** `REQ-MQTT-010`


### RGB color missing component rejected
**Requirement:** `REQ-MQTT-010`


### EnableC2 out of range rejected
**Requirement:** `REQ-MQTT-012`


### EnableC2 invalid string rejected
**Requirement:** `REQ-MQTT-012`


### RequiredEVCCID too long rejected
**Requirement:** `REQ-MQTT-013`


### PrioStrategy value 3 is rejected (out of range)
**Requirement:** `REQ-MQTT-015`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/PrioStrategy with payload "3"
- **Then** The parser returns false

### PrioStrategy negative value is rejected
**Requirement:** `REQ-MQTT-015`


### RotationInterval in gap (1-29) is rejected
**Requirement:** `REQ-MQTT-016`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/RotationInterval with payload "15"
- **Then** The parser returns false

### RotationInterval above maximum is rejected
**Requirement:** `REQ-MQTT-016`


### IdleTimeout below minimum (29) is rejected
**Requirement:** `REQ-MQTT-017`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/IdleTimeout with payload "29"
- **Then** The parser returns false

### IdleTimeout above maximum (301) is rejected
**Requirement:** `REQ-MQTT-017`


### IdleTimeout zero is rejected (minimum is 30)
**Requirement:** `REQ-MQTT-017`


### Max sum mains at lower boundary (10) is accepted
**Requirement:** `REQ-MQTT-005`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CurrentMaxSumMains with payload "10"
- **Then** Command is accepted with max_sum_mains = 10

### Max sum mains at upper boundary (600) is accepted
**Requirement:** `REQ-MQTT-005`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CurrentMaxSumMains with payload "600"
- **Then** Command is accepted with max_sum_mains = 600

### Negative current override is accepted (atoi converts, no range check)
**Requirement:** `REQ-MQTT-004`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CurrentOverride with payload "-10"
- **Then** Command is accepted (parser does not reject; dispatch layer validates)

### Empty payload is rejected for Mode command
**Requirement:** `REQ-MQTT-002`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/Mode with empty payload ""
- **Then** The parser returns false

### MQTTHeartbeat below minimum (9) is rejected
**Requirement:** `REQ-MQTT-023`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTHeartbeat with payload "9"
- **Then** The parser returns false

### MQTTHeartbeat above maximum (301) is rejected
**Requirement:** `REQ-MQTT-023`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTHeartbeat with payload "301"
- **Then** The parser returns false

### MQTTChangeOnly rejects invalid payload
**Requirement:** `REQ-MQTT-024`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MQTTChangeOnly with payload "2"
- **Then** The parser returns false

### Mains meter boundary value +2000 (200A exactly) is accepted
**Requirement:** `REQ-MQTT-025`

- **Given** A mains meter payload with L1=2000 dA (200A)
- **When** mqtt_parse_mains_meter is called
- **Then** Returns true with L1=2000

### Mains meter boundary value -2000 (-200A exactly) is accepted
**Requirement:** `REQ-MQTT-025`

- **Given** A mains meter payload with L1=-2000 dA (-200A)
- **When** mqtt_parse_mains_meter is called
- **Then** Returns true with L1=-2000

### EV meter power exceeding 100kW is rejected
**Requirement:** `REQ-MQTT-026`

- **Given** An EV meter payload with W=200000 (200kW, physically impossible)
- **When** mqtt_parse_ev_meter is called
- **Then** Returns false

### EV meter negative power exceeding -100kW is rejected
**Requirement:** `REQ-MQTT-026`

- **Given** An EV meter payload with W=-200000 (-200kW)
- **When** mqtt_parse_ev_meter is called
- **Then** Returns false

### EV meter energy exceeding 1TWh is rejected
**Requirement:** `REQ-MQTT-027`

- **Given** An EV meter payload with Wh=2000000000 (2TWh, absurd value)
- **When** mqtt_parse_ev_meter is called
- **Then** Returns false

### EV meter power at boundary 100000W (100kW) is accepted
**Requirement:** `REQ-MQTT-026`

- **Given** An EV meter payload with W=100000
- **When** mqtt_parse_ev_meter is called
- **Then** Returns true

### Reject MaxCircuitMains below minimum (1-9 range)
**Requirement:** `REQ-CIR-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MaxCircuitMains with payload "5"
- **Then** Parsing returns false (gap between 0 and 10)

### Reject MaxCircuitMains above maximum
**Requirement:** `REQ-CIR-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/MaxCircuitMains with payload "601"
- **Then** Parsing returns false

### Reject CircuitMeter with out of range values
**Requirement:** `REQ-CIR-011`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CircuitMeter with payload "2001:0:0"
- **Then** Parsing returns false (exceeds +/-2000 dA range)

### Reject CircuitMeter with missing fields
**Requirement:** `REQ-CIR-011`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CircuitMeter with payload "100:200"
- **Then** Parsing returns false (needs 3 fields)

### Unrecognized topic returns false
**Requirement:** `REQ-MQTT-014`


### Wrong prefix returns false
**Requirement:** `REQ-MQTT-014`


</details>

---

## MQTT Meter Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-007` | Mains meter format L1:L2:L3 is parsed correctly | `test_mains_meter_valid` | `test_mqtt_parser.c:243` |
| `REQ-MQTT-007` | Mains meter with negative values | `test_mains_meter_negative` | `test_mqtt_parser.c:259` |
| `REQ-MQTT-007` | Mains meter via full command parse | `test_mains_meter_command` | `test_mqtt_parser.c:302` |
| `REQ-MQTT-008` | EV meter format L1:L2:L3:W:WH is parsed correctly | `test_ev_meter_valid` | `test_mqtt_parser.c:317` |
| `REQ-MQTT-008` | EV meter with unknown values (-1) | `test_ev_meter_unknown_values` | `test_mqtt_parser.c:332` |
| `REQ-MQTT-008` | EV meter via full command parse | `test_ev_meter_command` | `test_mqtt_parser.c:355` |
| `REQ-MQTT-007` | Mains meter with extra trailing fields after L1:L2:L3 is accepted | `test_mains_meter_extra_fields_ignored` | `test_mqtt_parser.c:794` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Mains meter format L1:L2:L3 is parsed correctly
**Requirement:** `REQ-MQTT-007`

- **Given** Valid three-phase mains meter data
- **When** Payload is "100:200:300"
- **Then** L1=100, L2=200, L3=300

### Mains meter with negative values
**Requirement:** `REQ-MQTT-007`


### Mains meter via full command parse
**Requirement:** `REQ-MQTT-007`


### EV meter format L1:L2:L3:W:WH is parsed correctly
**Requirement:** `REQ-MQTT-008`


### EV meter with unknown values (-1)
**Requirement:** `REQ-MQTT-008`


### EV meter via full command parse
**Requirement:** `REQ-MQTT-008`


### Mains meter with extra trailing fields after L1:L2:L3 is accepted
**Requirement:** `REQ-MQTT-007`

- **Given** A valid MQTT prefix
- **When** Payload is "100:200:300:extra"
- **Then** L1=100, L2=200, L3=300 (extra data ignored by sscanf)

</details>

---

## MQTT Color Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-010` | Valid RGB color parsed | `test_rgb_valid` | `test_mqtt_parser.c:393` |
| `REQ-MQTT-010` | ColorOff topic parsed correctly | `test_color_off_command` | `test_mqtt_parser.c:436` |
| `REQ-MQTT-010` | ColorSolar topic parsed correctly | `test_color_solar_command` | `test_mqtt_parser.c:450` |
| `REQ-MQTT-010` | ColorCustom topic parsed correctly | `test_color_custom_command` | `test_mqtt_parser.c:461` |

<details>
<summary>Detailed steps (4 scenarios)</summary>

### Valid RGB color parsed
**Requirement:** `REQ-MQTT-010`


### ColorOff topic parsed correctly
**Requirement:** `REQ-MQTT-010`


### ColorSolar topic parsed correctly
**Requirement:** `REQ-MQTT-010`


### ColorCustom topic parsed correctly
**Requirement:** `REQ-MQTT-010`


</details>

---

## Solar Debug Telemetry

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SOL-020` | SolarDebug enable via MQTT | `test_solar_debug_enable` | `test_mqtt_parser.c:906` |
| `REQ-SOL-020` | SolarDebug disable via MQTT | `test_solar_debug_disable` | `test_mqtt_parser.c:920` |
| `REQ-SOL-020` | SolarDebug rejects invalid payload | `test_solar_debug_invalid` | `test_mqtt_parser.c:934` |
| `REQ-SOL-020` | Format solar debug snapshot as JSON with all fields | `test_solar_debug_to_json_all_fields` | `test_solar_debug_json.c:1` |
| `REQ-SOL-020` | JSON output starts with { and ends with } | `test_solar_debug_to_json_valid_framing` | `test_solar_debug_json.c:56` |
| `REQ-SOL-020` | Buffer too small for JSON output | `test_solar_debug_to_json_buffer_too_small` | `test_solar_debug_json.c:75` |
| `REQ-SOL-020` | Null pointer arguments | `test_solar_debug_to_json_null_args` | `test_solar_debug_json.c:92` |
| `REQ-SOL-020` | Zero-initialized snapshot produces valid JSON | `test_solar_debug_to_json_zeroed` | `test_solar_debug_json.c:110` |
| `REQ-SOL-020` | Negative values are correctly represented | `test_solar_debug_to_json_negative_values` | `test_solar_debug_json.c:129` |
| `REQ-SOL-020` | Return value matches actual string length | `test_solar_debug_to_json_return_value_matches_strlen` | `test_solar_debug_json.c:151` |

<details>
<summary>Detailed steps (10 scenarios)</summary>

### SolarDebug enable via MQTT
**Requirement:** `REQ-SOL-020`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/SolarDebug with payload "1"
- **Then** The parser returns true with solar_debug = true

### SolarDebug disable via MQTT
**Requirement:** `REQ-SOL-020`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/SolarDebug with payload "0"
- **Then** The parser returns true with solar_debug = false

### SolarDebug rejects invalid payload
**Requirement:** `REQ-SOL-020`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/SolarDebug with payload "2"
- **Then** The parser returns false

### Format solar debug snapshot as JSON with all fields
**Requirement:** `REQ-SOL-020`

- **Given** A solar debug snapshot with known values
- **When** solar_debug_to_json is called with a sufficiently large buffer
- **Then** All 14 fields appear in the JSON output with correct values

### JSON output starts with { and ends with }
**Requirement:** `REQ-SOL-020`

- **Given** A solar debug snapshot
- **When** solar_debug_to_json is called
- **Then** The output is valid JSON object framing

### Buffer too small for JSON output
**Requirement:** `REQ-SOL-020`

- **Given** A solar debug snapshot
- **When** solar_debug_to_json is called with a buffer that is too small
- **Then** The function returns -1

### Null pointer arguments
**Requirement:** `REQ-SOL-020`

- **Given** NULL snap or buf pointer
- **When** solar_debug_to_json is called
- **Then** The function returns -1

### Zero-initialized snapshot produces valid JSON
**Requirement:** `REQ-SOL-020`

- **Given** A zero-initialized solar debug snapshot
- **When** solar_debug_to_json is called
- **Then** All fields are zero in the output

### Negative values are correctly represented
**Requirement:** `REQ-SOL-020`

- **Given** A snapshot with negative Isum and IsetBalanced
- **When** solar_debug_to_json is called
- **Then** Negative values appear with minus sign

### Return value matches actual string length
**Requirement:** `REQ-SOL-020`

- **Given** A solar debug snapshot
- **When** solar_debug_to_json is called
- **Then** The return value equals strlen of the output

</details>

---

## Capacity Tariff MQTT

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-CAP-010` | Set capacity limit to a valid value via MQTT | `test_capacity_limit_valid` | `test_mqtt_parser.c:1101` |
| `REQ-CAP-010` | Set capacity limit to zero (disabled) via MQTT | `test_capacity_limit_zero_disables` | `test_mqtt_parser.c:1115` |
| `REQ-CAP-010` | Set capacity limit to maximum allowed value | `test_capacity_limit_max` | `test_mqtt_parser.c:1129` |
| `REQ-CAP-010` | Reject capacity limit above maximum | `test_capacity_limit_over_max` | `test_mqtt_parser.c:1143` |
| `REQ-CAP-010` | Reject negative capacity limit | `test_capacity_limit_negative` | `test_mqtt_parser.c:1155` |
| `REQ-CAP-010` | Reject empty payload for capacity limit | `test_capacity_limit_empty` | `test_mqtt_parser.c:1167` |
| `REQ-CAP-010` | Reject non-numeric payload for capacity limit | `test_capacity_limit_non_numeric` | `test_mqtt_parser.c:1179` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Set capacity limit to a valid value via MQTT
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "5000"
- **Then** Command type is MQTT_CMD_CAPACITY_LIMIT with capacity_limit 5000

### Set capacity limit to zero (disabled) via MQTT
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "0"
- **Then** Command type is MQTT_CMD_CAPACITY_LIMIT with capacity_limit 0

### Set capacity limit to maximum allowed value
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "25000"
- **Then** Command type is MQTT_CMD_CAPACITY_LIMIT with capacity_limit 25000

### Reject capacity limit above maximum
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "25001"
- **Then** Parsing returns false

### Reject negative capacity limit
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "-1"
- **Then** Parsing returns false

### Reject empty payload for capacity limit
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with empty payload
- **Then** Parsing returns false

### Reject non-numeric payload for capacity limit
**Requirement:** `REQ-CAP-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/CapacityLimit with payload "abc"
- **Then** Parsing returns false

</details>

---

## MQTT Change-Only Publishing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MQTT-020` | First integer publish always goes through | `test_int_first_publish` | `test_mqtt_publish.c:1` |
| `REQ-MQTT-020` | Unchanged integer is suppressed | `test_int_unchanged_suppressed` | `test_mqtt_publish.c:29` |
| `REQ-MQTT-020` | Changed integer value triggers publish | `test_int_changed_publishes` | `test_mqtt_publish.c:43` |
| `REQ-MQTT-021` | Heartbeat forces re-publish of unchanged integer | `test_int_heartbeat_republish` | `test_mqtt_publish.c:57` |
| `REQ-MQTT-020` | First string publish always goes through | `test_str_first_publish` | `test_mqtt_publish.c:74` |
| `REQ-MQTT-020` | Changed string value triggers publish | `test_str_changed_publishes` | `test_mqtt_publish.c:87` |
| `REQ-MQTT-022` | mqtt_cache_force_all marks all entries stale | `test_force_all_triggers_publish` | `test_mqtt_publish.c:104` |
| `REQ-MQTT-020` | CRC16 produces consistent non-zero hashes | `test_crc16_consistency` | `test_mqtt_publish.c:122` |
| `REQ-MQTT-020` | Out-of-range slot is rejected | `test_invalid_slot_rejected` | `test_mqtt_publish.c:143` |
| `REQ-MQTT-020` | MQTT_SLOT_COUNT fits within MQTT_CACHE_MAX_SLOTS | `test_slot_count_within_bounds` | `test_mqtt_publish.c:159` |

<details>
<summary>Detailed steps (10 scenarios)</summary>

### First integer publish always goes through
**Requirement:** `REQ-MQTT-020`

- **Given** An empty cache with heartbeat 60s
- **When** An integer value is checked for slot MQTT_SLOT_ESP_TEMP
- **Then** mqtt_should_publish_int returns true (first time)

### Unchanged integer is suppressed
**Requirement:** `REQ-MQTT-020`

- **Given** A cache with MQTT_SLOT_ESP_TEMP previously published as 42
- **When** The same value 42 is checked at now_s=110 (before heartbeat)
- **Then** mqtt_should_publish_int returns false

### Changed integer value triggers publish
**Requirement:** `REQ-MQTT-020`

- **Given** A cache with MQTT_SLOT_ESP_TEMP previously published as 42
- **When** A different value 43 is checked
- **Then** mqtt_should_publish_int returns true

### Heartbeat forces re-publish of unchanged integer
**Requirement:** `REQ-MQTT-021`

- **Given** A cache with MQTT_SLOT_ESP_TEMP published at t=100 with heartbeat 60s
- **When** The same value is checked at t=160 (heartbeat elapsed)
- **Then** mqtt_should_publish_int returns true

### First string publish always goes through
**Requirement:** `REQ-MQTT-020`

- **Given** An empty cache with heartbeat 60s
- **When** A string value "Normal" is checked for slot MQTT_SLOT_MODE
- **Then** mqtt_should_publish_str returns true

### Changed string value triggers publish
**Requirement:** `REQ-MQTT-020`

- **Given** A cache with MQTT_SLOT_MODE previously published as "Normal"
- **When** A different string "Solar" is checked
- **Then** mqtt_should_publish_str returns true

### mqtt_cache_force_all marks all entries stale
**Requirement:** `REQ-MQTT-022`

- **Given** A cache with MQTT_SLOT_ESP_TEMP published (unchanged value)
- **When** mqtt_cache_force_all is called then the same value is checked
- **Then** mqtt_should_publish_int returns true (forced)

### CRC16 produces consistent non-zero hashes
**Requirement:** `REQ-MQTT-020`

- **Given** Known string inputs
- **When** mqtt_crc16 is called
- **Then** Different strings produce different hashes and same strings produce same hash

### Out-of-range slot is rejected
**Requirement:** `REQ-MQTT-020`

- **Given** A valid cache
- **When** mqtt_should_publish_int is called with slot >= MQTT_CACHE_MAX_SLOTS
- **Then** Returns false (no crash, no publish)

### MQTT_SLOT_COUNT fits within MQTT_CACHE_MAX_SLOTS
**Requirement:** `REQ-MQTT-020`

- **Given** The enum definition
- **When** MQTT_SLOT_COUNT is compared to MQTT_CACHE_MAX_SLOTS
- **Then** MQTT_SLOT_COUNT is less than or equal to MQTT_CACHE_MAX_SLOTS

</details>

---

## MQTT SoC Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SOC-001` | Parse Set/InitialSoC with valid percentage | `test_initial_soc_valid` | `test_mqtt_soc.c:1` |
| `REQ-SOC-002` | Parse Set/InitialSoC with -1 to reset/clear value | `test_initial_soc_reset` | `test_mqtt_soc.c:32` |
| `REQ-SOC-005` | Parse Set/InitialSoC boundary value 0 | `test_initial_soc_zero` | `test_mqtt_soc.c:70` |
| `REQ-SOC-006` | Parse Set/InitialSoC boundary value 100 | `test_initial_soc_max` | `test_mqtt_soc.c:84` |
| `REQ-SOC-007` | Parse Set/FullSoC with valid percentage | `test_full_soc_valid` | `test_mqtt_soc.c:100` |
| `REQ-SOC-008` | Parse Set/FullSoC with -1 to reset/clear value | `test_full_soc_reset` | `test_mqtt_soc.c:114` |
| `REQ-SOC-010` | Parse Set/EnergyCapacity with valid Wh value | `test_energy_capacity_valid` | `test_mqtt_soc.c:142` |
| `REQ-SOC-012` | Parse Set/EnergyCapacity boundary value 200000 | `test_energy_capacity_boundary_max` | `test_mqtt_soc.c:168` |
| `REQ-SOC-013` | Parse Set/EnergyCapacity with -1 to reset/clear value | `test_energy_capacity_reset` | `test_mqtt_soc.c:182` |
| `REQ-SOC-015` | Parse Set/EnergyRequest with valid Wh value | `test_energy_request_valid` | `test_mqtt_soc.c:210` |
| `REQ-SOC-017` | Parse Set/EVCCID with valid identifier | `test_evccid_set_valid` | `test_mqtt_soc.c:238` |
| `REQ-SOC-019` | Set/EVCCID accepts exactly 31 characters | `test_evccid_set_max_length` | `test_mqtt_soc.c:266` |
| `REQ-SOC-020` | Set/EVCCID accepts empty string to clear | `test_evccid_set_empty` | `test_mqtt_soc.c:282` |

<details>
<summary>Detailed steps (13 scenarios)</summary>

### Parse Set/InitialSoC with valid percentage
**Requirement:** `REQ-SOC-001`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "80"
- **Then** Command type is MQTT_CMD_INITIAL_SOC with initial_soc = 80

### Parse Set/InitialSoC with -1 to reset/clear value
**Requirement:** `REQ-SOC-002`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "-1"
- **Then** Command type is MQTT_CMD_INITIAL_SOC with initial_soc = -1

### Parse Set/InitialSoC boundary value 0
**Requirement:** `REQ-SOC-005`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "0"
- **Then** Command type is MQTT_CMD_INITIAL_SOC with initial_soc = 0

### Parse Set/InitialSoC boundary value 100
**Requirement:** `REQ-SOC-006`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "100"
- **Then** Command type is MQTT_CMD_INITIAL_SOC with initial_soc = 100

### Parse Set/FullSoC with valid percentage
**Requirement:** `REQ-SOC-007`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/FullSoC with payload "95"
- **Then** Command type is MQTT_CMD_FULL_SOC with full_soc = 95

### Parse Set/FullSoC with -1 to reset/clear value
**Requirement:** `REQ-SOC-008`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/FullSoC with payload "-1"
- **Then** Command type is MQTT_CMD_FULL_SOC with full_soc = -1

### Parse Set/EnergyCapacity with valid Wh value
**Requirement:** `REQ-SOC-010`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "64000"
- **Then** Command type is MQTT_CMD_ENERGY_CAPACITY with energy_capacity = 64000

### Parse Set/EnergyCapacity boundary value 200000
**Requirement:** `REQ-SOC-012`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "200000"
- **Then** Command type is MQTT_CMD_ENERGY_CAPACITY with energy_capacity = 200000

### Parse Set/EnergyCapacity with -1 to reset/clear value
**Requirement:** `REQ-SOC-013`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "-1"
- **Then** Command type is MQTT_CMD_ENERGY_CAPACITY with energy_capacity = -1

### Parse Set/EnergyRequest with valid Wh value
**Requirement:** `REQ-SOC-015`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyRequest with payload "32000"
- **Then** Command type is MQTT_CMD_ENERGY_REQUEST with energy_request = 32000

### Parse Set/EVCCID with valid identifier
**Requirement:** `REQ-SOC-017`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EVCCID with payload "WBADE12345678901"
- **Then** Command type is MQTT_CMD_EVCCID_SET with evccid matching the payload

### Set/EVCCID accepts exactly 31 characters
**Requirement:** `REQ-SOC-019`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EVCCID with a 31-character payload
- **Then** The parser returns true with the full string stored

### Set/EVCCID accepts empty string to clear
**Requirement:** `REQ-SOC-020`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EVCCID with empty payload ""
- **Then** The parser returns true with an empty evccid

</details>

---

## MQTT SoC Input Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SOC-003` | Reject Set/InitialSoC with value above 100 | `test_initial_soc_above_max` | `test_mqtt_soc.c:46` |
| `REQ-SOC-004` | Reject Set/InitialSoC with value below -1 | `test_initial_soc_below_min` | `test_mqtt_soc.c:58` |
| `REQ-SOC-009` | Reject Set/FullSoC with value above 100 | `test_full_soc_above_max` | `test_mqtt_soc.c:128` |
| `REQ-SOC-011` | Reject Set/EnergyCapacity above 200000 Wh | `test_energy_capacity_above_max` | `test_mqtt_soc.c:156` |
| `REQ-SOC-014` | Reject Set/EnergyCapacity below -1 | `test_energy_capacity_below_min` | `test_mqtt_soc.c:196` |
| `REQ-SOC-016` | Reject Set/EnergyRequest above 200000 Wh | `test_energy_request_above_max` | `test_mqtt_soc.c:224` |
| `REQ-SOC-018` | Set/EVCCID truncated at 31 chars (32-byte buffer with NUL) | `test_evccid_set_too_long` | `test_mqtt_soc.c:252` |
| `REQ-SOC-021` | Empty payload is rejected for InitialSoC | `test_initial_soc_empty_payload` | `test_mqtt_soc.c:298` |
| `REQ-SOC-022` | Empty payload is rejected for FullSoC | `test_full_soc_empty_payload` | `test_mqtt_soc.c:310` |
| `REQ-SOC-023` | Empty payload is rejected for EnergyCapacity | `test_energy_capacity_empty_payload` | `test_mqtt_soc.c:322` |
| `REQ-SOC-024` | Empty payload is rejected for EnergyRequest | `test_energy_request_empty_payload` | `test_mqtt_soc.c:334` |
| `REQ-SOC-025` | Non-numeric payload is rejected for InitialSoC | `test_initial_soc_non_numeric` | `test_mqtt_soc.c:348` |
| `REQ-SOC-026` | Non-numeric payload is rejected for EnergyCapacity | `test_energy_capacity_non_numeric` | `test_mqtt_soc.c:360` |

<details>
<summary>Detailed steps (13 scenarios)</summary>

### Reject Set/InitialSoC with value above 100
**Requirement:** `REQ-SOC-003`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "101"
- **Then** The parser returns false

### Reject Set/InitialSoC with value below -1
**Requirement:** `REQ-SOC-004`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "-2"
- **Then** The parser returns false

### Reject Set/FullSoC with value above 100
**Requirement:** `REQ-SOC-009`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/FullSoC with payload "101"
- **Then** The parser returns false

### Reject Set/EnergyCapacity above 200000 Wh
**Requirement:** `REQ-SOC-011`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "200001"
- **Then** The parser returns false

### Reject Set/EnergyCapacity below -1
**Requirement:** `REQ-SOC-014`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "-2"
- **Then** The parser returns false

### Reject Set/EnergyRequest above 200000 Wh
**Requirement:** `REQ-SOC-016`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyRequest with payload "200001"
- **Then** The parser returns false

### Set/EVCCID truncated at 31 chars (32-byte buffer with NUL)
**Requirement:** `REQ-SOC-018`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EVCCID with a 32-character payload
- **Then** The parser returns false because payload >= sizeof(evccid)

### Empty payload is rejected for InitialSoC
**Requirement:** `REQ-SOC-021`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with empty payload ""
- **Then** The parser returns false

### Empty payload is rejected for FullSoC
**Requirement:** `REQ-SOC-022`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/FullSoC with empty payload ""
- **Then** The parser returns false

### Empty payload is rejected for EnergyCapacity
**Requirement:** `REQ-SOC-023`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with empty payload ""
- **Then** The parser returns false

### Empty payload is rejected for EnergyRequest
**Requirement:** `REQ-SOC-024`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyRequest with empty payload ""
- **Then** The parser returns false

### Non-numeric payload is rejected for InitialSoC
**Requirement:** `REQ-SOC-025`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/InitialSoC with payload "abc"
- **Then** The parser returns false

### Non-numeric payload is rejected for EnergyCapacity
**Requirement:** `REQ-SOC-026`

- **Given** A valid MQTT prefix
- **When** Topic is prefix/Set/EnergyCapacity with payload "abc"
- **Then** The parser returns false

</details>

---

## Multi-Node Load Balancing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MULTI-001` | Four EVSEs receive equal current distribution | `test_four_evse_fair_distribution` | `test_multi_node.c:1` |
| `REQ-MULTI-002` | Master EVSE BalancedMax is derived from ChargeCurrent | `test_four_evse_master_max_from_chargecurrent` | `test_multi_node.c:74` |
| `REQ-MULTI-003` | One EVSE with low max capacity, remainder shared by others | `test_one_evse_low_max_others_share` | `test_multi_node.c:102` |
| `REQ-MULTI-004` | Node going offline causes redistribution to remaining active nodes | `test_node_goes_offline_redistributes` | `test_multi_node.c:130` |
| `REQ-MULTI-005` | Priority scheduling allocates available power to highest-priority EVSE during shortage | `test_all_nodes_mincurrent_during_shortage` | `test_multi_node.c:159` |
| `REQ-MULTI-006` | MaxCircuit limits total current distribution across all nodes | `test_maxcircuit_limits_total_distribution` | `test_multi_node.c:189` |
| `REQ-MULTI-007` | MaxCircuit accounts for EV meter baseload in distribution | `test_maxcircuit_with_ev_meter_baseload` | `test_multi_node.c:217` |
| `REQ-MULTI-008` | Six EVSEs in large cluster receive fair distribution | `test_six_evse_fair_distribution` | `test_multi_node.c:243` |
| `REQ-MULTI-009` | NoCurrent counter increments during hard power shortage | `test_nocurrent_increments_on_hard_shortage` | `test_multi_node.c:269` |
| `REQ-MULTI-010` | NoCurrent counter clears when sufficient power is available | `test_nocurrent_zero_when_sufficient` | `test_multi_node.c:296` |
| `REQ-MULTI-011` | Node in STATE_B does not participate in current distribution | `test_state_b_node_gets_no_current` | `test_multi_node.c:321` |
| `REQ-MULTI-012` | IsetBalanced is capped at the sum of all active node maximums | `test_isetbalanced_capped_at_active_max` | `test_multi_node.c:346` |
| `REQ-MULTI-013` | Three EVSEs with all different BalancedMax values | `test_three_evse_all_different_max` | `test_multi_node.c:371` |
| `REQ-MULTI-014` | Tight circuit with unequal max: surplus from small EVSE redistributed | `test_unequal_max_tight_circuit` | `test_multi_node.c:402` |

<details>
<summary>Detailed steps (14 scenarios)</summary>

### Four EVSEs receive equal current distribution
**Requirement:** `REQ-MULTI-001`

- **Given** Master with 4 EVSEs all in STATE_C, MaxCircuit=64A, no EV meter baseload
- **When** Balanced current is calculated
- **Then** Each EVSE receives 160 deciamps (640 / 4 = 160) with all values equal

### Master EVSE BalancedMax is derived from ChargeCurrent
**Requirement:** `REQ-MULTI-002`

- **Given** Master with 4 EVSEs all in STATE_C, master ChargeCurrent limited to 200 deciamps (20A)
- **When** Balanced current is calculated
- **Then** Master EVSE (Balanced[0]) does not exceed its ChargeCurrent limit of 200 deciamps

### One EVSE with low max capacity, remainder shared by others
**Requirement:** `REQ-MULTI-003`

- **Given** Master with 3 EVSEs in STATE_C, node 1 limited to BalancedMax=60 deciamps (6A)
- **When** Balanced current is calculated
- **Then** Node 1 receives at most 60 deciamps while nodes 0 and 2 share the remainder equally

### Node going offline causes redistribution to remaining active nodes
**Requirement:** `REQ-MULTI-004`

- **Given** Master with 3 EVSEs in STATE_C receiving equal distribution
- **When** Node 2 goes offline (BalancedState changes to STATE_A) and current is recalculated
- **Then** Remaining active nodes each receive more current than before and offline node gets 0

### Priority scheduling allocates available power to highest-priority EVSE during shortage
**Requirement:** `REQ-MULTI-005`

- **Given** Master with 4 EVSEs in STATE_C in Smart mode, available power ~105 dA (enough for 1 EVSE, not 4)
- **When** Balanced current is calculated with insufficient power for all nodes
- **Then** Highest-priority EVSE gets all available power, others are paused

### MaxCircuit limits total current distribution across all nodes
**Requirement:** `REQ-MULTI-006`

- **Given** Master with 4 EVSEs in STATE_C in Normal mode with MaxCircuit=24A
- **When** Balanced current is calculated
- **Then** Total distributed current across all nodes does not exceed 240 deciamps (MaxCircuit * 10)

### MaxCircuit accounts for EV meter baseload in distribution
**Requirement:** `REQ-MULTI-007`

- **Given** Master with 2 EVSEs in STATE_C, MaxCircuit=20A, EV meter measuring 250 deciamps total
- **When** Balanced current is calculated with EV meter baseload subtracted
- **Then** Total distributed current does not exceed (MaxCircuit * 10) minus baseload

### Six EVSEs in large cluster receive fair distribution
**Requirement:** `REQ-MULTI-008`

- **Given** Master with 6 EVSEs all in STATE_C, MaxCircuit=64A
- **When** Balanced current is calculated
- **Then** All 6 EVSEs receive equal current within 1 deciamp tolerance (integer division rounding)

### NoCurrent counter increments during hard power shortage
**Requirement:** `REQ-MULTI-009`

- **Given** Master with 4 EVSEs in Smart mode, 50A mains measured against 25A limit, IsetBalanced too low
- **When** Balanced current is calculated and total MinCurrent demand exceeds available power
- **Then** NoCurrent counter increments above 0 indicating sustained shortage

### NoCurrent counter clears when sufficient power is available
**Requirement:** `REQ-MULTI-010`

- **Given** Master with 2 EVSEs in Smart mode, low mains load, IsetBalanced=400, NoCurrent previously at 5
- **When** Balanced current is calculated with plenty of available power
- **Then** NoCurrent counter decays by 1 (gradual recovery)

### Node in STATE_B does not participate in current distribution
**Requirement:** `REQ-MULTI-011`

- **Given** Master with 3 EVSEs, nodes 0 and 2 in STATE_C, node 1 in STATE_B (waiting)
- **When** Balanced current is calculated
- **Then** Only active STATE_C nodes (0 and 2) receive distributed current, each getting 320 deciamps

### IsetBalanced is capped at the sum of all active node maximums
**Requirement:** `REQ-MULTI-012`

- **Given** Master with 2 EVSEs in STATE_C, node 1 limited to BalancedMax=80 deciamps (8A)
- **When** Balanced current is calculated with IsetBalanced exceeding ActiveMax (320+80=400)
- **Then** IsetBalanced is capped to 400, node 0 gets 320 and node 1 gets 80

### Three EVSEs with all different BalancedMax values
**Requirement:** `REQ-MULTI-013`

- **Given** Master with 3 EVSEs: max 320, 160, 80 deciamps, MaxCircuit=64A
- **When** Balanced current is calculated
- **Then** Each EVSE capped at its max, remainder redistributed to uncapped EVSEs

### Tight circuit with unequal max: surplus from small EVSE redistributed
**Requirement:** `REQ-MULTI-014`

- **Given** 2 EVSEs: EVSE[0] max 320, EVSE[1] max 60 (MinCurrent), MaxCircuit=25A
- **When** Balanced current is calculated
- **Then** EVSE[1] gets 60, EVSE[0] gets remainder (250-60=190)

</details>

---

## Multi-Node Solar Charging

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MULTI-SOL-001` | Two nodes solar shortage: SolarStopTimer starts when Isum exceeds threshold | `test_solar_multi_node_shortage_starts_timer` | `test_multi_node_solar.c:1` |
| `REQ-MULTI-SOL-001B` | Two nodes solar shortage with moderate import starts SolarStopTimer | `test_solar_multi_node_shortage_timer_moderate_import` | `test_multi_node_solar.c:81` |
| `REQ-MULTI-SOL-002` | Two nodes solar shortage: priority scheduling pauses lower-priority node | `test_solar_multi_node_pauses_with_no_sun` | `test_multi_node_solar.c:107` |
| `REQ-MULTI-SOL-003` | Four nodes solar: Isum above threshold starts timer and pauses nodes | `test_solar_four_nodes_above_threshold` | `test_multi_node_solar.c:140` |
| `REQ-MULTI-SOL-003B` | Four nodes solar with 40A import starts SolarStopTimer | `test_solar_four_nodes_no_surplus_starts_timer` | `test_multi_node_solar.c:169` |
| `REQ-MULTI-SOL-004` | Two nodes with sufficient solar surplus: both charge | `test_solar_multi_node_surplus_both_charge` | `test_multi_node_solar.c:197` |
| `REQ-MULTI-SOL-005` | Two nodes with marginal surplus: enough for one, not both | `test_solar_multi_node_marginal_surplus` | `test_multi_node_solar.c:221` |
| `REQ-MULTI-SOL-006` | SolarStopTimer does not restart when already running | `test_solar_multi_node_timer_no_restart` | `test_multi_node_solar.c:250` |
| `REQ-MULTI-SOL-007` | Solar surplus returns: SolarStopTimer clears | `test_solar_multi_node_surplus_clears_timer` | `test_multi_node_solar.c:272` |
| `REQ-MULTI-SOL-008` | SolarStopTimer suppressed during startup settling | `test_solar_multi_node_timer_suppressed_startup` | `test_multi_node_solar.c:295` |
| `REQ-MULTI-SOL-008B` | SolarStopTimer threshold is per-EVSE: just below threshold, timer does not start | `test_solar_multi_node_timer_below_threshold_no_start` | `test_multi_node_solar.c:317` |
| `REQ-MULTI-SOL-008C` | SolarStopTimer threshold is per-EVSE: just above threshold, timer starts | `test_solar_multi_node_timer_above_threshold_starts` | `test_multi_node_solar.c:342` |
| `REQ-MULTI-SOL-009` | Solar mode produces different distribution than Normal mode | `test_solar_vs_normal_distribution_differs` | `test_multi_node_solar.c:371` |
| `REQ-MULTI-SOL-010` | Smart mode produces different distribution than Solar mode under same conditions | `test_solar_vs_smart_distribution_differs` | `test_multi_node_solar.c:410` |
| `REQ-MULTI-SOL-011` | Node goes offline during solar shortage | `test_solar_multi_node_offline_during_shortage` | `test_multi_node_solar.c:452` |
| `REQ-MULTI-SOL-012` | Solar mode with ImportCurrent allows some grid import | `test_solar_multi_node_import_current_tolerance` | `test_multi_node_solar.c:489` |
| `REQ-MULTI-SOL-013` | NoCurrent threshold eventually triggers LESS_6A in multi-node solar | `test_solar_multi_node_nocurrent_threshold` | `test_multi_node_solar.c:514` |
| `REQ-MULTI-SOL-014` | Sufficient solar but tight capacity headroom forces shortage | `test_solar_capacity_surplus_but_headroom_tight` | `test_multi_node_solar.c:551` |
| `REQ-MULTI-SOL-015` | No solar AND tight capacity: both constraints active | `test_solar_capacity_no_surplus_tight_headroom` | `test_multi_node_solar.c:587` |
| `REQ-MULTI-SOL-016` | Capacity headroom disabled (0) has no effect on solar logic | `test_solar_capacity_disabled_no_effect` | `test_multi_node_solar.c:614` |
| `REQ-MULTI-SOL-017` | Capacity headroom negative: power budget exceeded, forces immediate shortage | `test_solar_capacity_negative_headroom` | `test_multi_node_solar.c:640` |
| `REQ-MULTI-SOL-018` | SolarStopTimer expiry transitions STATE_C to STATE_C1 (power pause) | `test_solar_stop_pauses_power_not_session` | `test_multi_node_solar.c:681` |
| `REQ-MULTI-SOL-019` | LESS_6A clears when solar returns (auto-recovery) | `test_solar_return_clears_less6a` | `test_multi_node_solar.c:708` |
| `REQ-MULTI-SOL-020` | Full solar pause/resume cycle preserves AccessStatus | `test_solar_full_pause_cycle_preserves_access` | `test_multi_node_solar.c:735` |

<details>
<summary>Detailed steps (24 scenarios)</summary>

### Two nodes solar shortage: SolarStopTimer starts when Isum exceeds threshold
**Requirement:** `REQ-MULTI-SOL-001`

- **Given** Master with 2 EVSEs in STATE_C, solar mode, grid importing above threshold
- **When** evse_calc_balanced_current is called with Isum above (ActiveEVSE*MinCurrent*Phases - StartCurrent)*10
- **Then** SolarStopTimer starts counting down from StopTime * 60

### Two nodes solar shortage with moderate import starts SolarStopTimer
**Requirement:** `REQ-MULTI-SOL-001B`

- **Given** Master with 2 EVSEs in STATE_C, solar mode, grid importing 20A (no surplus)
- **When** evse_calc_balanced_current is called
- **Then** SolarStopTimer starts because Isum (200) > single-EVSE threshold (140)

### Two nodes solar shortage: priority scheduling pauses lower-priority node
**Requirement:** `REQ-MULTI-SOL-002`

- **Given** Master with 2 EVSEs in STATE_C, solar mode, grid importing heavily (Isum=300)
- **When** evse_calc_balanced_current is called with very low actual available power
- **Then** At least one EVSE gets Balanced=0 (paused via priority scheduling)

### Four nodes solar: Isum above threshold starts timer and pauses nodes
**Requirement:** `REQ-MULTI-SOL-003`

- **Given** Master with 4 EVSEs in STATE_C, solar mode, Isum above 4-node threshold
- **When** evse_calc_balanced_current is called
- **Then** SolarStopTimer is started and at least some EVSEs are paused

### Four nodes solar with 40A import starts SolarStopTimer
**Requirement:** `REQ-MULTI-SOL-003B`

- **Given** Master with 4 EVSEs in STATE_C, solar mode, grid importing 40A
- **When** evse_calc_balanced_current is called
- **Then** SolarStopTimer starts because Isum (400) > single-EVSE threshold (140)

### Two nodes with sufficient solar surplus: both charge
**Requirement:** `REQ-MULTI-SOL-004`

- **Given** Master with 2 EVSEs in STATE_C, solar mode, grid exporting 15A (surplus)
- **When** evse_calc_balanced_current is called
- **Then** Both EVSEs receive current >= MinCurrent and SolarStopTimer stays 0

### Two nodes with marginal surplus: enough for one, not both
**Requirement:** `REQ-MULTI-SOL-005`

- **Given** Master with 2 EVSEs in STATE_C, solar mode, surplus of ~8A (enough for 1 at 6A, not 2)
- **When** evse_calc_balanced_current is called
- **Then** Priority EVSE gets current, other is paused with NO_SUN

### SolarStopTimer does not restart when already running
**Requirement:** `REQ-MULTI-SOL-006`

- **Given** Master with 2 EVSEs in solar mode, SolarStopTimer already at 300
- **When** evse_calc_balanced_current is called again with shortage
- **Then** SolarStopTimer retains its existing value (not reset to StopTime*60)

### Solar surplus returns: SolarStopTimer clears
**Requirement:** `REQ-MULTI-SOL-007`

- **Given** Master with 2 EVSEs in solar mode, SolarStopTimer running at 300
- **When** surplus returns (no shortage) and evse_calc_balanced_current is called
- **Then** SolarStopTimer is reset to 0

### SolarStopTimer suppressed during startup settling
**Requirement:** `REQ-MULTI-SOL-008`

- **Given** Master with 2 EVSEs, Node[0].IntTimer < SOLARSTARTTIME (in startup)
- **When** evse_calc_balanced_current is called with shortage
- **Then** SolarStopTimer remains 0 (suppressed during startup)

### SolarStopTimer threshold is per-EVSE: just below threshold, timer does not start
**Requirement:** `REQ-MULTI-SOL-008B`

- **Given** Master with 2 EVSEs in solar mode, Isum just below single-EVSE threshold
- **When** evse_calc_balanced_current is called
- **Then** SolarStopTimer stays 0 (stopping last car would cause immediate restart)

### SolarStopTimer threshold is per-EVSE: just above threshold, timer starts
**Requirement:** `REQ-MULTI-SOL-008C`

- **Given** Master with 2 EVSEs in solar mode, Isum just above single-EVSE threshold
- **When** evse_calc_balanced_current is called
- **Then** SolarStopTimer starts (not enough solar for even one car)

### Solar mode produces different distribution than Normal mode
**Requirement:** `REQ-MULTI-SOL-009`

- **Given** Master with 2 EVSEs in STATE_C, same grid conditions
- **When** evse_calc_balanced_current is called in Normal mode vs Solar mode
- **Then** Solar mode distributes based on surplus; Normal mode distributes based on MaxCircuit

### Smart mode produces different distribution than Solar mode under same conditions
**Requirement:** `REQ-MULTI-SOL-010`

- **Given** Master with 2 EVSEs in STATE_C, grid importing 10A
- **When** evse_calc_balanced_current is called in Smart mode vs Solar mode
- **Then** Smart mode uses MaxMains regulation; Solar mode uses surplus regulation

### Node goes offline during solar shortage
**Requirement:** `REQ-MULTI-SOL-011`

- **Given** Master with 3 EVSEs in solar mode with shortage, SolarStopTimer running
- **When** Node 2 goes offline (STATE_A) and current is recalculated
- **Then** Fewer active EVSEs means less MinCurrent demand; may resolve shortage

### Solar mode with ImportCurrent allows some grid import
**Requirement:** `REQ-MULTI-SOL-012`

- **Given** Master with 2 EVSEs in solar mode, ImportCurrent=6A, grid importing 5A
- **When** evse_calc_balanced_current is called
- **Then** ImportCurrent tolerance means 5A import is acceptable; no shortage

### NoCurrent threshold eventually triggers LESS_6A in multi-node solar
**Requirement:** `REQ-MULTI-SOL-013`

- **Given** Master with 2 EVSEs in solar mode, repeated hard shortage cycles
- **When** evse_calc_balanced_current is called multiple times with NoCurrent accumulating
- **Then** After NoCurrent reaches threshold, LESS_6A error flag is set

### Sufficient solar but tight capacity headroom forces shortage
**Requirement:** `REQ-MULTI-SOL-014`

- **Given** Master with 2 EVSEs in solar mode, grid exporting (solar surplus),
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced is capped by headroom, shortage detected, priority scheduling runs

### No solar AND tight capacity: both constraints active
**Requirement:** `REQ-MULTI-SOL-015`

- **Given** Master with 2 EVSEs in solar mode, grid importing 20A,
- **When** evse_calc_balanced_current is called
- **Then** Shortage detected via both solar regulation AND capacity headroom

### Capacity headroom disabled (0) has no effect on solar logic
**Requirement:** `REQ-MULTI-SOL-016`

- **Given** Master with 2 EVSEs in solar mode, CapacityHeadroom_da = INT16_MAX (disabled)
- **When** evse_calc_balanced_current is called with solar surplus
- **Then** Capacity does not constrain charging; both EVSEs charge normally

### Capacity headroom negative: power budget exceeded, forces immediate shortage
**Requirement:** `REQ-MULTI-SOL-017`

- **Given** Master with 2 EVSEs in solar mode, CapacityHeadroom_da = -50 (over budget)
- **When** evse_calc_balanced_current is called even with solar surplus
- **Then** Shortage detected due to capacity (IsetBalanced capped very low)

### SolarStopTimer expiry transitions STATE_C to STATE_C1 (power pause)
**Requirement:** `REQ-MULTI-SOL-018`

- **Given** EVSE in STATE_C, SolarStopTimer about to expire
- **When** evse_tick_1s decrements SolarStopTimer to 0
- **Then** State transitions to STATE_C1 (power paused), LESS_6A set

### LESS_6A clears when solar returns (auto-recovery)
**Requirement:** `REQ-MULTI-SOL-019`

- **Given** EVSE with LESS_6A set, solar surplus returns (Isum negative)
- **When** evse_tick_1s checks evse_is_current_available
- **Then** LESS_6A is cleared, allowing state machine to resume charging

### Full solar pause/resume cycle preserves AccessStatus
**Requirement:** `REQ-MULTI-SOL-020`

- **Given** EVSE in STATE_C charging, SolarStopTimer expires
- **When** State goes C→C1 and C1Timer counts down to B1
- **Then** AccessStatus stays ON throughout (OCPP tx survives the pause)

</details>

---

## OCPP Current Limiting

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-001` | OCPP current limit exactly at MinCurrent boundary is accepted | `test_ocpp_limit_equal_to_mincurrent` | `test_ocpp.c:1` |
| `REQ-OCPP-002` | OCPP current limit exactly at MaxCurrent does not reduce current | `test_ocpp_limit_equal_to_maxcurrent` | `test_ocpp.c:60` |
| `REQ-OCPP-003` | OCPP current limit above MaxCurrent does not increase current beyond MaxCurrent | `test_ocpp_limit_above_maxcurrent_no_increase` | `test_ocpp.c:78` |
| `REQ-OCPP-004` | OCPP current limit is ignored when LoadBl is set to master | `test_ocpp_ignored_when_loadbl_master` | `test_ocpp.c:96` |
| `REQ-OCPP-005` | OCPP current limit is ignored when LoadBl is set to node | `test_ocpp_ignored_when_loadbl_node` | `test_ocpp.c:115` |
| `REQ-OCPP-006` | OverrideCurrent takes precedence over OCPP limit | `test_override_current_overrides_ocpp` | `test_ocpp.c:134` |
| `REQ-OCPP-007` | OverrideCurrent restores charging even when OCPP would zero the current | `test_override_current_overrides_ocpp_zero` | `test_ocpp.c:151` |
| `REQ-OCPP-008` | OCPP current limit of 0.0A zeros the charge current | `test_ocpp_limit_zero_zeros_current` | `test_ocpp.c:170` |
| `REQ-OCPP-009` | Negative OCPP current limit is treated as no limit set | `test_ocpp_negative_limit_no_restriction` | `test_ocpp.c:188` |
| `REQ-OCPP-010` | OCPP limit of 0.0A blocks current availability check | `test_ocpp_blocks_current_available_at_zero` | `test_ocpp.c:206` |
| `REQ-OCPP-011` | OCPP limit at MinCurrent allows current availability | `test_ocpp_allows_current_available_at_mincurrent` | `test_ocpp.c:223` |
| `REQ-OCPP-012` | Negative OCPP limit does not block current availability | `test_ocpp_negative_limit_allows_current_available` | `test_ocpp.c:241` |

<details>
<summary>Detailed steps (12 scenarios)</summary>

### OCPP current limit exactly at MinCurrent boundary is accepted
**Requirement:** `REQ-OCPP-001`

- **Given** EVSE is standalone in STATE_C with OcppMode enabled and MinCurrent=6A
- **When** OcppCurrentLimit is set to 6.0A (exactly MinCurrent) and balanced current is calculated
- **Then** ChargeCurrent is set to 60 deciamps (6A) because the limit equals MinCurrent

### OCPP current limit exactly at MaxCurrent does not reduce current
**Requirement:** `REQ-OCPP-002`

- **Given** EVSE is standalone in STATE_C with OcppMode enabled and MaxCurrent=16A
- **When** OcppCurrentLimit is set to 16.0A (exactly MaxCurrent) and balanced current is calculated
- **Then** ChargeCurrent remains at 160 deciamps (16A) because OCPP limit does not cap below MaxCurrent

### OCPP current limit above MaxCurrent does not increase current beyond MaxCurrent
**Requirement:** `REQ-OCPP-003`

- **Given** EVSE is standalone in STATE_C with OcppMode enabled and MaxCurrent=16A
- **When** OcppCurrentLimit is set to 32.0A (well above MaxCurrent) and balanced current is calculated
- **Then** ChargeCurrent stays at 160 deciamps (MaxCurrent) because OCPP cannot raise current above hardware limit

### OCPP current limit is ignored when LoadBl is set to master
**Requirement:** `REQ-OCPP-004`

- **Given** EVSE is a master (LoadBl=1) in STATE_C with OcppMode enabled
- **When** OcppCurrentLimit is set to 3.0A (below MinCurrent) and balanced current is calculated
- **Then** ChargeCurrent remains at 160 deciamps because OCPP limit requires standalone mode (LoadBl=0)

### OCPP current limit is ignored when LoadBl is set to node
**Requirement:** `REQ-OCPP-005`

- **Given** EVSE is a node (LoadBl=2) in STATE_C with OcppMode enabled
- **When** OcppCurrentLimit is set to 3.0A (below MinCurrent) and balanced current is calculated
- **Then** ChargeCurrent remains at 160 deciamps because OCPP limit requires standalone mode (LoadBl=0)

### OverrideCurrent takes precedence over OCPP limit
**Requirement:** `REQ-OCPP-006`

- **Given** EVSE is standalone in STATE_C with OcppCurrentLimit=10.0A and OverrideCurrent=80 deciamps
- **When** Balanced current is calculated
- **Then** ChargeCurrent is set to 80 deciamps because OverrideCurrent is applied after OCPP capping

### OverrideCurrent restores charging even when OCPP would zero the current
**Requirement:** `REQ-OCPP-007`

- **Given** EVSE is standalone in STATE_C with OcppCurrentLimit=3.0A (below MinCurrent) and OverrideCurrent=120
- **When** Balanced current is calculated
- **Then** ChargeCurrent is set to 120 deciamps because OverrideCurrent overrides the OCPP-zeroed value

### OCPP current limit of 0.0A zeros the charge current
**Requirement:** `REQ-OCPP-008`

- **Given** EVSE is standalone in STATE_C with OcppMode enabled
- **When** OcppCurrentLimit is set to 0.0A and balanced current is calculated
- **Then** ChargeCurrent is zeroed because 0.0A is below MinCurrent (6A)

### Negative OCPP current limit is treated as no limit set
**Requirement:** `REQ-OCPP-009`

- **Given** EVSE is standalone in STATE_C with OcppMode enabled
- **When** OcppCurrentLimit is set to -1.0A (default init value meaning no limit)
- **Then** ChargeCurrent remains at 160 deciamps because the OCPP capping block is skipped

### OCPP limit of 0.0A blocks current availability check
**Requirement:** `REQ-OCPP-010`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=0.0A
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because OCPP limit is below MinCurrent

### OCPP limit at MinCurrent allows current availability
**Requirement:** `REQ-OCPP-011`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=6.0A (MinCurrent)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because 6.0A is not less than MinCurrent

### Negative OCPP limit does not block current availability
**Requirement:** `REQ-OCPP-012`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=-1.0A (no limit)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because negative limit skips the OCPP availability check

</details>

---

## OCPP Authorization

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-025` | Auth path selection returns OCPP-controlled for RFIDReader=6 | `test_auth_path_rfid_reader_6` | `test_ocpp_auth.c:1` |
| `REQ-OCPP-026` | Auth path selection returns OCPP-controlled for RFIDReader=0 | `test_auth_path_rfid_reader_0` | `test_ocpp_auth.c:26` |
| `REQ-OCPP-027` | Auth path selection returns builtin-RFID for RFIDReader=1..5 | `test_auth_path_rfid_reader_1` | `test_ocpp_auth.c:38` |
| `REQ-OCPP-027` | Auth path selection returns builtin-RFID for RFIDReader=5 | `test_auth_path_rfid_reader_5` | `test_ocpp_auth.c:50` |
| `REQ-OCPP-027` | Auth path selection returns builtin-RFID for RFIDReader=3 | `test_auth_path_rfid_reader_3` | `test_ocpp_auth.c:62` |
| `REQ-OCPP-020` | OCPP sets Access_bit on rising edge of permits_charge | `test_should_set_access_on_rising_edge` | `test_ocpp_auth.c:76` |
| `REQ-OCPP-022` | OCPP does not re-set Access_bit if already permitted | `test_should_not_set_access_when_already_permitted` | `test_ocpp_auth.c:88` |
| `REQ-OCPP-020` | OCPP does not set Access_bit when charge not permitted | `test_should_not_set_access_when_not_permitted` | `test_ocpp_auth.c:100` |
| `REQ-OCPP-020` | OCPP does not set Access_bit on falling edge | `test_should_not_set_access_on_falling_edge` | `test_ocpp_auth.c:112` |
| `REQ-OCPP-021` | OCPP clears Access_bit when permission revoked and access is ON | `test_should_clear_access_when_revoked_and_on` | `test_ocpp_auth.c:126` |
| `REQ-OCPP-021` | OCPP does not clear Access_bit when permission is still granted | `test_should_not_clear_access_when_still_permitted` | `test_ocpp_auth.c:138` |
| `REQ-OCPP-021` | OCPP does not clear Access_bit when access is already OFF | `test_should_not_clear_access_when_already_off` | `test_ocpp_auth.c:150` |
| `REQ-OCPP-021` | OCPP does not clear Access_bit when access is PAUSE | `test_should_not_clear_access_when_paused` | `test_ocpp_auth.c:162` |
| `REQ-OCPP-028` | FreeVend + Solar mode with NO_SUN defers Access_bit | `test_defer_access_solar_no_sun` | `test_ocpp_auth.c:176` |
| `REQ-OCPP-028` | FreeVend + Solar mode without NO_SUN does not defer | `test_no_defer_access_solar_with_surplus` | `test_ocpp_auth.c:188` |
| `REQ-OCPP-029` | FreeVend + ChargeDelay active defers Access_bit | `test_defer_access_charge_delay_active` | `test_ocpp_auth.c:200` |
| `REQ-OCPP-029` | FreeVend + ChargeDelay=0 does not defer in Normal mode | `test_no_defer_access_normal_no_delay` | `test_ocpp_auth.c:212` |
| `REQ-OCPP-028` | FreeVend + Solar mode with ChargeDelay defers (both conditions) | `test_defer_access_solar_delay_and_no_sun` | `test_ocpp_auth.c:224` |
| `REQ-OCPP-029` | Smart mode with ChargeDelay defers Access_bit | `test_defer_access_smart_with_delay` | `test_ocpp_auth.c:236` |
| `REQ-OCPP-028` | Smart mode without delay or errors does not defer | `test_no_defer_access_smart_no_delay` | `test_ocpp_auth.c:248` |
| `REQ-OCPP-028` | Normal mode with NO_SUN error does not defer (only Solar checks NO_SUN) | `test_no_defer_access_normal_with_no_sun` | `test_ocpp_auth.c:260` |
| `REQ-OCPP-096` | Invalid mode value does not defer access (safe default) | `test_defer_access_invalid_mode_returns_false` | `test_ocpp_auth.c:272` |

<details>
<summary>Detailed steps (22 scenarios)</summary>

### Auth path selection returns OCPP-controlled for RFIDReader=6
**Requirement:** `REQ-OCPP-025`

- **Given** RFIDReader is set to 6 (Rmt/OCPP mode)
- **When** ocpp_select_auth_path is called
- **Then** Returns OCPP_AUTH_PATH_OCPP_CONTROLLED because OCPP controls Access_bit

### Auth path selection returns OCPP-controlled for RFIDReader=0
**Requirement:** `REQ-OCPP-026`

- **Given** RFIDReader is set to 0 (Disabled)
- **When** ocpp_select_auth_path is called
- **Then** Returns OCPP_AUTH_PATH_OCPP_CONTROLLED because OCPP controls Access_bit when RFID is disabled

### Auth path selection returns builtin-RFID for RFIDReader=1..5
**Requirement:** `REQ-OCPP-027`

- **Given** RFIDReader is set to 1 (built-in RFID store)
- **When** ocpp_select_auth_path is called
- **Then** Returns OCPP_AUTH_PATH_BUILTIN_RFID because built-in RFID controls charging

### Auth path selection returns builtin-RFID for RFIDReader=5
**Requirement:** `REQ-OCPP-027`

- **Given** RFIDReader is set to 5
- **When** ocpp_select_auth_path is called
- **Then** Returns OCPP_AUTH_PATH_BUILTIN_RFID

### Auth path selection returns builtin-RFID for RFIDReader=3
**Requirement:** `REQ-OCPP-027`

- **Given** RFIDReader is set to 3
- **When** ocpp_select_auth_path is called
- **Then** Returns OCPP_AUTH_PATH_BUILTIN_RFID

### OCPP sets Access_bit on rising edge of permits_charge
**Requirement:** `REQ-OCPP-020`

- **Given** Previous permits_charge was false
- **When** Current permits_charge transitions to true
- **Then** ocpp_should_set_access returns true (set Access_bit ON)

### OCPP does not re-set Access_bit if already permitted
**Requirement:** `REQ-OCPP-022`

- **Given** Previous permits_charge was already true
- **When** Current permits_charge is still true
- **Then** ocpp_should_set_access returns false (Access_bit already set once)

### OCPP does not set Access_bit when charge not permitted
**Requirement:** `REQ-OCPP-020`

- **Given** Previous permits_charge was false
- **When** Current permits_charge is still false
- **Then** ocpp_should_set_access returns false

### OCPP does not set Access_bit on falling edge
**Requirement:** `REQ-OCPP-020`

- **Given** Previous permits_charge was true
- **When** Current permits_charge transitions to false
- **Then** ocpp_should_set_access returns false

### OCPP clears Access_bit when permission revoked and access is ON
**Requirement:** `REQ-OCPP-021`

- **Given** AccessStatus is ON (1) and permits_charge is false
- **When** ocpp_should_clear_access is called
- **Then** Returns true (clear Access_bit)

### OCPP does not clear Access_bit when permission is still granted
**Requirement:** `REQ-OCPP-021`

- **Given** AccessStatus is ON (1) and permits_charge is true
- **When** ocpp_should_clear_access is called
- **Then** Returns false (Access_bit should stay)

### OCPP does not clear Access_bit when access is already OFF
**Requirement:** `REQ-OCPP-021`

- **Given** AccessStatus is OFF (0) and permits_charge is false
- **When** ocpp_should_clear_access is called
- **Then** Returns false (Access_bit already cleared)

### OCPP does not clear Access_bit when access is PAUSE
**Requirement:** `REQ-OCPP-021`

- **Given** AccessStatus is PAUSE (2) and permits_charge is false
- **When** ocpp_should_clear_access is called
- **Then** Returns false because the clear logic only triggers on ON, not PAUSE

### FreeVend + Solar mode with NO_SUN defers Access_bit
**Requirement:** `REQ-OCPP-028`

- **Given** Mode is Solar, ErrorFlags has NO_SUN set, ChargeDelay=0
- **When** ocpp_should_defer_access is called
- **Then** Returns true because Solar mode has no surplus available

### FreeVend + Solar mode without NO_SUN does not defer
**Requirement:** `REQ-OCPP-028`

- **Given** Mode is Solar, ErrorFlags is clear (surplus available), ChargeDelay=0
- **When** ocpp_should_defer_access is called
- **Then** Returns false because solar surplus is available

### FreeVend + ChargeDelay active defers Access_bit
**Requirement:** `REQ-OCPP-029`

- **Given** Mode is Normal, ChargeDelay=60 (delay active), ErrorFlags clear
- **When** ocpp_should_defer_access is called
- **Then** Returns true because ChargeDelay is active

### FreeVend + ChargeDelay=0 does not defer in Normal mode
**Requirement:** `REQ-OCPP-029`

- **Given** Mode is Normal, ChargeDelay=0, ErrorFlags clear
- **When** ocpp_should_defer_access is called
- **Then** Returns false because no deferral conditions are met

### FreeVend + Solar mode with ChargeDelay defers (both conditions)
**Requirement:** `REQ-OCPP-028`

- **Given** Mode is Solar, ChargeDelay=30, ErrorFlags has NO_SUN
- **When** ocpp_should_defer_access is called
- **Then** Returns true because both Solar/NO_SUN and ChargeDelay trigger deferral

### Smart mode with ChargeDelay defers Access_bit
**Requirement:** `REQ-OCPP-029`

- **Given** Mode is Smart, ChargeDelay=10, ErrorFlags clear
- **When** ocpp_should_defer_access is called
- **Then** Returns true because ChargeDelay is active regardless of mode

### Smart mode without delay or errors does not defer
**Requirement:** `REQ-OCPP-028`

- **Given** Mode is Smart, ChargeDelay=0, ErrorFlags clear
- **When** ocpp_should_defer_access is called
- **Then** Returns false because Smart mode without ChargeDelay has no deferral

### Normal mode with NO_SUN error does not defer (only Solar checks NO_SUN)
**Requirement:** `REQ-OCPP-028`

- **Given** Mode is Normal, ErrorFlags has NO_SUN, ChargeDelay=0
- **When** ocpp_should_defer_access is called
- **Then** Returns false because NO_SUN deferral only applies in Solar mode

### Invalid mode value does not defer access (safe default)
**Requirement:** `REQ-OCPP-096`

- **Given** Mode is 255 (out-of-range), ChargeDelay=0, ErrorFlags has NO_SUN
- **When** ocpp_should_defer_access is called
- **Then** Returns false because invalid modes should not defer (safe default)

</details>

---

## OCPP Connector State

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-040` | CP voltage PILOT_3V indicates connector plugged | `test_connector_plugged_at_3v` | `test_ocpp_connector.c:1` |
| `REQ-OCPP-040` | CP voltage PILOT_6V indicates connector plugged | `test_connector_plugged_at_6v` | `test_ocpp_connector.c:26` |
| `REQ-OCPP-040` | CP voltage PILOT_9V indicates connector plugged | `test_connector_plugged_at_9v` | `test_ocpp_connector.c:38` |
| `REQ-OCPP-041` | CP voltage PILOT_12V indicates connector unplugged | `test_connector_unplugged_at_12v` | `test_ocpp_connector.c:50` |
| `REQ-OCPP-042` | CP voltage PILOT_NOK indicates connector unplugged | `test_connector_unplugged_at_nok` | `test_ocpp_connector.c:62` |
| `REQ-OCPP-042` | CP voltage PILOT_DIODE indicates connector unplugged | `test_connector_unplugged_at_diode` | `test_ocpp_connector.c:74` |
| `REQ-OCPP-042` | CP voltage PILOT_SHORT indicates connector unplugged | `test_connector_unplugged_at_short` | `test_ocpp_connector.c:86` |
| `REQ-OCPP-043` | CP voltage PILOT_3V indicates EV ready (State C/D) | `test_ev_ready_at_3v` | `test_ocpp_connector.c:100` |
| `REQ-OCPP-043` | CP voltage PILOT_6V indicates EV ready (State C) | `test_ev_ready_at_6v` | `test_ocpp_connector.c:112` |
| `REQ-OCPP-044` | CP voltage PILOT_9V indicates EV connected but not ready (State B) | `test_ev_not_ready_at_9v` | `test_ocpp_connector.c:124` |
| `REQ-OCPP-044` | CP voltage PILOT_12V indicates no EV (State A) | `test_ev_not_ready_at_12v` | `test_ocpp_connector.c:136` |
| `REQ-OCPP-044` | CP voltage PILOT_NOK indicates EV not ready | `test_ev_not_ready_at_nok` | `test_ocpp_connector.c:148` |
| `REQ-OCPP-120` | LockingTx present → occupied (pre-existing condition) | `test_occupied_locking_tx_present` | `test_ocpp_connector.c:313` |
| `REQ-OCPP-121` | StopTx within grace window → occupied (Finishing) | `test_occupied_stoptx_inside_grace_window` | `test_ocpp_connector.c:330` |
| `REQ-OCPP-121` | StopTx exactly at grace boundary → NOT occupied (< is strict) | `test_occupied_stoptx_at_grace_boundary_exclusive` | `test_ocpp_connector.c:348` |
| `REQ-OCPP-122` | StopTx past grace window → NOT occupied (Available) | `test_occupied_stoptx_past_grace_window` | `test_ocpp_connector.c:366` |
| `REQ-OCPP-122` | Non-StopTx notification within grace → NOT occupied | `test_occupied_non_stoptx_notification_ignored` | `test_ocpp_connector.c:384` |
| `REQ-OCPP-122` | Uninitialized notification state → NOT occupied | `test_occupied_notification_undefined` | `test_ocpp_connector.c:402` |

<details>
<summary>Detailed steps (18 scenarios)</summary>

### CP voltage PILOT_3V indicates connector plugged
**Requirement:** `REQ-OCPP-040`

- **Given** CP voltage is PILOT_3V (3V, State C/D)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns true because PILOT_3V is within plugged range

### CP voltage PILOT_6V indicates connector plugged
**Requirement:** `REQ-OCPP-040`

- **Given** CP voltage is PILOT_6V (6V, State C)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns true because PILOT_6V is within plugged range

### CP voltage PILOT_9V indicates connector plugged
**Requirement:** `REQ-OCPP-040`

- **Given** CP voltage is PILOT_9V (9V, State B)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns true because PILOT_9V is within plugged range

### CP voltage PILOT_12V indicates connector unplugged
**Requirement:** `REQ-OCPP-041`

- **Given** CP voltage is PILOT_12V (12V, State A)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns false because PILOT_12V means no vehicle connected

### CP voltage PILOT_NOK indicates connector unplugged
**Requirement:** `REQ-OCPP-042`

- **Given** CP voltage is PILOT_NOK (0, fault condition)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns false because PILOT_NOK is outside plugged range

### CP voltage PILOT_DIODE indicates connector unplugged
**Requirement:** `REQ-OCPP-042`

- **Given** CP voltage is PILOT_DIODE (1, diode check)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns false because PILOT_DIODE is below PILOT_3V

### CP voltage PILOT_SHORT indicates connector unplugged
**Requirement:** `REQ-OCPP-042`

- **Given** CP voltage is PILOT_SHORT (255, short circuit)
- **When** ocpp_is_connector_plugged is called
- **Then** Returns false because PILOT_SHORT is above PILOT_9V

### CP voltage PILOT_3V indicates EV ready (State C/D)
**Requirement:** `REQ-OCPP-043`

- **Given** CP voltage is PILOT_3V
- **When** ocpp_is_ev_ready is called
- **Then** Returns true because PILOT_3V is within EV-ready range

### CP voltage PILOT_6V indicates EV ready (State C)
**Requirement:** `REQ-OCPP-043`

- **Given** CP voltage is PILOT_6V
- **When** ocpp_is_ev_ready is called
- **Then** Returns true because PILOT_6V is within EV-ready range

### CP voltage PILOT_9V indicates EV connected but not ready (State B)
**Requirement:** `REQ-OCPP-044`

- **Given** CP voltage is PILOT_9V
- **When** ocpp_is_ev_ready is called
- **Then** Returns false because State B means connected but not requesting charge

### CP voltage PILOT_12V indicates no EV (State A)
**Requirement:** `REQ-OCPP-044`

- **Given** CP voltage is PILOT_12V
- **When** ocpp_is_ev_ready is called
- **Then** Returns false because no vehicle is connected

### CP voltage PILOT_NOK indicates EV not ready
**Requirement:** `REQ-OCPP-044`

- **Given** CP voltage is PILOT_NOK (fault)
- **When** ocpp_is_ev_ready is called
- **Then** Returns false

### LockingTx present → occupied (pre-existing condition)
**Requirement:** `REQ-OCPP-120`

- **Given** locking_tx_present=true, no recent StopTx
- **When** ocpp_should_report_occupied is called
- **Then** Returns true

### StopTx within grace window → occupied (Finishing)
**Requirement:** `REQ-OCPP-121`

- **Given** No locking tx, StopTx fired 500 ms ago (< 2000 ms grace)
- **When** ocpp_should_report_occupied is called
- **Then** Returns true so CSMS sees Finishing before Available

### StopTx exactly at grace boundary → NOT occupied (< is strict)
**Requirement:** `REQ-OCPP-121`

- **Given** No locking tx, StopTx fired exactly OCPP_FINISHING_GRACE_MS ago
- **When** ocpp_should_report_occupied is called
- **Then** Returns false — grace window has elapsed

### StopTx past grace window → NOT occupied (Available)
**Requirement:** `REQ-OCPP-122`

- **Given** No locking tx, StopTx fired 3 seconds ago
- **When** ocpp_should_report_occupied is called
- **Then** Returns false — grace expired, transition to Available

### Non-StopTx notification within grace → NOT occupied
**Requirement:** `REQ-OCPP-122`

- **Given** tx_notif_defined=true but tx_notif_is_stoptx=false (e.g. StartTx)
- **When** ocpp_should_report_occupied is called
- **Then** Returns false — only StopTx triggers Finishing

### Uninitialized notification state → NOT occupied
**Requirement:** `REQ-OCPP-122`

- **Given** tx_notif_defined=false (no notification has ever fired)
- **When** ocpp_should_report_occupied is called
- **Then** Returns false — no spurious Finishing on fresh boot

</details>

---

## OCPP Connector Lock

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-110` | Active authorized transaction with car plugged → lock | `test_lock_active_tx_plugged` | `test_ocpp_connector.c:162` |
| `REQ-OCPP-110` | Lock condition holds at PILOT_3V boundary (charging) | `test_lock_active_tx_at_3v_boundary` | `test_ocpp_connector.c:180` |
| `REQ-OCPP-110` | Lock condition holds at PILOT_9V boundary (plugged, not charging yet) | `test_lock_active_tx_at_9v_boundary` | `test_ocpp_connector.c:193` |
| `REQ-OCPP-111` | No lock when no transaction present | `test_lock_no_tx_no_lock` | `test_ocpp_connector.c:206` |
| `REQ-OCPP-111` | No lock when transaction is not authorized | `test_lock_unauthorized_tx_no_lock` | `test_ocpp_connector.c:219` |
| `REQ-OCPP-111` | No lock when transaction neither active nor running | `test_lock_inactive_tx_no_lock` | `test_ocpp_connector.c:232` |
| `REQ-OCPP-111` | No lock when connector unplugged (PILOT_12V) | `test_lock_active_tx_unplugged_no_lock` | `test_ocpp_connector.c:245` |
| `REQ-OCPP-111` | No lock when connector reads PILOT_NOK (fault) and no LockingTx | `test_lock_pilot_nok_no_lock` | `test_ocpp_connector.c:258` |
| `REQ-OCPP-112` | LockingTx with start requested keeps connector locked | `test_lock_locking_tx_start_requested` | `test_ocpp_connector.c:272` |
| `REQ-OCPP-112` | LockingTx without start request does not force lock | `test_lock_locking_tx_no_start_request` | `test_ocpp_connector.c:285` |
| `REQ-OCPP-113` | All-false baseline returns false | `test_lock_all_false_baseline` | `test_ocpp_connector.c:298` |

<details>
<summary>Detailed steps (11 scenarios)</summary>

### Active authorized transaction with car plugged → lock
**Requirement:** `REQ-OCPP-110`

- **Given** tx is present, authorized, active; CP voltage is PILOT_6V (plugged)
- **When** ocpp_should_force_lock is called
- **Then** Returns true — connector must be locked during charging

### Lock condition holds at PILOT_3V boundary (charging)
**Requirement:** `REQ-OCPP-110`

- **Given** Active authorized tx, CP voltage is PILOT_3V (lower bound)
- **When** ocpp_should_force_lock is called
- **Then** Returns true

### Lock condition holds at PILOT_9V boundary (plugged, not charging yet)
**Requirement:** `REQ-OCPP-110`

- **Given** Active authorized tx, CP voltage is PILOT_9V (upper bound)
- **When** ocpp_should_force_lock is called
- **Then** Returns true

### No lock when no transaction present
**Requirement:** `REQ-OCPP-111`

- **Given** tx_present false, but CP voltage and other inputs say "active"
- **When** ocpp_should_force_lock is called
- **Then** Returns false — no transaction means no lock

### No lock when transaction is not authorized
**Requirement:** `REQ-OCPP-111`

- **Given** tx present but unauthorized, plugged
- **When** ocpp_should_force_lock is called
- **Then** Returns false

### No lock when transaction neither active nor running
**Requirement:** `REQ-OCPP-111`

- **Given** tx authorized but isActive==false && isRunning==false
- **When** ocpp_should_force_lock is called
- **Then** Returns false

### No lock when connector unplugged (PILOT_12V)
**Requirement:** `REQ-OCPP-111`

- **Given** Active authorized tx but CP says no vehicle
- **When** ocpp_should_force_lock is called
- **Then** Returns false

### No lock when connector reads PILOT_NOK (fault) and no LockingTx
**Requirement:** `REQ-OCPP-111`

- **Given** Authorized active tx, CP voltage PILOT_NOK
- **When** ocpp_should_force_lock is called
- **Then** Returns false — pilot fault means cable state is unknown,

### LockingTx with start requested keeps connector locked
**Requirement:** `REQ-OCPP-112`

- **Given** No regular tx active, LockingTx present and StartSync requested
- **When** ocpp_should_force_lock is called
- **Then** Returns true — RFID-locked connector waits for matching swipe

### LockingTx without start request does not force lock
**Requirement:** `REQ-OCPP-112`

- **Given** LockingTx present but its StartSync has not been requested
- **When** ocpp_should_force_lock is called
- **Then** Returns false

### All-false baseline returns false
**Requirement:** `REQ-OCPP-113`

- **Given** Every input false / PILOT_NOK
- **When** ocpp_should_force_lock is called
- **Then** Returns false — no condition triggers

</details>

---

## OCPP IEC 61851 Status Mapping

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-090` | State A without active transaction maps to Available | `test_iec_a_no_tx_available` | `test_ocpp_iec61851.c:1` |
| `REQ-OCPP-090` | State A with active transaction maps to Finishing | `test_iec_a_tx_active_finishing` | `test_ocpp_iec61851.c:28` |
| `REQ-OCPP-091` | State B without transaction maps to Preparing | `test_iec_b_no_tx_preparing` | `test_ocpp_iec61851.c:43` |
| `REQ-OCPP-091` | State B with active transaction maps to SuspendedEV | `test_iec_b_tx_active_suspended_ev` | `test_ocpp_iec61851.c:56` |
| `REQ-OCPP-092` | State C with EVSE offering current maps to Charging | `test_iec_c_evse_ready_charging` | `test_ocpp_iec61851.c:71` |
| `REQ-OCPP-092` | State C with EVSE not offering current maps to SuspendedEVSE | `test_iec_c_evse_not_ready_suspended_evse` | `test_ocpp_iec61851.c:84` |
| `REQ-OCPP-093` | State D with EVSE ready maps to Charging | `test_iec_d_evse_ready_charging` | `test_ocpp_iec61851.c:99` |
| `REQ-OCPP-093` | State D with EVSE not ready maps to SuspendedEVSE | `test_iec_d_evse_not_ready_suspended_evse` | `test_ocpp_iec61851.c:112` |
| `REQ-OCPP-094` | State E maps to Faulted | `test_iec_e_faulted` | `test_ocpp_iec61851.c:127` |
| `REQ-OCPP-094` | State F maps to Faulted | `test_iec_f_faulted` | `test_ocpp_iec61851.c:140` |
| `REQ-OCPP-094` | Unknown state maps to Faulted | `test_iec_unknown_faulted` | `test_ocpp_iec61851.c:153` |

<details>
<summary>Detailed steps (11 scenarios)</summary>

### State A without active transaction maps to Available
**Requirement:** `REQ-OCPP-090`

- **Given** IEC 61851 state is A (no vehicle), no transaction active
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Available"

### State A with active transaction maps to Finishing
**Requirement:** `REQ-OCPP-090`

- **Given** IEC 61851 state is A (no vehicle), transaction still active (just unplugged)
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Finishing" because the transaction is ending

### State B without transaction maps to Preparing
**Requirement:** `REQ-OCPP-091`

- **Given** IEC 61851 state is B (vehicle connected), no transaction
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Preparing" because the vehicle is waiting for authorization

### State B with active transaction maps to SuspendedEV
**Requirement:** `REQ-OCPP-091`

- **Given** IEC 61851 state is B (connected but not drawing), transaction active
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "SuspendedEV" because the EV has paused charging

### State C with EVSE offering current maps to Charging
**Requirement:** `REQ-OCPP-092`

- **Given** IEC 61851 state is C (charging), EVSE ready (PWM > 0)
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Charging"

### State C with EVSE not offering current maps to SuspendedEVSE
**Requirement:** `REQ-OCPP-092`

- **Given** IEC 61851 state is C, EVSE not ready (current = 0, e.g. OCPP limit)
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "SuspendedEVSE" because the EVSE has paused charging

### State D with EVSE ready maps to Charging
**Requirement:** `REQ-OCPP-093`

- **Given** IEC 61851 state is D (charging with ventilation), EVSE ready
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Charging" (same as State C for OCPP)

### State D with EVSE not ready maps to SuspendedEVSE
**Requirement:** `REQ-OCPP-093`

- **Given** IEC 61851 state is D, EVSE not ready
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "SuspendedEVSE"

### State E maps to Faulted
**Requirement:** `REQ-OCPP-094`

- **Given** IEC 61851 state is E (error)
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Faulted"

### State F maps to Faulted
**Requirement:** `REQ-OCPP-094`

- **Given** IEC 61851 state is F (not available)
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Faulted"

### Unknown state maps to Faulted
**Requirement:** `REQ-OCPP-094`

- **Given** IEC 61851 state is an invalid character
- **When** ocpp_iec61851_to_status is called
- **Then** Returns "Faulted" as a safe default

</details>

---

## OCPP Load Balancing Exclusivity

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-030` | OCPP+LoadBl=0 has no conflict, Smart Charging active | `test_lb_standalone_no_conflict` | `test_ocpp_lb.c:1` |
| `REQ-OCPP-030` | OCPP disabled has no conflict regardless of LoadBl | `test_lb_ocpp_disabled_no_conflict` | `test_ocpp_lb.c:27` |
| `REQ-OCPP-031` | OCPP+LoadBl=1 is a conflict, Smart Charging ineffective | `test_lb_master_conflict` | `test_ocpp_lb.c:42` |
| `REQ-OCPP-031` | OCPP+LoadBl=2 (node) is a conflict | `test_lb_node_conflict` | `test_ocpp_lb.c:55` |
| `REQ-OCPP-032` | LoadBl changes from 0 to 1 while OCPP active is a conflict | `test_lb_changed_0_to_1_conflict` | `test_ocpp_lb.c:68` |
| `REQ-OCPP-033` | LoadBl changes from 1 to 0 while OCPP active needs reinit | `test_lb_changed_1_to_0_needs_reinit` | `test_ocpp_lb.c:83` |
| `REQ-OCPP-032` | Runtime transition: standalone → master → back to standalone | `test_lb_transition_standalone_master_standalone` | `test_ocpp_lb.c:98` |
| `REQ-OCPP-033` | Runtime transition: master init → standalone change | `test_lb_transition_master_init_to_standalone` | `test_ocpp_lb.c:119` |
| `REQ-OCPP-034` | High LoadBl values (nodes 3-8) all trigger conflict | `test_lb_all_node_values_conflict` | `test_ocpp_lb.c:139` |

<details>
<summary>Detailed steps (9 scenarios)</summary>

### OCPP+LoadBl=0 has no conflict, Smart Charging active
**Requirement:** `REQ-OCPP-030`

- **Given** OCPP is enabled, LoadBl=0 (standalone), and OCPP was initialized in standalone mode
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_OK because Smart Charging and LoadBl are compatible

### OCPP disabled has no conflict regardless of LoadBl
**Requirement:** `REQ-OCPP-030`

- **Given** OCPP is disabled, LoadBl=1
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_OK because OCPP is not active

### OCPP+LoadBl=1 is a conflict, Smart Charging ineffective
**Requirement:** `REQ-OCPP-031`

- **Given** OCPP is enabled, LoadBl=1 (master), OCPP was initialized standalone
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_CONFLICT because the state machine ignores OCPP limits when LoadBl!=0

### OCPP+LoadBl=2 (node) is a conflict
**Requirement:** `REQ-OCPP-031`

- **Given** OCPP is enabled, LoadBl=2 (node), OCPP was initialized standalone
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_CONFLICT

### LoadBl changes from 0 to 1 while OCPP active is a conflict
**Requirement:** `REQ-OCPP-032`

- **Given** OCPP is enabled, LoadBl changed to 1 at runtime, was_standalone=true
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_CONFLICT because Smart Charging callback is still registered but limits are ignored

### LoadBl changes from 1 to 0 while OCPP active needs reinit
**Requirement:** `REQ-OCPP-033`

- **Given** OCPP is enabled, LoadBl=0 now, but was_standalone=false (was non-zero at init)
- **When** ocpp_check_lb_exclusivity is called
- **Then** Returns OCPP_LB_NEEDS_REINIT because Smart Charging callback was never registered

### Runtime transition: standalone → master → back to standalone
**Requirement:** `REQ-OCPP-032`

- **Given** OCPP was initialized in standalone mode (was_standalone=true)
- **When** LoadBl changes 0→1 (conflict) then 1→0 (back to standalone)
- **Then** First check returns CONFLICT, second returns OK (was_standalone still true from init)

### Runtime transition: master init → standalone change
**Requirement:** `REQ-OCPP-033`

- **Given** OCPP was initialized in master mode (was_standalone=false)
- **When** LoadBl changes from 1 to 0
- **Then** Returns NEEDS_REINIT because Smart Charging was never registered

### High LoadBl values (nodes 3-8) all trigger conflict
**Requirement:** `REQ-OCPP-034`

- **Given** OCPP is enabled and was initialized standalone
- **When** LoadBl is set to values 3 through 8
- **Then** All return OCPP_LB_CONFLICT

</details>

---

## OCPP Silence Detection

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-100` | No action while WebSocket is disconnected | `test_silence_no_action_when_disconnected` | `test_ocpp_resilience.c:1` |
| `REQ-OCPP-100` | Disconnected transport ignores stale response timestamp | `test_silence_disconnected_ignores_stale_response` | `test_ocpp_resilience.c:36` |
| `REQ-OCPP-101` | First probe fires when probe interval has elapsed since boot | `test_silence_first_probe_at_interval` | `test_ocpp_resilience.c:55` |
| `REQ-OCPP-101` | No probe fires before the interval elapses | `test_silence_no_probe_before_interval` | `test_ocpp_resilience.c:74` |
| `REQ-OCPP-101` | Probe interval boundary is inclusive | `test_silence_probe_at_boundary` | `test_ocpp_resilience.c:92` |
| `REQ-OCPP-102` | Force reconnect when backend has been silent past timeout | `test_silence_force_reconnect_after_timeout` | `test_ocpp_resilience.c:112` |
| `REQ-OCPP-102` | Reconnect priority — probe interval elapsed AND silence timeout exceeded | `test_silence_reconnect_priority_over_probe` | `test_ocpp_resilience.c:130` |
| `REQ-OCPP-103` | Cold-boot guard — last_response_ms == 0 must not force reconnect | `test_silence_zero_response_does_not_force_reconnect` | `test_ocpp_resilience.c:148` |
| `REQ-OCPP-103` | Cold-boot guard with no probe due either | `test_silence_zero_response_no_probe_due` | `test_ocpp_resilience.c:167` |
| `REQ-OCPP-104` | Healthy steady state — fresh response, recent probe | `test_silence_healthy_steady_state` | `test_ocpp_resilience.c:185` |

<details>
<summary>Detailed steps (10 scenarios)</summary>

### No action while WebSocket is disconnected
**Requirement:** `REQ-OCPP-100`

- **Given** ws_connected is false, all timers stale
- **When** ocpp_silence_decide is called
- **Then** Returns NO_ACTION because the WS layer handles reconnection itself

### Disconnected transport ignores stale response timestamp
**Requirement:** `REQ-OCPP-100`

- **Given** ws_connected is false, last_response is 10 minutes ago
- **When** ocpp_silence_decide is called
- **Then** Returns NO_ACTION — disconnected transport short-circuits everything

### First probe fires when probe interval has elapsed since boot
**Requirement:** `REQ-OCPP-101`

- **Given** ws_connected, last_response is 1 second ago, last_probe is 0
- **When** ocpp_silence_decide is called
- **Then** Returns SEND_PROBE because (now - last_probe) >= probe interval

### No probe fires before the interval elapses
**Requirement:** `REQ-OCPP-101`

- **Given** ws_connected, last_probe was 1 second ago, response fresh
- **When** ocpp_silence_decide is called
- **Then** Returns NO_ACTION — too soon to probe again

### Probe interval boundary is inclusive
**Requirement:** `REQ-OCPP-101`

- **Given** ws_connected, last_probe was exactly OCPP_PROBE_INTERVAL_MS ago
- **When** ocpp_silence_decide is called
- **Then** Returns SEND_PROBE — boundary value triggers a new probe

### Force reconnect when backend has been silent past timeout
**Requirement:** `REQ-OCPP-102`

- **Given** ws_connected, last_response is OCPP_SILENCE_TIMEOUT_MS+1 ago
- **When** ocpp_silence_decide is called
- **Then** Returns FORCE_RECONNECT (priority over probe)

### Reconnect priority — probe interval elapsed AND silence timeout exceeded
**Requirement:** `REQ-OCPP-102`

- **Given** ws_connected, both probe interval and silence timeout exceeded
- **When** ocpp_silence_decide is called
- **Then** Returns FORCE_RECONNECT, not SEND_PROBE — reconnect takes priority

### Cold-boot guard — last_response_ms == 0 must not force reconnect
**Requirement:** `REQ-OCPP-103`

- **Given** ws_connected, last_response is 0 (uninitialized), now is far in
- **When** ocpp_silence_decide is called
- **Then** Returns SEND_PROBE (probe is fine to send) but NEVER FORCE_RECONNECT,

### Cold-boot guard with no probe due either
**Requirement:** `REQ-OCPP-103`

- **Given** ws_connected, last_response is 0, last_probe is also recent
- **When** ocpp_silence_decide is called
- **Then** Returns NO_ACTION — no reconnect (zero-guard) and no probe (interval not elapsed)

### Healthy steady state — fresh response, recent probe
**Requirement:** `REQ-OCPP-104`

- **Given** ws_connected, response 1s ago, probe 30s ago (less than interval)
- **When** ocpp_silence_decide is called
- **Then** Returns NO_ACTION

</details>

---

## OCPP RFID Formatting

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-054` | New reader 7-byte UUID formatted as 14-char hex string | `test_rfid_new_reader_7byte` | `test_ocpp_rfid.c:1` |
| `REQ-OCPP-052` | UUID with leading zeros preserved in hex output | `test_rfid_leading_zeros_preserved` | `test_ocpp_rfid.c:30` |
| `REQ-OCPP-053` | Old reader format uses RFID[1..6] offset | `test_rfid_old_reader_6byte` | `test_ocpp_rfid.c:47` |
| `REQ-OCPP-053` | Old reader with leading zero bytes preserved | `test_rfid_old_reader_leading_zeros` | `test_ocpp_rfid.c:62` |
| `REQ-OCPP-050` | 4-byte UUID formatted as 8-char hex string | `test_rfid_4byte_new_reader` | `test_ocpp_rfid.c:79` |
| `REQ-OCPP-050` | NULL RFID input produces empty string | `test_rfid_null_input` | `test_ocpp_rfid.c:96` |
| `REQ-OCPP-050` | Zero-length RFID produces empty string | `test_rfid_zero_length` | `test_ocpp_rfid.c:111` |
| `REQ-OCPP-095` | 3-byte output buffer fits exactly one hex byte plus null | `test_rfid_format_small_buffer_boundary` | `test_ocpp_rfid.c:128` |
| `REQ-OCPP-095` | 2-byte output buffer cannot fit any hex byte (needs 3: 2 chars + null) | `test_rfid_format_2byte_buffer_empty` | `test_ocpp_rfid.c:143` |

<details>
<summary>Detailed steps (9 scenarios)</summary>

### New reader 7-byte UUID formatted as 14-char hex string
**Requirement:** `REQ-OCPP-054`

- **Given** RFID bytes {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67} (new reader)
- **When** ocpp_format_rfid_hex is called
- **Then** Output is "ABCDEF01234567" (7 bytes * 2 hex chars)

### UUID with leading zeros preserved in hex output
**Requirement:** `REQ-OCPP-052`

- **Given** RFID bytes {0x00, 0x00, 0x0A, 0x0B, 0x00, 0x00, 0x00} (new reader with leading zeros)
- **When** ocpp_format_rfid_hex is called
- **Then** Output is "0000 0A0B000000" with leading zeros preserved

### Old reader format uses RFID[1..6] offset
**Requirement:** `REQ-OCPP-053`

- **Given** RFID bytes {0x01, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF} (old reader flag at [0])
- **When** ocpp_format_rfid_hex is called
- **Then** Output is "AABBCCDDEEFF" (6 bytes from [1] to [6])

### Old reader with leading zero bytes preserved
**Requirement:** `REQ-OCPP-053`

- **Given** RFID bytes {0x01, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04} (old reader)
- **When** ocpp_format_rfid_hex is called
- **Then** Output is "000001020304" with leading zeros from [1] preserved

### 4-byte UUID formatted as 8-char hex string
**Requirement:** `REQ-OCPP-050`

- **Given** RFID bytes {0xDE, 0xAD, 0xBE, 0xEF} (4-byte UID, new reader)
- **When** ocpp_format_rfid_hex is called with rfid_len=4
- **Then** Output is "DEADBEEF" (4 bytes * 2 hex chars)

### NULL RFID input produces empty string
**Requirement:** `REQ-OCPP-050`

- **Given** RFID pointer is NULL
- **When** ocpp_format_rfid_hex is called
- **Then** Output is empty string

### Zero-length RFID produces empty string
**Requirement:** `REQ-OCPP-050`

- **Given** RFID bytes exist but length is 0
- **When** ocpp_format_rfid_hex is called
- **Then** Output is empty string

### 3-byte output buffer fits exactly one hex byte plus null
**Requirement:** `REQ-OCPP-095`

- **Given** RFID bytes {0xAB} and output buffer of size 3
- **When** ocpp_format_rfid_hex is called
- **Then** Output is "AB" (2 hex chars + null fits exactly in 3 bytes)

### 2-byte output buffer cannot fit any hex byte (needs 3: 2 chars + null)
**Requirement:** `REQ-OCPP-095`

- **Given** RFID bytes {0xAB} and output buffer of size 2
- **When** ocpp_format_rfid_hex is called
- **Then** Output is empty string because 2 hex chars + null requires 3 bytes

</details>

---

## OCPP Settings Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-060` | Valid wss:// URL accepted | `test_url_valid_wss` | `test_ocpp_settings.c:1` |
| `REQ-OCPP-061` | Valid ws:// URL accepted | `test_url_valid_ws` | `test_ocpp_settings.c:27` |
| `REQ-OCPP-062` | URL without ws/wss scheme rejected | `test_url_http_rejected` | `test_ocpp_settings.c:40` |
| `REQ-OCPP-062` | URL with https scheme rejected | `test_url_https_rejected` | `test_ocpp_settings.c:53` |
| `REQ-OCPP-063` | Empty URL rejected | `test_url_empty_rejected` | `test_ocpp_settings.c:66` |
| `REQ-OCPP-063` | NULL URL rejected | `test_url_null_rejected` | `test_ocpp_settings.c:79` |
| `REQ-OCPP-062` | Bare scheme without host rejected | `test_url_bare_scheme_rejected` | `test_ocpp_settings.c:92` |
| `REQ-OCPP-062` | Bare wss scheme without host rejected | `test_url_bare_wss_scheme_rejected` | `test_ocpp_settings.c:105` |
| `REQ-OCPP-062` | Plain text without scheme rejected | `test_url_no_scheme_rejected` | `test_ocpp_settings.c:118` |
| `REQ-OCPP-097` | URL with CRLF injection rejected | `test_url_crlf_rejected` | `test_ocpp_settings.c:131` |
| `REQ-OCPP-097` | URL with space rejected | `test_url_space_rejected` | `test_ocpp_settings.c:144` |
| `REQ-OCPP-097` | URL with valid special characters accepted | `test_url_valid_special_chars_accepted` | `test_ocpp_settings.c:157` |
| `REQ-OCPP-097` | URL with backslash rejected | `test_url_backslash_rejected` | `test_ocpp_settings.c:173` |
| `REQ-OCPP-097` | URL with curly braces rejected | `test_url_braces_rejected` | `test_ocpp_settings.c:186` |
| `REQ-OCPP-064` | Valid ChargeBoxId accepted | `test_cbid_valid` | `test_ocpp_settings.c:201` |
| `REQ-OCPP-064` | ChargeBoxId with special characters rejected | `test_cbid_special_chars_rejected` | `test_ocpp_settings.c:214` |
| `REQ-OCPP-065` | ChargeBoxId length > 20 rejected (OCPP 1.6 CiString20) | `test_cbid_too_long_rejected` | `test_ocpp_settings.c:227` |
| `REQ-OCPP-065` | ChargeBoxId exactly 20 characters is accepted | `test_cbid_exactly_20_accepted` | `test_ocpp_settings.c:240` |
| `REQ-OCPP-064` | Empty ChargeBoxId rejected | `test_cbid_empty_rejected` | `test_ocpp_settings.c:253` |
| `REQ-OCPP-064` | ChargeBoxId with ampersand rejected | `test_cbid_ampersand_rejected` | `test_ocpp_settings.c:266` |
| `REQ-OCPP-066` | Auth key length > 40 rejected (OCPP 1.6 limit) | `test_auth_key_too_long` | `test_ocpp_settings.c:281` |
| `REQ-OCPP-066` | Auth key exactly 40 characters is accepted | `test_auth_key_exactly_40_accepted` | `test_ocpp_settings.c:294` |
| `REQ-OCPP-066` | Empty auth key is valid (no auth configured) | `test_auth_key_empty_accepted` | `test_ocpp_settings.c:307` |
| `REQ-OCPP-H4-001` | Loopback IPv4 127.0.0.1 rejected | `test_url_loopback_127_0_0_1_rejected` | `test_ocpp_settings.c:322` |
| `REQ-OCPP-H4-001` | Any 127.x loopback rejected (covers 127.42.0.1 etc.) | `test_url_loopback_127_any_rejected` | `test_ocpp_settings.c:331` |
| `REQ-OCPP-H4-001` | localhost hostname rejected | `test_url_loopback_localhost_rejected` | `test_ocpp_settings.c:340` |
| `REQ-OCPP-H4-001` | LOCALHOST uppercase rejected (case-insensitive host check) | `test_url_loopback_localhost_uppercase_rejected` | `test_ocpp_settings.c:349` |
| `REQ-OCPP-H4-001` | 0.0.0.0 (bind-any / loopback alias) rejected | `test_url_loopback_0_0_0_0_rejected` | `test_ocpp_settings.c:358` |
| `REQ-OCPP-H4-001` | IPv6 loopback [::1] rejected | `test_url_loopback_ipv6_rejected` | `test_ocpp_settings.c:367` |
| `REQ-OCPP-H4-002` | IPv4 link-local 169.254.x rejected (AutoIP / APIPA) | `test_url_linklocal_ipv4_rejected` | `test_ocpp_settings.c:376` |
| `REQ-OCPP-H4-002` | IPv6 link-local fe80:: rejected | `test_url_linklocal_ipv6_rejected` | `test_ocpp_settings.c:385` |
| `REQ-OCPP-H4-003` | Embedded user:pass@host rejected | `test_url_embedded_creds_rejected` | `test_ocpp_settings.c:394` |
| `REQ-OCPP-H4-003` | Embedded @ in authority (even without colon) rejected | `test_url_embedded_at_rejected` | `test_ocpp_settings.c:403` |
| `REQ-OCPP-H4-004` | @ inside path component is allowed (authority is clean) | `test_url_at_in_path_allowed` | `test_ocpp_settings.c:412` |
| `REQ-OCPP-H4-005` | RFC1918 private ranges still allowed — many users self-host CSMS on LAN | `test_url_rfc1918_private_still_allowed` | `test_ocpp_settings.c:421` |
| `REQ-OCPP-H4-005` | Normal public hostnames still allowed (regression-proof) | `test_url_public_hostname_still_allowed` | `test_ocpp_settings.c:434` |

<details>
<summary>Detailed steps (36 scenarios)</summary>

### Valid wss:// URL accepted
**Requirement:** `REQ-OCPP-060`

- **Given** URL is "wss://ocpp.example.com/smartevse"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_OK

### Valid ws:// URL accepted
**Requirement:** `REQ-OCPP-061`

- **Given** URL is "ws://192.168.1.100:8180/steve/websocket/CentralSystemService"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_OK

### URL without ws/wss scheme rejected
**Requirement:** `REQ-OCPP-062`

- **Given** URL is "http://ocpp.example.com"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_SCHEME

### URL with https scheme rejected
**Requirement:** `REQ-OCPP-062`

- **Given** URL is "https://ocpp.example.com"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_SCHEME

### Empty URL rejected
**Requirement:** `REQ-OCPP-063`

- **Given** URL is empty string
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_EMPTY

### NULL URL rejected
**Requirement:** `REQ-OCPP-063`

- **Given** URL pointer is NULL
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_EMPTY

### Bare scheme without host rejected
**Requirement:** `REQ-OCPP-062`

- **Given** URL is "ws://" with no host
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_SCHEME because there is no content after scheme

### Bare wss scheme without host rejected
**Requirement:** `REQ-OCPP-062`

- **Given** URL is "wss://" with no host
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_SCHEME

### Plain text without scheme rejected
**Requirement:** `REQ-OCPP-062`

- **Given** URL is "ocpp.example.com" (no ws:// prefix)
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_SCHEME

### URL with CRLF injection rejected
**Requirement:** `REQ-OCPP-097`

- **Given** URL is "ws://example.com\r\nHost: evil"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS because CRLF is not allowed

### URL with space rejected
**Requirement:** `REQ-OCPP-097`

- **Given** URL is "ws://example.com/path with space"
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS because spaces are not allowed

### URL with valid special characters accepted
**Requirement:** `REQ-OCPP-097`

- **Given** URL contains all allowed special chars (path/query/fragment): . : / - _ ? = & @ % + #
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_OK

### URL with backslash rejected
**Requirement:** `REQ-OCPP-097`

- **Given** URL contains a backslash character
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS

### URL with curly braces rejected
**Requirement:** `REQ-OCPP-097`

- **Given** URL contains curly brace characters
- **When** ocpp_validate_backend_url is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS

### Valid ChargeBoxId accepted
**Requirement:** `REQ-OCPP-064`

- **Given** ChargeBoxId is "SmartEVSE-12345"
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_OK

### ChargeBoxId with special characters rejected
**Requirement:** `REQ-OCPP-064`

- **Given** ChargeBoxId contains '<' character
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS

### ChargeBoxId length > 20 rejected (OCPP 1.6 CiString20)
**Requirement:** `REQ-OCPP-065`

- **Given** ChargeBoxId is 21 characters long
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_TOO_LONG

### ChargeBoxId exactly 20 characters is accepted
**Requirement:** `REQ-OCPP-065`

- **Given** ChargeBoxId is exactly 20 characters long
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_OK

### Empty ChargeBoxId rejected
**Requirement:** `REQ-OCPP-064`

- **Given** ChargeBoxId is empty string
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_EMPTY

### ChargeBoxId with ampersand rejected
**Requirement:** `REQ-OCPP-064`

- **Given** ChargeBoxId contains '&' character
- **When** ocpp_validate_chargebox_id is called
- **Then** Returns OCPP_VALIDATE_BAD_CHARS

### Auth key length > 40 rejected (OCPP 1.6 limit)
**Requirement:** `REQ-OCPP-066`

- **Given** Auth key is 41 characters long
- **When** ocpp_validate_auth_key is called
- **Then** Returns OCPP_VALIDATE_TOO_LONG

### Auth key exactly 40 characters is accepted
**Requirement:** `REQ-OCPP-066`

- **Given** Auth key is exactly 40 characters long
- **When** ocpp_validate_auth_key is called
- **Then** Returns OCPP_VALIDATE_OK

### Empty auth key is valid (no auth configured)
**Requirement:** `REQ-OCPP-066`

- **Given** Auth key is empty string
- **When** ocpp_validate_auth_key is called
- **Then** Returns OCPP_VALIDATE_OK because empty means no auth

### Loopback IPv4 127.0.0.1 rejected
**Requirement:** `REQ-OCPP-H4-001`


### Any 127.x loopback rejected (covers 127.42.0.1 etc.)
**Requirement:** `REQ-OCPP-H4-001`


### localhost hostname rejected
**Requirement:** `REQ-OCPP-H4-001`


### LOCALHOST uppercase rejected (case-insensitive host check)
**Requirement:** `REQ-OCPP-H4-001`


### 0.0.0.0 (bind-any / loopback alias) rejected
**Requirement:** `REQ-OCPP-H4-001`


### IPv6 loopback [::1] rejected
**Requirement:** `REQ-OCPP-H4-001`


### IPv4 link-local 169.254.x rejected (AutoIP / APIPA)
**Requirement:** `REQ-OCPP-H4-002`


### IPv6 link-local fe80:: rejected
**Requirement:** `REQ-OCPP-H4-002`


### Embedded user:pass@host rejected
**Requirement:** `REQ-OCPP-H4-003`


### Embedded @ in authority (even without colon) rejected
**Requirement:** `REQ-OCPP-H4-003`


### @ inside path component is allowed (authority is clean)
**Requirement:** `REQ-OCPP-H4-004`


### RFC1918 private ranges still allowed — many users self-host CSMS on LAN
**Requirement:** `REQ-OCPP-H4-005`


### Normal public hostnames still allowed (regression-proof)
**Requirement:** `REQ-OCPP-H4-005`


</details>

---

## OCPP Telemetry

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-OCPP-080` | Telemetry init zeros all counters | `test_telemetry_init_zeros_all` | `test_ocpp_telemetry.c:1` |
| `REQ-OCPP-081` | Transaction start increments counter and sets active flag | `test_telemetry_tx_start` | `test_ocpp_telemetry.c:44` |
| `REQ-OCPP-081` | Transaction stop increments counter and clears active flag | `test_telemetry_tx_stop` | `test_ocpp_telemetry.c:59` |
| `REQ-OCPP-081` | Multiple transactions accumulate counters | `test_telemetry_multiple_tx` | `test_ocpp_telemetry.c:75` |
| `REQ-OCPP-082` | Auth accept/reject/timeout counters increment independently | `test_telemetry_auth_counters` | `test_ocpp_telemetry.c:96` |
| `REQ-OCPP-083` | WebSocket connect/disconnect counters track reconnections | `test_telemetry_ws_reconnect_tracking` | `test_ocpp_telemetry.c:117` |
| `REQ-OCPP-080` | NULL pointer does not crash | `test_telemetry_null_safety` | `test_ocpp_telemetry.c:137` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Telemetry init zeros all counters
**Requirement:** `REQ-OCPP-080`

- **Given** A telemetry struct with arbitrary values
- **When** ocpp_telemetry_init is called
- **Then** All counters and flags are zero/false

### Transaction start increments counter and sets active flag
**Requirement:** `REQ-OCPP-081`

- **Given** Telemetry is initialized
- **When** ocpp_telemetry_tx_started is called
- **Then** tx_start_count is 1 and tx_active is true

### Transaction stop increments counter and clears active flag
**Requirement:** `REQ-OCPP-081`

- **Given** A transaction has been started
- **When** ocpp_telemetry_tx_stopped is called
- **Then** tx_stop_count is 1 and tx_active is false

### Multiple transactions accumulate counters
**Requirement:** `REQ-OCPP-081`

- **Given** Telemetry is initialized
- **When** 3 transactions are started and stopped
- **Then** tx_start_count and tx_stop_count are both 3

### Auth accept/reject/timeout counters increment independently
**Requirement:** `REQ-OCPP-082`

- **Given** Telemetry is initialized
- **When** 2 accepts, 1 reject, 1 timeout are recorded
- **Then** Each counter reflects the correct count

### WebSocket connect/disconnect counters track reconnections
**Requirement:** `REQ-OCPP-083`

- **Given** Telemetry is initialized
- **When** 5 connects and 4 disconnects occur (currently connected)
- **Then** ws_connect_count=5, ws_disconnect_count=4

### NULL pointer does not crash
**Requirement:** `REQ-OCPP-080`

- **Given** NULL telemetry pointer
- **When** Any telemetry function is called
- **Then** No crash occurs

</details>

---

## Operating Modes

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MODE-001` | Normal mode sets IsetBalanced to MaxCurrent | `test_normal_mode_uses_max_current` | `test_operating_modes.c:1` |
| `REQ-MODE-002` | Normal mode ignores mains meter readings | `test_normal_mode_ignores_mains` | `test_operating_modes.c:45` |
| `REQ-MODE-003` | Normal mode respects MaxCapacity as upper bound | `test_normal_mode_respects_max_capacity` | `test_operating_modes.c:62` |
| `REQ-MODE-004` | Smart mode limits current based on MaxMains minus baseload | `test_smart_mode_respects_maxmains` | `test_operating_modes.c:81` |
| `REQ-MODE-005` | Smart mode increases current conservatively (Idifference/4) | `test_smart_mode_slow_increase` | `test_operating_modes.c:101` |
| `REQ-MODE-006` | Smart mode decreases current rapidly when over mains limit | `test_smart_mode_fast_decrease` | `test_operating_modes.c:123` |
| `REQ-MODE-007` | Solar mode requires surplus power to make current available | `test_solar_current_available_requires_surplus` | `test_operating_modes.c:146` |
| `REQ-MODE-008` | Solar mode allows charging when sufficient surplus is available | `test_solar_current_available_with_surplus` | `test_operating_modes.c:165` |
| `REQ-MODE-009` | Solar mode increases current in small steps when surplus is available | `test_solar_fine_grained_increase` | `test_operating_modes.c:185` |
| `REQ-MODE-010` | Solar mode decreases current rapidly when importing from grid | `test_solar_rapid_decrease_on_import` | `test_operating_modes.c:209` |
| `REQ-MODE-011` | Solar mode ImportCurrent offset allows controlled grid import | `test_solar_import_current_offset` | `test_operating_modes.c:233` |
| `REQ-MODE-012` | EnableC2=NOT_PRESENT does not force single phase | `test_force_single_phase_not_present` | `test_operating_modes.c:259` |
| `REQ-MODE-013` | EnableC2=ALWAYS_OFF forces single phase operation | `test_force_single_phase_always_off` | `test_operating_modes.c:273` |
| `REQ-MODE-014` | EnableC2=SOLAR_OFF forces single phase when in Solar mode | `test_force_single_phase_solar_off_in_solar_mode` | `test_operating_modes.c:287` |
| `REQ-MODE-015` | EnableC2=SOLAR_OFF does not force single phase in Smart mode | `test_force_single_phase_solar_off_in_smart_mode` | `test_operating_modes.c:302` |
| `REQ-MODE-016` | EnableC2=AUTO forces single phase when charging on 1 phase | `test_force_single_phase_auto_c2_1p` | `test_operating_modes.c:317` |
| `REQ-MODE-017` | EnableC2=AUTO does not force single phase when charging on 3 phases | `test_force_single_phase_auto_c2_3p` | `test_operating_modes.c:332` |
| `REQ-MODE-018` | EnableC2=ALWAYS_ON does not force single phase | `test_force_single_phase_always_on` | `test_operating_modes.c:347` |
| `REQ-MODE-019` | STATE_C entry with single phase disables contactor 2 | `test_state_C_contactor2_off_when_single_phase` | `test_operating_modes.c:361` |
| `REQ-MODE-020` | STATE_C entry with three phase enables both contactors | `test_state_C_contactor2_on_when_three_phase` | `test_operating_modes.c:378` |
| `REQ-MODE-021` | Phase switch from 3P to 1P completes on STATE_C entry | `test_phase_switch_going_to_1p` | `test_operating_modes.c:395` |

<details>
<summary>Detailed steps (21 scenarios)</summary>

### Normal mode sets IsetBalanced to MaxCurrent
**Requirement:** `REQ-MODE-001`

- **Given** EVSE is standalone in STATE_C in Normal mode
- **When** Balanced current is calculated
- **Then** IsetBalanced equals MaxCurrent * 10 (fixed current allocation)

### Normal mode ignores mains meter readings
**Requirement:** `REQ-MODE-002`

- **Given** EVSE is standalone in STATE_C in Normal mode with high MainsMeterImeasured=300
- **When** Balanced current is calculated
- **Then** IsetBalanced remains at MaxCurrent * 10 regardless of mains load

### Normal mode respects MaxCapacity as upper bound
**Requirement:** `REQ-MODE-003`

- **Given** EVSE is standalone in STATE_C in Normal mode with MaxCapacity=10A and MaxCurrent=16A
- **When** Balanced current is calculated
- **Then** ChargeCurrent is limited to 100 deciamps (MaxCapacity * 10) instead of MaxCurrent

### Smart mode limits current based on MaxMains minus baseload
**Requirement:** `REQ-MODE-004`

- **Given** EVSE is standalone in STATE_C in Smart mode with MaxMains=25A and MainsMeterImeasured=200
- **When** Balanced current is calculated
- **Then** IsetBalanced does not exceed (MaxMains * 10) minus baseload

### Smart mode increases current conservatively (Idifference/4)
**Requirement:** `REQ-MODE-005`

- **Given** EVSE is standalone in STATE_C in Smart mode with low mains usage and measurements updated
- **When** Balanced current is calculated with headroom available
- **Then** IsetBalanced increases from its initial value but conservatively (not full step)

### Smart mode decreases current rapidly when over mains limit
**Requirement:** `REQ-MODE-006`

- **Given** EVSE is standalone in STATE_C in Smart mode with IsetBalanced=200 and mains way over MaxMains=10A
- **When** Balanced current is calculated with negative Idifference
- **Then** IsetBalanced decreases rapidly (full Idifference, not divided) below the initial 200

### Solar mode requires surplus power to make current available
**Requirement:** `REQ-MODE-007`

- **Given** EVSE is in Solar mode with StartCurrent=6A and Isum=0 (no surplus)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because there is no solar surplus for charging

### Solar mode allows charging when sufficient surplus is available
**Requirement:** `REQ-MODE-008`

- **Given** EVSE is in Solar mode with StartCurrent=6A and Isum=-80 (8A export surplus)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because export surplus exceeds StartCurrent threshold

### Solar mode increases current in small steps when surplus is available
**Requirement:** `REQ-MODE-009`

- **Given** EVSE is standalone in STATE_C in Solar mode with 2A export surplus and past solar startup phase
- **When** Balanced current is calculated
- **Then** IsetBalanced increases from its initial 100 value in fine-grained solar increments

### Solar mode decreases current rapidly when importing from grid
**Requirement:** `REQ-MODE-010`

- **Given** EVSE is standalone in STATE_C in Solar mode with Isum=50 (5A import) and IsetBalanced=100
- **When** Balanced current is calculated with grid import detected
- **Then** IsetBalanced decreases below 100 to reduce grid import quickly

### Solar mode ImportCurrent offset allows controlled grid import
**Requirement:** `REQ-MODE-011`

- **Given** EVSE is in Solar mode with ImportCurrent=3A allowance and Isum=20 (2A import within allowance)
- **When** Balanced current is calculated with import within the allowed offset
- **Then** IsetBalanced increases because IsumImport (20 - 30 = -10) indicates effective surplus

### EnableC2=NOT_PRESENT does not force single phase
**Requirement:** `REQ-MODE-012`

- **Given** EVSE has EnableC2 set to NOT_PRESENT (contactor 2 not installed)
- **When** evse_force_single_phase is called
- **Then** Returns 0 because the phase switching hardware is not present

### EnableC2=ALWAYS_OFF forces single phase operation
**Requirement:** `REQ-MODE-013`

- **Given** EVSE has EnableC2 set to ALWAYS_OFF (contactor 2 always disabled)
- **When** evse_force_single_phase is called
- **Then** Returns 1 because the EVSE is configured to always operate in single phase

### EnableC2=SOLAR_OFF forces single phase when in Solar mode
**Requirement:** `REQ-MODE-014`

- **Given** EVSE has EnableC2 set to SOLAR_OFF and Mode is MODE_SOLAR
- **When** evse_force_single_phase is called
- **Then** Returns 1 because SOLAR_OFF disables contactor 2 in solar mode

### EnableC2=SOLAR_OFF does not force single phase in Smart mode
**Requirement:** `REQ-MODE-015`

- **Given** EVSE has EnableC2 set to SOLAR_OFF and Mode is MODE_SMART
- **When** evse_force_single_phase is called
- **Then** Returns 0 because SOLAR_OFF only applies in Solar mode, not Smart mode

### EnableC2=AUTO forces single phase when charging on 1 phase
**Requirement:** `REQ-MODE-016`

- **Given** EVSE has EnableC2 set to AUTO and Nr_Of_Phases_Charging=1
- **When** evse_force_single_phase is called
- **Then** Returns 1 because AUTO mode follows the current phase count

### EnableC2=AUTO does not force single phase when charging on 3 phases
**Requirement:** `REQ-MODE-017`

- **Given** EVSE has EnableC2 set to AUTO and Nr_Of_Phases_Charging=3
- **When** evse_force_single_phase is called
- **Then** Returns 0 because AUTO mode allows 3-phase operation when already on 3 phases

### EnableC2=ALWAYS_ON does not force single phase
**Requirement:** `REQ-MODE-018`

- **Given** EVSE has EnableC2 set to ALWAYS_ON (contactor 2 always enabled for 3-phase)
- **When** evse_force_single_phase is called
- **Then** Returns 0 because the EVSE is configured to always operate in three phase

### STATE_C entry with single phase disables contactor 2
**Requirement:** `REQ-MODE-019`

- **Given** EVSE has EnableC2 set to ALWAYS_OFF (force single phase)
- **When** EVSE transitions to STATE_C
- **Then** Contactor 1 is on, contactor 2 is off, and Nr_Of_Phases_Charging is 1

### STATE_C entry with three phase enables both contactors
**Requirement:** `REQ-MODE-020`

- **Given** EVSE has EnableC2 set to NOT_PRESENT (default 3-phase behavior)
- **When** EVSE transitions to STATE_C
- **Then** Both contactor 1 and contactor 2 are on and Nr_Of_Phases_Charging is 3

### Phase switch from 3P to 1P completes on STATE_C entry
**Requirement:** `REQ-MODE-021`

- **Given** EVSE has Switching_Phases_C2=GOING_TO_SWITCH_1P and EnableC2=AUTO
- **When** EVSE transitions to STATE_C
- **Then** Nr_Of_Phases_Charging is set to 1 and Switching_Phases_C2 is cleared to NO_SWITCH

</details>

---

## P1 Meter Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-MTR-070` | JSON number extractor finds integer value | `test_json_find_integer` | `test_p1_parse.c:1` |
| `REQ-MTR-071` | JSON number extractor finds negative decimal value | `test_json_find_negative_decimal` | `test_p1_parse.c:38` |
| `REQ-MTR-072` | JSON number extractor returns 0 for missing key | `test_json_find_missing_key` | `test_p1_parse.c:55` |
| `REQ-MTR-073` | JSON extractor handles key that is a prefix of another key | `test_json_find_partial_key_no_match` | `test_p1_parse.c:71` |
| `REQ-MTR-074` | JSON extractor handles whitespace around colon | `test_json_find_whitespace_around_colon` | `test_p1_parse.c:87` |
| `REQ-MTR-075` | JSON extractor NULL safety | `test_json_find_null_safety` | `test_p1_parse.c:104` |
| `REQ-MTR-076` | 3-phase P1 response with positive currents and positive power | `test_parse_3phase_positive` | `test_p1_parse.c:122` |
| `REQ-MTR-077` | 1-phase P1 response (only L1 present) | `test_parse_1phase` | `test_p1_parse.c:147` |
| `REQ-MTR-078` | Negative power causes negative current (solar feed-in) | `test_parse_feedin_negative_power` | `test_p1_parse.c:166` |
| `REQ-MTR-079` | Mixed phases: L1 consuming, L2 feeding in | `test_parse_mixed_direction` | `test_p1_parse.c:185` |
| `REQ-MTR-080` | Missing all current keys returns invalid | `test_parse_no_current_keys` | `test_p1_parse.c:207` |
| `REQ-MTR-081` | Missing power keys defaults to positive current | `test_parse_missing_power_defaults_positive` | `test_p1_parse.c:225` |
| `REQ-MTR-082` | NULL JSON returns invalid result | `test_parse_null_json` | `test_p1_parse.c:247` |
| `REQ-MTR-083` | Empty JSON string returns invalid result | `test_parse_empty_json` | `test_p1_parse.c:261` |
| `REQ-MTR-084` | Real-world Kaifa single-phase P1 response | `test_parse_real_world_kaifa` | `test_p1_parse.c:276` |
| `REQ-MTR-085` | Zero current and zero power | `test_parse_zero_values` | `test_p1_parse.c:306` |
| `REQ-MTR-086` | Power stores diagnostic values | `test_parse_power_diagnostics` | `test_p1_parse.c:331` |
| `REQ-PWR-030` | NaN current value is rejected by JSON extractor | `test_json_find_nan_rejected` | `test_p1_parse.c:354` |
| `REQ-PWR-031` | Infinity current value is rejected by JSON extractor | `test_json_find_infinity_rejected` | `test_p1_parse.c:370` |
| `REQ-PWR-032` | Negative infinity is rejected by JSON extractor | `test_json_find_neg_infinity_rejected` | `test_p1_parse.c:386` |
| `REQ-PWR-033` | Current value exceeding int16_t range marks result invalid | `test_parse_current_overflow_invalid` | `test_p1_parse.c:402` |
| `REQ-PWR-034` | NaN in full P1 response is rejected | `test_parse_nan_in_response_rejected` | `test_p1_parse.c:418` |

<details>
<summary>Detailed steps (22 scenarios)</summary>

### JSON number extractor finds integer value
**Requirement:** `REQ-MTR-070`

- **Given** JSON string containing "active_current_l1_a":12
- **When** p1_json_find_number is called with key "active_current_l1_a"
- **Then** Returns 1 and value is 12.0

### JSON number extractor finds negative decimal value
**Requirement:** `REQ-MTR-071`

- **Given** JSON string containing "active_power_l1_w":-2725.5
- **When** p1_json_find_number is called with key "active_power_l1_w"
- **Then** Returns 1 and value is approximately -2725.5

### JSON number extractor returns 0 for missing key
**Requirement:** `REQ-MTR-072`

- **Given** JSON string without the requested key
- **When** p1_json_find_number is called with key "nonexistent_key"
- **Then** Returns 0

### JSON extractor handles key that is a prefix of another key
**Requirement:** `REQ-MTR-073`

- **Given** JSON with "active_current_l1_a" and search for "active_current_l1"
- **When** p1_json_find_number is called
- **Then** Returns 0 because the key must match exactly (followed by closing quote)

### JSON extractor handles whitespace around colon
**Requirement:** `REQ-MTR-074`

- **Given** JSON with spaces around the colon: "key" : 42
- **When** p1_json_find_number is called
- **Then** Returns 1 and value is 42

### JSON extractor NULL safety
**Requirement:** `REQ-MTR-075`

- **Given** NULL json, key, or out pointers
- **When** p1_json_find_number is called
- **Then** Returns 0 without crashing

### 3-phase P1 response with positive currents and positive power
**Requirement:** `REQ-MTR-076`

- **Given** JSON with L1=10.5A/2400W, L2=8.3A/1900W, L3=12.1A/2800W
- **When** p1_parse_response is called
- **Then** phases=3, currents=[105, 83, 121] deci-amps (all positive)

### 1-phase P1 response (only L1 present)
**Requirement:** `REQ-MTR-077`

- **Given** JSON with only L1 current and power fields
- **When** p1_parse_response is called
- **Then** phases=1, current_da[0]=114 (11.43A * 10, rounded)

### Negative power causes negative current (solar feed-in)
**Requirement:** `REQ-MTR-078`

- **Given** JSON with L1=-11.43A current and -2725W power (feeding in)
- **When** p1_parse_response is called
- **Then** current_da[0] = -114 (negative because power is negative)

### Mixed phases: L1 consuming, L2 feeding in
**Requirement:** `REQ-MTR-079`

- **Given** JSON with L1=5A/1150W (consuming) and L2=3A/-690W (feeding in)
- **When** p1_parse_response is called
- **Then** current_da[0]=50, current_da[1]=-30

### Missing all current keys returns invalid
**Requirement:** `REQ-MTR-080`

- **Given** JSON with only power fields, no current fields
- **When** p1_parse_response is called
- **Then** valid=0, phases=0

### Missing power keys defaults to positive current
**Requirement:** `REQ-MTR-081`

- **Given** JSON with current fields but no power fields
- **When** p1_parse_response is called
- **Then** currents are positive (power defaults to 0, which is >= 0)

### NULL JSON returns invalid result
**Requirement:** `REQ-MTR-082`

- **Given** NULL json pointer
- **When** p1_parse_response is called
- **Then** valid=0, phases=0

### Empty JSON string returns invalid result
**Requirement:** `REQ-MTR-083`

- **Given** Empty JSON string "{}"
- **When** p1_parse_response is called
- **Then** valid=0, phases=0

### Real-world Kaifa single-phase P1 response
**Requirement:** `REQ-MTR-084`

- **Given** Actual P1 meter JSON response from a Kaifa meter with solar feed-in
- **When** p1_parse_response is called
- **Then** Correctly extracts L1 current as -114 dA (11.43A feed-in)

### Zero current and zero power
**Requirement:** `REQ-MTR-085`

- **Given** JSON with all currents and powers at 0
- **When** p1_parse_response is called
- **Then** All current_da values are 0

### Power stores diagnostic values
**Requirement:** `REQ-MTR-086`

- **Given** JSON with L1=8.5A/1955W, L2=6.2A/1426W
- **When** p1_parse_response is called
- **Then** power_w contains [1955, 1426, 0] for diagnostics

### NaN current value is rejected by JSON extractor
**Requirement:** `REQ-PWR-030`

- **Given** JSON string containing "active_current_l1_a":"NaN"
- **When** p1_json_find_number is called
- **Then** Returns 0 (parse failure) because NaN is not a valid number

### Infinity current value is rejected by JSON extractor
**Requirement:** `REQ-PWR-031`

- **Given** JSON string containing "active_current_l1_a":Infinity
- **When** p1_json_find_number is called
- **Then** Returns 0 (parse failure) because Infinity is not a valid meter reading

### Negative infinity is rejected by JSON extractor
**Requirement:** `REQ-PWR-032`

- **Given** JSON string containing "active_current_l1_a":-Infinity
- **When** p1_json_find_number is called
- **Then** Returns 0 (parse failure)

### Current value exceeding int16_t range marks result invalid
**Requirement:** `REQ-PWR-033`

- **Given** JSON with current 4000.0A (40000 dA exceeds INT16_MAX=32767)
- **When** p1_parse_response is called
- **Then** Result is invalid because deci-amp value overflows int16_t

### NaN in full P1 response is rejected
**Requirement:** `REQ-PWR-034`

- **Given** JSON with NaN value for active_current_l1_a
- **When** p1_parse_response is called
- **Then** Result is invalid because NaN cannot be parsed as a number

</details>

---

## Phase Switching

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-PHASE-003` | AUTO + SOLAR: no switch needed when already at correct phase count | `test_check_auto_solar_forces_1p` | `test_phase_switching.c:1` |
| `REQ-PHASE-004` | AUTO + SOLAR already on 1 phase results in NO_SWITCH | `test_check_auto_solar_already_1p` | `test_phase_switching.c:52` |
| `REQ-PHASE-005` | AUTO + SMART forces 3-phase when currently on 1 phase | `test_check_auto_smart_forces_3p` | `test_phase_switching.c:73` |
| `REQ-PHASE-006` | AUTO + SMART already on 3 phases results in NO_SWITCH | `test_check_auto_smart_already_3p` | `test_phase_switching.c:94` |
| `REQ-PHASE-007` | ALWAYS_OFF in STATE_A sets Nr_Of_Phases_Charging directly to 1 | `test_check_always_off_in_state_a` | `test_phase_switching.c:115` |
| `REQ-PHASE-008` | ALWAYS_OFF in STATE_B sets deferred switching flag to 1P | `test_check_always_off_in_state_b` | `test_phase_switching.c:136` |
| `REQ-PHASE-009` | SOLAR_OFF + SMART forces 3-phase charging | `test_check_solar_off_smart_3p` | `test_phase_switching.c:156` |
| `REQ-PHASE-010` | SOLAR_OFF + SOLAR forces 1-phase charging | `test_check_solar_off_solar_1p` | `test_phase_switching.c:178` |
| `REQ-PHASE-011` | STATE_C entry applies deferred 1P switch and opens contactor 2 | `test_state_c_applies_1p_switch` | `test_phase_switching.c:199` |
| `REQ-PHASE-012` | STATE_C entry applies deferred 3P switch and closes contactor 2 | `test_state_c_applies_3p_switch` | `test_phase_switching.c:220` |
| `REQ-PHASE-013` | STATE_C entry resets Switching_Phases_C2 to NO_SWITCH | `test_state_c_resets_switching` | `test_phase_switching.c:241` |
| `REQ-PHASE-014` | Full 3P to 1P to 3P phase switching cycle in solar mode | `test_full_3p_1p_3p_cycle` | `test_phase_switching.c:259` |
| `REQ-PH-015` | Severe solar shortage uses short PhaseSwitchTimer | `test_severe_shortage_uses_short_timer` | `test_phase_switching.c:357` |
| `REQ-PH-016` | Mild solar shortage uses long PhaseSwitchTimer (StopTime-based) | `test_mild_shortage_uses_long_timer` | `test_phase_switching.c:379` |
| `REQ-PH-017` | PhaseSwitchTimer reaching <=2 triggers 3P to 1P switch | `test_phase_switch_timer_triggers_1p` | `test_phase_switching.c:399` |
| `REQ-PH-018` | Switching from 3P to 1P starts the hold-down counter | `test_3p_to_1p_starts_holddown` | `test_phase_switching.c:418` |
| `REQ-PH-019` | Hold-down counter prevents premature 1P to 3P upgrade | `test_holddown_prevents_3p_upgrade` | `test_phase_switching.c:439` |
| `REQ-PH-020` | Hold-down expired allows 1P to 3P upgrade to proceed | `test_holddown_expired_allows_upgrade` | `test_phase_switching.c:464` |
| `REQ-PH-021` | PhaseSwitchTimer is independent of SolarStopTimer | `test_phase_timer_independent_of_solar_stop` | `test_phase_switching.c:488` |
| `REQ-PH-022` | PhaseSwitchTimer counts down each second in tick_1s | `test_phase_timer_countdown_in_tick_1s` | `test_phase_switching.c:509` |
| `REQ-PH-023` | Phase switching timer fields initialized correctly by evse_init | `test_phase_timer_defaults` | `test_phase_switching.c:529` |
| `REQ-PH-024` | Phase switch completion resets IntTimer for startup protection | `test_phase_switch_resets_inttimer` | `test_phase_switching.c:550` |
| `REQ-PH-025` | 3P upgrade also resets IntTimer | `test_3p_upgrade_resets_inttimer` | `test_phase_switching.c:571` |
| `REQ-PH-026` | Normal STATE_C entry (no phase switch) does not reset IntTimer | `test_no_switch_preserves_inttimer` | `test_phase_switching.c:592` |
| `REQ-PH-027` | SolarStopTimer suppressed during startup period after phase switch | `test_solar_stop_suppressed_during_startup` | `test_phase_switching.c:612` |
| `REQ-PH-028` | SolarStopTimer allowed after startup period | `test_solar_stop_allowed_after_startup` | `test_phase_switching.c:632` |

<details>
<summary>Detailed steps (26 scenarios)</summary>

### AUTO + SOLAR: no switch needed when already at correct phase count
**Requirement:** `REQ-PHASE-003`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, MODE_SOLAR, and various phase counts
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is NO_SWITCH when already at the correct phase count

### AUTO + SOLAR already on 1 phase results in NO_SWITCH
**Requirement:** `REQ-PHASE-004`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, MODE_SOLAR, and 1 phase
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is NO_SWITCH (already single phase)

### AUTO + SMART forces 3-phase when currently on 1 phase
**Requirement:** `REQ-PHASE-005`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, MODE_SMART, and 1 phase
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_3P

### AUTO + SMART already on 3 phases results in NO_SWITCH
**Requirement:** `REQ-PHASE-006`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, MODE_SMART, and 3 phases
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is NO_SWITCH (already three phase)

### ALWAYS_OFF in STATE_A sets Nr_Of_Phases_Charging directly to 1
**Requirement:** `REQ-PHASE-007`

- **Given** The EVSE is in STATE_A with EnableC2=ALWAYS_OFF and 3 phases configured
- **When** evse_check_switching_phases is called
- **Then** Nr_Of_Phases_Charging is set directly to 1 (no deferred switch needed)

### ALWAYS_OFF in STATE_B sets deferred switching flag to 1P
**Requirement:** `REQ-PHASE-008`

- **Given** The EVSE is in STATE_B with EnableC2=ALWAYS_OFF and 3 phases configured
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P (deferred until STATE_C entry)

### SOLAR_OFF + SMART forces 3-phase charging
**Requirement:** `REQ-PHASE-009`

- **Given** The EVSE is in STATE_B with EnableC2=SOLAR_OFF, MODE_SMART, and 1 phase
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_3P

### SOLAR_OFF + SOLAR forces 1-phase charging
**Requirement:** `REQ-PHASE-010`

- **Given** The EVSE is in STATE_B with EnableC2=SOLAR_OFF, MODE_SOLAR, and 3 phases
- **When** evse_check_switching_phases is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P

### STATE_C entry applies deferred 1P switch and opens contactor 2
**Requirement:** `REQ-PHASE-011`

- **Given** Switching_Phases_C2 is GOING_TO_SWITCH_1P with EnableC2=ALWAYS_OFF
- **When** The state is set to STATE_C
- **Then** Nr_Of_Phases_Charging is 1 and contactor2 is off (open)

### STATE_C entry applies deferred 3P switch and closes contactor 2
**Requirement:** `REQ-PHASE-012`

- **Given** Switching_Phases_C2 is GOING_TO_SWITCH_3P with EnableC2=ALWAYS_ON
- **When** The state is set to STATE_C
- **Then** Nr_Of_Phases_Charging is 3 and contactor2 is on (closed)

### STATE_C entry resets Switching_Phases_C2 to NO_SWITCH
**Requirement:** `REQ-PHASE-013`

- **Given** Switching_Phases_C2 is GOING_TO_SWITCH_1P
- **When** The state is set to STATE_C
- **Then** Switching_Phases_C2 is reset to NO_SWITCH

### Full 3P to 1P to 3P phase switching cycle in solar mode
**Requirement:** `REQ-PHASE-014`

- **Given** The EVSE is solar charging on 3 phases with EnableC2=AUTO
- **When** Solar shortage triggers 3P->1P switch, then surplus triggers 1P->3P switch
- **Then** The EVSE correctly switches from 3P to 1P and back to 3P with proper contactor and flag states

### Severe solar shortage uses short PhaseSwitchTimer
**Requirement:** `REQ-PH-015`

- **Given** The EVSE is solar charging on 3P with severe shortage (IsumImport >= MinCurrent*10)
- **When** evse_calc_balanced_current is called
- **Then** PhaseSwitchTimer is set to PhaseSwitchSevereTime (30s default)

### Mild solar shortage uses long PhaseSwitchTimer (StopTime-based)
**Requirement:** `REQ-PH-016`

- **Given** The EVSE is solar charging on 3P with mild shortage (0 < IsumImport < MinCurrent*10)
- **When** evse_calc_balanced_current is called
- **Then** PhaseSwitchTimer is set to StopTime*60 (600s default)

### PhaseSwitchTimer reaching <=2 triggers 3P to 1P switch
**Requirement:** `REQ-PH-017`

- **Given** The EVSE is solar charging on 3P with PhaseSwitchTimer=2 and ongoing shortage
- **When** evse_calc_balanced_current is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P

### Switching from 3P to 1P starts the hold-down counter
**Requirement:** `REQ-PH-018`

- **Given** The EVSE is solar charging on 3P with PhaseSwitchTimer about to trigger
- **When** The 3P→1P switch is triggered (PhaseSwitchTimer<=2)
- **Then** PhaseSwitchHoldDown is set to PhaseSwitchHoldDownTime

### Hold-down counter prevents premature 1P to 3P upgrade
**Requirement:** `REQ-PH-019`

- **Given** The EVSE is solar charging on 1P with sufficient surplus but PhaseSwitchHoldDown > 0
- **When** evse_calc_balanced_current is called
- **Then** PhaseSwitchTimer stays 0 and Switching_Phases_C2 stays NO_SWITCH (upgrade blocked)

### Hold-down expired allows 1P to 3P upgrade to proceed
**Requirement:** `REQ-PH-020`

- **Given** The EVSE is solar charging on 1P with sufficient surplus and PhaseSwitchHoldDown=0
- **When** evse_calc_balanced_current is called
- **Then** PhaseSwitchTimer starts countdown for 3P upgrade

### PhaseSwitchTimer is independent of SolarStopTimer
**Requirement:** `REQ-PH-021`

- **Given** PhaseSwitchTimer and SolarStopTimer are at different values
- **When** evse_calc_balanced_current triggers a phase switch timer
- **Then** Only PhaseSwitchTimer changes, SolarStopTimer is unaffected

### PhaseSwitchTimer counts down each second in tick_1s
**Requirement:** `REQ-PH-022`

- **Given** PhaseSwitchTimer=10 and PhaseSwitchHoldDown=5
- **When** evse_tick_1s is called
- **Then** PhaseSwitchTimer decrements to 9 and PhaseSwitchHoldDown decrements to 4

### Phase switching timer fields initialized correctly by evse_init
**Requirement:** `REQ-PH-023`

- **Given** A freshly initialized EVSE context
- **When** evse_init is called
- **Then** PhaseSwitchHoldDownTime and PhaseSwitchSevereTime have correct defaults

### Phase switch completion resets IntTimer for startup protection
**Requirement:** `REQ-PH-024`

- **Given** The EVSE was charging on 3P with IntTimer=500 and switches to 1P
- **When** STATE_C is entered with Switching_Phases_C2 = GOING_TO_SWITCH_1P
- **Then** Node[0].IntTimer is reset to 0 (new startup period begins)

### 3P upgrade also resets IntTimer
**Requirement:** `REQ-PH-025`

- **Given** The EVSE was charging on 1P with IntTimer=300 and switches to 3P
- **When** STATE_C is entered with Switching_Phases_C2 = GOING_TO_SWITCH_3P
- **Then** Node[0].IntTimer is reset to 0

### Normal STATE_C entry (no phase switch) does not reset IntTimer
**Requirement:** `REQ-PH-026`

- **Given** The EVSE enters STATE_C without a phase switch (Switching_Phases_C2 = NO_SWITCH)
- **When** evse_set_state is called with STATE_C
- **Then** Node[0].IntTimer is NOT reset (keeps previous value)

### SolarStopTimer suppressed during startup period after phase switch
**Requirement:** `REQ-PH-027`

- **Given** The EVSE just completed a phase switch (IntTimer=5, < SOLARSTARTTIME)
- **When** evse_calc_balanced_current detects a shortage in solar mode
- **Then** SolarStopTimer is NOT started (suppressed during startup settling)

### SolarStopTimer allowed after startup period
**Requirement:** `REQ-PH-028`

- **Given** The EVSE is past startup (IntTimer > SOLARSTARTTIME) with shortage
- **When** evse_calc_balanced_current detects a shortage in solar mode
- **Then** SolarStopTimer IS started (startup protection expired)

</details>

---

## PIN Rate Limit

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-AUTH-020` | Clean state allows the first request | `test_pin_rl_clean_state_allows` | `test_pin_rate_limit.c:1` |
| `REQ-AUTH-020` | First two failures do not trigger cooldown | `test_pin_rl_first_two_failures_free` | `test_pin_rate_limit.c:25` |
| `REQ-AUTH-021` | Third failure arms a 10-second cooldown | `test_pin_rl_third_failure_10s_cooldown` | `test_pin_rate_limit.c:43` |
| `REQ-AUTH-021` | Fourth failure extends cooldown to 60 seconds | `test_pin_rl_fourth_failure_60s_cooldown` | `test_pin_rate_limit.c:62` |
| `REQ-AUTH-021` | Fifth failure extends cooldown to 5 minutes | `test_pin_rl_fifth_failure_5min_cooldown` | `test_pin_rate_limit.c:77` |
| `REQ-AUTH-021` | Sixth and subsequent failures cap at 30 minutes | `test_pin_rl_capped_at_30min` | `test_pin_rate_limit.c:90` |
| `REQ-AUTH-022` | After cooldown elapses, new attempt is allowed | `test_pin_rl_cooldown_elapses` | `test_pin_rate_limit.c:108` |
| `REQ-AUTH-023` | retry_after rounds up to whole seconds | `test_pin_rl_retry_after_rounding` | `test_pin_rate_limit.c:129` |
| `REQ-AUTH-024` | Successful PIN resets counter and cooldown | `test_pin_rl_success_clears_cooldown` | `test_pin_rate_limit.c:152` |
| `REQ-AUTH-025` | After idle > 10 min, counter auto-resets on next check | `test_pin_rl_idle_reset` | `test_pin_rate_limit.c:174` |
| `REQ-AUTH-025` | Idle-reset does not fire while a cooldown is still active | `test_pin_rl_idle_reset_respects_cooldown` | `test_pin_rate_limit.c:194` |
| `REQ-AUTH-026` | NULL state fails open (no crash, lets request through) | `test_pin_rl_null_safe` | `test_pin_rate_limit.c:218` |

<details>
<summary>Detailed steps (12 scenarios)</summary>

### Clean state allows the first request
**Requirement:** `REQ-AUTH-020`

- **Given** A zero-initialised pin_rate_limit_t
- **When** pin_rl_check is called
- **Then** Returns ALLOW

### First two failures do not trigger cooldown
**Requirement:** `REQ-AUTH-020`

- **Given** A clean rate limiter
- **When** Two consecutive failures are recorded
- **Then** pin_rl_check still returns ALLOW (no cooldown armed)

### Third failure arms a 10-second cooldown
**Requirement:** `REQ-AUTH-021`

- **Given** Two failures already recorded
- **When** A third failure is recorded and check is called immediately
- **Then** check returns DENY_COOLDOWN and retry_after ~= 10 s

### Fourth failure extends cooldown to 60 seconds
**Requirement:** `REQ-AUTH-021`


### Fifth failure extends cooldown to 5 minutes
**Requirement:** `REQ-AUTH-021`


### Sixth and subsequent failures cap at 30 minutes
**Requirement:** `REQ-AUTH-021`


### After cooldown elapses, new attempt is allowed
**Requirement:** `REQ-AUTH-022`

- **Given** A cooldown armed for 10 seconds at t=1000ms
- **When** check is called at t=12000ms (11s later)
- **Then** check returns ALLOW and retry_after == 0

### retry_after rounds up to whole seconds
**Requirement:** `REQ-AUTH-023`

- **Given** A 10s cooldown armed at t=1000
- **When** queried at t=1500 (500ms in) it reports 10s, at t=9500 reports 1s

### Successful PIN resets counter and cooldown
**Requirement:** `REQ-AUTH-024`

- **Given** A state with an active cooldown after 3 failures
- **When** pin_rl_record_success is called
- **Then** Subsequent checks ALLOW immediately and count is 0

### After idle > 10 min, counter auto-resets on next check
**Requirement:** `REQ-AUTH-025`

- **Given** 2 failures recorded (no cooldown yet)
- **When** check is called more than 10 min later
- **Then** fail_count resets to 0 — no accidental lockout of returning users

### Idle-reset does not fire while a cooldown is still active
**Requirement:** `REQ-AUTH-025`

- **Given** Third failure arming a 10s cooldown
- **When** check is called 11 minutes later — but the cooldown was only 10s
- **Then** Cooldown has long since elapsed, allow, but fail_count stays 3

### NULL state fails open (no crash, lets request through)
**Requirement:** `REQ-AUTH-026`

- **Given** A NULL pin_rate_limit_t pointer
- **When** check / record_* / retry_after are called
- **Then** No crash; check returns ALLOW, retry_after returns 0

</details>

---

## Power Availability

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-PWR-001` | Normal mode always reports current as available regardless of mains load | `test_normal_mode_always_available` | `test_power_availability.c:1` |
| `REQ-PWR-002` | Normal mode available even with high mains load | `test_normal_mode_available_with_high_load` | `test_power_availability.c:45` |
| `REQ-PWR-003` | Smart mode allows current when mains load plus MinCurrent is under MaxMains | `test_smart_maxmains_allows_under_limit` | `test_power_availability.c:62` |
| `REQ-PWR-004` | Smart mode blocks current when mains load plus MinCurrent exceeds MaxMains | `test_smart_maxmains_blocks_over_limit` | `test_power_availability.c:80` |
| `REQ-PWR-005` | Smart mode allows current when circuit load is under MaxCircuit limit | `test_smart_maxcircuit_allows_under_limit` | `test_power_availability.c:101` |
| `REQ-PWR-006` | Smart mode blocks current when circuit load exceeds MaxCircuit limit | `test_smart_maxcircuit_blocks_over_limit` | `test_power_availability.c:121` |
| `REQ-PWR-007` | MaxSumMains allows current when sum of phase currents is under limit | `test_maxsummains_allows_under_limit` | `test_power_availability.c:143` |
| `REQ-PWR-008` | MaxSumMains blocks current when sum of phase currents exceeds limit | `test_maxsummains_blocks_over_limit` | `test_power_availability.c:162` |
| `REQ-PWR-009` | MaxSumMains=0 disables the sum-of-mains check entirely | `test_maxsummains_zero_disables_check` | `test_power_availability.c:182` |
| `REQ-PWR-010` | Solar mode blocks current when no surplus is available | `test_solar_no_surplus_blocks` | `test_power_availability.c:203` |
| `REQ-PWR-011` | Solar mode allows current when surplus exceeds StartCurrent | `test_solar_surplus_allows` | `test_power_availability.c:220` |
| `REQ-PWR-012` | Solar mode blocks current when surplus is below StartCurrent threshold | `test_solar_insufficient_surplus_blocks` | `test_power_availability.c:237` |
| `REQ-PWR-013` | Solar mode with active EVSE checks fair share before allowing more | `test_solar_with_active_evse_checks_fair_share` | `test_power_availability.c:254` |
| `REQ-PWR-014` | OCPP limit below MinCurrent blocks power availability | `test_ocpp_limit_blocks_when_below_min` | `test_power_availability.c:280` |
| `REQ-PWR-015` | OCPP limit above MinCurrent allows power availability | `test_ocpp_limit_allows_when_above_min` | `test_power_availability.c:297` |
| `REQ-PWR-016` | OCPP negative limit (no limit set) allows power availability | `test_ocpp_no_limit_allows` | `test_power_availability.c:314` |
| `REQ-PWR-017` | OCPP availability check is skipped for non-standalone configurations | `test_ocpp_check_only_for_standalone` | `test_power_availability.c:330` |
| `REQ-PWR-018` | PWM duty cycle conversion for 6A (minimum charge current) | `test_current_to_duty_6A` | `test_power_availability.c:350` |
| `REQ-PWR-019` | PWM duty cycle conversion for 16A (common residential limit) | `test_current_to_duty_16A` | `test_power_availability.c:364` |
| `REQ-PWR-020` | PWM duty cycle conversion for 51A (upper boundary of low-range formula) | `test_current_to_duty_51A` | `test_power_availability.c:378` |
| `REQ-PWR-021` | PWM duty cycle conversion for 60A (high-range formula) | `test_current_to_duty_high_range` | `test_power_availability.c:392` |
| `REQ-PWR-022` | PWM duty cycle conversion for 80A (near maximum charge current) | `test_current_to_duty_80A` | `test_power_availability.c:406` |

<details>
<summary>Detailed steps (22 scenarios)</summary>

### Normal mode always reports current as available regardless of mains load
**Requirement:** `REQ-PWR-001`

- **Given** EVSE is standalone in Normal mode with very high MainsMeterImeasured=999
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because Normal mode does not check mains

### Normal mode available even with high mains load
**Requirement:** `REQ-PWR-002`

- **Given** EVSE is standalone in Normal mode with MainsMeterImeasured=400
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because Normal mode ignores mains measurements

### Smart mode allows current when mains load plus MinCurrent is under MaxMains
**Requirement:** `REQ-PWR-003`

- **Given** EVSE is standalone in Smart mode with MaxMains=25A and MainsMeterImeasured=100 (10A)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because baseload (10A) + MinCurrent (6A) = 16A < MaxMains (25A)

### Smart mode blocks current when mains load plus MinCurrent exceeds MaxMains
**Requirement:** `REQ-PWR-004`

- **Given** EVSE is standalone in Smart mode with MaxMains=10A and MainsMeterImeasured=200 (20A baseload)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because baseload (20A) + MinCurrent (6A) = 26A > MaxMains (10A)

### Smart mode allows current when circuit load is under MaxCircuit limit
**Requirement:** `REQ-PWR-005`

- **Given** EVSE is master (LoadBl=1) in Smart mode with MaxCircuit=20A and EVMeterImeasured=50
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because circuit load (5A) + MinCurrent (6A) is under MaxCircuit

### Smart mode blocks current when circuit load exceeds MaxCircuit limit
**Requirement:** `REQ-PWR-006`

- **Given** EVSE is master (LoadBl=1) in Smart mode with MaxCircuit=8A and EVMeterImeasured=100 (10A)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because circuit load (10A) already exceeds MaxCircuit (8A)

### MaxSumMains allows current when sum of phase currents is under limit
**Requirement:** `REQ-PWR-007`

- **Given** EVSE is in Smart mode with MaxSumMains=50 and Isum=100 (10A total)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because Isum plus MinCurrent is under MaxSumMains limit

### MaxSumMains blocks current when sum of phase currents exceeds limit
**Requirement:** `REQ-PWR-008`

- **Given** EVSE is in Smart mode with MaxSumMains=10 and Isum=200 (way over limit)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because total phase current sum exceeds MaxSumMains

### MaxSumMains=0 disables the sum-of-mains check entirely
**Requirement:** `REQ-PWR-009`

- **Given** EVSE is in Smart mode with MaxSumMains=0 (disabled) and Isum=9999 (extremely high)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because MaxSumMains=0 means the check is skipped

### Solar mode blocks current when no surplus is available
**Requirement:** `REQ-PWR-010`

- **Given** EVSE is in Solar mode with StartCurrent=6A and Isum=0 (no export)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because there is no solar surplus for charging

### Solar mode allows current when surplus exceeds StartCurrent
**Requirement:** `REQ-PWR-011`

- **Given** EVSE is in Solar mode with StartCurrent=6A and Isum=-80 (8A export surplus)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because 8A surplus exceeds 6A StartCurrent threshold

### Solar mode blocks current when surplus is below StartCurrent threshold
**Requirement:** `REQ-PWR-012`

- **Given** EVSE is in Solar mode with StartCurrent=10A and Isum=-80 (only 8A surplus)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because 8A surplus is below the 10A StartCurrent threshold

### Solar mode with active EVSE checks fair share before allowing more
**Requirement:** `REQ-PWR-013`

- **Given** EVSE is in Solar mode with one active EVSE at MinCurrent and Isum=10 (1A import)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because grid import indicates insufficient surplus for another EVSE

### OCPP limit below MinCurrent blocks power availability
**Requirement:** `REQ-PWR-014`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=4.0A (below MinCurrent=6A)
- **When** evse_is_current_available is called
- **Then** Returns 0 (unavailable) because OCPP limit is below the minimum viable charge current

### OCPP limit above MinCurrent allows power availability
**Requirement:** `REQ-PWR-015`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=10.0A (above MinCurrent=6A)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because OCPP limit is above the minimum viable charge current

### OCPP negative limit (no limit set) allows power availability
**Requirement:** `REQ-PWR-016`

- **Given** EVSE is standalone with OcppMode enabled and OcppCurrentLimit=-1.0A (no limit)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because negative OCPP limit means no restriction

### OCPP availability check is skipped for non-standalone configurations
**Requirement:** `REQ-PWR-017`

- **Given** EVSE is master (LoadBl=1) with OcppMode enabled and OcppCurrentLimit=3.0A (below MinCurrent)
- **When** evse_is_current_available is called
- **Then** Returns 1 (available) because OCPP check requires LoadBl=0 (standalone)

### PWM duty cycle conversion for 6A (minimum charge current)
**Requirement:** `REQ-PWR-018`

- **Given** A charge current of 60 deciamps (6A)
- **When** evse_current_to_duty is called
- **Then** Returns 102 as the PWM duty cycle value (60/0.6 * 1024/1000)

### PWM duty cycle conversion for 16A (common residential limit)
**Requirement:** `REQ-PWR-019`

- **Given** A charge current of 160 deciamps (16A)
- **When** evse_current_to_duty is called
- **Then** Returns a duty cycle value between 100 and 600 (low-range formula)

### PWM duty cycle conversion for 51A (upper boundary of low-range formula)
**Requirement:** `REQ-PWR-020`

- **Given** A charge current of 510 deciamps (51A)
- **When** evse_current_to_duty is called
- **Then** Returns a duty cycle value between 800 and 1000 (near top of low-range)

### PWM duty cycle conversion for 60A (high-range formula)
**Requirement:** `REQ-PWR-021`

- **Given** A charge current of 600 deciamps (60A)
- **When** evse_current_to_duty is called
- **Then** Returns a duty cycle value between 850 and 1000 (high-range formula: current/2.5 + 640)

### PWM duty cycle conversion for 80A (near maximum charge current)
**Requirement:** `REQ-PWR-022`

- **Given** A charge current of 800 deciamps (80A)
- **When** evse_current_to_duty is called
- **Then** Returns a duty cycle value between 950 and 1024 (near the top of the PWM range)

</details>

---

## Reconnect backoff

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-NET-010` | Clean state allows immediate attempt | `test_clean_state_allows` | `test_reconnect_backoff.c:1` |
| `REQ-NET-011` | First failure arms 1-second backoff | `test_first_failure_1s` | `test_reconnect_backoff.c:23` |
| `REQ-NET-011` | Each subsequent failure doubles the backoff up to 30 s cap | `test_doubling_schedule` | `test_reconnect_backoff.c:37` |
| `REQ-NET-012` | Success clears the failure counter and the cooldown | `test_success_clears` | `test_reconnect_backoff.c:57` |
| `REQ-NET-013` | After cooldown elapses, attempts allowed without state mutation | `test_cooldown_elapses` | `test_reconnect_backoff.c:78` |
| `REQ-NET-014` | seconds_until_next rounds up | `test_seconds_rounds_up` | `test_reconnect_backoff.c:102` |
| `REQ-NET-015` | NULL state is safe and fails open | `test_null_safe` | `test_reconnect_backoff.c:121` |
| `REQ-NET-016` | consecutive_failures saturates at 0xFF | `test_counter_saturates` | `test_reconnect_backoff.c:137` |

<details>
<summary>Detailed steps (8 scenarios)</summary>

### Clean state allows immediate attempt
**Requirement:** `REQ-NET-010`


### First failure arms 1-second backoff
**Requirement:** `REQ-NET-011`


### Each subsequent failure doubles the backoff up to 30 s cap
**Requirement:** `REQ-NET-011`


### Success clears the failure counter and the cooldown
**Requirement:** `REQ-NET-012`


### After cooldown elapses, attempts allowed without state mutation
**Requirement:** `REQ-NET-013`

- **Given** A 4-second cooldown after 3 failures
- **When** should_attempt is called past the cooldown deadline
- **Then** Returns true; counter unchanged (only failure or success mutates)

### seconds_until_next rounds up
**Requirement:** `REQ-NET-014`


### NULL state is safe and fails open
**Requirement:** `REQ-NET-015`


### consecutive_failures saturates at 0xFF
**Requirement:** `REQ-NET-016`


</details>

---

## Priority-Based Power Scheduling

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-LB-100` | MODBUS_ADDR strategy produces ascending address order | `test_sort_modbus_addr` | `test_scheduling.c:1` |
| `REQ-LB-101` | FIRST_CONNECTED strategy orders by earliest connection time | `test_sort_first_connected` | `test_scheduling.c:70` |
| `REQ-LB-102` | LAST_CONNECTED strategy orders by most recent connection time | `test_sort_last_connected` | `test_scheduling.c:94` |
| `REQ-LB-103` | Disconnected EVSEs are sorted to end regardless of strategy | `test_sort_disconnected_to_end` | `test_scheduling.c:118` |
| `REQ-LB-110` | Insufficient power for 3 EVSEs: first 2 in priority get MinCurrent | `test_shortage_first_two_get_current` | `test_scheduling.c:146` |
| `REQ-LB-111` | Power for only 1 EVSE: highest priority gets it all | `test_shortage_one_evse_gets_all` | `test_scheduling.c:177` |
| `REQ-LB-112` | Sufficient power: all EVSEs get current, no scheduling needed | `test_sufficient_power_no_scheduling` | `test_scheduling.c:204` |
| `REQ-LB-113` | Surplus above MinCurrent distributed fairly among active EVSEs | `test_surplus_distributed_fairly` | `test_scheduling.c:232` |
| `REQ-LB-114` | Standalone mode (LoadBl=0) does not use priority scheduling | `test_standalone_no_scheduling` | `test_scheduling.c:263` |
| `REQ-LB-115` | Solar mode: paused EVSEs get NO_SUN error instead of LESS_6A | `test_solar_paused_gets_no_sun` | `test_scheduling.c:300` |
| `REQ-LB-116` | Capped EVSE surplus redistributed to uncapped ones | `test_capped_surplus_redistribution` | `test_scheduling.c:337` |
| `REQ-LB-117` | Power exactly equals MinCurrent for 1 EVSE | `test_exactly_one_mincurrent` | `test_scheduling.c:363` |
| `REQ-LB-118` | Zero available power pauses all EVSEs | `test_zero_power_pauses_all` | `test_scheduling.c:394` |
| `REQ-LB-119` | NoCurrent does NOT increment when priority scheduling pauses some EVSEs | `test_no_current_not_incremented_on_deliberate_pause` | `test_scheduling.c:422` |
| `REQ-LB-120` | EVSE drawing <1A when IdleTimer expires gets paused | `test_idle_evse_paused_at_timeout` | `test_scheduling.c:450` |
| `REQ-LB-121` | EVSE not paused before IdleTimeout expires (anti-flap) | `test_antiflap_not_paused_early` | `test_scheduling.c:479` |
| `REQ-LB-122` | EVSE drawing power when IdleTimer expires stays active | `test_charging_evse_stays_active` | `test_scheduling.c:505` |
| `REQ-LB-123` | Full idle cycle: all EVSEs tried, recircle to first | `test_idle_cycle_wraps_around` | `test_scheduling.c:534` |
| `REQ-LB-140` | RotationTimer expiry pauses current EVSE and activates next | `test_rotation_timer_expires` | `test_scheduling.c:567` |
| `REQ-LB-141` | RotationInterval=0 disables rotation entirely | `test_rotation_disabled` | `test_scheduling.c:598` |
| `REQ-LB-142` | Rotation wraps from last priority to first | `test_rotation_wraps_to_first` | `test_scheduling.c:628` |
| `REQ-LB-143` | Rotation skips disconnected EVSEs (STATE_A) | `test_rotation_skips_disconnected` | `test_scheduling.c:657` |
| `REQ-LB-144` | Newly activated EVSE gets idle check before rotation timer applies | `test_idle_check_before_rotation` | `test_scheduling.c:687` |
| `REQ-LB-150` | Power increases: paused EVSE reactivated immediately | `test_power_increase_reactivates` | `test_scheduling.c:723` |
| `REQ-LB-151` | Reactivation follows priority order | `test_reactivation_follows_priority` | `test_scheduling.c:758` |
| `REQ-LB-160` | Original bug: 2 EVSEs, power drops, only 1 stops (no oscillation) | `test_regression_no_oscillation` | `test_scheduling.c:790` |
| `REQ-LB-161` | 6 EVSEs, power for 5: lowest priority paused | `test_six_evse_lowest_paused` | `test_scheduling.c:820` |
| `REQ-LB-162` | Node goes offline: removed from scheduling | `test_offline_node_removed` | `test_scheduling.c:845` |
| `REQ-LB-163` | New EVSE join during shortage doesn't displace active ones | `test_new_evse_doesnt_displace` | `test_scheduling.c:872` |

<details>
<summary>Detailed steps (29 scenarios)</summary>

### MODBUS_ADDR strategy produces ascending address order
**Requirement:** `REQ-LB-100`

- **Given** Master (LoadBl=1) with 4 EVSEs in STATE_C
- **When** evse_sort_priority() is called
- **Then** Priority[] = {0, 1, 2, 3}

### FIRST_CONNECTED strategy orders by earliest connection time
**Requirement:** `REQ-LB-101`

- **Given** Master with 3 EVSEs in STATE_C
- **When** evse_sort_priority() is called
- **Then** Priority[] = {1, 2, 0, ...} (EVSE[1] first, EVSE[0] last)

### LAST_CONNECTED strategy orders by most recent connection time
**Requirement:** `REQ-LB-102`

- **Given** Master with 3 EVSEs in STATE_C
- **When** evse_sort_priority() is called
- **Then** Priority[] = {0, 2, 1, ...} (EVSE[0] first, EVSE[1] last)

### Disconnected EVSEs are sorted to end regardless of strategy
**Requirement:** `REQ-LB-103`

- **Given** Master with 4 EVSEs: [0]=STATE_C, [1]=STATE_A, [2]=STATE_C, [3]=STATE_A
- **When** evse_sort_priority() is called
- **Then** Priority[] = {0, 2, 1, 3} (active EVSEs first, then disconnected)

### Insufficient power for 3 EVSEs: first 2 in priority get MinCurrent
**Requirement:** `REQ-LB-110`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A, MaxCircuit=20A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Balanced[0] >= 60 and Balanced[1] >= 60 and Balanced[2] == 0

### Power for only 1 EVSE: highest priority gets it all
**Requirement:** `REQ-LB-111`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Balanced[0] == 80 and Balanced[1] == 0 and Balanced[2] == 0

### Sufficient power: all EVSEs get current, no scheduling needed
**Requirement:** `REQ-LB-112`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** All EVSEs get current, no LESS_6A errors, NoCurrent == 0

### Surplus above MinCurrent distributed fairly among active EVSEs
**Requirement:** `REQ-LB-113`

- **Given** Master with 2 EVSEs in STATE_C, MinCurrent=6A, BalancedMax={320,320}
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Balanced[0] == 100 and Balanced[1] == 100 (10A each = 6A + 4A surplus)

### Standalone mode (LoadBl=0) does not use priority scheduling
**Requirement:** `REQ-LB-114`

- **Given** Single EVSE (LoadBl=0) in STATE_C, MinCurrent=6A, Mode=SMART
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** NoCurrent increments (original behavior preserved), no ScheduleState changes

### Solar mode: paused EVSEs get NO_SUN error instead of LESS_6A
**Requirement:** `REQ-LB-115`

- **Given** Master with 2 EVSEs in STATE_C, Mode=MODE_SOLAR
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Balanced[1] == 0 and BalancedError[1] has NO_SUN set

### Capped EVSE surplus redistributed to uncapped ones
**Requirement:** `REQ-LB-116`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Balanced[1] == 80 (capped) and Balanced[0] + Balanced[2] == 160

### Power exactly equals MinCurrent for 1 EVSE
**Requirement:** `REQ-LB-117`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Exactly 1 EVSE has Balanced >= 60, exactly 2 have Balanced == 0

### Zero available power pauses all EVSEs
**Requirement:** `REQ-LB-118`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** All Balanced[] == 0, all paused, NoCurrent increments

### NoCurrent does NOT increment when priority scheduling pauses some EVSEs
**Requirement:** `REQ-LB-119`

- **Given** Master with 3 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** NoCurrent == 0, EVSE[0] is charging

### EVSE drawing <1A when IdleTimer expires gets paused
**Requirement:** `REQ-LB-120`

- **Given** Master with 2 EVSEs in STATE_C, EVSE[0] active, EVSE[1] paused
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[0] paused, EVSE[1] activated with IdleTimer[1] = 0

### EVSE not paused before IdleTimeout expires (anti-flap)
**Requirement:** `REQ-LB-121`

- **Given** EVSE[0] active with IdleTimer[0] = 30, IdleTimeout = 60
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[0] remains active

### EVSE drawing power when IdleTimer expires stays active
**Requirement:** `REQ-LB-122`

- **Given** EVSE[0] active with IdleTimer[0] = 59, IdleTimeout = 60
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[0] stays active, RotationTimer starts if RotationInterval > 0

### Full idle cycle: all EVSEs tried, recircle to first
**Requirement:** `REQ-LB-123`

- **Given** 3 EVSEs in STATE_C, EVSE[2] active (last tried), EVSE[0] and [1] paused
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[2] paused, EVSE[0] reactivated (wraps around)

### RotationTimer expiry pauses current EVSE and activates next
**Requirement:** `REQ-LB-140`

- **Given** 3 EVSEs in STATE_C, EVSE[0] active, RotationInterval=30
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[0] paused, EVSE[1] activated, RotationTimer reset to 1800

### RotationInterval=0 disables rotation entirely
**Requirement:** `REQ-LB-141`

- **Given** 2 EVSEs, EVSE[0] active, RotationInterval = 0
- **When** Checking ScheduleState
- **Then** EVSE[0] still active (never rotated)

### Rotation wraps from last priority to first
**Requirement:** `REQ-LB-142`

- **Given** 3 EVSEs in priority order {0,1,2}, EVSE[2] active
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[2] paused, EVSE[0] activated

### Rotation skips disconnected EVSEs (STATE_A)
**Requirement:** `REQ-LB-143`

- **Given** 3 EVSEs: [0] active, [1] STATE_A disconnected, [2] paused
- **When** evse_schedule_tick_1s() is called
- **Then** EVSE[0] paused, EVSE[2] activated (EVSE[1] skipped)

### Newly activated EVSE gets idle check before rotation timer applies
**Requirement:** `REQ-LB-144`

- **Given** EVSE[1] just activated via rotation, IdleTimeout=60, RotationInterval=30
- **When** 60 seconds pass
- **Then** EVSE[1] paused due to idle (not waiting for rotation)

### Power increases: paused EVSE reactivated immediately
**Requirement:** `REQ-LB-150`

- **Given** 3 EVSEs, EVSE[0] active, EVSE[1] and [2] paused
- **When** evse_calc_balanced_current(ctx, 0) is called with new power
- **Then** EVSE[1] reactivated, IdleTimer reset

### Reactivation follows priority order
**Requirement:** `REQ-LB-151`

- **Given** 3 EVSEs paused, PrioStrategy=PRIO_MODBUS_ADDR
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** EVSE[0] and EVSE[1] activated (not [0] and [2])

### Original bug: 2 EVSEs, power drops, only 1 stops (no oscillation)
**Requirement:** `REQ-LB-160`

- **Given** Master with 2 EVSEs in STATE_C, MinCurrent=6A, MaxCircuit=11A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** Exactly 1 EVSE continues, 1 paused, NoCurrent == 0

### 6 EVSEs, power for 5: lowest priority paused
**Requirement:** `REQ-LB-161`

- **Given** Master with 6 EVSEs in STATE_C, MinCurrent=6A
- **When** evse_calc_balanced_current(ctx, 0) is called
- **Then** EVSEs [0]-[4] receive current, EVSE[5] paused

### Node goes offline: removed from scheduling
**Requirement:** `REQ-LB-162`

- **Given** 3 EVSEs, EVSE[1] goes offline (STATE_A)
- **When** evse_schedule_tick_1s() runs
- **Then** EVSE[1] gets ScheduleState = SCHED_INACTIVE

### New EVSE join during shortage doesn't displace active ones
**Requirement:** `REQ-LB-163`

- **Given** 2 EVSEs charging, power for 2 at MinCurrent
- **When** evse_calc_balanced_current(ctx, 1) is called
- **Then** EVSE[0] and EVSE[1] keep allocation, EVSE[2] gets 0

</details>

---

## Serial Message Parsing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SERIAL-001` | Valid three-phase Irms message with address 011 | `test_irms_valid_three_phase` | `test_serial_parser.c:1` |
| `REQ-SERIAL-001` | Irms message with negative current values | `test_irms_negative_values` | `test_serial_parser.c:40` |
| `REQ-SERIAL-001` | Irms message with zero values | `test_irms_zero_values` | `test_serial_parser.c:57` |
| `REQ-SERIAL-001` | Irms message embedded in larger buffer with extra text | `test_irms_embedded_in_buffer` | `test_serial_parser.c:74` |
| `REQ-SERIAL-002` | Valid power measurement with address 010 | `test_power_valid` | `test_serial_parser.c:147` |
| `REQ-SERIAL-002` | Power measurement with negative value (export) | `test_power_negative` | `test_serial_parser.c:162` |
| `REQ-SERIAL-003` | Valid 16-byte node status with state B and no errors | `test_node_status_valid` | `test_serial_parser.c:220` |
| `REQ-SERIAL-003` | Node status with error flags and solar timer | `test_node_status_error_and_timer` | `test_serial_parser.c:248` |
| `REQ-SERIAL-003` | Node status with mode Smart and max current boundary | `test_node_status_max_current_boundary` | `test_serial_parser.c:276` |

<details>
<summary>Detailed steps (9 scenarios)</summary>

### Valid three-phase Irms message with address 011
**Requirement:** `REQ-SERIAL-001`

- **Given** A serial buffer containing "Irms:011,312,123,124"
- **When** serial_parse_irms is called
- **Then** Address is 11 and three phase currents are parsed correctly

### Irms message with negative current values
**Requirement:** `REQ-SERIAL-001`

- **Given** A serial buffer with negative Irms values (solar injection)
- **When** serial_parse_irms is called
- **Then** Negative values are parsed correctly

### Irms message with zero values
**Requirement:** `REQ-SERIAL-001`

- **Given** A serial buffer with all zero Irms values
- **When** serial_parse_irms is called
- **Then** All values parsed as zero

### Irms message embedded in larger buffer with extra text
**Requirement:** `REQ-SERIAL-001`

- **Given** A serial buffer with text before and after the Irms token
- **When** serial_parse_irms is called
- **Then** The Irms message is found and parsed correctly

### Valid power measurement with address 010
**Requirement:** `REQ-SERIAL-002`

- **Given** A serial buffer containing "PowerMeasured:010,500"
- **When** serial_parse_power is called
- **Then** Address is 10 and power is 500

### Power measurement with negative value (export)
**Requirement:** `REQ-SERIAL-002`

- **Given** A serial buffer with negative power value
- **When** serial_parse_power is called
- **Then** Negative power is parsed correctly

### Valid 16-byte node status with state B and no errors
**Requirement:** `REQ-SERIAL-003`

- **Given** A 16-byte buffer with state=1 (B), error=0, mode=0 (Normal)
- **When** serial_parse_node_status is called
- **Then** All fields parsed correctly

### Node status with error flags and solar timer
**Requirement:** `REQ-SERIAL-003`

- **Given** A buffer with RCM_TRIPPED error and large solar timer
- **When** serial_parse_node_status is called
- **Then** Error and solar timer are parsed correctly

### Node status with mode Smart and max current boundary
**Requirement:** `REQ-SERIAL-003`

- **Given** A buffer with mode=1 (Smart) and max current 255 (max byte value)
- **When** serial_parse_node_status is called
- **Then** Max current is 255 * 10 = 2550

</details>

---

## Serial Input Validation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SERIAL-004` | Irms message with missing fields returns false | `test_irms_missing_fields` | `test_serial_parser.c:91` |
| `REQ-SERIAL-004` | Irms token not found in buffer | `test_irms_token_not_found` | `test_serial_parser.c:104` |
| `REQ-SERIAL-004` | NULL buffer passed to Irms parser | `test_irms_null_buffer` | `test_serial_parser.c:117` |
| `REQ-SERIAL-004` | Empty buffer passed to Irms parser | `test_irms_empty_buffer` | `test_serial_parser.c:130` |
| `REQ-SERIAL-004` | Power message with missing field returns false | `test_power_missing_field` | `test_serial_parser.c:177` |
| `REQ-SERIAL-004` | Power token not found in buffer | `test_power_token_not_found` | `test_serial_parser.c:190` |
| `REQ-SERIAL-004` | NULL buffer passed to power parser | `test_power_null_buffer` | `test_serial_parser.c:203` |
| `REQ-SERIAL-004` | Node status buffer too short | `test_node_status_buffer_too_short` | `test_serial_parser.c:297` |
| `REQ-SERIAL-004` | NULL buffer passed to node status parser | `test_node_status_null_buffer` | `test_serial_parser.c:311` |
| `REQ-SERIAL-004` | NULL output passed to node status parser | `test_node_status_null_output` | `test_serial_parser.c:324` |

<details>
<summary>Detailed steps (10 scenarios)</summary>

### Irms message with missing fields returns false
**Requirement:** `REQ-SERIAL-004`

- **Given** A serial buffer with only 2 of 4 expected Irms fields
- **When** serial_parse_irms is called
- **Then** Returns false

### Irms token not found in buffer
**Requirement:** `REQ-SERIAL-004`

- **Given** A serial buffer without the Irms token
- **When** serial_parse_irms is called
- **Then** Returns false

### NULL buffer passed to Irms parser
**Requirement:** `REQ-SERIAL-004`

- **Given** A NULL buffer pointer
- **When** serial_parse_irms is called
- **Then** Returns false without crashing

### Empty buffer passed to Irms parser
**Requirement:** `REQ-SERIAL-004`

- **Given** An empty string buffer
- **When** serial_parse_irms is called
- **Then** Returns false

### Power message with missing field returns false
**Requirement:** `REQ-SERIAL-004`

- **Given** A serial buffer with only the address, no power value
- **When** serial_parse_power is called
- **Then** Returns false

### Power token not found in buffer
**Requirement:** `REQ-SERIAL-004`

- **Given** A serial buffer without the PowerMeasured token
- **When** serial_parse_power is called
- **Then** Returns false

### NULL buffer passed to power parser
**Requirement:** `REQ-SERIAL-004`

- **Given** A NULL buffer pointer
- **When** serial_parse_power is called
- **Then** Returns false without crashing

### Node status buffer too short
**Requirement:** `REQ-SERIAL-004`

- **Given** A buffer shorter than 16 bytes
- **When** serial_parse_node_status is called
- **Then** Returns false

### NULL buffer passed to node status parser
**Requirement:** `REQ-SERIAL-004`

- **Given** A NULL buffer pointer
- **When** serial_parse_node_status is called
- **Then** Returns false without crashing

### NULL output passed to node status parser
**Requirement:** `REQ-SERIAL-004`

- **Given** A valid buffer but NULL output pointer
- **When** serial_parse_node_status is called
- **Then** Returns false without crashing

</details>

---

## Battery Current Calculation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-CALC-001` | Fresh battery data in solar mode | `test_battery_current_fresh_solar_api` | `test_serial_parser.c:341` |
| `REQ-CALC-001` | Stale battery data is ignored after 60 seconds | `test_battery_current_stale_data` | `test_serial_parser.c:354` |
| `REQ-CALC-001` | Battery data exactly at 60 second boundary | `test_battery_current_boundary_60s` | `test_serial_parser.c:367` |
| `REQ-CALC-001` | Non-solar mode returns zero | `test_battery_current_normal_mode` | `test_serial_parser.c:380` |
| `REQ-CALC-001` | Non-API meter in solar mode still returns battery current | `test_battery_current_non_api_meter` | `test_serial_parser.c:393` |
| `REQ-CALC-001` | Never-updated battery returns zero | `test_battery_current_never_updated` | `test_serial_parser.c:406` |
| `REQ-CALC-001` | Negative battery current (discharging) in solar mode | `test_battery_current_negative_discharge` | `test_serial_parser.c:419` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### Fresh battery data in solar mode
**Requirement:** `REQ-CALC-001`

- **Given** Battery update 30s ago, solar mode, current = 1000
- **When** calc_battery_current is called
- **Then** Returns 1000 (battery current value)

### Stale battery data is ignored after 60 seconds
**Requirement:** `REQ-CALC-001`

- **Given** Battery update 61s ago
- **When** calc_battery_current is called
- **Then** Returns 0 (stale data ignored)

### Battery data exactly at 60 second boundary
**Requirement:** `REQ-CALC-001`

- **Given** Battery update exactly 60s ago
- **When** calc_battery_current is called
- **Then** Returns battery current (60s is not stale)

### Non-solar mode returns zero
**Requirement:** `REQ-CALC-001`

- **Given** Normal mode with fresh battery data
- **When** calc_battery_current is called
- **Then** Returns 0 (battery only used in solar mode)

### Non-API meter in solar mode still returns battery current
**Requirement:** `REQ-CALC-001`

- **Given** Solar mode with non-API meter type
- **When** calc_battery_current is called
- **Then** Returns battery current (battery used with any meter in solar mode)

### Never-updated battery returns zero
**Requirement:** `REQ-CALC-001`

- **Given** time_since_update is 0 (never updated)
- **When** calc_battery_current is called
- **Then** Returns 0

### Negative battery current (discharging) in solar mode
**Requirement:** `REQ-CALC-001`

- **Given** Battery discharging with negative current value
- **When** calc_battery_current is called
- **Then** Returns the negative value

</details>

---

## Current Sum Calculation

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-CALC-002` | Three-phase system distributes battery current equally | `test_isum_three_phase_battery` | `test_serial_parser.c:436` |
| `REQ-CALC-003` | Single-phase battery adjustment uses L1 only | `test_isum_single_phase_battery` | `test_serial_parser.c:457` |
| `REQ-CALC-002` | Zero battery current leaves mains unchanged | `test_isum_zero_battery` | `test_serial_parser.c:478` |
| `REQ-CALC-002` | Negative mains currents (solar injection) with battery | `test_isum_negative_mains` | `test_serial_parser.c:499` |
| `REQ-CALC-002` | Battery current not evenly divisible by 3 | `test_isum_battery_rounding` | `test_serial_parser.c:520` |

<details>
<summary>Detailed steps (5 scenarios)</summary>

### Three-phase system distributes battery current equally
**Requirement:** `REQ-CALC-002`

- **Given** Three-phase mains at 100,200,300 dA and battery current 300 dA
- **When** calc_isum is called with enable_c2 = NOT_PRESENT
- **Then** Battery current divided by 3 (100) subtracted from each phase, Isum = 300

### Single-phase battery adjustment uses L1 only
**Requirement:** `REQ-CALC-003`

- **Given** EnableC2 ALWAYS_OFF, battery current 300 dA
- **When** calc_isum is called
- **Then** Full battery current subtracted from L1, L2 and L3 unchanged

### Zero battery current leaves mains unchanged
**Requirement:** `REQ-CALC-002`

- **Given** Zero battery current
- **When** calc_isum is called
- **Then** Adjusted currents equal original mains currents

### Negative mains currents (solar injection) with battery
**Requirement:** `REQ-CALC-002`

- **Given** Negative mains currents and positive battery current
- **When** calc_isum is called
- **Then** Battery adjustment makes values more negative

### Battery current not evenly divisible by 3
**Requirement:** `REQ-CALC-002`

- **Given** Battery current of 100 (100/3 = 33 per phase, integer division)
- **When** calc_isum is called
- **Then** Each phase reduced by 33 (truncated integer division)

</details>

---

## Charge Session Logging

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-ERE-001` | Start and end a normal charge session | `test_session_basic_lifecycle` | `test_session_log.c:1` |
| `REQ-ERE-002` | Session IDs increment across sessions | `test_session_id_increments` | `test_session_log.c:51` |
| `REQ-ERE-003` | OCPP transaction ID replaces session ID | `test_session_ocpp_id` | `test_session_log.c:74` |
| `REQ-ERE-004` | session_end without prior session_start is ignored | `test_session_end_without_start` | `test_session_log.c:95` |
| `REQ-ERE-005` | session_start while session active discards previous | `test_session_start_while_active` | `test_session_log.c:111` |
| `REQ-ERE-006` | session_get_last before any session returns NULL | `test_session_get_last_before_any` | `test_session_log.c:136` |
| `REQ-ERE-007` | session_set_ocpp_id with no active session is ignored | `test_session_set_ocpp_no_active` | `test_session_log.c:149` |
| `REQ-ERE-008` | Solar mode session records mode correctly | `test_session_solar_mode` | `test_session_log.c:164` |
| `REQ-ERE-015` | Zero energy session is recorded correctly | `test_session_zero_energy` | `test_session_log.c:323` |
| `REQ-CIR-020` | Session with circuit energy includes circuit_kwh in JSON | `test_session_circuit_energy_json` | `test_session_log.c:343` |
| `REQ-CIR-021` | Session without circuit energy omits circuit_kwh from JSON | `test_session_no_circuit_energy_json` | `test_session_log.c:369` |
| `REQ-CIR-022` | Circuit energy calculation: end minus start | `test_session_circuit_energy_calculation` | `test_session_log.c:391` |
| `REQ-CIR-023` | session_set_circuit_energy with no active session is ignored | `test_session_set_circuit_energy_no_active` | `test_session_log.c:413` |
| `REQ-ERE-020` | session_start with timestamp 0 is rejected | `test_session_start_rejects_zero_timestamp` | `test_session_log.c:430` |
| `REQ-ERE-021` | session_start with pre-2024 timestamp is rejected | `test_session_start_rejects_pre2024_timestamp` | `test_session_log.c:444` |
| `REQ-ERE-022` | session_start with valid 2024+ timestamp succeeds | `test_session_start_accepts_valid_timestamp` | `test_session_log.c:458` |
| `REQ-ERE-025` | Session shorter than 60 seconds is discarded | `test_session_short_duration_discarded` | `test_session_log.c:474` |
| `REQ-ERE-026` | Session with duration exactly 60 seconds is kept | `test_session_exact_min_duration_kept` | `test_session_log.c:492` |

<details>
<summary>Detailed steps (18 scenarios)</summary>

### Start and end a normal charge session
**Requirement:** `REQ-ERE-001`

- **Given** The session logger is initialized
- **When** A session is started then ended with energy readings
- **Then** energy_charged_wh equals end_energy - start_energy

### Session IDs increment across sessions
**Requirement:** `REQ-ERE-002`

- **Given** The session logger is initialized
- **When** Two sessions are started and ended
- **Then** The second session has a higher session_id

### OCPP transaction ID replaces session ID
**Requirement:** `REQ-ERE-003`

- **Given** An active charge session
- **When** session_set_ocpp_id is called with a transaction ID
- **Then** The session record has ocpp_active=1 and the OCPP transaction ID

### session_end without prior session_start is ignored
**Requirement:** `REQ-ERE-004`

- **Given** The session logger is initialized with no active session
- **When** session_end is called
- **Then** No crash occurs and session_get_last returns NULL

### session_start while session active discards previous
**Requirement:** `REQ-ERE-005`

- **Given** An active charge session
- **When** session_start is called again
- **Then** The previous session is discarded and a new one begins

### session_get_last before any session returns NULL
**Requirement:** `REQ-ERE-006`

- **Given** The session logger is freshly initialized
- **When** session_get_last is called
- **Then** NULL is returned

### session_set_ocpp_id with no active session is ignored
**Requirement:** `REQ-ERE-007`

- **Given** The session logger is initialized with no active session
- **When** session_set_ocpp_id is called
- **Then** No crash occurs and no state changes

### Solar mode session records mode correctly
**Requirement:** `REQ-ERE-008`

- **Given** The session logger is initialized
- **When** A session is started with MODE_SOLAR
- **Then** The completed record has mode=2

### Zero energy session is recorded correctly
**Requirement:** `REQ-ERE-015`

- **Given** A session where start and end energy are the same
- **When** The session ends
- **Then** energy_charged_wh is 0

### Session with circuit energy includes circuit_kwh in JSON
**Requirement:** `REQ-CIR-020`

- **Given** A completed session with CircuitMeter energy set
- **When** session_to_json is called
- **Then** JSON includes circuit_kwh field with correct value

### Session without circuit energy omits circuit_kwh from JSON
**Requirement:** `REQ-CIR-021`

- **Given** A completed session without CircuitMeter energy
- **When** session_to_json is called
- **Then** JSON does not include circuit_kwh field

### Circuit energy calculation: end minus start
**Requirement:** `REQ-CIR-022`

- **Given** A session with circuit start=100000 and circuit end=107500
- **When** The session ends
- **Then** circuit_energy_wh equals 7500

### session_set_circuit_energy with no active session is ignored
**Requirement:** `REQ-CIR-023`

- **Given** No active session
- **When** session_set_circuit_energy is called
- **Then** No crash and no state change

### session_start with timestamp 0 is rejected
**Requirement:** `REQ-ERE-020`

- **Given** The session logger is initialized
- **When** session_start is called with timestamp 0 (NTP not synced)
- **Then** No session is started and session_is_active returns 0

### session_start with pre-2024 timestamp is rejected
**Requirement:** `REQ-ERE-021`

- **Given** The session logger is initialized
- **When** session_start is called with timestamp 1000 (pre-2024)
- **Then** No session is started and session_is_active returns 0

### session_start with valid 2024+ timestamp succeeds
**Requirement:** `REQ-ERE-022`

- **Given** The session logger is initialized
- **When** session_start is called with timestamp 1710000000 (March 2024)
- **Then** A session is started and session_is_active returns 1

### Session shorter than 60 seconds is discarded
**Requirement:** `REQ-ERE-025`

- **Given** The session logger is initialized
- **When** A session is started and ended after only 30 seconds
- **Then** The session is discarded, session_is_active returns 0, and session_get_last returns NULL

### Session with duration exactly 60 seconds is kept
**Requirement:** `REQ-ERE-026`

- **Given** The session logger is initialized
- **When** A session is started and ended after exactly 60 seconds
- **Then** The session is stored and session_get_last returns a valid record with correct energy

</details>

---

## Charge Session JSON Export

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-ERE-010` | JSON output contains all ERE-required fields | `test_session_json_basic` | `test_session_log.c:186` |
| `REQ-ERE-011` | JSON with OCPP active includes transaction ID | `test_session_json_ocpp` | `test_session_log.c:219` |
| `REQ-ERE-012` | Null record returns -1 | `test_session_json_null_record` | `test_session_log.c:240` |
| `REQ-ERE-012` | Null buffer returns -1 | `test_session_json_null_buffer` | `test_session_log.c:253` |
| `REQ-ERE-012` | Zero-length buffer returns -1 | `test_session_json_zero_buffer` | `test_session_log.c:270` |
| `REQ-ERE-013` | Too-small buffer returns -1 | `test_session_json_small_buffer` | `test_session_log.c:287` |
| `REQ-ERE-014` | Smart mode string in JSON | `test_session_json_smart_mode` | `test_session_log.c:304` |

<details>
<summary>Detailed steps (7 scenarios)</summary>

### JSON output contains all ERE-required fields
**Requirement:** `REQ-ERE-010`

- **Given** A completed charge session
- **When** session_to_json is called
- **Then** The JSON contains session_id, start, end, kwh, and energy fields

### JSON with OCPP active includes transaction ID
**Requirement:** `REQ-ERE-011`

- **Given** A completed session with OCPP transaction ID set
- **When** session_to_json is called
- **Then** ocpp_tx_id contains the numeric transaction ID

### Null record returns -1
**Requirement:** `REQ-ERE-012`

- **Given** A NULL session record pointer
- **When** session_to_json is called
- **Then** It returns -1

### Null buffer returns -1
**Requirement:** `REQ-ERE-012`

- **Given** A valid session record
- **When** session_to_json is called with NULL buffer
- **Then** It returns -1

### Zero-length buffer returns -1
**Requirement:** `REQ-ERE-012`

- **Given** A valid session record
- **When** session_to_json is called with bufsz=0
- **Then** It returns -1

### Too-small buffer returns -1
**Requirement:** `REQ-ERE-013`

- **Given** A valid session record
- **When** session_to_json is called with a very small buffer
- **Then** It returns -1 (truncation detected)

### Smart mode string in JSON
**Requirement:** `REQ-ERE-014`

- **Given** A completed session in MODE_SMART
- **When** session_to_json is called
- **Then** mode field is "smart"

</details>

---

## Solar Balancing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-SOLAR-001` | 3-phase solar shortage starts PhaseSwitchTimer | `test_solar_3p_shortage_starts_timer` | `test_solar_balancing.c:1` |
| `REQ-SOLAR-002` | PhaseSwitchTimer reaching 2 or below triggers 3P to 1P phase switch | `test_solar_3p_timer_triggers_1p_switch` | `test_solar_balancing.c:67` |
| `REQ-SOLAR-003` | 1-phase solar surplus near MaxCurrent starts PhaseSwitchTimer for 3P upgrade | `test_solar_1p_surplus_starts_timer` | `test_solar_balancing.c:89` |
| `REQ-SOLAR-004` | PhaseSwitchTimer reaching 3 or below on 1P triggers switch to 3P | `test_solar_1p_timer_triggers_3p_switch` | `test_solar_balancing.c:116` |
| `REQ-SOLAR-005` | Insufficient surplus resets PhaseSwitchTimer to prevent false 3P upgrade | `test_solar_insufficient_surplus_resets_timer` | `test_solar_balancing.c:141` |
| `REQ-SOLAR-006` | During solar startup period, EVSE is forced to MinCurrent | `test_solar_startup_forces_mincurrent` | `test_solar_balancing.c:166` |
| `REQ-SOLAR-007` | Past startup period, EVSE uses calculated distribution value | `test_solar_past_startup_uses_calculated` | `test_solar_balancing.c:184` |
| `REQ-SOLAR-008` | Small solar export results in gradual current increase | `test_solar_fine_increase_small` | `test_solar_balancing.c:204` |
| `REQ-SOLAR-009` | Large solar export results in larger current increase | `test_solar_fine_increase_large` | `test_solar_balancing.c:225` |
| `REQ-SOLAR-010` | Moderate grid import decreases solar charging current | `test_solar_fine_decrease_moderate` | `test_solar_balancing.c:246` |
| `REQ-SOLAR-011` | Large grid import aggressively decreases solar charging current | `test_solar_fine_decrease_aggressive` | `test_solar_balancing.c:266` |
| `REQ-SOLAR-012` | Solar B-state with AUTO and small surplus determines 1-phase charging | `test_solar_b_state_auto_determines_1p` | `test_solar_balancing.c:286` |
| `REQ-SOLAR-013` | Solar B-state with AUTO and large surplus determines 3-phase charging | `test_solar_b_state_auto_determines_3p` | `test_solar_balancing.c:307` |
| `REQ-SOLAR-014` | Hard current shortage increments NoCurrent counter | `test_hard_shortage_increments_nocurrent` | `test_solar_balancing.c:328` |
| `REQ-SOLAR-015` | Soft shortage (Isum exceeds MaxSumMains) starts MaxSumMains timer | `test_soft_shortage_starts_maxsummains_timer` | `test_solar_balancing.c:349` |
| `REQ-SOLAR-016` | No shortage condition clears SolarStopTimer and decays NoCurrent | `test_no_shortage_clears_timers` | `test_solar_balancing.c:374` |
| `REQ-SOLAR-017` | IsetBalanced is capped at 800 (80A maximum) | `test_isetbalanced_capped_at_800` | `test_solar_balancing.c:397` |
| `REQ-SOLAR-018` | Normal mode forces 3-phase charging regardless of current phase count | `test_normal_mode_forces_3p` | `test_solar_balancing.c:417` |
| `REQ-SOLAR-019` | phasesLastUpdateFlag=false prevents IsetBalanced regulation | `test_phases_flag_gates_regulation` | `test_solar_balancing.c:444` |
| `REQ-SOLAR-020` | Multi-EVSE solar startup: EVSE in startup gets MinCurrent, others get calculated | `test_multi_evse_solar_startup` | `test_solar_balancing.c:467` |
| `REQ-SOL-021` | EMA smoothing dampens sudden IsetBalanced changes | `test_ema_smoothing_dampens_change` | `test_solar_balancing.c:523` |
| `REQ-SOL-022` | EMA with alpha=100 tracks raw IsetBalanced exactly (no smoothing) | `test_ema_alpha_100_no_smoothing` | `test_solar_balancing.c:543` |
| `REQ-SOL-023` | EMA with alpha=0 holds previous value (full dampening) | `test_ema_alpha_0_full_dampening` | `test_solar_balancing.c:563` |
| `REQ-SOL-024` | EMA defaults are initialized correctly by evse_init | `test_smoothing_defaults_initialized` | `test_solar_balancing.c:580` |
| `REQ-SOL-025` | Smart mode dead band suppresses small adjustments | `test_smart_deadband_suppresses_small_change` | `test_solar_balancing.c:600` |
| `REQ-SOL-026` | Smart mode dead band allows large adjustments through | `test_smart_deadband_allows_large_change` | `test_solar_balancing.c:618` |
| `REQ-SOL-027` | Smart mode dead band suppresses small negative Idifference | `test_smart_deadband_suppresses_small_decrease` | `test_solar_balancing.c:635` |
| `REQ-SOL-028` | Symmetric ramp applies same rate for increasing and decreasing | `test_symmetric_ramp_increase` | `test_solar_balancing.c:658` |
| `REQ-SOL-029` | Symmetric ramp applies same divisor for decrease (was full-step) | `test_symmetric_ramp_decrease` | `test_solar_balancing.c:681` |
| `REQ-SOL-030` | Solar fine regulation dead band expanded to 5 dA | `test_solar_fine_deadband_expanded` | `test_solar_balancing.c:707` |
| `REQ-SOL-031` | Solar fine regulation triggers decrease above expanded dead band | `test_solar_fine_deadband_triggers_above` | `test_solar_balancing.c:733` |
| `REQ-SOL-032` | NoCurrent below threshold does not trigger LESS_6A | `test_nocurrent_below_threshold_no_less6a` | `test_solar_balancing.c:769` |
| `REQ-SOL-033` | NoCurrent reaching threshold triggers LESS_6A | `test_nocurrent_at_threshold_triggers_less6a` | `test_solar_balancing.c:786` |
| `REQ-SOL-034` | NoCurrent decays gradually when shortage resolves (not instant reset) | `test_nocurrent_decays_gradually` | `test_solar_balancing.c:805` |
| `REQ-SOL-035` | NoCurrent at 0 stays at 0 when no shortage | `test_nocurrent_stays_zero` | `test_solar_balancing.c:825` |
| `REQ-SOL-036` | Solar min run time prevents LESS_6A during initial charging | `test_solar_min_run_time_prevents_less6a` | `test_solar_balancing.c:846` |
| `REQ-SOL-037` | Solar min run time expired allows LESS_6A | `test_solar_min_run_time_expired_allows_less6a` | `test_solar_balancing.c:864` |
| `REQ-SOL-038` | Solar mode uses shorter charge delay when LESS_6A active | `test_solar_charge_delay_shorter` | `test_solar_balancing.c:884` |
| `REQ-SOL-039` | Smart mode still uses full charge delay when LESS_6A active | `test_smart_charge_delay_unchanged` | `test_solar_balancing.c:905` |
| `REQ-SOL-040` | Cycling prevention defaults initialized correctly | `test_cycling_prevention_defaults` | `test_solar_balancing.c:927` |
| `REQ-SOL-041` | Settling window suppresses smart regulation after current change | `test_settling_window_suppresses_regulation` | `test_solar_balancing.c:947` |
| `REQ-SOL-042` | Regulation proceeds normally when settling timer is 0 | `test_settling_expired_allows_regulation` | `test_solar_balancing.c:970` |
| `REQ-SOL-043` | Balanced[0] change triggers settling timer | `test_current_change_triggers_settling` | `test_solar_balancing.c:992` |
| `REQ-SOL-044` | Ramp rate limits how much Balanced[0] can change per cycle | `test_ramp_rate_limits_increase` | `test_solar_balancing.c:1019` |
| `REQ-SOL-045` | Ramp rate limits how much Balanced[0] can decrease per cycle | `test_ramp_rate_limits_decrease` | `test_solar_balancing.c:1044` |
| `REQ-SOL-046` | SettlingTimer counts down each second | `test_settling_timer_countdown` | `test_solar_balancing.c:1069` |
| `REQ-SOL-047` | Slow EV compatibility defaults initialized correctly | `test_slow_ev_defaults` | `test_solar_balancing.c:1087` |
| `REQ-SOL-048` | MaxRampRate=0 disables ramp rate limiting | `test_ramp_rate_zero_no_limit` | `test_solar_balancing.c:1106` |
| `REQ-SOL-049` | Debug snapshot is populated after evse_calc_balanced_current | `test_solar_debug_snapshot_populated` | `test_solar_balancing.c:1131` |

<details>
<summary>Detailed steps (49 scenarios)</summary>

### 3-phase solar shortage starts PhaseSwitchTimer
**Requirement:** `REQ-SOLAR-001`

- **Given** The EVSE is solar charging on 3 phases with EnableC2=AUTO and high mains load
- **When** evse_calc_balanced_current is called with large import (Isum=200)
- **Then** PhaseSwitchTimer is set to a value greater than 0

### PhaseSwitchTimer reaching 2 or below triggers 3P to 1P phase switch
**Requirement:** `REQ-SOLAR-002`

- **Given** The EVSE is solar charging on 3 phases with EnableC2=AUTO and PhaseSwitchTimer=2
- **When** evse_calc_balanced_current is called with ongoing shortage
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P

### 1-phase solar surplus near MaxCurrent starts PhaseSwitchTimer for 3P upgrade
**Requirement:** `REQ-SOLAR-003`

- **Given** The EVSE is solar charging on 1 phase with IsetBalanced near MaxCurrent and good surplus
- **When** evse_calc_balanced_current is called with export (Isum=-100)
- **Then** PhaseSwitchTimer is set to 63 (countdown to 3P switch)

### PhaseSwitchTimer reaching 3 or below on 1P triggers switch to 3P
**Requirement:** `REQ-SOLAR-004`

- **Given** The EVSE is solar charging on 1 phase with PhaseSwitchTimer=3 and large surplus
- **When** evse_calc_balanced_current is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_3P

### Insufficient surplus resets PhaseSwitchTimer to prevent false 3P upgrade
**Requirement:** `REQ-SOLAR-005`

- **Given** The EVSE is solar charging on 1 phase with IsetBalanced well below MaxCurrent
- **When** evse_calc_balanced_current is called with minimal surplus (Isum=-10)
- **Then** PhaseSwitchTimer is reset to 0

### During solar startup period, EVSE is forced to MinCurrent
**Requirement:** `REQ-SOLAR-006`

- **Given** The EVSE is solar charging with IntTimer below SOLARSTARTTIME (in startup)
- **When** evse_calc_balanced_current is called
- **Then** Balanced[0] is set to MinCurrent*10 regardless of IsetBalanced

### Past startup period, EVSE uses calculated distribution value
**Requirement:** `REQ-SOLAR-007`

- **Given** The EVSE is solar charging with IntTimer past SOLARSTARTTIME
- **When** evse_calc_balanced_current is called
- **Then** Balanced[0] uses the calculated value (at least MinCurrent*10)

### Small solar export results in gradual current increase
**Requirement:** `REQ-SOLAR-008`

- **Given** The EVSE is solar charging with small export (Isum=-5)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced increases by at least 1 (fine-grained increase)

### Large solar export results in larger current increase
**Requirement:** `REQ-SOLAR-009`

- **Given** The EVSE is solar charging with large export (Isum=-50)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced increases by more than the small export case

### Moderate grid import decreases solar charging current
**Requirement:** `REQ-SOLAR-010`

- **Given** The EVSE is solar charging with IsetBalanced=150 and moderate import (Isum=15)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced decreases below 150

### Large grid import aggressively decreases solar charging current
**Requirement:** `REQ-SOLAR-011`

- **Given** The EVSE is solar charging with IsetBalanced=200 and large import (Isum=50)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced decreases below 200

### Solar B-state with AUTO and small surplus determines 1-phase charging
**Requirement:** `REQ-SOLAR-012`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, 3 phases, and small surplus (Isum=-50)
- **When** evse_calc_balanced_current is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P

### Solar B-state with AUTO and large surplus determines 3-phase charging
**Requirement:** `REQ-SOLAR-013`

- **Given** The EVSE is in STATE_B with EnableC2=AUTO, 1 phase, and large surplus (Isum=-500)
- **When** evse_calc_balanced_current is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_3P

### Hard current shortage increments NoCurrent counter
**Requirement:** `REQ-SOLAR-014`

- **Given** The EVSE is in MODE_SMART with heavily overloaded mains and low MaxMains
- **When** evse_calc_balanced_current is called
- **Then** NoCurrent counter is incremented above 0

### Soft shortage (Isum exceeds MaxSumMains) starts MaxSumMains timer
**Requirement:** `REQ-SOLAR-015`

- **Given** The EVSE is in MODE_SMART with Isum exceeding MaxSumMains and MaxSumMainsTime=5
- **When** evse_calc_balanced_current is called
- **Then** MaxSumMainsTimer is set to MaxSumMainsTime*60 (300 seconds)

### No shortage condition clears SolarStopTimer and decays NoCurrent
**Requirement:** `REQ-SOLAR-016`

- **Given** The EVSE is in MODE_SMART with low mains load and high MaxMains
- **When** evse_calc_balanced_current is called with no shortage detected
- **Then** SolarStopTimer is reset to 0 and NoCurrent decays by 1

### IsetBalanced is capped at 800 (80A maximum)
**Requirement:** `REQ-SOLAR-017`

- **Given** The EVSE is in MODE_SMART with IsetBalanced=900 and large surplus
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced does not exceed 800

### Normal mode forces 3-phase charging regardless of current phase count
**Requirement:** `REQ-SOLAR-018`

- **Given** A standalone EVSE in MODE_NORMAL currently on 1 phase
- **When** evse_calc_balanced_current is called
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_3P

### phasesLastUpdateFlag=false prevents IsetBalanced regulation
**Requirement:** `REQ-SOLAR-019`

- **Given** The EVSE is in MODE_SMART with phasesLastUpdateFlag=false and large surplus
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced remains unchanged (regulation gated)

### Multi-EVSE solar startup: EVSE in startup gets MinCurrent, others get calculated
**Requirement:** `REQ-SOLAR-020`

- **Given** Two EVSEs as master, EVSE 0 in startup (IntTimer < SOLARSTARTTIME), EVSE 1 past startup
- **When** evse_calc_balanced_current is called
- **Then** EVSE 0 Balanced is set to MinCurrent*10 (startup forcing)

### EMA smoothing dampens sudden IsetBalanced changes
**Requirement:** `REQ-SOL-021`

- **Given** The EVSE is in smart mode with IsetBalanced_ema=100 and EmaAlpha=50
- **When** evse_calc_balanced_current computes a new IsetBalanced of 200
- **Then** IsetBalanced_ema moves toward 200 but not all the way (between 100 and 200)

### EMA with alpha=100 tracks raw IsetBalanced exactly (no smoothing)
**Requirement:** `REQ-SOL-022`

- **Given** The EVSE is in smart mode with EmaAlpha=100 and IsetBalanced_ema=50
- **When** evse_calc_balanced_current computes a new IsetBalanced with large surplus
- **Then** IsetBalanced_ema updates to a value different from the old 50

### EMA with alpha=0 holds previous value (full dampening)
**Requirement:** `REQ-SOL-023`

- **Given** The EVSE is in smart mode with EmaAlpha=0 and IsetBalanced_ema=80
- **When** evse_calc_balanced_current computes a different IsetBalanced
- **Then** IsetBalanced_ema remains at 80

### EMA defaults are initialized correctly by evse_init
**Requirement:** `REQ-SOL-024`

- **Given** A freshly initialized EVSE context
- **When** evse_init is called
- **Then** EmaAlpha=100 (no smoothing), SmartDeadBand=10, RampRateDivisor=4, SolarFineDeadBand=5

### Smart mode dead band suppresses small adjustments
**Requirement:** `REQ-SOL-025`

- **Given** The EVSE is in smart mode with SmartDeadBand=10 and small Idifference (~5 dA)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced does not change (within dead band)

### Smart mode dead band allows large adjustments through
**Requirement:** `REQ-SOL-026`

- **Given** The EVSE is in smart mode with SmartDeadBand=10 and large Idifference
- **When** evse_calc_balanced_current is called with large surplus (Idifference >> 10)
- **Then** IsetBalanced increases (dead band does not suppress)

### Smart mode dead band suppresses small negative Idifference
**Requirement:** `REQ-SOL-027`

- **Given** The EVSE is in smart mode with SmartDeadBand=10 and Idifference=-5
- **When** evse_calc_balanced_current is called with slight overload
- **Then** IsetBalanced does not decrease (within dead band)

### Symmetric ramp applies same rate for increasing and decreasing
**Requirement:** `REQ-SOL-028`

- **Given** The EVSE is in smart mode with RampRateDivisor=4 and Idifference=40
- **When** evse_calc_balanced_current is called with positive Idifference
- **Then** IsetBalanced increases by Idifference/4 = 10

### Symmetric ramp applies same divisor for decrease (was full-step)
**Requirement:** `REQ-SOL-029`

- **Given** The EVSE is in smart mode with RampRateDivisor=4 and Idifference=-40
- **When** evse_calc_balanced_current is called with negative Idifference
- **Then** IsetBalanced decreases by |Idifference|/4 = 10 (not full 40)

### Solar fine regulation dead band expanded to 5 dA
**Requirement:** `REQ-SOL-030`

- **Given** The EVSE is solar charging with IsumImport=4 (was outside old 3 dA band, now inside 5 dA)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced does not decrease from fine regulation (4 dA within 5 dA dead band)

### Solar fine regulation triggers decrease above expanded dead band
**Requirement:** `REQ-SOL-031`

- **Given** The EVSE is solar charging with IsumImport=15 (well above 5 dA dead band)
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced decreases (outside dead band)

### NoCurrent below threshold does not trigger LESS_6A
**Requirement:** `REQ-SOL-032`

- **Given** The EVSE is in MODE_SMART with NoCurrent=5 and NoCurrentThreshold=10
- **When** evse_calc_balanced_current is called with hard shortage
- **Then** NoCurrent increments but LESS_6A is not set (below threshold)

### NoCurrent reaching threshold triggers LESS_6A
**Requirement:** `REQ-SOL-033`

- **Given** The EVSE is in MODE_SMART with NoCurrent=9 and NoCurrentThreshold=10
- **When** evse_calc_balanced_current is called with hard shortage
- **Then** NoCurrent reaches 10 and LESS_6A is set

### NoCurrent decays gradually when shortage resolves (not instant reset)
**Requirement:** `REQ-SOL-034`

- **Given** The EVSE is in MODE_SMART with NoCurrent=8 and no shortage
- **When** evse_calc_balanced_current is called with surplus
- **Then** NoCurrent decrements by 1 (not reset to 0)

### NoCurrent at 0 stays at 0 when no shortage
**Requirement:** `REQ-SOL-035`

- **Given** The EVSE is in MODE_SMART with NoCurrent=0 and no shortage
- **When** evse_calc_balanced_current is called
- **Then** NoCurrent stays at 0

### Solar min run time prevents LESS_6A during initial charging
**Requirement:** `REQ-SOL-036`

- **Given** The EVSE is solar charging with IntTimer < SolarMinRunTime and hard shortage
- **When** NoCurrent exceeds threshold
- **Then** LESS_6A is NOT set (protected by min run time)

### Solar min run time expired allows LESS_6A
**Requirement:** `REQ-SOL-037`

- **Given** The EVSE is solar charging with IntTimer >= SolarMinRunTime and hard shortage
- **When** NoCurrent exceeds threshold
- **Then** LESS_6A is set (min run time has passed)

### Solar mode uses shorter charge delay when LESS_6A active
**Requirement:** `REQ-SOL-038`

- **Given** The EVSE is in MODE_SOLAR with LESS_6A error active and SolarChargeDelay=15
- **When** evse_tick_1s is called
- **Then** ChargeDelay is set to SolarChargeDelay (15) not CHARGEDELAY (60)

### Smart mode still uses full charge delay when LESS_6A active
**Requirement:** `REQ-SOL-039`

- **Given** The EVSE is in MODE_SMART with LESS_6A error active and no current available
- **When** evse_tick_1s is called
- **Then** ChargeDelay is set to CHARGEDELAY (60)

### Cycling prevention defaults initialized correctly
**Requirement:** `REQ-SOL-040`

- **Given** A freshly initialized EVSE context
- **When** evse_init is called
- **Then** NoCurrentThreshold=10, SolarChargeDelay=15, SolarMinRunTime=60

### Settling window suppresses smart regulation after current change
**Requirement:** `REQ-SOL-041`

- **Given** The EVSE is in smart mode with SettlingTimer > 0 (settling active)
- **When** evse_calc_balanced_current is called with large surplus
- **Then** IsetBalanced does not increase (regulation suppressed during settling)

### Regulation proceeds normally when settling timer is 0
**Requirement:** `REQ-SOL-042`

- **Given** The EVSE is in smart mode with SettlingTimer=0 and large surplus
- **When** evse_calc_balanced_current is called
- **Then** IsetBalanced increases (regulation active)

### Balanced[0] change triggers settling timer
**Requirement:** `REQ-SOL-043`

- **Given** The EVSE is solar charging with LastBalanced=100 and SettlingWindow=5
- **When** evse_calc_balanced_current produces a different Balanced[0]
- **Then** SettlingTimer is set to SettlingWindow

### Ramp rate limits how much Balanced[0] can change per cycle
**Requirement:** `REQ-SOL-044`

- **Given** The EVSE is smart charging with MaxRampRate=30 and Balanced[0]=100
- **When** evse_calc_balanced_current produces a large increase
- **Then** Balanced[0] changes by at most MaxRampRate from LastBalanced

### Ramp rate limits how much Balanced[0] can decrease per cycle
**Requirement:** `REQ-SOL-045`

- **Given** The EVSE is smart charging with MaxRampRate=30 and Balanced[0]=160
- **When** evse_calc_balanced_current produces a large decrease
- **Then** Balanced[0] decreases by at most MaxRampRate from LastBalanced

### SettlingTimer counts down each second
**Requirement:** `REQ-SOL-046`

- **Given** SettlingTimer=3
- **When** evse_tick_1s is called
- **Then** SettlingTimer decrements to 2

### Slow EV compatibility defaults initialized correctly
**Requirement:** `REQ-SOL-047`

- **Given** A freshly initialized EVSE context
- **When** evse_init is called
- **Then** SettlingWindow=5, MaxRampRate=30, SettlingTimer=0, LastBalanced=0

### MaxRampRate=0 disables ramp rate limiting
**Requirement:** `REQ-SOL-048`

- **Given** The EVSE is smart charging with MaxRampRate=0
- **When** evse_calc_balanced_current produces a large change
- **Then** Balanced[0] is not ramp-limited (can change freely)

### Debug snapshot is populated after evse_calc_balanced_current
**Requirement:** `REQ-SOL-049`

- **Given** The EVSE is solar charging with known meter readings
- **When** evse_calc_balanced_current is called
- **Then** solar_debug snapshot contains matching values

</details>

---

## IEC 61851-1 State Transitions

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-IEC61851-001` | EVSE initialises to disconnected state | `test_init_state_is_A` | `test_state_transitions.c:1` |
| `REQ-IEC61851-002` | Contactors are open after initialisation | `test_init_contactors_off` | `test_state_transitions.c:45` |
| `REQ-IEC61851-003` | Pilot signal is connected after initialisation | `test_init_pilot_connected` | `test_state_transitions.c:59` |
| `REQ-IEC61851-004` | No error flags after initialisation | `test_init_no_errors` | `test_state_transitions.c:72` |
| `REQ-IEC61851-005` | STATE_A remains when no vehicle is connected | `test_A_stays_A_on_12V` | `test_state_transitions.c:85` |
| `REQ-IEC61851-006` | Vehicle connection triggers STATE_A to STATE_B transition | `test_A_to_B_on_9V_when_ready` | `test_state_transitions.c:99` |
| `REQ-IEC61851-007` | Modem negotiation required before STATE_B when ModemStage is 0 | `test_A_to_modem_when_modem_stage_0` | `test_state_transitions.c:113` |
| `REQ-IEC61851-007B` | A→B goes directly to STATE_B when modem is disabled | `test_A_to_B_skips_modem_when_disabled` | `test_state_transitions.c:132` |
| `REQ-IEC61851-008` | Unauthorized EVSE blocks STATE_A to STATE_B transition | `test_A_stays_A_when_access_off` | `test_state_transitions.c:151` |
| `REQ-IEC61851-011` | Vehicle disconnect in STATE_B returns to STATE_A | `test_B_to_A_on_disconnect` | `test_state_transitions.c:166` |
| `REQ-IEC61851-012` | Vehicle charge request after diode check triggers STATE_B to STATE_C | `test_B_to_C_on_6V_with_diode_check` | `test_state_transitions.c:213` |
| `REQ-IEC61851-013` | Charge request without diode check does not transition to STATE_C | `test_B_to_C_requires_diode_check` | `test_state_transitions.c:234` |
| `REQ-IEC61851-014` | PILOT_DIODE signal sets DiodeCheck flag | `test_diode_check_sets_on_pilot_diode` | `test_state_transitions.c:255` |
| `REQ-IEC61851-015` | Contactor 1 is closed when entering STATE_C | `test_C_contactor1_on` | `test_state_transitions.c:271` |
| `REQ-IEC61851-016` | Vehicle disconnect during charging returns to STATE_A with contactors open | `test_C_to_A_on_disconnect` | `test_state_transitions.c:285` |
| `REQ-IEC61851-019` | Vehicle disconnect from STATE_C1 returns to STATE_A | `test_C1_to_A_on_disconnect` | `test_state_transitions.c:301` |
| `REQ-IEC61851-022` | Vehicle disconnect from STATE_B1 returns to STATE_A | `test_B1_to_A_on_disconnect` | `test_state_transitions.c:352` |
| `REQ-IEC61851-023` | Entering STATE_B1 sets a non-zero ChargeDelay | `test_set_state_B1_sets_charge_delay` | `test_state_transitions.c:410` |
| `REQ-IEC61851-024` | Entering STATE_A clears LESS_6A error and ChargeDelay | `test_set_state_A_clears_errors_and_delay` | `test_state_transitions.c:425` |
| `REQ-IEC61851-025` | State transitions are recorded in the transition log | `test_transition_log_records_states` | `test_state_transitions.c:442` |
| `REQ-IEC61851-026` | Entering STATE_C1 sets PWM to off (+12V) | `test_set_state_C1_sets_pwm_off` | `test_state_transitions.c:459` |
| `REQ-IEC61851-027` | Full charge cycle: A -> B -> C -> B -> A | `test_full_charge_cycle` | `test_state_transitions.c:474` |
| `REQ-IEC61851-028` | Vehicle disconnect during ACTSTART is NOT handled in tick_10ms | `test_actstart_to_A_on_disconnect` | `test_state_transitions.c:511` |
| `REQ-IEC61851-029` | ActivationMode=0 triggers STATE_ACTSTART on pilot detection in STATE_B | `test_activation_mode_triggers_actstart` | `test_state_transitions.c:528` |
| `REQ-IEC61851-031` | ActivationMode=255 (always active) does not count down | `test_activation_mode_255_does_not_countdown` | `test_state_transitions.c:545` |
| `REQ-IEC61851-032` | STATE_ACTSTART returns to STATE_B when ActivationTimer expires | `test_actstart_returns_to_B_when_timer_expires` | `test_state_transitions.c:576` |
| `REQ-PHASE-002` | STATE_B re-entry sets Switching_Phases_C2 flag instead of direct phase change | `test_state_B_calls_check_switching_phases_from_B` | `test_state_transitions.c:593` |
| `REQ-IEC61851-M3` | STATE_B entry does NOT set pilot_connected when modem disabled | `test_state_b_no_pilot_reconnect_without_modem` | `test_state_transitions.c:688` |
| `REQ-IEC61851-M3B` | STATE_B entry DOES set pilot_connected when modem enabled | `test_state_b_pilot_reconnect_with_modem` | `test_state_transitions.c:710` |

<details>
<summary>Detailed steps (29 scenarios)</summary>

### EVSE initialises to disconnected state
**Requirement:** `REQ-IEC61851-001`

- **Given** The EVSE is powered on
- **When** evse_init() is called
- **Then** The state machine starts in STATE_A (disconnected)

### Contactors are open after initialisation
**Requirement:** `REQ-IEC61851-002`

- **Given** The EVSE is powered on
- **When** evse_init() is called
- **Then** Both contactor1 and contactor2 are off (open)

### Pilot signal is connected after initialisation
**Requirement:** `REQ-IEC61851-003`

- **Given** The EVSE is powered on
- **When** evse_init() is called
- **Then** The pilot signal is connected (pilot_connected is true)

### No error flags after initialisation
**Requirement:** `REQ-IEC61851-004`

- **Given** The EVSE is powered on
- **When** evse_init() is called
- **Then** ErrorFlags is NO_ERROR

### STATE_A remains when no vehicle is connected
**Requirement:** `REQ-IEC61851-005`

- **Given** The EVSE is in STATE_A (disconnected) and ready to charge
- **When** A 12V pilot signal is received (no vehicle present)
- **Then** The state remains STATE_A

### Vehicle connection triggers STATE_A to STATE_B transition
**Requirement:** `REQ-IEC61851-006`

- **Given** The EVSE is in STATE_A, authorized, and ready to charge
- **When** A 9V pilot signal is received (vehicle connected)
- **Then** The state transitions to STATE_B (connected, not charging)

### Modem negotiation required before STATE_B when ModemStage is 0
**Requirement:** `REQ-IEC61851-007`

- **Given** The EVSE is in STATE_A with ModemStage=0 (unauthenticated modem)
- **When** A 9V pilot signal is received (vehicle connected)
- **Then** The state transitions to STATE_MODEM_REQUEST for ISO15118 negotiation

### A→B goes directly to STATE_B when modem is disabled
**Requirement:** `REQ-IEC61851-007B`

- **Given** The EVSE is in STATE_A with ModemStage=0 but ModemEnabled=false
- **When** A 9V pilot signal is received (vehicle connected)
- **Then** The state transitions directly to STATE_B (modem flow skipped)

### Unauthorized EVSE blocks STATE_A to STATE_B transition
**Requirement:** `REQ-IEC61851-008`

- **Given** The EVSE is in STATE_A with AccessStatus OFF (not authorized)
- **When** A 9V pilot signal is received (vehicle connected)
- **Then** The state remains STATE_A (transition blocked)

### Vehicle disconnect in STATE_B returns to STATE_A
**Requirement:** `REQ-IEC61851-011`

- **Given** The EVSE is in STATE_A with an active TEMP_HIGH error flag
- **Given** The EVSE is in STATE_A with ChargeDelay > 0
- **Given** The EVSE is in STATE_B (vehicle connected, not charging)
- **When** A 9V pilot signal is received (vehicle connected)
- **When** A 9V pilot signal is received (vehicle connected)
- **When** A 12V pilot signal is received (vehicle disconnected)
- **Then** The state transitions to STATE_B1 (connected, waiting due to error)
- **Then** The state transitions to STATE_B1 (connected, waiting for delay)
- **Then** The state transitions back to STATE_A (disconnected)

### Vehicle charge request after diode check triggers STATE_B to STATE_C
**Requirement:** `REQ-IEC61851-012`

- **Given** The EVSE is in STATE_B with DiodeCheck passed and sufficient current
- **When** A 6V pilot signal is sustained for 500ms (vehicle requests charge)
- **Then** The state transitions to STATE_C (charging)

### Charge request without diode check does not transition to STATE_C
**Requirement:** `REQ-IEC61851-013`

- **Given** The EVSE is in STATE_B with DiodeCheck NOT passed
- **When** A 6V pilot signal is sustained for 500ms
- **Then** The state does NOT transition to STATE_C

### PILOT_DIODE signal sets DiodeCheck flag
**Requirement:** `REQ-IEC61851-014`

- **Given** The EVSE is in STATE_B with DiodeCheck=0
- **When** A PILOT_DIODE signal is received
- **Then** DiodeCheck is set to 1

### Contactor 1 is closed when entering STATE_C
**Requirement:** `REQ-IEC61851-015`

- **Given** The EVSE transitions to STATE_C (charging)
- **When** evse_set_state is called with STATE_C
- **Then** contactor1_state is true (closed, power flowing)

### Vehicle disconnect during charging returns to STATE_A with contactors open
**Requirement:** `REQ-IEC61851-016`

- **Given** The EVSE is in STATE_C (charging)
- **When** A 12V pilot signal is received (vehicle disconnected)
- **Then** The state transitions to STATE_A and contactor1 is opened

### Vehicle disconnect from STATE_C1 returns to STATE_A
**Requirement:** `REQ-IEC61851-019`

- **Given** The EVSE is in STATE_C (charging)
- **Given** The EVSE is in STATE_C (charging)
- **Given** The EVSE is in STATE_C1 (charging suspended)
- **When** A 9V pilot signal is received (vehicle stops charge request)
- **When** PILOT_SHORT is sustained for more than 500ms (debounce period)
- **When** A 12V pilot signal is received (vehicle disconnected)
- **Then** The state transitions to STATE_B and DiodeCheck is reset to 0
- **Then** The state transitions to STATE_B
- **Then** The state transitions to STATE_A

### Vehicle disconnect from STATE_B1 returns to STATE_A
**Requirement:** `REQ-IEC61851-022`

- **Given** The EVSE is in STATE_C1 (charging suspended)
- **Given** The EVSE is in STATE_C1 with C1Timer set to 6 seconds
- **Given** The EVSE is in STATE_B1 (waiting) with pilot reconnected
- **When** A 9V pilot signal is received
- **When** The C1Timer counts down to zero via tick_1s
- **When** A 12V pilot signal is received (vehicle disconnected)
- **Then** The state transitions to STATE_B1 (waiting), not STATE_B
- **Then** The state transitions to STATE_B1 and both contactors are opened
- **Then** The state transitions to STATE_A

### Entering STATE_B1 sets a non-zero ChargeDelay
**Requirement:** `REQ-IEC61851-023`

- **Given** The EVSE is ready to charge with ChargeDelay=0
- **When** The state is set to STATE_B1
- **Then** ChargeDelay is set to a value greater than 0

### Entering STATE_A clears LESS_6A error and ChargeDelay
**Requirement:** `REQ-IEC61851-024`

- **Given** The EVSE has LESS_6A error flag set and ChargeDelay > 0
- **When** The state is set to STATE_A
- **Then** LESS_6A is cleared from ErrorFlags and ChargeDelay is set to 0

### State transitions are recorded in the transition log
**Requirement:** `REQ-IEC61851-025`

- **Given** The EVSE is ready to charge
- **When** Two state transitions occur (STATE_B then STATE_C)
- **Then** transition_count is 2 and the log contains both states in order

### Entering STATE_C1 sets PWM to off (+12V)
**Requirement:** `REQ-IEC61851-026`

- **Given** The EVSE is in STATE_C (charging)
- **When** The state is set to STATE_C1 (charging suspended)
- **Then** PWM duty is set to 1024 (off / +12V constant)

### Full charge cycle: A -> B -> C -> B -> A
**Requirement:** `REQ-IEC61851-027`

- **Given** The EVSE is in STATE_A, authorized and ready to charge
- **When** The vehicle connects (9V), requests charge (6V), stops (9V), disconnects (12V)
- **Then** The EVSE transitions A->B->C->B->A with correct contactor states

### Vehicle disconnect during ACTSTART is NOT handled in tick_10ms
**Requirement:** `REQ-IEC61851-028`

- **Given** The EVSE is in STATE_ACTSTART (activation mode)
- **When** A 12V pilot signal is received (vehicle disconnected)
- **Then** The state stays ACTSTART (original behavior: no pilot check in ACTSTART,

### ActivationMode=0 triggers STATE_ACTSTART on pilot detection in STATE_B
**Requirement:** `REQ-IEC61851-029`

- **Given** The EVSE is in STATE_B with ActivationMode=0
- **When** A 9V pilot signal is received
- **Then** The state transitions to STATE_ACTSTART with ActivationTimer set to 3

### ActivationMode=255 (always active) does not count down
**Requirement:** `REQ-IEC61851-031`

- **Given** The EVSE has ActivationMode set to 5
- **Given** The EVSE has ActivationMode set to 255
- **When** One second tick occurs
- **When** One second tick occurs
- **Then** ActivationMode decrements to 4
- **Then** ActivationMode remains at 255

### STATE_ACTSTART returns to STATE_B when ActivationTimer expires
**Requirement:** `REQ-IEC61851-032`

- **Given** The EVSE is in STATE_ACTSTART with ActivationTimer=0 (expired)
- **When** A non-12V pilot signal is received
- **Then** The state transitions to STATE_B and ActivationMode is set to 255

### STATE_B re-entry sets Switching_Phases_C2 flag instead of direct phase change
**Requirement:** `REQ-PHASE-002`

- **Given** The EVSE is in STATE_COMM_B_OK (master approved B transition)
- **Given** The EVSE is in STATE_COMM_C_OK (master approved C transition)
- **Given** The EVSE is configured as a node (LoadBl=2)
- **Given** The EVSE is in STATE_A with EnableC2=ALWAYS_OFF and 3 phases configured
- **Given** The EVSE is already in STATE_B with EnableC2=ALWAYS_OFF and 3 phases configured
- **When** A 9V pilot signal is received
- **When** A 6V pilot signal is received
- **When** A 9V pilot signal is received (vehicle connected)
- **When** The state is set to STATE_B
- **When** The state is set to STATE_B again
- **Then** The state transitions to STATE_B and ActivationMode is set to 30
- **Then** The state transitions to STATE_C (charging)
- **Then** The state transitions to STATE_COMM_B (requesting master permission)
- **Then** Nr_Of_Phases_Charging is set directly to 1 (single phase)
- **Then** Switching_Phases_C2 is set to GOING_TO_SWITCH_1P (deferred switch)

### STATE_B entry does NOT set pilot_connected when modem disabled
**Requirement:** `REQ-IEC61851-M3`

- **Given** ModemEnabled=false, EVSE transitions A→B
- **When** evse_set_state is called with STATE_B
- **Then** pilot_connected is NOT explicitly set by STATE_B entry

### STATE_B entry DOES set pilot_connected when modem enabled
**Requirement:** `REQ-IEC61851-M3B`

- **Given** ModemEnabled=true, EVSE transitions to STATE_B
- **When** evse_set_state is called with STATE_B
- **Then** pilot_connected is set to true

</details>

---

## 10ms Tick Processing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-TICK10-001` | Pilot disconnect guard ignores 9V signal while active | `test_pilot_disconnect_guards_reading` | `test_tick_10ms.c:1` |
| `REQ-TICK10-002` | Pilot disconnect flag clears when timer reaches zero | `test_pilot_disconnect_clears_on_timer_zero` | `test_tick_10ms.c:47` |
| `REQ-TICK10-003` | RFID reader type 1 starts access lock timer | `test_rfid_reader_1_starts_access_timer` | `test_tick_10ms.c:66` |
| `REQ-TICK10-004` | MaxCapacity limits charge current when below MaxCurrent | `test_maxcapacity_limits_charge_current` | `test_tick_10ms.c:85` |
| `REQ-TICK10-005` | MaxCapacity at or above MaxCurrent falls back to MinCurrent | `test_maxcapacity_default_uses_mincurrent` | `test_tick_10ms.c:101` |
| `REQ-TICK10-006` | LESS_6A error flag set when insufficient current available in Smart mode | `test_less_6a_when_no_current_available` | `test_tick_10ms.c:120` |
| `REQ-TICK10-007` | STATE_B with 6V pilot increments state timer for debounce | `test_b_6v_increments_state_timer` | `test_tick_10ms.c:144` |
| `REQ-TICK10-008` | STATE_B with 9V pilot resets the state timer | `test_b_9v_resets_state_timer` | `test_tick_10ms.c:161` |
| `REQ-TICK10-009` | STATE_B to STATE_C transition requires 55 consecutive 6V ticks | `test_b_to_c_debounce_threshold` | `test_tick_10ms.c:178` |
| `REQ-TICK10-010` | STATE_B to STATE_C transition is blocked when errors are present | `test_b_to_c_requires_diode_and_no_errors` | `test_tick_10ms.c:201` |
| `REQ-TICK10-011` | STATE_C transitions to STATE_B after sustained pilot short debounce | `test_c_short_debounce` | `test_tick_10ms.c:222` |
| `REQ-TICK10-012` | STATE_C stays in STATE_C on 6V pilot and resets state timer | `test_c_6v_no_transition` | `test_tick_10ms.c:243` |
| `REQ-TICK10-013` | COMM_B state does not trigger A-to-B transition logic on 9V pilot | `test_comm_b_stays_on_9v` | `test_tick_10ms.c:262` |
| `REQ-TICK10-014` | Node transitions from STATE_B to STATE_COMM_C instead of STATE_C | `test_node_b_to_comm_c` | `test_tick_10ms.c:286` |
| `REQ-TICK10-015` | A-to-B transition sets BalancedMax from MaxCapacity | `test_a_to_b_sets_balanced_max` | `test_tick_10ms.c:309` |
| `REQ-TICK10-016` | A-to-B transition does NOT set extra PWM duty (F3 fidelity fix) | `test_a_to_b_no_extra_pwm` | `test_tick_10ms.c:324` |
| `REQ-TICK10-017` | A-to-B transition initializes ActivationMode to 30 and clears AccessTimer | `test_a_to_b_sets_activation_mode_30` | `test_tick_10ms.c:343` |
| `REQ-TICK10-018` | STATE_B1 remains in B1 when errors are present on 9V pilot | `test_b1_with_errors_stays_b1_on_9v` | `test_tick_10ms.c:360` |
| `REQ-TICK10-019` | Modem states are NOT handled in tick_10ms (matches original Timer10ms) | `test_modem_states_to_a_on_12v` | `test_tick_10ms.c:381` |
| `REQ-TICK10-020` | ACTSTART transitions to STATE_B when activation timer expires | `test_actstart_to_b_when_timer_zero` | `test_tick_10ms.c:403` |

<details>
<summary>Detailed steps (20 scenarios)</summary>

### Pilot disconnect guard ignores 9V signal while active
**Requirement:** `REQ-TICK10-001`

- **Given** EVSE is ready to charge with PilotDisconnected=true and PilotDisconnectTime > 0
- **When** A 9V pilot signal (vehicle connected) is received during a 10ms tick
- **Then** The EVSE remains in STATE_A because the disconnect guard suppresses the pilot reading

### Pilot disconnect flag clears when timer reaches zero
**Requirement:** `REQ-TICK10-002`

- **Given** EVSE is ready to charge with PilotDisconnected=true and PilotDisconnectTime=0
- **When** A 9V pilot signal is received during a 10ms tick
- **Then** PilotDisconnected is cleared to false and pilot_connected is set to true

### RFID reader type 1 starts access lock timer
**Requirement:** `REQ-TICK10-003`

- **Given** EVSE is ready to charge with RFIDReader=1, AccessTimer=0, and AccessStatus=ON
- **When** A 12V pilot signal (no vehicle) is received during a 10ms tick
- **Then** AccessTimer is set to RFIDLOCKTIME to begin the RFID lock countdown

### MaxCapacity limits charge current when below MaxCurrent
**Requirement:** `REQ-TICK10-004`

- **Given** EVSE is ready to charge with MaxCapacity=8A which is less than MaxCurrent=13A
- **When** A 9V pilot signal triggers the A-to-B transition during a 10ms tick
- **Then** ChargeCurrent is set to 80 deciamps (MaxCapacity * 10)

### MaxCapacity at or above MaxCurrent falls back to MinCurrent
**Requirement:** `REQ-TICK10-005`

- **Given** EVSE is ready to charge with MaxCapacity=16A >= MaxCurrent=13A and MinCurrent=6A
- **When** A 9V pilot signal triggers the A-to-B transition during a 10ms tick
- **Then** ChargeCurrent is set to 60 deciamps (MinCurrent * 10) as the default starting point

### LESS_6A error flag set when insufficient current available in Smart mode
**Requirement:** `REQ-TICK10-006`

- **Given** EVSE is in Smart mode standalone with very low MaxMains=2A and MainsMeterImeasured=200 (overloaded)
- **When** A 9V pilot signal (vehicle connected) is received during a 10ms tick
- **Then** The LESS_6A error flag is set because available current is below MinCurrent

### STATE_B with 6V pilot increments state timer for debounce
**Requirement:** `REQ-TICK10-007`

- **Given** EVSE is in STATE_B with DiodeCheck=1 and StateTimer=0
- **When** A 6V pilot signal (vehicle requesting charge) is received during a 10ms tick
- **Then** StateTimer increments to 1, counting toward the B-to-C debounce threshold

### STATE_B with 9V pilot resets the state timer
**Requirement:** `REQ-TICK10-008`

- **Given** EVSE is in STATE_B with StateTimer=30 (partially debounced)
- **When** A 9V pilot signal (vehicle connected but not requesting charge) is received
- **Then** StateTimer is reset to 0, canceling the B-to-C debounce countdown

### STATE_B to STATE_C transition requires 55 consecutive 6V ticks
**Requirement:** `REQ-TICK10-009`

- **Given** EVSE is in STATE_B with DiodeCheck=1 and ChargeCurrent at MaxCurrent
- **When** 50 consecutive 6V pilot ticks are received (below threshold) then 5 more (reaching 55)
- **Then** The EVSE does not transition at 50 ticks but transitions to STATE_C at 55 ticks

### STATE_B to STATE_C transition is blocked when errors are present
**Requirement:** `REQ-TICK10-010`

- **Given** EVSE is in STATE_B with DiodeCheck=1 but ErrorFlags contains TEMP_HIGH
- **When** 55 consecutive 6V pilot ticks are received (past debounce threshold)
- **Then** The EVSE does not transition to STATE_C because an error condition is active

### STATE_C transitions to STATE_B after sustained pilot short debounce
**Requirement:** `REQ-TICK10-011`

- **Given** EVSE is in STATE_C (actively charging)
- **When** Fewer than 50 PILOT_SHORT ticks are received followed by enough to exceed 50 total
- **Then** The EVSE stays in STATE_C below 50 ticks but transitions to STATE_B after 50 consecutive short ticks

### STATE_C stays in STATE_C on 6V pilot and resets state timer
**Requirement:** `REQ-TICK10-012`

- **Given** EVSE is in STATE_C with StateTimer=20
- **When** A 6V pilot signal is received during a 10ms tick
- **Then** The EVSE remains in STATE_C and StateTimer is reset to 0

### COMM_B state does not trigger A-to-B transition logic on 9V pilot
**Requirement:** `REQ-TICK10-013`

- **Given** EVSE is a node (LoadBl=2) in STATE_COMM_B waiting for master confirmation
- **When** A 9V pilot signal is received during a 10ms tick
- **Then** The EVSE does not transition to STATE_B because COMM_B bypasses the A-to-B path

### Node transitions from STATE_B to STATE_COMM_C instead of STATE_C
**Requirement:** `REQ-TICK10-014`

- **Given** EVSE is a node (LoadBl=2) in STATE_B with DiodeCheck=1 and sufficient charge current
- **When** 55 consecutive 6V pilot ticks are received (past debounce threshold)
- **Then** The EVSE transitions to STATE_COMM_C (waiting for master to confirm charge start)

### A-to-B transition sets BalancedMax from MaxCapacity
**Requirement:** `REQ-TICK10-015`

- **Given** EVSE is ready to charge in standalone mode with MaxCapacity=10A
- **When** A 9V pilot signal triggers the A-to-B transition
- **Then** BalancedMax[0] is set to 100 deciamps (MaxCapacity * 10)

### A-to-B transition does NOT set extra PWM duty (F3 fidelity fix)
**Requirement:** `REQ-TICK10-016`

- **Given** EVSE is ready to charge in standalone mode
- **When** A 9V pilot signal triggers the A-to-B transition
- **Then** PWM duty remains 1024 (from STATE_A entry); module does not set PWM on A→B,

### A-to-B transition initializes ActivationMode to 30 and clears AccessTimer
**Requirement:** `REQ-TICK10-017`

- **Given** EVSE is ready to charge in standalone mode
- **When** A 9V pilot signal triggers the A-to-B transition
- **Then** ActivationMode is set to 30 (countdown for activation) and AccessTimer is cleared to 0

### STATE_B1 remains in B1 when errors are present on 9V pilot
**Requirement:** `REQ-TICK10-018`

- **Given** EVSE is in STATE_B1 (connected but waiting) with TEMP_HIGH error flag set
- **When** A 9V pilot signal is received during a 10ms tick
- **Then** The EVSE stays in STATE_B1 because errors prevent transition to charging states

### Modem states are NOT handled in tick_10ms (matches original Timer10ms)
**Requirement:** `REQ-TICK10-019`

- **Given** EVSE is in one of the modem states (REQUEST, WAIT, DONE, or DENIED)
- **When** A 12V pilot signal (no vehicle) is received during a 10ms tick
- **Then** The EVSE stays in its modem state (modem is managed solely by tick_1s)

### ACTSTART transitions to STATE_B when activation timer expires
**Requirement:** `REQ-TICK10-020`

- **Given** EVSE is in STATE_ACTSTART with ActivationTimer=0 (timer expired)
- **When** A 9V pilot signal is received during a 10ms tick
- **Then** The EVSE transitions to STATE_B and ActivationMode is set to 255 (disabled)

</details>

---

## 1-Second Tick Processing

| Requirement | Scenario | Test Function | Source |
|-------------|----------|---------------|--------|
| `REQ-TICK1S-001` | SolarStopTimer decrements by one each second | `test_solar_stop_timer_countdown` | `test_tick_1s.c:1` |
| `REQ-TICK1S-002` | SolarStopTimer expiry triggers STATE_C to STATE_C1 transition | `test_solar_stop_timer_triggers_c1` | `test_tick_1s.c:39` |
| `REQ-TICK1S-003` | SolarStopTimer expiry does not trigger C1 when not in STATE_C | `test_solar_stop_timer_not_in_c` | `test_tick_1s.c:62` |
| `REQ-TICK1S-004` | Node charge timers increment when node is in STATE_C | `test_node_charge_timer_increments` | `test_tick_1s.c:86` |
| `REQ-TICK1S-005` | Node charge timer resets when node is not in STATE_C | `test_node_charge_timer_resets` | `test_tick_1s.c:104` |
| `REQ-TICK1S-006` | Multiple node charge timers update independently based on each node state | `test_multi_node_timers` | `test_tick_1s.c:120` |
| `REQ-TICK1S-007` | MainsMeter timeout sets CT_NOCOMM error on node | `test_mains_meter_timeout_node` | `test_tick_1s.c:144` |
| `REQ-TICK1S-008` | MainsMeter timeout counter decrements on node each second | `test_mains_meter_node_countdown` | `test_tick_1s.c:161` |
| `REQ-TICK1S-009` | LESS_6A error forces STATE_C to STATE_C1 via power unavailable | `test_less_6a_enforces_power_unavailable` | `test_tick_1s.c:179` |
| `REQ-TICK1S-010` | LESS_6A error sets ChargeDelay to CHARGEDELAY (60 seconds) | `test_less_6a_sets_charge_delay` | `test_tick_1s.c:201` |
| `REQ-TICK1S-011` | MaxSumMains timer decrements each second | `test_maxsummains_timer_countdown` | `test_tick_1s.c:226` |
| `REQ-TICK1S-012` | MaxSumMains timer expiry triggers STATE_C to STATE_C1 transition | `test_maxsummains_timer_triggers_c1` | `test_tick_1s.c:241` |
| `REQ-TICK1S-013` | AccessTimer is cleared when EVSE is not in STATE_A | `test_access_timer_cleared_not_in_a` | `test_tick_1s.c:265` |
| `REQ-TICK1S-014` | EV meter timeout counter decrements each second | `test_ev_meter_timeout_countdown` | `test_tick_1s.c:283` |
| `REQ-TICK1S-015` | EV meter timeout reaching zero sets EV_NOCOMM error | `test_ev_meter_timeout_triggers_error` | `test_tick_1s.c:299` |
| `REQ-TICK1S-016` | Activation timer decrements each second | `test_activation_timer_countdown` | `test_tick_1s.c:319` |
| `REQ-TICK1S-017` | ActivationMode counter decrements each second | `test_activation_mode_countdown` | `test_tick_1s.c:336` |
| `REQ-TICK1S-018` | ChargeDelay is overridden by LESS_6A enforcement after decrementing to zero | `test_charge_delay_overridden_by_less_6a` | `test_tick_1s.c:353` |
| `REQ-TICK1S-F2A` | LESS_6A resets ChargeDelay to CHARGEDELAY every tick, even when non-zero | `test_less_6a_resets_charge_delay_every_tick` | `test_tick_1s.c:378` |
| `REQ-TICK1S-F2B` | LESS_6A prevents ChargeDelay from ever reaching zero | `test_less_6a_charge_delay_never_reaches_zero` | `test_tick_1s.c:400` |
| `REQ-TICK1S-020` | Re-set LESS_6A during solar-mode ChargeDelay countdown when current becomes unavailable | `test_charge_delay_resets_less6a_when_solar_lost` | `test_tick_1s.c:424` |
| `REQ-TICK1S-021` | ChargeDelay re-set does NOT fire when solar is still available | `test_charge_delay_leaves_less6a_clear_when_solar_present` | `test_tick_1s.c:447` |
| `REQ-TICK1S-022` | ChargeDelay re-set does NOT fire in non-solar mode | `test_charge_delay_less6a_reset_solar_only` | `test_tick_1s.c:472` |

<details>
<summary>Detailed steps (23 scenarios)</summary>

### SolarStopTimer decrements by one each second
**Requirement:** `REQ-TICK1S-001`

- **Given** EVSE is in normal mode with SolarStopTimer=3
- **When** A 1-second tick occurs
- **Then** SolarStopTimer decrements to 2

### SolarStopTimer expiry triggers STATE_C to STATE_C1 transition
**Requirement:** `REQ-TICK1S-002`

- **Given** EVSE is in Smart mode in STATE_C with high mains load and SolarStopTimer=1
- **When** A 1-second tick decrements SolarStopTimer to 0
- **Then** The EVSE transitions to STATE_C1 (charging suspended) and LESS_6A error flag is set

### SolarStopTimer expiry does not trigger C1 when not in STATE_C
**Requirement:** `REQ-TICK1S-003`

- **Given** EVSE is in Smart mode in STATE_B (not charging) with SolarStopTimer=1
- **When** A 1-second tick decrements SolarStopTimer to 0
- **Then** The EVSE does not transition to STATE_C1 but LESS_6A error flag is still set

### Node charge timers increment when node is in STATE_C
**Requirement:** `REQ-TICK1S-004`

- **Given** Node 0 is in STATE_C with IntTimer=5 and Timer=100
- **When** A 1-second tick occurs
- **Then** IntTimer increments to 6 and Timer increments to 101

### Node charge timer resets when node is not in STATE_C
**Requirement:** `REQ-TICK1S-005`

- **Given** Node 0 is in STATE_B (connected but not charging) with IntTimer=20
- **When** A 1-second tick occurs
- **Then** IntTimer is reset to 0

### Multiple node charge timers update independently based on each node state
**Requirement:** `REQ-TICK1S-006`

- **Given** Nodes 0 and 2 are in STATE_C (charging) and node 1 is in STATE_B, all with IntTimer=10
- **When** A 1-second tick occurs
- **Then** Nodes 0 and 2 increment to 11 while node 1 resets to 0

### MainsMeter timeout sets CT_NOCOMM error on node
**Requirement:** `REQ-TICK1S-007`

- **Given** EVSE is a node (LoadBl=2) with MainsMeterTimeout=0
- **When** A 1-second tick occurs
- **Then** CT_NOCOMM error flag is set indicating mains meter communication lost

### MainsMeter timeout counter decrements on node each second
**Requirement:** `REQ-TICK1S-008`

- **Given** EVSE is a node (LoadBl=3) with MainsMeterTimeout=5
- **When** A 1-second tick occurs
- **Then** MainsMeterTimeout decrements to 4

### LESS_6A error forces STATE_C to STATE_C1 via power unavailable
**Requirement:** `REQ-TICK1S-009`

- **Given** EVSE is in Smart mode in STATE_C with LESS_6A error flag set and high mains load
- **When** A 1-second tick occurs
- **Then** The EVSE transitions to STATE_C1 (charging suspended due to insufficient power)

### LESS_6A error sets ChargeDelay to CHARGEDELAY (60 seconds)
**Requirement:** `REQ-TICK1S-010`

- **Given** EVSE is in Smart mode in STATE_B1 with LESS_6A error flag set and ChargeDelay=0
- **When** A 1-second tick occurs
- **Then** ChargeDelay is set to CHARGEDELAY (60 seconds) to prevent rapid retry

### MaxSumMains timer decrements each second
**Requirement:** `REQ-TICK1S-011`

- **Given** EVSE has MaxSumMainsTimer=5
- **When** A 1-second tick occurs
- **Then** MaxSumMainsTimer decrements to 4

### MaxSumMains timer expiry triggers STATE_C to STATE_C1 transition
**Requirement:** `REQ-TICK1S-012`

- **Given** EVSE is in Smart mode in STATE_C with high mains load and MaxSumMainsTimer=1
- **When** A 1-second tick decrements MaxSumMainsTimer to 0
- **Then** The EVSE transitions to STATE_C1 and LESS_6A error flag is set

### AccessTimer is cleared when EVSE is not in STATE_A
**Requirement:** `REQ-TICK1S-013`

- **Given** EVSE is in STATE_B with AccessTimer=30
- **When** A 1-second tick occurs
- **Then** AccessTimer is cleared to 0 because it is only relevant in STATE_A

### EV meter timeout counter decrements each second
**Requirement:** `REQ-TICK1S-014`

- **Given** EVMeterType=1 (meter installed) with EVMeterTimeout=5
- **When** A 1-second tick occurs
- **Then** EVMeterTimeout decrements to 4

### EV meter timeout reaching zero sets EV_NOCOMM error
**Requirement:** `REQ-TICK1S-015`

- **Given** EVMeterType=1 with EVMeterTimeout=0 and no existing errors in Smart mode
- **When** A 1-second tick occurs
- **Then** EV_NOCOMM error flag is set indicating EV meter communication lost

### Activation timer decrements each second
**Requirement:** `REQ-TICK1S-016`

- **Given** EVSE has ActivationTimer=3
- **When** A 1-second tick occurs
- **Then** ActivationTimer decrements to 2

### ActivationMode counter decrements each second
**Requirement:** `REQ-TICK1S-017`

- **Given** EVSE has ActivationMode=10
- **When** A 1-second tick occurs
- **Then** ActivationMode decrements to 9

### ChargeDelay is overridden by LESS_6A enforcement after decrementing to zero
**Requirement:** `REQ-TICK1S-018`

- **Given** EVSE is in Smart mode in STATE_B1 with ChargeDelay=1 and LESS_6A error flag set
- **When** A 1-second tick decrements ChargeDelay to 0 then LESS_6A enforcement re-sets it
- **Then** ChargeDelay is set back to CHARGEDELAY (60 seconds) by LESS_6A enforcement

### LESS_6A resets ChargeDelay to CHARGEDELAY every tick, even when non-zero
**Requirement:** `REQ-TICK1S-F2A`

- **Given** EVSE is in Smart mode in STATE_B1 with LESS_6A set and ChargeDelay=30
- **When** A 1-second tick occurs
- **Then** ChargeDelay is reset to CHARGEDELAY (60), not decremented to 29

### LESS_6A prevents ChargeDelay from ever reaching zero
**Requirement:** `REQ-TICK1S-F2B`

- **Given** EVSE is in Smart mode in STATE_B1 with LESS_6A set and ChargeDelay=1
- **When** A 1-second tick occurs (ChargeDelay decrements to 0, then LESS_6A resets it)
- **Then** ChargeDelay is CHARGEDELAY (60), not 0

### Re-set LESS_6A during solar-mode ChargeDelay countdown when current becomes unavailable
**Requirement:** `REQ-TICK1S-020`

- **Given** Solar mode, ChargeDelay=30, LESS_6A cleared, current NOT available (high mains load)
- **When** A 1-second tick occurs
- **Then** LESS_6A is re-set so the countdown restarts on the next cycle (prevents charging-without-solar oscillation)

### ChargeDelay re-set does NOT fire when solar is still available
**Requirement:** `REQ-TICK1S-021`

- **Given** Solar mode, ChargeDelay=30, LESS_6A cleared, current IS available (solar surplus)
- **When** A 1-second tick occurs
- **Then** LESS_6A remains clear — no spurious re-set

### ChargeDelay re-set does NOT fire in non-solar mode
**Requirement:** `REQ-TICK1S-022`

- **Given** Smart mode, ChargeDelay=30, LESS_6A cleared, current NOT available
- **When** A 1-second tick occurs
- **Then** LESS_6A remains clear — the re-set logic is solar-only

</details>

---

*Generated by extract_traceability.py | SmartEVSE-3 Specification by Example*