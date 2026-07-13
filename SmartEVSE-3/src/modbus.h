/*
;	 Project:       Smart EVSE
;
;
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
; THE SOFTWARE.
*/

#ifndef __EVSE_MODBUS
#define __EVSE_MODBUS

#include "meter.h"
#ifdef SMARTEVSE_VERSION //ESP32
#include "ModbusServerRTU.h"
#include "ModbusClientRTU.h"
#endif

struct ModBus {
    uint8_t Address;
    uint8_t Function;
    uint16_t Register;
    uint16_t RegisterCount;
    uint16_t Value;
    uint8_t *Data;
    uint8_t DataLength;
    uint8_t Type;
    uint8_t RequestAddress;
    uint8_t RequestFunction;
    uint16_t RequestRegister;
    uint8_t Exception;
};

#ifdef SMARTEVSE_VERSION //ESP32

// definition of MBserver / MBclient class is done in evse.cpp
extern ModbusServerRTU MBserver;
extern ModbusClientRTU MBclient; 
#endif

void ModbusReadInputRequest(uint8_t address, uint8_t function, uint16_t reg, uint16_t quantity);
void ModbusWriteSingleRequest(uint8_t address, uint16_t reg, uint16_t value);
void ModbusWriteMultipleRequest(uint8_t address, uint16_t reg, uint16_t *values, uint8_t count);
void ModbusException(uint8_t address, uint8_t function, uint8_t exception);

#ifdef SMARTEVSE_VERSION
void ModbusUserWriteSingle(uint8_t address, uint16_t reg, uint16_t value);
void ModbusUserWriteMultiple(uint8_t address, uint16_t reg, uint16_t *values, uint8_t count);

// User-initiated read (FC=3/4) for the web UI's Modbus test tool. Result is
// delivered asynchronously into g_modbusUserTest, matched via the eModbus
// request token so it's never confused with the periodic meter polling even
// if it targets the same slave address.
#define MODBUS_USER_TEST_MAX_REGS 32   // Modbus spec allows up to 125; this is a manual diagnostic tool, not a bulk reader

struct ModbusUserTestResult {
    bool     pending;
    bool     done;
    bool     ok;
    uint8_t  address;
    uint8_t  function;
    uint16_t reg;
    uint16_t quantity;
    uint32_t token;
    uint16_t data[MODBUS_USER_TEST_MAX_REGS];
    uint8_t  dataCount;
    uint8_t  exceptionCode;
    uint32_t timestamp_ms;
};
extern ModbusUserTestResult g_modbusUserTest;

void ModbusUserReadRequest(uint8_t address, uint8_t function, uint16_t reg, uint16_t quantity);
#endif

void requestMeasurement(uint8_t Meter, uint8_t Address, uint16_t Register, uint8_t Count);
void requestCurrentMeasurement(uint8_t Meter, uint8_t Address);
void BroadcastSettings(void);
#endif
