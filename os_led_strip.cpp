#include "os_led_strip.h"
#include "global_includes.h"

#ifdef OS_LED_STRIP
int os_led_strip_init(os_led_strip_t *strip, led_strip_type_t type, int bus, int gpio, uint32_t numpixels)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    // Set number of pixels
    strip->numpixel = numpixels;

    int ret = os_mut_init(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    switch (type)
    {
#ifdef NEOPIXEL_LED_STRIP
    case STRIP_NEOPIXEL_RGB:
    {
        strip->strip = _neopixel_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _neopixel_os_led_strip_set;
        strip->strip_show_func = _neopixel_os_led_strip_show;
        strip->strip_update_brightness_func = _neopixel_led_strip_set_brightness;
        break;
    }
#endif

#ifdef LED_STRIP_RMT
    case STRIP_RMT_RGB:
    {
        strip->strip = _rmt_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _rmt_os_led_strip_set;
        strip->strip_show_func = _rmt_os_led_strip_show;
        strip->strip_update_brightness_func = _rmt_dma_os_led_strip_set_brightness;
        break;
    }
#endif
#ifdef ARDUINO_SPI_ESP32_STRIP
    case STRIP_ARDUINO_SPI_DMA_RGB:
    {
        strip->strip = _spi_dma_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _spi_dma_os_led_strip_set;
        strip->strip_show_func = _spi_dma_os_led_strip_show;
        strip->strip_update_brightness_func = _spi_dma_os_led_strip_set_brightness;
    break;
    }
#endif

#ifdef ARDUINO_I2S_ESP32_STRIP
    case STRIP_ARDUINO_I2S_DMA_RGB:
    {
        strip->strip = _i2s_dma_os_led_strip_init(bus, gpio, numpixels);
        strip->strip_set_func = _i2s_dma_os_led_strip_set;
        strip->strip_show_func = _i2s_dma_os_led_strip_show;
        strip->strip_update_brightness_func = _i2s_dma_os_led_strip_set_brightness;
    break;
    }
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

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    int final_ret = strip->strip_set_func(strip->strip, pixel, r, g, b);
    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return final_ret;
}

int os_led_strip_show(os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    int final_ret = strip->strip_show_func(strip->strip);
    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return final_ret;
}

int os_led_strip_set_rgb(os_led_strip_t *strip, uint32_t pixel, rgb_t col)
{
    return os_led_strip_set(strip, pixel, col.r, col.g, col.b);
}

int os_led_strip_set_rgb_range(os_led_strip_t *strip, uint32_t lower_range, uint32_t upper_range, rgb_t *col)
{
    // Bounds check!
    if (lower_range >= strip->numpixel | upper_range >= strip->numpixel)
    {
        return OS_RET_INVALID_PARAM;
    }

    if (lower_range >= upper_range)
    {
        return OS_RET_INVALID_PARAM;
    }

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    // Iterate through range of pixels to set in range
    for (int n = lower_range; n <= upper_range; n++)
    {
        ret = strip->strip_set_func(strip->strip, n, col[lower_range + n].r, col[lower_range + n].g, col[lower_range + n].b);
        if (ret != OS_RET_OK)
        {
            // Failiure somewhere, exit out!
            int final_ret = os_mut_exit(&strip->mutex);
            if (final_ret != OS_RET_OK)
            {
                return final_ret;
            }
            return ret;
        }
    }

    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return ret;
}

int os_led_strip_set_hsv_range(os_led_strip_t *strip, uint32_t lower_range, uint32_t upper_range, hsv_t *col)
{
    // Bounds check!
    if (lower_range >= strip->numpixel | upper_range >= strip->numpixel)
    {
        return OS_RET_INVALID_PARAM;
    }

    if (lower_range >= upper_range)
    {
        return OS_RET_INVALID_PARAM;
    }

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    // Iterate through range of pixels to set in range
    for (int n = lower_range; n <= upper_range; n++)
    {
        rgb_t col_rgb = hsv2rgb(col[lower_range + n]);

        ret = strip->strip_set_func(strip->strip, n, col_rgb.r, col_rgb.g, col_rgb.b);
        if (ret != OS_RET_OK)
        {
            // Failiure somewhere, exit out!
            int final_ret = os_mut_exit(&strip->mutex);
            if (final_ret != OS_RET_OK)
            {
                return final_ret;
            }
            return ret;
        }
    }

    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return ret;
}

int os_led_strip_fill_rgb_range(os_led_strip_t *strip, uint32_t lower_range, uint32_t upper_range, rgb_t col)
{
    // Bounds check!
    if (lower_range >= strip->numpixel | upper_range >= strip->numpixel)
    {
        return OS_RET_INVALID_PARAM;
    }

    if (lower_range >= upper_range)
    {
        return OS_RET_INVALID_PARAM;
    }

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    // Iterate through range of pixels to set in range
    for (int n = lower_range; n <= upper_range; n++)
    {

        ret = strip->strip_set_func(strip->strip, n, col.r, col.g, col.b);
        if (ret != OS_RET_OK)
        {
            // Failiure somewhere, exit out!
            int final_ret = os_mut_exit(&strip->mutex);
            if (final_ret != OS_RET_OK)
            {
                return final_ret;
            }
            return ret;
        }
    }

    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return ret;
}

int os_led_strip_fill_hsv_range(os_led_strip_t *strip, uint32_t lower_range, uint32_t upper_range, hsv_t col)
{
    // Bounds check!
    if (lower_range >= strip->numpixel | upper_range >= strip->numpixel)
    {
        return OS_RET_INVALID_PARAM;
    }

    if (lower_range >= upper_range)
    {
        return OS_RET_INVALID_PARAM;
    }

    int ret = os_mut_entry_wait_indefinite(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    rgb_t col_rgb = hsv2rgb(col);

    // Iterate through range of pixels to set in range
    for (int n = lower_range; n <= upper_range; n++)
    {
        ret = strip->strip_set_func(strip->strip, n, col_rgb.r, col_rgb.g, col_rgb.b);
        if (ret != OS_RET_OK)
        {
            // Failiure somewhere, exit out!
            int final_ret = os_mut_exit(&strip->mutex);
            if (final_ret != OS_RET_OK)
            {
                return final_ret;
            }
            return ret;
        }
    }

    ret = os_mut_exit(&strip->mutex);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    return ret;
}

int os_led_strip_set_hsv(os_led_strip_t *strip, uint32_t pixel, hsv_t col)
{
    rgb_t col_rgb = hsv2rgb(col);
    return os_led_strip_set(strip, pixel, col_rgb.r, col_rgb.g, col_rgb.b);
}
#endif