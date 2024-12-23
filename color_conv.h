#ifndef _KELVIN_RGB_H
#define _KELVIN_RGB_H

#include "stdint.h"
/**
 * @brief Structure representing an RGB color.
 */
typedef struct
{
    uint8_t r; /**< Red component value. */
    uint8_t g; /**< Green component value. */
    uint8_t b; /**< Blue component value. */
} rgb_t;

/**
 * @brief Structure representing an HSV color.
 */
typedef struct
{
    uint8_t h; /**< Hue component value. */
    uint8_t s; /**< Saturation component value. */
    uint8_t v; /**< Value (brightness) component value. */
} hsv_t;

/**
 * @brief Converts an HSV color to an RGB color.
 *
 * @param hsv The HSV color to convert.
 * @return The RGB color converted from HSV.
 */
rgb_t hsv2rgb(hsv_t hsv);

/**
 * @brief Converts a Kelvin color temperature to an RGB color.
 *
 * @param kelvin The Kelvin color temperature.
 * @return The RGB color converted from the Kelvin temperature.
 */
rgb_t kelvin2rgb(int kelvin);

/**
 * @brief Convert RGB color to HSV color space.
 *
 * @param rgb RGB color values.
 * @return Corresponding HSV color values.
 */
hsv_t rgb2hsv(const rgb_t rgb);

/**
 * @brief Converts an RGB888 color to RGB565 format.
 *
 * This function takes the red, green, and blue components of an RGB888 color,
 * each represented as an 8-bit value, and converts them to a 16-bit RGB565 format.
 *
 * RGB565 format:
 * - 5 bits for red (MSB)
 * - 6 bits for green (middle bits)
 * - 5 bits for blue (LSB)
 *
 * @param red   The 8-bit red component (0-255).
 * @param green The 8-bit green component (0-255).
 * @param blue  The 8-bit blue component (0-255).
 * @return The 16-bit RGB565 representation of the color.
 */
uint16_t rgb888_to_rgb565(uint8_t red, uint8_t green, uint8_t blue);

#endif