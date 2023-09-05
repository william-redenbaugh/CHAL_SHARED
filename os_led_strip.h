#ifndef _OS_LED_STRIP_H
#define _OS_LED_STRIP_H
#include "platform_cshal.h"
#include "color_conv.h"
#include "enabled_modules.h"
#ifdef OS_LED_STRIP

/**
 * @brief Initializes the LED strip.
 *
 * This function initializes the LED strip with the specified parameters.
 *
 * @param strip A pointer to the LED strip structure to be initialized.
 * @param type The type of LED strip being used (e.g., RGB, RGBW, etc.).
 * @param bus The bus number to which the LED strip is connected.
 * @param gpio The GPIO number used for the LED strip data line.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_init(os_led_strip_t *strip, led_strip_type_t type, int bus, int gpio, uint32_t numpixels);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the RGB color of a specific pixel in the LED strip.
 *
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param r The red component of the pixel's color (0-255).
 * @param g The green component of the pixel's color (0-255).
 * @param b The blue component of the pixel's color (0-255).
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_set(os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the RGB color of a specific pixel in the LED strip.
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param rgb_t the red, green, blue componenet
 */
int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the RGB color of a specific pixel in the LED strip.
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param hsv_t the red, green, blue componenet
 */
int os_led_strip_set_hsv(os_led_strip_t *strip, uint32_t pixel, hsv_t col);

/**
 * @brief Shows the updated LED colors on the strip.
 *
 * This function åupdates the LED strip with the colors previously set using os_led_strip_set().
 *
 * @param strip A pointer to the initialized LED strip structure.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_show(os_led_strip_t *strip);

#endif
#endif