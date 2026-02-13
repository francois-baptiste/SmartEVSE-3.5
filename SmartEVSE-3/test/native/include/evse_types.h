#ifndef EVSE_TYPES_H
#define EVSE_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define NR_EVSES 8

// ---- States (from main_c.h) ----
#define STATE_A             0   // Vehicle not connected
#define STATE_B             1   // Vehicle connected / not ready to accept energy
#define STATE_C             2   // Vehicle connected / ready to accept energy
#define STATE_D             3   // Vehicle connected / ventilation required (unused)
#define STATE_COMM_B        4   // Node requests A->B (set by node)
#define STATE_COMM_B_OK     5   // Master approves A->B (set by master)
#define STATE_COMM_C        6   // Node requests B->C (set by node)
#define STATE_COMM_C_OK     7   // Master approves B->C (set by master)
#define STATE_ACTSTART      8   // Activation mode in progress
#define STATE_B1            9   // Vehicle connected / EVSE not ready: no PWM
#define STATE_C1           10   // Vehicle charging / EVSE stopping: no PWM
#define STATE_MODEM_REQUEST 11  // Requesting ISO15118, 0% duty
#define STATE_MODEM_WAIT   12   // Requesting ISO15118, 5% duty
#define STATE_MODEM_DONE   13   // Modem communication successful
#define STATE_MODEM_DENIED 14   // Modem access denied (EVCCID mismatch)
#define NOSTATE           255

// ---- Modes (from main.h) ----
#define MODE_NORMAL  0
#define MODE_SMART   1
#define MODE_SOLAR   2

// ---- Error flags (from main_c.h) ----
#define NO_ERROR     0
#define LESS_6A      1
#define CT_NOCOMM    2
#define TEMP_HIGH    4
#define EV_NOCOMM    8
#define RCM_TRIPPED 16
#define RCM_TEST    32
#define Test_IO     64
#define BL_FLASH   128

// ---- PWM constants ----
#define PWM_5   50
#define PWM_95 950
#define PWM_96 960
#define PWM_100 1000

// ---- Pilot voltage levels (as returned by pilot reading) ----
#define PILOT_12V   12
#define PILOT_9V     9
#define PILOT_6V     6
#define PILOT_DIODE  5
#define PILOT_SHORT  3
#define PILOT_NOK    1

// ---- Phase switching states (from main.h Switch_Phase_t) ----
#define NO_SWITCH             0
#define GOING_TO_SWITCH_1P    1
#define GOING_TO_SWITCH_3P    2

// ---- Access status (from main.h) ----
typedef enum { OFF = 0, ON = 1, PAUSE = 2 } AccessStatus_t;

// ---- EnableC2 values (from main.h) ----
typedef enum {
    NOT_PRESENT = 0,
    ALWAYS_OFF  = 1,
    SOLAR_OFF   = 2,
    AUTO_C2     = 3,
    ALWAYS_ON   = 4
} EnableC2_t;

// ---- Default config values (from main.h) ----
#define MAX_MAINS          25
#define MAX_CURRENT        13
#define MIN_CURRENT         6
#define MAX_CIRCUIT        16
#define MAX_SUMMAINS        0
#define MAX_SUMMAINSTIME    0
#define START_CURRENT       4
#define STOP_TIME          10
#define IMPORT_CURRENT      0
#define MAX_TEMPERATURE    65
#define CHARGEDELAY        60
#define COMM_TIMEOUT       11
#define COMM_EVTIMEOUT     64
#define SOLARSTARTTIME     40
#define RFIDLOCKTIME       60
#define GRID_RELAY_MAX_SUMMAINS 18

// ---- Node info (from main.cpp) ----
typedef struct {
    uint8_t  Online;
    uint8_t  ConfigChanged;
    uint8_t  EVMeter;
    uint8_t  EVAddress;
    uint8_t  MinCurrent;
    uint8_t  Phases;
    uint32_t Timer;
    uint32_t IntTimer;
    uint16_t SolarTimer;
    uint8_t  Mode;
} Node_t;

