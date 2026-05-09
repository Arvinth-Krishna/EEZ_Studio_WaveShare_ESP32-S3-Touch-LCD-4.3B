/*****************************************************************************
 * | File         :   i2c.c
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

#include "i2c.h"  // Include I2C driver header for I2C functions
static const char *TAG = "i2c";  // Define a tag for logging

/**
 * @brief Initialize the I2C master interface.
 * 
 * This function configures the I2C master bus and adds a device with the specified address.
 * The I2C clock source, frequency, SCL/SDA pins, and other settings are configured here.
 * 
 * @param Addr The I2C address of the device to be initialized.
 * @return The device handle if initialization is successful, NULL otherwise.
 */
esp_err_t DEV_I2C_Init()
{
    // Define I2C bus configuration parameters
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = EXAMPLE_I2C_MASTER_SDA,
        .scl_io_num = EXAMPLE_I2C_MASTER_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
    };
    conf.master.clk_speed = EXAMPLE_I2C_MASTER_FREQUENCY;


    i2c_param_config(EXAMPLE_I2C_MASTER_NUM, &conf);

    return i2c_driver_install(EXAMPLE_I2C_MASTER_NUM, conf.mode, 0, 0, 0);

}

/**
 * @brief Write a single byte to the I2C device.
 * 
 * This function sends a command byte and a value byte to the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param Cmd The command byte to send.
 * @param value The value byte to send.
 */
esp_err_t DEV_I2C_Write_Byte(uint8_t addr, uint8_t reg, uint8_t Value)
{
    uint8_t write_buf[2] = {reg, Value};
    return i2c_master_write_to_device(EXAMPLE_I2C_MASTER_NUM, addr, write_buf, 2, 1000 / portTICK_PERIOD_MS);
}

/**
 * @brief Read a single byte from the I2C device.
 * 
 * This function reads a byte of data from the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @return The byte read from the device.
 */
esp_err_t DEV_I2C_Read_Byte(uint8_t addr, uint8_t *data)
{
    return i2c_master_read_from_device(EXAMPLE_I2C_MASTER_NUM, addr, data, 1, 1000 / portTICK_PERIOD_MS);
}


/**
 * @brief Write multiple bytes to the I2C device.
 * 
 * This function sends a block of data to the I2C device.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param pdata Pointer to the data to send.
 * @param len The number of bytes to send.
 */
esp_err_t DEV_I2C_Write_nByte(uint8_t addr, uint8_t *pData, uint32_t Len)
{
    return i2c_master_write_to_device(EXAMPLE_I2C_MASTER_NUM, addr, pData, Len, 1000 / portTICK_PERIOD_MS);
}

/**
 * @brief Read multiple bytes from the I2C device.
 * 
 * This function reads multiple bytes from the I2C device.
 * The function sends a command byte and receives the specified number of bytes.
 * 
 * @param dev_handle The handle to the I2C device.
 * @param Cmd The command byte to send.
 * @param pdata Pointer to the buffer where received data will be stored.
 * @param len The number of bytes to read.
 */
esp_err_t DEV_I2C_Read_Nbyte(uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t Len)
{
    return i2c_master_write_read_device(EXAMPLE_I2C_MASTER_NUM, addr, &reg, 1, pData, Len, 1000 / portTICK_PERIOD_MS);
}
