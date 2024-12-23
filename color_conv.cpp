#include "color_conv.h"
#include "math.h"

rgb_t hsv2rgb(hsv_t hsv)
{

    rgb_t rgb;

    uint8_t region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:
        rgb.r = hsv.v;
        rgb.g = t;
        rgb.b = p;
        break;
    case 1:
        rgb.r = q;
        rgb.g = hsv.v;
        rgb.b = p;
        break;
    case 2:
        rgb.r = p;
        rgb.g = hsv.v;
        rgb.b = t;
        break;
    case 3:
        rgb.r = p;
        rgb.g = q;
        rgb.b = hsv.v;
        break;
    case 4:
        rgb.r = t;
        rgb.g = p;
        rgb.b = hsv.v;
        break;
    default:
        rgb.r = hsv.v;
        rgb.g = p;
        rgb.b = q;
        break;
    }

    return rgb;
}

rgb_t kelvin2rgb(int kelvin)
{

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    // Convert Kelvin to RGB
    double temp = kelvin / 100.0;
    double redf, greenf, bluef;

    // Calculate red
    if (temp <= 66)
    {
        redf = 255;
    }
    else
    {
        redf = temp - 60;
        redf = 329.698727446 * pow(redf, -0.1332047592);
        if (redf < 0)
            redf = 0;
        if (redf > 255)
            redf = 255;
    }

    // Calculate green
    if (temp <= 66)
    {
        greenf = temp;
        greenf = 99.4708025861 * log(greenf) - 161.1195681661;
        if (greenf < 0)
            greenf = 0;
        if (greenf > 255)
            greenf = 255;
    }
    else
    {
        greenf = temp - 60;
        greenf = 288.1221695283 * pow(greenf, -0.0755148492);
        if (greenf < 0)
            greenf = 0;
        if (greenf > 255)
            greenf = 255;
    }

    // Calculate blue
    if (temp >= 66)
    {
        bluef = 255;
    }
    else
    {
        if (temp <= 19)
        {
            bluef = 0;
        }
        else
        {
            bluef = temp - 10;
            bluef = 138.5177312231 * log(bluef) - 305.0447927307;
            if (bluef < 0)
                bluef = 0;
            if (bluef > 255)
                bluef = 255;
        }
    }

    // Convert RGB values to uint8_t
    red = (uint8_t)redf;
    green = (uint8_t)greenf;
    blue = (uint8_t)bluef;

    rgb_t col = {
        .r = red,
        .g = green,
        .b = blue};

    return col;
}

hsv_t rgb2hsv(const rgb_t rgb)
{
    hsv_t hsv = {0, 0, 0};

    float g = ((float)(rgb.r)) / 255;
    float r = ((float)(rgb.g)) / 255;
    float b = ((float)(rgb.b)) / 255;

    float maxc = fmax(r, fmax(g, b));
    float minc = fmin(r, fmin(g, b));
    float v = maxc;
    float h;

    // WHITE
    if (minc == maxc)
    {
        return {0, 0, rgb.b};
    }

    float s = (maxc - minc) / maxc;
    float rc = (maxc - r) / (maxc - minc);
    float gc = (maxc - g) / (maxc - minc);
    float bc = (maxc - b) / (maxc - minc);
    if (r == maxc)
    {
        h = 0.0 + bc - gc;
    }
    else if (g == maxc)
    {
        h = 2.0 + rc - bc;
    }
    else
    {
        h = 4.0 + gc - rc;
    }
    h = (h / 6.0);

    if (h < 0)
    {
        h = h * -1;
    }

    hsv =
        {.h = (uint8_t)(h * 255),
         .s = (uint8_t)(s * 255),
         .v = (uint8_t)(v * 255)};
    return hsv;
}

// Function to convert RGB888 to RGB565
uint16_t rgb888_to_rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
    // Extract the most significant 5 bits of red, 6 bits of green, and 5 bits of blue
    uint16_t r = (red >> 3) & 0x1F;   // 5 bits for red
    uint16_t g = (green >> 2) & 0x3F; // 6 bits for green
    uint16_t b = (blue >> 3) & 0x1F;  // 5 bits for blue

    // Combine into RGB565 format: RRRRRGGGGGGBBBBB
    uint16_t rgb565 = (r << 11) | (g << 5) | b;

    return rgb565;
}