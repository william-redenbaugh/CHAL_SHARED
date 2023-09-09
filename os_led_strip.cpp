/**
 * @file os_led_strip.cpp
 * @brief This file contains the implementation of the OS LED strip module.
 * 
 * The OS LED strip module is responsible for controlling LED strips.
 * It provides functions for initializing the LED strip, setting the color of specific pixels,
 * and showing the updated colors on the strip.
 */
#include "os_led_strip.h"
#include "global_includes.h"
#include "global_includes.h"

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
 * @param numpixels The number of pixels in the LED strip.
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_init(os_led_strip_t *strip, led_strip_type_t type, int bus, int gpio, uint32_t numpixels)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    // Set number of pixels
    strip->numpixel = numpixels;
    
    switch (type)
    {
#ifdef NEOPIXEL_LED_STRIP
    case STRIP_NEOPIXEL_RGB:
        strip->strip = _neopixel_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _neopixel_os_led_strip_set;
        strip->strip_show_func = _neopixel_os_led_strip_show;
        break;
#endif

#ifdef LED_STRIP_RMT
    case STRIP_RMT_RGB:
        strip->strip = _rmt_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _rmt_os_led_strip_set;
        strip->strip_show_func = _rmt_os_led_strip_show;
        break;
#endif
    }

    if (strip->strip == NULL)
    {
        return OS_RET_LOW_MEM_ERROR;
    }

    return OS_RET_OK;
}

// These are essentially wrapper functions since we can change the type of LED strip we want to use
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
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_set(os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    return strip->strip_set_func(strip->strip, pixel, r, g, b);
}

/**
 * @brief Shows the updated LED colors on the strip.
 * 
 * This function updates the LED strip with the colors previously set using os_led_strip_set(),
 * os_led_strip_set_rgb(), or os_led_strip_set_hsv().
 * 
 * @param strip A pointer to the initialized LED strip structure.
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_show(os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    return strip->strip_show_func(strip->strip);
}

/**
 * @brief Sets the color of a specific pixel in the LED strip using an RGB color structure.
 * 
 * This function sets the RGB color of a specific pixel in the LED strip using an RGB color structure.
 * 
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param col The RGB color structure containing the red, green, and blue components of the pixel's color.
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col)
{
    return os_led_strip_set(strip, pixel, col.r, col.g, col.b);
}

/**
 * @brief Sets the color of a specific pixel in the LED strip using an HSV color structure.
 * 
 * This function sets the RGB color of a specific pixel in the LED strip using an HSV color structure.
 * 
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param col The HSV color structure containing the hue, saturation, and value components of the pixel's color.
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_set_hsv(os_led_strip_t *strip, uint32_t pixel, hsv_t col)
{
    rgb_t col_rgb = hsv2rgb(col);
    return os_led_strip_set(strip, pixel, col_rgb.r, col_rgb.g, col_rgb.b);
}
#endif