// hal_bluetooth_serial.h

#ifndef HAL_BLUETOOTH_SERIAL_H
#define HAL_BLUETOOTH_SERIAL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @file hal_bluetooth_serial.h
 * @brief Hardware Abstraction Layer (HAL) for Serial over Bluetooth.
 */

/**
 * @brief Error codes for the HAL layer.
 */
typedef enum
{
    HAL_BT_SERIAL_OK,             ///< Operation completed successfully.
    HAL_BT_SERIAL_ERROR,          ///< General error occurred.
    HAL_BT_SERIAL_INVALID_ARG,    ///< Invalid argument provided.
    HAL_BT_SERIAL_BUFFER_OVERFLOW ///< Circular buffer overflow occurred.
} hal_bt_serial_err_t;

/**
 * @brief Initialize the Bluetooth Serial module.
 *
 * This function initializes the Bluetooth stack and sets up the Serial Port Profile (SPP) mode.
 * It must be called before any other HAL functions.
 *
 * @return HAL_BT_SERIAL_OK on success, or an appropriate error code if an error occurs.
 */
hal_bt_serial_err_t hal_bluetooth_serial_init(void);

/**
 * @brief Send data over Bluetooth Serial.
 *
 * This function sends the provided data over Bluetooth SPP to the connected device.
 *
 * @param[in] data Pointer to the data to be sent.
 * @param[in] len  Length of the data to be sent.
 * @return HAL_BT_SERIAL_OK on success, or an appropriate error code if an error occurs.
 */
int hal_bluetooth_serial_send(const uint8_t *data, size_t len);

/**
 * @brief Receive data over Bluetooth Serial.
 *
 * This function reads data from the Bluetooth SPP circular buffer into the provided buffer.
 * If there is insufficient data in the buffer to fulfill the request, an error is returned.
 *
 * @param[out] data Pointer to the buffer where received data will be stored.
 * @param[in]  len  Maximum number of bytes to receive.
 * @return HAL_BT_SERIAL_OK on success, HAL_BT_SERIAL_ERROR if there is insufficient data,
 *         or HAL_BT_SERIAL_INVALID_ARG if the provided buffer is NULL or the length is 0.
 */
int hal_bluetooth_serial_receive(uint8_t *data, size_t len);

/**
 * @brief Close the Bluetooth Serial module.
 *
 * This function closes the Bluetooth SPP connection and performs necessary cleanup.
 * It should be called when communication over Bluetooth is no longer needed.
 */
void hal_bluetooth_serial_close(void);

/**
 * @brief Initialize the Bluetooth Serial module.
 *
 * This function initializes the Bluetooth stack and sets up the Serial Port Profile (SPP) mode.
 * It must be called before any other HAL functions.
 *
 * @return HAL_BT_SERIAL_OK on success, or an appropriate error code if an error occurs.
 */
hal_bt_serial_err_t hal_ble_serial_init(void);

/**
 * @brief Send data over Bluetooth Serial.
 *
 * This function sends the provided data over Bluetooth SPP to the connected device.
 *
 * @param[in] data Pointer to the data to be sent.
 * @param[in] len  Length of the data to be sent.
 * @return HAL_BT_SERIAL_OK on success, or an appropriate error code if an error occurs.
 */
int hal_ble_serial_send(uint8_t *data, size_t len);

/**
 * @brief Receive data over Bluetooth Serial.
 *
 * This function reads data from the Bluetooth SPP circular buffer into the provided buffer.
 * If there is insufficient data in the buffer to fulfill the request, an error is returned.
 *
 * @param[out] data Pointer to the buffer where received data will be stored.
 * @param[in]  len  Maximum number of bytes to receive.
 * @return HAL_BT_SERIAL_OK on success, HAL_BT_SERIAL_ERROR if there is insufficient data,
 *         or HAL_BT_SERIAL_INVALID_ARG if the provided buffer is NULL or the length is 0.
 */
int hal_ble_serial_receive(uint8_t *data, size_t len);


/**
 * @brief Receive data over Bluetooth Serial. Block until data is pushed in
 *
 * This function reads data from the Bluetooth SPP circular buffer into the provided buffer.
 * If there is insufficient data in the buffer to fulfill the request, an error is returned.
 *
 * @param[out] data Pointer to the buffer where received data will be stored.
 * @param[in]  len  Maximum number of bytes to receive.
 * @return HAL_BT_SERIAL_OK on success, HAL_BT_SERIAL_ERROR if there is insufficient data,
 *         or HAL_BT_SERIAL_INVALID_ARG if the provided buffer is NULL or the length is 0.
 */
int hal_ble_serial_receive_block(uint8_t *data, size_t len);

/**
 * @brief Receive data over Bluetooth Serial. Block until data is pushed in
 *
 * This function reads data from the Bluetooth SPP circular buffer into the provided buffer.
 * If there is insufficient data in the buffer to fulfill the request, an error is returned.
 *
 * @param[out] data Pointer to the buffer where received data will be stored.
 * @param[in]  len  Maximum number of bytes to receive.
 * @param uint32_t timeout_ms
 * @return HAL_BT_SERIAL_OK on success, HAL_BT_SERIAL_ERROR if there is insufficient data,
 *         or HAL_BT_SERIAL_INVALID_ARG if the provided buffer is NULL or the length is 0.
 */
int hal_ble_serial_receive_block_timeout(uint8_t *data, size_t len, uint32_t timeout_ms);

/**
 * @brief Close the Bluetooth Serial module.
 *
 * This function closes the Bluetooth SPP connection and performs necessary cleanup.
 * It should be called when communication over Bluetooth is no longer needed.
 */
void hal_ble_serial_close(void);

/**
 * @brief Flush the contents from serial
*/
int hal_ble_flush_serial(void);

#endif // HAL_BLUETOOTH_SERIAL_H