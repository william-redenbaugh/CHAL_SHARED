/**
 * @file os_led_strip.h
 * @brief This file contains the definition of the OS LED strip module.
 * 
 * The OS LED strip module is responsible for controlling LED strips.
 * It provides functions for initializing the LED strip, setting the color of specific pixels,
 * and showing the updated colors on the strip.
 */
#ifndef _OS_LED_STRIP_H
#define _OS_LED_STRIP_H
#define _OS_LED_STRIP_H
#include "platform_cshal.h"
#include "color_conv.h"
#include "enabled_modules.h"
#ifdef OS_LED_STRIP
struct _os_led_strip_t;

// All the function definitions for the nepixel strips are here.
#ifdef NEOPIXEL_LED_STRIP
/**
 * @brief Initializes a NeoPixel LED strip object.
 *
 * This function initializes a NeoPixel LED strip object with the specified parameters.
 *
 * @param bus The communication bus identifier (e.g., SPI or I2C).
 * @param gpio The GPIO pin number to which the NeoPixel data line is connected.
 * @param numpixels The number of pixels in the LED strip.
 * @return A pointer to the initialized NeoPixel LED strip object (_os_led_strip_t*).
 */
_os_led_strip_t *_neopixel_os_led_strip_init(int bus, int gpio, uint32_t numpixels);

/**
 * @brief Sets the color of a specific pixel in the NeoPixel LED strip.
 *
 * This function sets the color of a specific pixel in the NeoPixel LED strip.
 *
 * @param strip A pointer to the NeoPixel LED strip object.
 * @param pixel The index of the pixel whose color you want to set.
 * @param r The red component of the pixel's color (0-255).
 * @param g The green component of the pixel's color (0-255).
 * @param b The blue component of the pixel's color (0-255).
 * @return 0 on success, or a negative error code on failure.
 */
int _neopixel_os_led_strip_set(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Shows the current pixel colors on the NeoPixel LED strip.
 *
 * This function sends the color data to the NeoPixel LED strip, making the
 * colors set by _neopixel_os_led_strip_set() visible on the strip.
 *
 * @param strip A pointer to the NeoPixel LED strip object.
 * @return 0 on success, or a negative error code on failure.
 */
int _neopixel_os_led_strip_show(_os_led_strip_t *strip);
#endif

// When we are using the Remote Control Module(typically for ESP32 to control LED strips)
#ifdef LED_STRIP_RMT
/**
 * @brief Initializes an LED strip object using the Remote Control Module (RMT).
 *
 * This function initializes an LED strip object for controlling LED strips using
 * the Remote Control Module (RMT), typically for ESP32.
 *
 * @param strip A pointer to the LED strip object to be initialized.
 * @param bus The communication bus identifier (e.g., SPI or I2C).
 * @param gpio The GPIO pin number to which the LED strip data line is connected.
 * @param numpixels The number of pixels in the LED strip.
 * @return 0 on success, or a negative error code on failure.
 *
 * @note This function is available only when the preprocessor macro LED_STRIP_RMT is defined.
 */
_os_led_strip_t *_rmt_os_led_strip_init(int bus, int gpio, uint32_t numpixels);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the color of a specific pixel in the LED strip.
 *
 * @param strip A pointer to the LED strip object.
 * @param pixel The index of the pixel whose color you want to set.
 * @param r The red component of the pixel's color (0-255).
 * @param g The green component of the pixel's color (0-255).
 * @param b The blue component of the pixel's color (0-255).
 * @return 0 on success, or a negative error code on failure.
 *
 * @note This function is available only when the preprocessor macro LED_STRIP_RMT is defined.
 */
int _rmt_os_led_strip_set(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Shows the current pixel colors on the LED strip.
 *
 * This function sends the color data to the LED strip, making the colors set by
 * _rmt_os_led_strip_set() visible on the strip.
 *
 * @param strip A pointer to the LED strip object.
 * @return 0 on success, or a negative error code on failure.
 *
 * @note This function is available only when the preprocessor macro LED_STRIP_RMT is defined.
 */
int _rmt_os_led_strip_show(_os_led_strip_t *strip);
#endif

typedef enum
{
#ifdef NEOPIXEL_LED_STRIP
    STRIP_NEOPIXEL_RGB,
#endif
#ifdef LED_STRIP_RMT
    STRIP_RMT_RGB
#endif
} led_strip_type_t;

/**
 * @brief Pointer Function for setting a led strip
 */
typedef int (*led_strip_set_t)(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);
typedef int (*led_strip_show_t)(_os_led_strip_t *strip);

typedef struct os_led_strip_t
{
    _os_led_strip_t *strip;
    os_mut_t mutex;
    int numpixel;

    // Function pointers for setting and showing the pixel data.
    led_strip_set_t strip_set_func;
    led_strip_show_t strip_show_func;

} os_led_strip_t;

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
int os_led_strip_set(os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the RGB color of a specific pixel in the LED strip.
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param rgb_t the red, green, blue componenet
 */
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
int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col);

/**
 * @brief Sets the color of a specific pixel in the LED strip.
 *
 * This function sets the RGB color of a specific pixel in the LED strip.
 * @param strip A pointer to the initialized LED strip structure.
 * @param pixel The index of the pixel whose color will be set.
 * @param hsv_t the red, green, blue componenet
 */
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
/**
 * @brief Shows the updated LED colors on the strip.
 * 
 * This function updates the LED strip with the colors previously set using os_led_strip_set(),
 * os_led_strip_set_rgb(), or os_led_strip_set_hsv().
 * 
 * @param strip A pointer to the initialized LED strip structure.
 * @return 0 on success, or a negative error code on failure.
 */
int os_led_strip_show(os_led_strip_t *strip);

#endif
#endif