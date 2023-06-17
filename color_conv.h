#ifndef _KELVIN_RGB_H
#define _KELVIN_RGB_H

#include "stdint.h"
/**
 * @brief Structure representing an RGB color.
 */
typedef struct {
    uint8_t r; /**< Red component value. */
    uint8_t g; /**< Green component value. */
    uint8_t b; /**< Blue component value. */
} rgb_t;

/**
 * @brief Structure representing an HSV color.
 */
typedef struct {
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


#endif