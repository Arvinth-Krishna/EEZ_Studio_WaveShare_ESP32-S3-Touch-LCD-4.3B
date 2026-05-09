/*****************************************************************************
 * | File         :   ch422g.h
 * | Author       :   Waveshare team
 * | Function     :   GPIO control using CH422G via I2C interface
 * | Info         :
 * |                 Header file for controlling GPIO pins via the CH422G
 * |                 chip using I2C communication. This file defines the
 * |                 necessary I2C addresses, commands, and GPIO pin control
 * |                 functions.
 * ----------------
 * | This version :   V1.0
 * | Date         :   2024-11-19
 * | Info         :   Basic version
 *
 ******************************************************************************/

#ifndef __CH422G_H
#define __CH422G_H

#include "i2c.h"  // Include I2C header for I2C communication functions

/* 
 * CH422G GPIO control via I2C - Register and Command Definitions
 *
 * The CH422G does not have a unique slave address, but it uses predefined 
 * function registers that act as I2C slave addresses.
 *
 * Example usage:
 * 1. Set the working mode by writing to the register at address 0x24
 * 2. Send function commands to control the GPIO pins and modes
 */

/* CH422G Function Register Addresses */
#define CH422G_Mode          0x24  // Slave address for mode configuration register

/* Mode control flags (from the chip manual) */
#define CH422G_Mode_IO_IN    0x00  // Input enable
#define CH422G_Mode_IO_OE    0x01  // Output enable
#define CH422G_Mode_A_SCAN   0x02  // Dynamic scan mode enable
#define CH422G_Mode_OD_EN    0x04  // Open-drain mode for pins OC3 to OC0
#define CH422G_Mode_SLEEP    0x08  // Low power sleep mode control

/* Open-drain output control */
#define CH422G_OD_OUT        0x23  // Control register for OC (open-drain) pins
#define CH422G_OD_OUT_0      0x00  // OC0 output high (used for isolation of DO0)
#define CH422G_OD_OUT_1      0x01  // OC1 output high (used for isolation of DO1)
#define CH422G_OD_OUT_2      0x02  // OC2 output high
#define CH422G_OD_OUT_3      0x03  // OC3 output high

/* GPIO output control */
#define CH422G_IO_OUT        0x38  // Control register for IO pin outputs
#define CH422G_IO_OUT_0      0x01  // IO0 output high
#define CH422G_IO_OUT_1      0x02  // IO1 output high
#define CH422G_IO_OUT_2      0x04  // IO2 output high
#define CH422G_IO_OUT_3      0x08  // IO3 output high
#define CH422G_IO_OUT_4      0x10  // IO4 output high
#define CH422G_IO_OUT_5      0x20  // IO5 output high
#define CH422G_IO_OUT_6      0x40  // IO6 output high
#define CH422G_IO_OUT_7      0x80  // IO7 output high

/* GPIO input control */
#define CH422G_IO_IN         0x26  // Register for reading the input pin states

/* Specific IO pin assignments */
#define CH422G_IO_0          0x00  // IO0 
#define CH422G_IO_1          0x01  // IO1 (used for touch reset)
#define CH422G_IO_2          0x02  // IO2 (backlight control)
#define CH422G_IO_3          0x03  // IO3 (used for lcd reset)
#define CH422G_IO_4          0x04  // IO4 (SD card CS pin)
#define CH422G_IO_5          0x05  // IO5 (Select communication interface: 0 for USB, 1 for CAN)
#define CH422G_IO_6          0x06  // IO6
#define CH422G_IO_7          0x07  // IO7

/* Structure to represent the CH422G device */
typedef struct _ch422g_obj_t {
    uint8_t io_oe;  // Control flag for output enable (IO)
    uint8_t od_en;  // Control flag for open-drain enable
    uint8_t io_in;  // Control flag for input mode
    uint8_t Last_io_value;
    uint8_t Last_od_value;
} ch422g_obj_t;


/* Function declarations */
void CH422G_init();                     // Initialize the CH422G device
void CH422G_io_output(uint8_t pin, uint8_t value);     // Set IO pin output (high/low)
uint8_t CH422G_io_input(uint8_t pin);   // Read IO pin input state
void CH422G_od_output(uint8_t pin, uint8_t value);     // Set open-drain output (high/low)

#endif  // __CH422G_H
