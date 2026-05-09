/*****************************************************************************
 * | File         :   i2c.h
 * | Author       :   Waveshare team
 * | Function     :   Hardware underlying interface
 * | Info         :
 * |                 I2C driver code for I2C communication.
 * ----------------
 * | This version :   V1.0
 * | Date         :   2024-11-26
 * | Info         :   Basic version
 *
 ******************************************************************************/

#ifndef __I2C_H
#define __I2C_H

#include <stdio.h>          // Standard input/output library
#include <string.h>         // String manipulation functions
#include "driver/i2c.h"    // ESP32 I2C master driver library
#include "esp_log.h"        // ESP32 logging library for debugging

// Define the SDA (data) and SCL (clock) pins for I2C communication
#define EXAMPLE_I2C_MASTER_SDA GPIO_NUM_8  // SDA pin
#define EXAMPLE_I2C_MASTER_SCL GPIO_NUM_9  // SCL pin

// Define the I2C frequency (400 kHz)
#define EXAMPLE_I2C_MASTER_FREQUENCY (400 * 1000)  // I2C speed

// Define the I2C master port number (I2C_NUM_0 in this case)
#define EXAMPLE_I2C_MASTER_NUM I2C_NUM_0


// Function prototypes for I2C communication

/**
 * @brief Initialize the I2C master interface.
 * 
 * This function sets up the I2C master interface, including the SDA/SCL pins,
 * clock frequency, and device address.
 * 
 * @param Addr The I2C address of the device to initialize.
 * @return A handle to the I2C device if initialization is successful, NULL if failure.
 */
esp_err_t DEV_I2C_Init();

/**
 * @brief Write a single byte to the I2C device.
 * 
 * This function sends a command byte and a data byte to the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param Cmd The command byte to send to the device.
 * @param value The value byte to send to the device.
 */
esp_err_t DEV_I2C_Write_Byte(uint8_t addr, uint8_t reg, uint8_t Value);

/**
 * @brief Read a single byte from the I2C device.
 * 
 * This function reads one byte of data from the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @return The byte read from the I2C device.
 */
esp_err_t DEV_I2C_Read_Byte(uint8_t addr, uint8_t *data);

/**
 * @brief Write multiple bytes to the I2C device.
 * 
 * This function sends a block of data (multiple bytes) to the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param pdata A pointer to the data to write.
 * @param len The number of bytes to write.
 */
esp_err_t DEV_I2C_Write_nByte(uint8_t addr, uint8_t *pData, uint32_t Len);

/**
 * @brief Read multiple bytes from the I2C device.
 * 
 * This function sends a command byte and reads multiple bytes from the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param Cmd The command byte to send.
 * @param pdata A pointer to the buffer to store the received data.
 * @param len The number of bytes to read.
 */
esp_err_t DEV_I2C_Read_nByte(uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t Len);

#endif
