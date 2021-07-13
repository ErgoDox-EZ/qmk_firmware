// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "moonlander.h"
#include "i2c_master.h"
#include "i2c2_master.h"
#include "cirque_tm040040.h"
#include "pointing_device.h"

// Register config values for this demo
#ifndef SYSCONFIG_1_VALUE
#    define SYSCONFIG_1_VALUE 0x00
#endif
#ifndef FEEDCONFIG_1_VALUE
#    define FEEDCONFIG_1_VALUE 0x03  // 0x03 for absolute mode 0x01 for relative mode
// #    define FEEDCONFIG_1_VALUE 0x81 // 0x03 for absolute mode 0x01 for relative mode
#endif
#ifndef FEEDCONFIG_2_VALUE
// #    define FEEDCONFIG_2_VALUE 0x1F  // 0x1F for normal functionality 0x1E for intellimouse disabled
#    define FEEDCONFIG_2_VALUE 0x1C  // 0x1F for normal functionality 0x1E for intellimouse disabled
#endif
#ifndef Z_IDLE_COUNT_VALUE
#    define Z_IDLE_COUNT_VALUE 0x05
#endif

absData_t touchData  = {0};
relData_t rTouchData = {0};
bool      touchpad_init[2];

void print_byte(uint8_t byte) { xprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')); }

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}
void pointing_device_task(void) {
    report_mouse_t mouse_report = pointing_device_get_report();
#if 1
    static uint16_t x = 0, y = 0;
    int8_t report_x = 0, report_y = 0;

    Pinnacle_GetAbsolute(&touchData);
    ScaleData(&touchData, 256 * keyboard_config.dpi_config, 256 * keyboard_config.dpi_config);  // Scale coordinates to arbitrary X, Y resolution

    if (x && y && touchData.xValue && touchData.yValue) {
        report_x = (int8_t)(touchData.xValue - x);
        report_y = (int8_t)(touchData.yValue - y);
    }
    x = touchData.xValue;
    y = touchData.yValue;

    if (rTouchData.buttonFlags) {
        mouse_report.buttons |= MOUSE_BTN1;
    } else {
        mouse_report.buttons &= ~MOUSE_BTN1;
    }

#else
    Pinnacle_GetRelative(&rTouchData);

    mouse_report.x = rTouchData.xValue;
    mouse_report.y = rTouchData.yValue;
    //xprintf("%d", result->buttonFlags);
    xprintf("\n");
    if (rTouchData.buttonFlags) {
        mouse_report.buttons |= MOUSE_BTN1;
    } else {
        mouse_report.buttons &= ~MOUSE_BTN1;
    }

    rTouchData.xValue = 0;
    rTouchData.yValue = 0;
#endif
    process_mouse_user(&mouse_report, report_x, report_y);
    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

/*  Pinnacle-based TM040040 Functions  */
void pointing_device_init(void) {
    i2c_init();
    touchpad_init[0] = true;
    i2c2_init();
    touchpad_init[1] = true;
    // Host clears SW_CC flag
    Pinnacle_ClearFlags();

    // clear flags will attempt to ping both pads, and if it errors out,
    // will de-init that side. So if both sides are connected, and working,
    // de-init the left side, since we assume right side dominance.
    if (touchpad_init[0] && touchpad_init[1]) {
        touchpad_init[1] = false;
    }
    // Host configures bits of registers 0x03 and 0x05
    RAP_Write(SYSCONFIG_1, SYSCONFIG_1_VALUE);
    RAP_Write(FEEDCONFIG_2, FEEDCONFIG_2_VALUE);

    // Host enables preferred output mode (absolute)
    RAP_Write(FEEDCONFIG_1, FEEDCONFIG_1_VALUE);

    // Host sets z-idle packet count to 5 (default is 30)
    RAP_Write(Z_IDLE_COUNT, Z_IDLE_COUNT_VALUE);

    setAdcAttenuation(0xFF);
    tuneEdgeSensitivity();
    Pinnacle_EnableFeed(true);
}

// Reads XYZ data from Pinnacle registers 0x14 through 0x17
// Stores result in absData_t struct with xValue, yValue, and zValue members
void Pinnacle_GetAbsolute(absData_t* result) {
    uint8_t data[6] = {0};
    RAP_ReadBytes(PACKET_BYTE_0, data, 6);

    Pinnacle_ClearFlags();

    result->buttonFlags = data[0] & 0x3F;
    result->xValue      = data[2] | ((data[4] & 0x0F) << 8);
    result->yValue      = data[3] | ((data[4] & 0xF0) << 4);
    result->zValue      = data[5] & 0x3F;


    result->touchDown = result->xValue != 0;
}

void Pinnacle_GetRelative(relData_t* result) {
    uint8_t data[3] = {0};
    RAP_ReadBytes(PACKET_BYTE_0, data, 3);

    Pinnacle_ClearFlags();

    result->buttonFlags = (bool)(data[0] & 0x07);
    result->xValue      = (int8_t)data[1];
    result->yValue      = (int8_t)data[2];
}

// Clears Status1 register flags (SW_CC and SW_DR)
void Pinnacle_ClearFlags() {
    RAP_Write(STATUS_1, 0x00);
    wait_us(50);
}

// Enables/Disables the feed
void Pinnacle_EnableFeed(bool feedEnable) {
    uint8_t temp;

    RAP_ReadBytes(FEEDCONFIG_1, &temp, 1);  // Store contents of FeedConfig1 register

    if (feedEnable) {
        temp |= 0x01;  // Set Feed Enable bit
        RAP_Write(0x04, temp);
    } else {
        temp &= ~0x01;  // Clear Feed Enable bit
        RAP_Write(0x04, temp);
    }
}

/*  ERA (Extended Register Access) Functions  */
// Reads <count> bytes from an extended register at <address> (16-bit address),
// stores values in <*data>
void ERA_ReadBytes(uint16_t address, uint8_t* data, uint16_t count) {
    uint8_t ERAControlValue = 0xFF;

    Pinnacle_EnableFeed(false);  // Disable feed

    RAP_Write(ERA_HIGH_BYTE, (uint8_t)(address >> 8));     // Send upper byte of ERA address
    RAP_Write(ERA_LOW_BYTE, (uint8_t)(address & 0x00FF));  // Send lower byte of ERA address

    for (uint16_t i = 0; i < count; i++) {
        RAP_Write(ERA_CONTROL, 0x05);  // Signal ERA-read (auto-increment) to Pinnacle

        // Wait for status register 0x1E to clear
        do {
            RAP_ReadBytes(ERA_CONTROL, &ERAControlValue, 1);
        } while (ERAControlValue != 0x00);

        RAP_ReadBytes(ERA_VALUE, data + i, 1);

        Pinnacle_ClearFlags();
    }
}

// Writes a byte, <data>, to an extended register at <address> (16-bit address)
void ERA_WriteByte(uint16_t address, uint8_t data) {
    uint8_t ERAControlValue = 0xFF;

    Pinnacle_EnableFeed(false);  // Disable feed

    RAP_Write(ERA_VALUE, data);  // Send data byte to be written

    RAP_Write(ERA_HIGH_BYTE, (uint8_t)(address >> 8));     // Upper byte of ERA address
    RAP_Write(ERA_LOW_BYTE, (uint8_t)(address & 0x00FF));  // Lower byte of ERA address

    RAP_Write(ERA_CONTROL, 0x02);  // Signal an ERA-write to Pinnacle

    // Wait for status register 0x1E to clear
    do {
        RAP_ReadBytes(ERA_CONTROL, &ERAControlValue, 1);
    } while (ERAControlValue != 0x00);

    Pinnacle_ClearFlags();
}

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | address;  // Form the READ command byte
    // uint8_t i       = 0;
    if (touchpad_init[0]) {
        i2c_writeReg(SLAVE_ADDR << 1, cmdByte, NULL, 0, I2C_TIMEOUT);
        if (i2c_readReg(SLAVE_ADDR << 1, cmdByte, data, count, I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error right touchpad\n");
            touchpad_init[0] = false;
        }
        i2c_stop();
    }

    if (touchpad_init[1]) {
        i2c2_writeReg(SLAVE_ADDR << 1, cmdByte, NULL, 0, I2C_TIMEOUT);
        if (i2c2_readReg(SLAVE_ADDR << 1, cmdByte, data, count, I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error left touchpad\n");
            touchpad_init[1] = false;
        }
        i2c2_stop();
    }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | address;  // Form the WRITE command byte

    if (touchpad_init[0]) {
        if (i2c_writeReg(SLAVE_ADDR << 1, cmdByte, &data, sizeof(data), I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error right touchpad\n");
            touchpad_init[0] = false;
        }
        i2c_stop();
    }
    if (address == FEEDCONFIG_1 && data == FEEDCONFIG_1_VALUE) {
        data = 0xC3;
    }
    if (touchpad_init[1]) {
        if (i2c2_writeReg(SLAVE_ADDR << 1, cmdByte, &data, sizeof(data), I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error left touchpad\n");
            touchpad_init[1] = false;
        }
        i2c2_stop();
    }
}

/*  Logical Scaling Functions */
// Clips raw coordinates to "reachable" window of sensor
// NOTE: values outside this window can only appear as a result of noise
void ClipCoordinates(absData_t* coordinates) {
    if (coordinates->xValue < PINNACLE_X_LOWER) {
        coordinates->xValue = PINNACLE_X_LOWER;
    } else if (coordinates->xValue > PINNACLE_X_UPPER) {
        coordinates->xValue = PINNACLE_X_UPPER;
    }
    if (coordinates->yValue < PINNACLE_Y_LOWER) {
        coordinates->yValue = PINNACLE_Y_LOWER;
    } else if (coordinates->yValue > PINNACLE_Y_UPPER) {
        coordinates->yValue = PINNACLE_Y_UPPER;
    }
}

// Scales data to desired X & Y resolution
void ScaleData(absData_t* coordinates, uint16_t xResolution, uint16_t yResolution) {
    uint32_t xTemp = 0;
    uint32_t yTemp = 0;

    ClipCoordinates(coordinates);

    xTemp = coordinates->xValue;
    yTemp = coordinates->yValue;

    // translate coordinates to (0, 0) reference by subtracting edge-offset
    xTemp -= PINNACLE_X_LOWER;
    yTemp -= PINNACLE_Y_LOWER;

    // scale coordinates to (xResolution, yResolution) range
    coordinates->xValue = (uint16_t)(xTemp * xResolution / PINNACLE_X_RANGE);
    coordinates->yValue = (uint16_t)(yTemp * yResolution / PINNACLE_Y_RANGE);
}

void setAdcAttenuation(uint8_t adcGain) {
    uint8_t temp = 0x00;

    ERA_ReadBytes(0x0187, &temp, 1);
    temp &= 0x3F; // clear top two bits
    temp |= adcGain;
    ERA_WriteByte(0x0187, temp);
    ERA_ReadBytes(0x0187, &temp, 1);
}

// Changes thresholds to improve detection of fingers
void tuneEdgeSensitivity(void) {
    uint8_t temp = 0x00;

    ERA_ReadBytes(0x0149, &temp, 1);
    ERA_WriteByte(0x0149,  0x04);
    ERA_ReadBytes(0x0149, &temp, 1);

    ERA_ReadBytes(0x0168, &temp, 1);
    ERA_WriteByte(0x0168,  0x03);
    ERA_ReadBytes(0x0168, &temp, 1);
}
