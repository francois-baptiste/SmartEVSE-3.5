"""
Acrel ADL400-D meter profile tests: phase-B-only EV reads and mixed 16-bit/32-bit decode.

Tests REQ-MTR-180 through REQ-MTR-184.

@feature Modbus Compatibility
"""

import sys
import os
import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from frame_builder import build_response_data
from meter_profiles import acrel_ev_l2, acrel_mains


class TestAcrelEVL2RegisterMap:
    """
    @feature Modbus Compatibility
    @req REQ-MTR-180
    @scenario Acrel EV L2 profile register addresses match the ADL400-D datasheet values
    """

    def test_current_register_is_phase_b(self):
        """@given EMConfig[] entry for meter type 20 (EM_ACREL_EV_L2)
        @then IRegister 0x65 (101) matches the datasheet's Phase B (Ib) current register"""
        assert acrel_ev_l2.REGISTERS['current_l1'] == 0x65
        assert acrel_ev_l2.FUNCTION_CODE == 3

    def test_power_register(self):
        """@then PRegister 0x166 (358) matches Phase B active power (Pb)"""
        assert acrel_ev_l2.REGISTERS['power_total'] == 0x166

    def test_energy_register(self):
        """@then ERegister 0x89 (137) matches Phase B energy (Eb)"""
        assert acrel_ev_l2.REGISTERS['energy_import'] == 0x89

    def test_is_not_3phase(self):
        """@then This profile reads only one physical phase (L2/Phase B), not the L1/L2/L3 array"""
        assert acrel_ev_l2.IS_3PHASE is False
        assert acrel_ev_l2.PHASE_LABEL == 'L2'


class TestAcrelMainsRegisterMap:
    """
    @feature Modbus Compatibility
    @req REQ-MTR-181
    @scenario Acrel Mains profile register addresses match the ADL400-D datasheet values
    """

    def test_current_registers(self):
        """@given EMConfig[] entry for meter type 21 (EM_ACREL_MAINS)
        @then Ia/Ib/Ic sit at 100/101/102, satisfying the standard INT16 +1/+2 offset convention"""
        assert acrel_mains.REGISTERS['current_l1'] == 0x64
        assert acrel_mains.REGISTERS['current_l2'] == acrel_mains.REGISTERS['current_l1'] + 1
        assert acrel_mains.REGISTERS['current_l3'] == acrel_mains.REGISTERS['current_l1'] + 2

    def test_total_power_and_energy_registers(self):
        """@then PRegister 0x16A (362) and ERegister 0x0 match Total Power/Energy"""
        assert acrel_mains.REGISTERS['power_total'] == 0x16A
        assert acrel_mains.REGISTERS['energy_import'] == 0x0

    def test_phase_power_block_adjacent_to_total(self):
        """@given the per-phase power block used only for current-sign recovery
        @then Pa/Pb/Pc/Total (356/358/360/362) are four consecutive 32-bit registers"""
        regs = acrel_mains.PHASE_POWER_REGISTERS
        assert regs['power_l1'] == 356
        assert regs['power_l2'] == 358
        assert regs['power_l3'] == 360
        assert regs['power_l3'] + 2 == acrel_mains.REGISTERS['power_total']


class TestAcrelPhaseBOnlyCurrent:
    """
    @feature Modbus Compatibility
    @req REQ-MTR-182
    @scenario EV L2 profile decodes Phase B current and nothing else
    """

    def test_phase_b_current_decoded(self, bridge):
        """@given a 1-register response with Phase B current = 16.00A (raw 1600, INT16)
        @when decoded with IDivisor - 3
        @then the result is 16000 mA, with L1/L3 never read (only 1 register was requested)"""
        tv = acrel_ev_l2.TEST_VECTORS[0]
        data = build_response_data(tv['current_values'], acrel_ev_l2.DATA_TYPE, acrel_ev_l2.ENDIANNESS)
        # Only 1 register (2 bytes) exists in this response -- proves L1/L3 are never
        # part of the request/response for this profile, unlike the generic 3-phase read.
        assert len(data) == 2

        divisor = acrel_ev_l2.I_DIVISOR - 3
        r = bridge.decode_value(data, 0, acrel_ev_l2.ENDIANNESS, acrel_ev_l2.DATA_TYPE, divisor)
        assert r.valid == 1
        assert r.value == tv['expected_current_mA'][0]

    def test_standby_zero_current(self, bridge):
        """@given Phase B at standby (0A)
        @when decoded
        @then the result is 0 mA"""
        tv = acrel_ev_l2.TEST_VECTORS[2]
        data = build_response_data(tv['current_values'], acrel_ev_l2.DATA_TYPE, acrel_ev_l2.ENDIANNESS)
        divisor = acrel_ev_l2.I_DIVISOR - 3
        r = bridge.decode_value(data, 0, acrel_ev_l2.ENDIANNESS, acrel_ev_l2.DATA_TYPE, divisor)
        assert r.valid == 1
        assert r.value == 0


