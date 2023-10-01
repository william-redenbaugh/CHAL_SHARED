#ifndef _OS_SPI_H
#define _OS_SPI_H

#include "global_includes.h"
#include "stdlib.h"
#include "stdint.h"

typedef struct os_spi_gpio_t
{
    int mosi = -1;
    int miso = -1;
    int clk = -1;
} os_spi_gpio_t;

typedef struct os_spi_t
{

    int fd;
    // If platform supports flexible GPIO configuration
    os_spi_gpio_t gpio_man;

    // Pointer to spi handle
} os_spi_t;

typedef struct os_device_t
{
    uint8_t spi_mode;
    size_t dma_buf_size;
    int chip_select;
    int clk;
    void *device;
    os_spi_t *bus;
} os_device_t;

typedef struct os_device_init_params
{
    size_t dma_buf_size;
    uint8_t spi_mode;
    int cs_gpio;
    int clk;
    os_spi_t *bus;
} os_device_init_params;

/**
 * @brief Begins the SPI interface
 * @param os_spi_t *pointer to the SPI interface
 */
int os_spi_initialize(os_spi_t *spi, int fd, os_spi_gpio_t *gpio);

/**
 * @brief Stops the SPI interface
 * @param os_spi_t *pointer to the SPI interface
 */
int os_spi_deinit(os_spi_t *spi);

/**
 * @brief We need to pair a device on the spi_bus;
 */
int os_spi_couple_device(os_device_init_params init_params, os_device_t *device);

/**
 * @brief Sets the SPI interface Speed
 * @param os_spi_t *pointer to the SPI interface
 * @param uint32_t freq_hz speed of interface
 */
int os_spi_setbus(os_spi_t *spi, uint32_t freq_hz);

/**
 * @brief Transfers data to/from the SPI interface
 * @param os_spi_t *pointer to the SPI interface
 * @param uint8_t* pointer to recieving buffer
 * @param uint8_t* pointer to sending buffer
 * @param size_t size of buffer transfering
 */
int os_spi_transfer(os_spi_t *spi, uint8_t *rx, uint8_t *tx, size_t size);

/**
 * @brief Sends data to the SPI interface
 * @param os_spi_t *pointer to the SPI interface
 * @param uint8_t *buf pointer to sending buffer
 * @param size_t size of buffer sending data out
 */
int os_spi_send(os_spi_t *spi, uint8_t *buf, size_t size);

/**
 * @brief Recieves Data from the SPI interface
 * @param os_spi_t *pointer to the SPI interface
 * @param uint8_t *buf pointer to recieving buffer
 * @param size_t size of buffer reciving data in
 */
int os_spi_recieve(os_spi_t *spi, uint8_t *buf, size_t size);
#endif