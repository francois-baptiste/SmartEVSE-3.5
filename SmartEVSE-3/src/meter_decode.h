/*
 * meter_decode.h - Pure C meter byte decoding for Modbus energy meters
 *
 * Extracted from meter.cpp combineBytes() and decodeMeasurement()
 * for native testability. No platform dependencies.
 */

#ifndef METER_DECODE_H
#define METER_DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Endianness modes (byte order + word order) */
#define ENDIANNESS_LBF_LWF 0  /* low byte first, low word first (little endian) */
#define ENDIANNESS_LBF_HWF 1  /* low byte first, high word first */
#define ENDIANNESS_HBF_LWF 2  /* high byte first, low word first */
#define ENDIANNESS_HBF_HWF 3  /* high byte first, high word first (big endian) */

/* Modbus data types */
typedef enum {
    METER_DATATYPE_INT32   = 0,
    METER_DATATYPE_FLOAT32 = 1,
    METER_DATATYPE_INT16   = 2,
    METER_DATATYPE_MAX
} meter_datatype_t;

/*
 * Decoded measurement result.
 */
typedef struct {
    int32_t value;    /* Decoded value after endianness conversion and divisor */
    uint8_t valid;    /* 1 if decode succeeded, 0 on error */
} meter_reading_t;

/*
 * Combine raw Modbus bytes into a 32-bit value according to endianness
 * and data type. Writes to *out_value (int32_t for INT32/INT16, or
 * reinterpreted float bits for FLOAT32).
 *
 * @param out       Output: combined bytes (caller casts to int32_t or float)
 * @param buf       Input: raw Modbus response data bytes
 * @param pos       Byte offset into buf where this register starts
 * @param endianness ENDIANNESS_* constant
 * @param datatype   METER_DATATYPE_* constant
 *
 * The caller must ensure buf has at least pos + 4 bytes available
 * (or pos + 2 for INT16).
 */
void meter_combine_bytes(void *out, const uint8_t *buf, uint8_t pos,
                         uint8_t endianness, meter_datatype_t datatype);

/*
 * Decode a single measurement value from a Modbus response buffer.
 *
 * @param buf        Raw data bytes from Modbus response
 * @param index      Register index (0-based); byte offset = index * register_size
 * @param endianness ENDIANNESS_* constant
 * @param datatype   METER_DATATYPE_* constant
 * @param divisor    Power-of-10 divisor: positive = divide, negative = multiply
 *                   e.g., divisor=1 divides by 10, divisor=-3 multiplies by 1000
 * @return           Decoded measurement result
 */
meter_reading_t meter_decode_value(const uint8_t *buf, uint8_t index,
                                   uint8_t endianness, meter_datatype_t datatype,
                                   int8_t divisor);

/*
 * Returns the byte size of a single register for the given data type.
 * INT16 = 2, INT32/FLOAT32 = 4.
 */
uint8_t meter_register_size(meter_datatype_t datatype);

/* Meter type ids — must match the EM_* constants in meter.h */
#define METER_TYPE_EASTRON1P     10
#define METER_TYPE_HOMEWIZARD_P1 13
#define METER_TYPE_ORNO1P        18

/*
 * Number of phases of the mains installation as seen by the mains meter.
 *
 * @param meter_type  EM_* mains meter type
 * @param p1_phases   Phase count reported by a HomeWizard P1 meter
 *                    (0 = unknown/not a P1 meter)
 * @return            1 for single-phase installations (inherently 1-phase
 *                    meter types, or a P1 meter reporting 1 phase), 3 otherwise
 */
uint8_t meter_mains_phase_count(uint8_t meter_type, uint8_t p1_phases);

/*
 * Mains apparent power in VA.
 *
 * Uses the Linky SINSTS reading when available; otherwise estimates from
 * the L1 current at nominal 230 V. Always returns a magnitude (>= 0).
 *
 * @param irms_da         L1 current in deci-amps (A * 10), may be negative
 * @param linky_va        Apparent power reported by a Linky meter (VA)
 * @param linky_available 1 if Linky telemetry is valid
 * @return                Apparent power in VA
 */
int32_t meter_apparent_power_va(int16_t irms_da, float linky_va,
                                uint8_t linky_available);

#ifdef __cplusplus
}
#endif

#endif /* METER_DECODE_H */
