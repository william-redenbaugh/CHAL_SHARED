#include "os_led_strip.h"

int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col)
{
    return os_led_strip_set(strip, pixel, col.r, col.g, col.b);
}

int os_led_strip_set_hsv(os_led_strip_t *strip, uint32_t pixel, hsv_t col)
{
    rgb_t col_rgb = hsv2rgb(col);
    return os_led_strip_set(strip, pixel, col_rgb.r, col_rgb.g, col_rgb.b);
}