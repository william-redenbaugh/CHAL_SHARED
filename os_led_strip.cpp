#include "os_led_strip.h"
#include "global_includes.h"

#ifdef OS_LED_STRIP
int os_led_strip_init(os_led_strip_t *strip, led_strip_type_t type, int bus, int gpio, uint32_t numpixels)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

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
int os_led_strip_set(os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    return strip->strip_set_func(strip->strip, pixel, r, g, b);
}

int os_led_strip_show(os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    return strip->strip_show_func(strip->strip);
}

int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col)
{
    return os_led_strip_set(strip, pixel, col.r, col.g, col.b);
}

int os_led_strip_set_hsv(os_led_strip_t *strip, uint32_t pixel, hsv_t col)
{
    rgb_t col_rgb = hsv2rgb(col);
    return os_led_strip_set(strip, pixel, col_rgb.r, col_rgb.g, col_rgb.b);
}
#endif