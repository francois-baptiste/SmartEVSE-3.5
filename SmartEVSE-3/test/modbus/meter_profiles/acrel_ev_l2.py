"""Acrel ADL400-D Phase B (L2) only energy meter profile (EV meter).

EMConfig[] index 20 (EM_ACREL_EV_L2). FC3 (holding registers), big-endian HBF_HWF.

This profile reads ONLY the Phase B (L2) registers -- Ib, Ub, Pb, Eb -- so that
when used as the EV meter, load balancing tracks just the EV charger's own
draw on its single connected phase, ignoring L1/L3 on the shared 3-phase meter.

Mixed-width register map: voltage/current are 16-bit (base DATA_TYPE), but
power/energy are 32-bit despite the meter's base datatype -- the same
technique already used for SolarEdge/Sinotimer (see meter.cpp
receivePowerMeasurement/receiveEnergyMeasurement explicit INT32 overrides).
Current is unsigned magnitude; direction is recovered from the (also 32-bit)
power register's sign, cached across a separate poll since Ib (101) and Pb
(358) are too far apart to read in one Modbus transaction.

Test vector convention (matching abb_b23.py/sinotimer.py): every *_value
field is the RAW register integer as encoded on the wire for that quantity's
datatype/divisor -- e.g. 16.00A at IDivisor=2 is stored as 1600, not 16.0.
"""

METER_TYPE = 20
METER_NAME = "Acrel ADL400-D EV L2"
ENDIANNESS = "HBF_HWF"
FUNCTION_CODE = 3
DATA_TYPE = "INT16"          # base datatype: voltage + current

# From EMConfig[20]: URegister=0x62, UDivisor=1
#                    IRegister=0x65, IDivisor=2
#                    PRegister=0x166, PDivisor=0  (32-bit override)
#                    ERegister=0x89, EDivisor=2   (32-bit override)
#                    ERegister_Exp=0 (no export register)
REGISTERS = {
    'voltage_l2':    0x62,   # 98 -- Phase B voltage (unused by firmware today, see meter.h)
    'current_l1':    0x65,   # 101 -- Phase B (L2) current; only "phase" this profile reads
    'power_total':   0x166,  # 358 -- Phase B power, 32-bit
    'energy_import': 0x89,   # 137 -- Phase B energy, 32-bit
    'energy_export': 0,      # not supported on this profile
}

U_DIVISOR = 1    # 0.1V resolution
I_DIVISOR = 2    # 0.01A resolution
P_DIVISOR = 0    # 1W resolution
E_DIVISOR = 2    # 0.01kWh resolution
E_DIVISOR_EXP = 0

# Power and Energy are 32-bit on the wire despite DATA_TYPE == 'INT16'.
POWER_DATA_TYPE = 'INT32'
ENERGY_DATA_TYPE = 'INT32'

IS_3PHASE = False
PHASE_LABEL = 'L2'   # physically Phase B, not L1 -- documented for clarity only

TEST_VECTORS = [
    {
        'name': 'nominal_16A',
        'description': 'Phase B 16A charging, values in 0.01A/0.01kWh units',
        'current_values': [1600],       # 16.00A
        'power_value': 3680,            # 3680W (PDivisor=0)
        'energy_import_value': 56789,   # 567.89 kWh (EDivisor=2)
        'energy_export_value': 0,
        'expected_current_mA': [16000, 0, 0],
        'expected_power_W': 3680,
        'expected_energy_import_Wh': 567890,
        'expected_energy_export_Wh': 0,
    },
    {
        'name': 'minimum_6A',
        'description': 'Phase B 6A minimum charge',
        'current_values': [600],        # 6.00A
        'power_value': 1380,
        'energy_import_value': 1,       # 0.01 kWh
        'energy_export_value': 0,
        'expected_current_mA': [6000, 0, 0],
        'expected_power_W': 1380,
        'expected_energy_import_Wh': 10,
        'expected_energy_export_Wh': 0,
    },
    {
        'name': 'standby_zero',
        'description': 'No load',
        'current_values': [0],
        'power_value': 0,
        'energy_import_value': 10000,   # 100.00 kWh
        'energy_export_value': 0,
        'expected_current_mA': [0, 0, 0],
        'expected_power_W': 0,
        'expected_energy_import_Wh': 100000,
        'expected_energy_export_Wh': 0,
    },
]
