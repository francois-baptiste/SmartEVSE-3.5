"""Acrel ADL400-D 3-phase mains meter profile.

EMConfig[] index 21 (EM_ACREL_MAINS). FC3 (holding registers), big-endian HBF_HWF.

Reads Total Power/Energy plus all three phase currents (L1/L2/L3) for dynamic
load balancing. Current registers (100/101/102) satisfy the standard INT16
3-phase "+1/+2" offset convention (see test_phase_mapping.py /
test_register_maps.py TestPhaseOffsetConsistency), so no per-meter request
special-case is needed for the current read itself.

Mixed-width register map: current is 16-bit (base DATA_TYPE), but Total
Power/Energy are 32-bit despite the base datatype -- same technique as
SolarEdge/Sinotimer. Current is unsigned magnitude; direction is recovered
from a per-phase active power block (Pa=356, Pb=358, Pc=360, Total=362, all
32-bit) polled separately, since it sits ~260 registers away from the current
block and can't be read in the same Modbus transaction.

Test vector convention (matching abb_b23.py): every *_value field is the RAW
register integer as encoded on the wire for that quantity's divisor.
"""

METER_TYPE = 21
METER_NAME = "Acrel ADL400-D Mains"
ENDIANNESS = "HBF_HWF"
FUNCTION_CODE = 3
DATA_TYPE = "INT16"          # base datatype: current

# From EMConfig[21]: URegister=0, UDivisor=0 (unused)
#                    IRegister=0x64, IDivisor=2
#                    PRegister=0x16A, PDivisor=0   (32-bit override)
#                    ERegister=0x0,  EDivisor=2    (32-bit override)
#                    ERegister_Exp=0 (no export register)
REGISTERS = {
    'current_l1':    0x64,   # 100 -- Ia
    'current_l2':    0x65,   # 101 -- Ib (+1, INT16 convention)
    'current_l3':    0x66,   # 102 -- Ic (+2, INT16 convention)
    'power_total':   0x16A,  # 362 -- Total active power, 32-bit
    'energy_import': 0x0,    # 0   -- Total active energy, 32-bit
    'energy_export': 0,      # not supported on this profile
}

# Per-phase power block used only for current-direction sign recovery
# (polled separately from current; not part of EMConfig[]).
PHASE_POWER_REGISTERS = {
    'power_l1': 356,  # 0x164 -- Pa
    'power_l2': 358,  # 0x166 -- Pb
    'power_l3': 360,  # 0x168 -- Pc
}

I_DIVISOR = 2    # 0.01A resolution
P_DIVISOR = 0    # 1W resolution
E_DIVISOR = 2    # 0.01kWh resolution
E_DIVISOR_EXP = 0

# Power and Energy are 32-bit on the wire despite DATA_TYPE == 'INT16'.
POWER_DATA_TYPE = 'INT32'
ENERGY_DATA_TYPE = 'INT32'

IS_3PHASE = True

TEST_VECTORS = [
    {
        'name': 'nominal_3phase_16A',
        'description': '3-phase 16A import, values in 0.01A/0.01kWh units',
        'current_values': [1600, 1600, 1600],
        'power_value': 11040,             # 11040W (PDivisor=0)
        'energy_import_value': 123456,    # 1234.56 kWh (EDivisor=2)
        'energy_export_value': 0,
        'expected_current_mA': [16000, 16000, 16000],
        'expected_power_W': 11040,
        'expected_energy_import_Wh': 1234560,
        'expected_energy_export_Wh': 0,
    },
    {
        'name': 'unbalanced_load',
        'description': 'Unbalanced 3-phase load (25A/10A/5A)',
        'current_values': [2500, 1000, 500],
        'power_value': 8050,
        'energy_import_value': 50000,     # 500.00 kWh
        'energy_export_value': 0,
        'expected_current_mA': [25000, 10000, 5000],
        'expected_power_W': 8050,
        'expected_energy_import_Wh': 5000000,
        'expected_energy_export_Wh': 0,
    },
    {
        'name': 'standby_zero',
        'description': 'No load',
        'current_values': [0, 0, 0],
        'power_value': 0,
        'energy_import_value': 0,
        'energy_export_value': 0,
        'expected_current_mA': [0, 0, 0],
        'expected_power_W': 0,
        'expected_energy_import_Wh': 0,
        'expected_energy_export_Wh': 0,
    },
]

# Per-phase power block test vectors (Pa/Pb/Pc/Total), used to prove the
# current-direction sign-recovery mechanism decodes correctly.
PHASE_POWER_VECTORS = [
    {
        'name': 'all_import',
        'power_values': [1000, 1200, 900, 3100],   # Pa, Pb, Pc, Total
        'expected_W': [1000, 1200, 900, 3100],
    },
    {
        'name': 'solar_export_all_phases',
        'power_values': [-500, -600, -450, -1550],
        'expected_W': [-500, -600, -450, -1550],
    },
]
