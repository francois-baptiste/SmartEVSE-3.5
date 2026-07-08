/*
 * meter_decode.c - Pure C meter byte decoding for Modbus energy meters
 *
 * Extracted from meter.cpp combineBytes() and decodeMeasurement().
 * No platform dependencies.
 */

#include "meter_decode.h"
#include <string.h>
#include <math.h>
#include <limits.h>

/* Power-of-10 lookup table (matches firmware's pow_10[]) */
static const unsigned long pow10_table[10] = {
    1, 10, 100, 1000, 10000, 100000,
    1000000, 10000000, 100000000, 1000000000
};

uint8_t meter_register_size(meter_datatype_t datatype)
{
    return (datatype == METER_DATATYPE_INT16) ? 2 : 4;
}

void meter_combine_bytes(void *out, const uint8_t *buf, uint8_t pos,
                         uint8_t endianness, meter_datatype_t datatype)
{
    if (!out || !buf) return;

    /* Target is little-endian (ESP32, x86, ARM) */
    char *p = (char *)out;

    switch (endianness) {
        case ENDIANNESS_LBF_LWF: /* low byte first, low word first (LE) */
            *p++ = (char)buf[pos + 0];
            *p++ = (char)buf[pos + 1];
            if (datatype != METER_DATATYPE_INT16) {
                *p++ = (char)buf[pos + 2];
                *p   = (char)buf[pos + 3];
            }
            break;

        case ENDIANNESS_LBF_HWF: /* low byte first, high word first */
            if (datatype != METER_DATATYPE_INT16) {
                *p++ = (char)buf[pos + 2];
                *p++ = (char)buf[pos + 3];
            }
            *p++ = (char)buf[pos + 0];
            *p   = (char)buf[pos + 1];
            break;

        case ENDIANNESS_HBF_LWF: /* high byte first, low word first */
            *p++ = (char)buf[pos + 1];
            *p++ = (char)buf[pos + 0];
            if (datatype != METER_DATATYPE_INT16) {
                *p++ = (char)buf[pos + 3];
                *p   = (char)buf[pos + 2];
            }
            break;

        case ENDIANNESS_HBF_HWF: /* high byte first, high word first (BE) */
            if (datatype != METER_DATATYPE_INT16) {
                *p++ = (char)buf[pos + 3];
                *p++ = (char)buf[pos + 2];
            }
            *p++ = (char)buf[pos + 1];
            *p   = (char)buf[pos + 0];
            break;

        default:
            break;
    }
}

meter_reading_t meter_decode_value(const uint8_t *buf, uint8_t index,
                                   uint8_t endianness, meter_datatype_t datatype,
                                   int8_t divisor)
{
    meter_reading_t result = {0, 0};

    if (!buf) return result;
    if (datatype >= METER_DATATYPE_MAX) return result;

    /* Validate divisor range for pow10 lookup (table has 10 entries: 0..9).
     * Check raw range first to avoid UB when negating INT8_MIN (-128). */
    if (divisor < -9 || divisor > 9) return result;

    uint8_t reg_size = meter_register_size(datatype);
    uint8_t pos = index * reg_size;

    if (datatype == METER_DATATYPE_FLOAT32) {
        float f_combined = 0.0f;
        meter_combine_bytes(&f_combined, buf, pos, endianness, datatype);
        /* Reject NaN/Inf from corrupt meter data */
        if (isnan(f_combined) || isinf(f_combined)) return result;
        if (divisor >= 0) {
            result.value = (int32_t)(f_combined / (int32_t)pow10_table[divisor]);
        } else {
            result.value = (int32_t)(f_combined * (int32_t)pow10_table[-divisor]);
        }
    } else {
        int32_t i_combined = 0;
        meter_combine_bytes(&i_combined, buf, pos, endianness, datatype);
        if (datatype == METER_DATATYPE_INT16) {
            /* Sign extend 16-bit into 32-bit */
            i_combined = (int32_t)((int16_t)i_combined);
        }
        if (divisor >= 0) {
            result.value = i_combined / (int32_t)pow10_table[divisor];
        } else {
            /* Check for multiplication overflow before computing */
            int32_t multiplier = (int32_t)pow10_table[-divisor];
            int32_t abs_combined = (i_combined >= 0) ? i_combined : -i_combined;
            if (i_combined != 0 && abs_combined > INT32_MAX / multiplier) {
                return result; /* overflow would occur */
            }
            result.value = i_combined * multiplier;
        }
    }

    result.valid = 1;
    return result;
}

uint8_t meter_mains_phase_count(uint8_t meter_type, uint8_t p1_phases)
{
    if (meter_type == METER_TYPE_EASTRON1P || meter_type == METER_TYPE_ORNO1P)
        return 1;
    if (meter_type == METER_TYPE_HOMEWIZARD_P1 && p1_phases == 1)
        return 1;
    return 3;
}

int32_t meter_apparent_power_va(int16_t irms_da, float linky_va,
                                uint8_t linky_available)
{
    if (linky_available && !isnan(linky_va) && !isinf(linky_va) &&
        linky_va > 0.0f && linky_va < 1.0e9f) {
        return (int32_t)(linky_va + 0.5f);
    }
    /* Estimate: |I| * 230 V nominal; irms_da is A*10 */
    int32_t abs_da = (irms_da >= 0) ? irms_da : -(int32_t)irms_da;
    return abs_da * 23;
}
