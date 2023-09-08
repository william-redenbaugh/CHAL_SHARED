#ifndef _OS_OLED_DISPLAY_H
#define _OS_OLED_DISPLAY_H

#include "platform_cshal.h"
#include "color_conv.h"
#include "enabled_modules.h"

#ifdef OS_OLED_DISPLAY

struct _os_oled_display_t;

typedef int (*oled_display_init_t)(_os_oled_display_t *display);
typedef int (*oled_display_set_pixel_t)(_os_oled_display_t *display, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
typedef int (*oled_display_update_t)(_os_oled_display_t *display);

typedef struct os_oled_display_t
{
    _os_oled_display_t *display;
    os_mut_t mutex;
    int width;
    int height;

    // Function pointers for initializing, setting pixels, and updating the display.
    oled_display_init_t display_init_func;
    oled_display_set_pixel_t display_set_pixel_func;
    oled_display_update_t display_update_func;

} os_oled_display_t;

int os_oled_display_init(os_oled_display_t *display, int bus, int gpio, uint32_t width, uint32_t height);
int os_oled_display_set_pixel(os_oled_display_t *display, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
int os_oled_display_update(os_oled_display_t *display);

#endif
#endif
