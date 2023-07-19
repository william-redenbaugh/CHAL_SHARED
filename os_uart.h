#ifndef _OS_UART_H
#define _OS_UART_H

#include "global_includes.h"
#include "stdlib.h"
#include "stdint.h"

typedef struct os_uart_t
{
    uint32_t baud;
    int fd;
} os_uart_t;

/**
 * @brief Begins the UART interface
 * @param os_uart_t *pointer to the UART interface
 */
int os_uart_begin(os_uart_t *uart, int fd, int baud);

/**
 * @brief Completes the UART Interface
 * @param os_uart_t *pointer to the UART interface
 */
int os_uart_end(os_uart_t *uart);

/**
 * @brief printf for specific uart interface
 * @param os_uart_t *uart interface
 * @param ... params
*/
void os_uart_printf(os_uart_t *uart, const char *format, ...);

/**
 * @brief Reads characters from the UART until a specified terminator character is encountered.
 *
 * This function reads characters from the UART associated with the given UART object until the specified
 * terminator character is encountered or the maximum number of characters (size) is reached, whichever comes first.
 *
 * @param uart      Pointer to the UART object representing the UART to read from.
 * @param terminator The character used as a terminator to stop reading from the UART.
 * @param data      Pointer to the buffer where the read data will be stored.
 * @param size      The maximum number of characters to read (size of the data buffer).
 *
 * @return The number of characters actually read from the UART and stored in the data buffer.
 *         The return value does not include the terminator character.
 */
int os_uart_readstring_until(os_uart_t *uart, char terminator, uint8_t *data, size_t size);


/**
 * @brief Reads a string of characters from the UART.
 *
 * This function reads characters from the UART associated with the given UART object and stores them in the provided
 * data buffer until the maximum number of characters (size) is reached or a null terminator ('\0') is encountered,
 * whichever comes first.
 *
 * @param uart      Pointer to the UART object representing the UART to read from.
 * @param data      Pointer to the buffer where the read data will be stored.
 * @param size      The maximum number of characters to read (size of the data buffer).
 *
 * @return The number of characters actually read from the UART and stored in the data buffer.
 *         The return value does not include the null terminator ('\0').
 */
int os_uart_readstring(os_uart_t *uart, uint8_t *data, size_t size);

/**
 * @brief Sets the frequency of the UART interface
 * @param os_uart_t *pointer to the UART interface
 * @param uint32_t frequency/baud rate of UART interfaces
 */
int os_uart_setbus(os_uart_t *uart, uint32_t freq_baud);

/**
 * @brief Transfers data to/from the UART interface
 * @param os_uart_t *pointer to the UART interface
 * @param uint8_t *rx pointer to RX buffer
 * @param uint8_t
 */
int os_uart_transfer(os_uart_t *uart, uint8_t *rx, uint8_t *tx, size_t size);

/**
 * @brief Sends data to the UART interface
 * @param os_uart_t *pointer to the UART interface
 */
int os_uart_send(os_uart_t *uart, uint8_t *buf, size_t size);

/**
 * @brief Recieves Data from the UART interface
 * @param os_uart_t *pointer to the UART interface
 */
int os_uart_recieve(os_uart_t *uart, uint8_t *buf, size_t size);
#endif