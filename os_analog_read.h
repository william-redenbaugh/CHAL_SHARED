#ifndef _OS_ANALOG_READ_H
#define _OS_ANALOG_READ_H
#include "stdint.h"
#include "stdlib.h"

struct dma_adc_handle_t;

/**
 * @brief Initializes the DMA based ADC module available on certain platforms
 * @param int adc_channel channel that we are using for the input of the ADC data
 * @param uint32_t buffer_size how many samples are we trying to collect
 * @param uint32_t speed speed of data coming into the system 
 * @returns dma_adc_handle_t* pointer to a handler for the microphone
*/
dma_adc_handle_t* os_init_dma_adc(int adc_channel, uint32_t buffer_size, uint32_t speed);

int os_dma_read(dma_adc_handle_t *handle, uint8_t *buffer, size_t size);
#endif
