// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license

#pragma once

#include "quantum.h"

// Convenient way to store and access measurements
typedef struct {
    uint16_t xValue;
    uint16_t yValue;
    uint16_t zValue;
    uint8_t  buttonFlags;
    bool     touchDown;
} absData_t;

typedef struct {
    int8_t xValue;
    int8_t yValue;
    bool buttonFlags;
} relData_t;

extern absData_t touchData;
extern relData_t rTouchData;

void Pinnacle_GetAbsolute(absData_t* result);
void Pinnacle_GetRelative(relData_t* result);
void Pinnacle_ClearFlags(void);
void Pinnacle_EnableFeed(bool feedEnable);
void ERA_ReadBytes(uint16_t address, uint8_t* data, uint16_t count);
void ERA_WriteByte(uint16_t address, uint8_t data);
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count);
void RAP_Write(uint8_t address, uint8_t data);
void ClipCoordinates(absData_t* coordinates);
void ScaleData(absData_t* coordinates, uint16_t xResolution, uint16_t yResolution);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);
void setAdcAttenuation(uint8_t adcGain);
void tuneEdgeSensitivity(void);
// Cirque's 7-bit I2C Slave Address
#define SLAVE_ADDR           0x2A

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK           0x80
#define READ_MASK            0xA0

// Registers for RAP
#define FIRMWARE_ID          0x00
#define FIRMWARE_VERSION_C   0x01
#define STATUS_1             0x02
#define SYSCONFIG_1          0x03
#define FEEDCONFIG_1         0x04
#define FEEDCONFIG_2         0x05
#define CALIBRATION_CONFIG_1 0x07
#define PS2_AU_CONTROL       0x08
#define SAMPLE_RATE          0x09
#define Z_IDLE_COUNT         0x0A
#define Z_SCALER             0x0B
#define SLEEP_INTERVAL       0x0C
#define SLEEP_TIMER          0x0D
#define PACKET_BYTE_0        0x12
#define PACKET_BYTE_1        0x13
#define PACKET_BYTE_2        0x14
#define PACKET_BYTE_3        0x15
#define PACKET_BYTE_4        0x16
#define PACKET_BYTE_5        0x17

// Coordinate scaling values
#define PINNACLE_XMAX        2047 // max value Pinnacle can report for X
#define PINNACLE_YMAX        1535 // max value Pinnacle can report for Y
#define PINNACLE_X_LOWER     127  // min "reachable" X value
#define PINNACLE_X_UPPER     1919 // max "reachable" X value
#define PINNACLE_Y_LOWER     63   // min "reachable" Y value
#define PINNACLE_Y_UPPER     1471 // max "reachable" Y value
#define PINNACLE_X_RANGE     (PINNACLE_X_UPPER - PINNACLE_X_LOWER)
#define PINNACLE_Y_RANGE     (PINNACLE_Y_UPPER - PINNACLE_Y_LOWER)

#define ERA_VALUE            0x1B
#define ERA_HIGH_BYTE        0x1C
#define ERA_LOW_BYTE         0x1D
#define ERA_CONTROL          0x1E

// ADC-attenuation settings (held in BIT_7 and BIT_6)
// 1X = most sensitive, 4X = least sensitive
#define ADC_ATTENUATE_1X   0x00
#define ADC_ATTENUATE_2X   0x40
#define ADC_ATTENUATE_3X   0x80
#define ADC_ATTENUATE_4X   0xC0
