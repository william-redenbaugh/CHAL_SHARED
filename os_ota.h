#ifndef _OS_OTA_H
#define _OS_OTA_H

#include "stdint.h"

/**
 * @brief Initializes the OTA (Over-The-Air) update process.
 *
 * This function begins the OTA update process by performing necessary initialization.
 *
 * @return An integer indicating the success (0) or failure (-1) of the initialization.
 */
int os_ota_begin(void);

/**
 * @brief Writes data for OTA (Over-The-Air) update.
 *
 * This function is used to write data for the OTA update.
 *
 * @param data Pointer to the data buffer to be written.
 * @param size Size of the data to be written in bytes.
 * @return An integer indicating the number of bytes successfully written or an error code.
 */
int os_ota_write(uint8_t *data, int size);

/**
 * @brief Finalizes the OTA (Over-The-Air) update process.
 *
 * This function ends the OTA update process and performs cleanup tasks.
 *
 * @return An integer indicating the success (0) or failure (-1) of the ending process.
 */
int os_ota_end(void);

/**
 * @brief Marks the ongoing OTA update as invalid and halts the process.
 *
 * This function marks the ongoing OTA update as invalid, preventing further execution,
 * and halts the update process.
 *
 * @return An integer indicating the success (0) or failure (-1) of marking the update as invalid.
 */
int os_ota_halt_mark_invalid(void);

/**
 * @brief Marks current boot as functional, prevents OTA from rebooting from previous build before
*/
void os_ota_mark_functional_boot(void);
#endif