// ---- HAL (Hardware Abstraction Layer) ----
// All hardware interactions go through these function pointers
typedef struct evse_hal {
    void (*set_cp_duty)(uint32_t duty_cycle);
    void (*contactor1)(bool on);
    void (*contactor2)(bool on);
    void (*set_pilot)(bool connected);  // true=connected, false=disconnected
    void (*actuator_lock)(void);
    void (*actuator_unlock)(void);
    void (*actuator_off)(void);
} evse_hal_t;

// ---- The full EVSE state context (replaces ALL globals) ----
typedef struct {
    // --- Core state ---
    uint8_t State;

    // --- Operating config ---
    uint8_t Mode;       // MODE_NORMAL / MODE_SMART / MODE_SOLAR
    uint8_t LoadBl;     // 0=Disabled, 1=Master, 2-8=Node

    // --- Authorization ---
    AccessStatus_t AccessStatus;
    uint8_t RFIDReader;
    bool    OcppMode;
    float   OcppCurrentLimit;
    bool    CPDutyOverride;

    // --- Power limits ---
    uint16_t MaxMains;
    uint16_t MaxCurrent;
    uint16_t MinCurrent;
    uint16_t MaxCircuit;
    uint16_t MaxCapacity;
    uint16_t MaxSumMains;
    uint8_t  MaxSumMainsTime;
    uint16_t GridRelayMaxSumMains;
    bool     GridRelayOpen;

    // --- Current distribution ---
    uint16_t Balanced[NR_EVSES];
    uint16_t BalancedMax[NR_EVSES];
    uint8_t  BalancedState[NR_EVSES];
    uint16_t BalancedError[NR_EVSES];
    uint16_t ChargeCurrent;
    int32_t  IsetBalanced;
    uint16_t OverrideCurrent;

    // --- Meter readings (simulated inputs) ---
    int16_t  Isum;
    int16_t  MainsMeterIrms[3];
    int16_t  MainsMeterImeasured;
    int16_t  EVMeterIrms[3];
    int16_t  EVMeterImeasured;
    uint8_t  MainsMeterType;
    uint8_t  EVMeterType;
    uint8_t  MainsMeterTimeout;
    uint8_t  EVMeterTimeout;

    // --- Error handling ---
    uint8_t ErrorFlags;
    uint8_t ChargeDelay;
    uint8_t NoCurrent;

    // --- Timers ---
    uint16_t SolarStopTimer;
    uint16_t MaxSumMainsTimer;
    uint8_t  StateTimer;
    uint8_t  AccessTimer;
    uint8_t  C1Timer;

    // --- Phase switching ---
    EnableC2_t EnableC2;
    uint8_t Nr_Of_Phases_Charging;
    uint8_t Switching_Phases_C2;
    bool    phasesLastUpdateFlag;   // Set when new mains meter measurements arrive
    bool    LimitedByMaxSumMains;   // Tracks when MaxSumMains is the limiting factor

    // --- Modem ---
    uint8_t ModemStage;
    uint8_t ToModemWaitStateTimer;
    uint8_t ToModemDoneStateTimer;
    uint8_t LeaveModemDoneStateTimer;
    uint8_t LeaveModemDeniedStateTimer;
    int8_t  DisconnectTimeCounter;       // Modem disconnect recovery (-1=disabled)
    char    RequiredEVCCID[32];          // Required EV CC ID for modem auth
    char    EVCCID[32];                  // Actual EV CC ID received from modem

    // --- Solar config ---
    uint16_t StartCurrent;
    uint16_t StopTime;
    uint16_t ImportCurrent;

    // --- Safety ---
    int8_t  TempEVSE;
    uint16_t maxTemp;
    uint8_t RCmon;
    bool    RCMFault;

    // --- Misc ---
    uint8_t DiodeCheck;
    bool    PilotDisconnected;
    uint8_t PilotDisconnectTime;
    uint8_t ActivationMode;
    uint8_t ActivationTimer;

    // --- Node tracking ---
    Node_t Node[NR_EVSES];

    // --- HAL ---
    evse_hal_t hal;

    // --- Test instrumentation (for assertions) ---
    uint32_t last_pwm_duty;
    bool     contactor1_state;
    bool     contactor2_state;
    bool     pilot_connected;
    int      transition_count;
    uint8_t  transition_log[64];
} evse_ctx_t;

#endif // EVSE_TYPES_H
