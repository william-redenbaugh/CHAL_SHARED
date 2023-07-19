#ifndef _OS_UART_H
#define _OS_UART_H

#include "global_includes.h"
#include "stdlib.h"
#include "stdint.h"

#define PRINTF_BUFFER_SIZE 256
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