class TestAcrelMixedWidthDecode:
    """
    @feature Modbus Compatibility
    @req REQ-MTR-183
    @scenario Power/Energy decode correctly as 32-bit despite the profile's 16-bit base DataType

    This is the direct regression test for the reported problem: EMConfig[] has a single
    DataType per meter, but the ADL400-D reports voltage/current as 16-bit and power/energy
    as 32-bit. meter.cpp's receivePowerMeasurement/receiveEnergyMeasurement force an explicit
    MB_DATATYPE_INT32 override for EM_ACREL_EV_L2/EM_ACREL_MAINS (mirroring the existing
    SolarEdge/Sinotimer precedent) instead of using the profile's declared INT16 DataType.
    """

    @pytest.mark.parametrize("profile", [acrel_ev_l2, acrel_mains],
                             ids=[acrel_ev_l2.METER_NAME, acrel_mains.METER_NAME])
    def test_power_decodes_as_int32_not_base_datatype(self, bridge, profile):
        """@given a Power value that requires 32 bits to represent (3680W)
        @when decoded once using the profile's base DATA_TYPE (INT16, the bug) and once using
              POWER_DATA_TYPE (INT32, the fix)
        @then the INT16 decode is wrong (reads only the high half) while the INT32 decode
              matches the expected value, proving the override is load-bearing, not cosmetic"""
        tv = profile.TEST_VECTORS[0]
        data = build_response_data([tv['power_value']], profile.POWER_DATA_TYPE, profile.ENDIANNESS)

        wrong = bridge.decode_value(data, 0, profile.ENDIANNESS, profile.DATA_TYPE, profile.P_DIVISOR)
        correct = bridge.decode_value(data, 0, profile.ENDIANNESS, profile.POWER_DATA_TYPE, profile.P_DIVISOR)

        assert correct.valid == 1
        assert correct.value == tv['expected_power_W']
        assert wrong.value != correct.value, \
            f"{profile.METER_NAME}: INT16 base-datatype decode should NOT match the 32-bit value"

    @pytest.mark.parametrize("profile", [acrel_ev_l2, acrel_mains],
                             ids=[acrel_ev_l2.METER_NAME, acrel_mains.METER_NAME])
    def test_energy_decodes_as_int32(self, bridge, profile):
        """@given an Energy value in 0.01kWh units requiring 32 bits
        @when decoded with ENERGY_DATA_TYPE (INT32) and EDivisor - 3 (kWh -> Wh)
        @then the result matches the expected Wh value"""
        tv = profile.TEST_VECTORS[0]
        data = build_response_data([tv['energy_import_value']], profile.ENERGY_DATA_TYPE, profile.ENDIANNESS)
        divisor = profile.E_DIVISOR - 3
        r = bridge.decode_value(data, 0, profile.ENDIANNESS, profile.ENERGY_DATA_TYPE, divisor)
        assert r.valid == 1
        assert r.value == tv['expected_energy_import_Wh']


class TestAcrelMainsCurrentAndSignRecovery:
    """
    @feature Modbus Compatibility
    @req REQ-MTR-184
    @scenario Mains profile decodes L1/L2/L3 current and per-phase power for sign recovery
    """

    def test_unbalanced_3phase_current(self, bridge):
        """@given an unbalanced load (25A, 10A, 5A) across L1/L2/L3
        @when decoded
        @then each phase value is correctly assigned, matching the generic 3-phase convention"""
        tv = acrel_mains.TEST_VECTORS[1]
        data = build_response_data(tv['current_values'], acrel_mains.DATA_TYPE, acrel_mains.ENDIANNESS)
        divisor = acrel_mains.I_DIVISOR - 3

        results = [bridge.decode_value(data, i, acrel_mains.ENDIANNESS, acrel_mains.DATA_TYPE, divisor)
                   for i in range(3)]
        for i, r in enumerate(results):
            assert r.valid == 1
            assert r.value == tv['expected_current_mA'][i]

    def test_phase_power_block_all_import(self, bridge):
        """@given Pa/Pb/Pc/Total all positive (import on every phase)
        @when the 4-value power block is decoded
        @then all four values decode correctly with no overlap between phases"""
        pv = acrel_mains.PHASE_POWER_VECTORS[0]
        data = build_response_data(pv['power_values'], acrel_mains.POWER_DATA_TYPE, acrel_mains.ENDIANNESS)
        results = [bridge.decode_value(data, i, acrel_mains.ENDIANNESS, acrel_mains.POWER_DATA_TYPE, acrel_mains.P_DIVISOR)
                   for i in range(4)]
        for i, r in enumerate(results):
            assert r.valid == 1
            assert r.value == pv['expected_W'][i]

    def test_phase_power_block_solar_export(self, bridge):
        """@given Pa/Pb/Pc/Total all negative (solar export on every phase)
        @when the power block is decoded
        @then negative sign is preserved on every phase, as needed to flip the corresponding
              cached current reading (Power[x] < 0 -> var[x] = -var[x] in meter.cpp)"""
        pv = acrel_mains.PHASE_POWER_VECTORS[1]
        data = build_response_data(pv['power_values'], acrel_mains.POWER_DATA_TYPE, acrel_mains.ENDIANNESS)
        results = [bridge.decode_value(data, i, acrel_mains.ENDIANNESS, acrel_mains.POWER_DATA_TYPE, acrel_mains.P_DIVISOR)
                   for i in range(4)]
        for i, r in enumerate(results):
            assert r.valid == 1
            assert r.value == pv['expected_W'][i]
            assert r.value < 0
