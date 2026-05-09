/*****************************************************************************
 * | File         :   ch422g.c
 * | Author       :   Waveshare team
 * | Function     :   CH422G GPIO control via I2C interface
 * | Info         :
 * |                 I2C driver code for controlling GPIO pins using CH422G chip.
 * ----------------
 * | This version :   V1.0
 * | Date         :   2024-11-27
 * | Info         :   Basic version, includes functions to read and write 
 * |                 GPIO pins using I2C communication with CH422G.
 *
 ******************************************************************************/

#include "ch422g.h"  // Include CH422G driver header for GPIO functions
ch422g_obj_t CH422G;  // Define the global CH422G object

/**
 * @brief Initialize the CH422G device.
 * 
 * This function configures the slave addresses for different registers of the
 * CH422G chip via I2C, and sets the control flags for input/output modes.
 */
void CH422G_init()
{
    // Set control flags for IO output enable and open-drain output mode
    CH422G.io_oe = CH422G_Mode_IO_OE;  // Output enable flag
    CH422G.od_en = CH422G_Mode_OD_EN & 0xFB;  // Open-drain enable flag
    CH422G.io_in = CH422G_Mode_IO_IN;  // Input mode flag
    CH422G.Last_io_value = 0xFF;
    CH422G.Last_od_value = 0xFF;
}

/**
 * @brief Set the value of the IO output pins on the CH422G device.
 * 
 * This function writes an 8-bit value to the IO output register. The value
 * determines the high or low state of the pins.
 * 
 * @param pin The 8-bit value to set on the output pins (0 = low, 1 = high).
 */
void CH422G_io_output(uint8_t pin, uint8_t value) 
{
    // Set the output enable flag for the pins
    DEV_I2C_Write_nByte(CH422G_Mode, &CH422G.io_oe, 1);
    if (value == 1)
        CH422G.Last_io_value |=(1 << pin);
    else
        CH422G.Last_io_value &=(~(1 << pin));
    // Write the 8-bit value to the IO output register
    DEV_I2C_Write_nByte(CH422G_IO_OUT, &CH422G.Last_io_value, 1);
}

/**
 * @brief Set the value of the open-drain (OD) output pins on the CH422G device.
 * 
 * This function configures the CH422G in push-pull mode and writes an 8-bit value
 * to the OD output register to control the state of the pins.
 * 
 * @param pin The 8-bit value to set on the open-drain output pins (0 = low, 1 = high).
 */
void CH422G_od_output(uint8_t pin, uint8_t value) 
{
    // Enable open-drain mode (push-pull configuration)
    DEV_I2C_Write_nByte(CH422G_Mode, &CH422G.od_en, 1);
    if (value == 1)
        CH422G.Last_od_value |= (1 << pin);
    else
        CH422G.Last_od_value &= (~(1 << pin));
    
    // Write the 8-bit value to the open-drain output register
    DEV_I2C_Write_nByte(CH422G_OD_OUT, &CH422G.Last_od_value, 1);
}

/**
 * @brief Read the value from the IO input pins on the CH422G device.
 * 
 * This function reads the value of the IO input register and returns the state
 * of the specified pins.
 * 
 * @param pin The bit mask to specify which pin to read (e.g., 0x01 for the first pin).
 * @return The value of the specified pin(s) (0 = low, 1 = high).
 */
uint8_t CH422G_io_input(uint8_t pin) 
{
    uint8_t value = 0;
    // Set the mode to input for the pins
    DEV_I2C_Write_nByte(CH422G_Mode, &CH422G.io_in, 1);
    // Read the value of the input pins
    DEV_I2C_Read_Byte(CH422G_IO_IN,&value);
    // Return the value of the specific pin(s) by masking with the provided bit mask
    return (value & (1 << pin));
}
