#ifndef _STATUS_LED_H

#include "stdint.h"

/**
 * @brief Initialize the Status LED to give us information
 */
void status_led_init(void *parameters);

/**
 * @brief Set the status led to whatever we want
 */
void status_led_set(uint8_t r, uint8_t g, uint8_t b);
#endif