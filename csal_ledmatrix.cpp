#include "csal_ledmatrix.h"
#include "global_includes.h"

bool is_valid_line(os_2d_line_t line)
{
    if (line.p1.x > line.p2.x)
        return false;
    if (line.p1.y > line.p2.y)
        return false;
    return true;
}

static int os_matrix_draw_vline(os_ledmatrix_t *matrix, int len, os_2d_point_t point, rgb_t col)
{

    for (int n = point.y; n <= point.y + len; n++)
    {
        matrix->setpixel_func(matrix->data_ptr, point.x, n, col.r, col.g, col.b);
    }

    return OS_RET_OK;
}

/*
static int os_matrix_draw_hline(os_ledmatrix_t *matrix, int len, os_2d_point_t point, rgb_t col)
{
    for (int n = point.x; n <= point.x + len; n++)
    {
        matrix->setpixel_func(matrix->data_ptr, n, point.y, col.r, col.g, col.b);
    }

    return OS_RET_OK;
}
*/

// Swaps x n y corrdinates to make them valid
os_2d_line_t os_make_line_valid(os_2d_line_t line)
{
    if (line.p1.x > line.p2.x)
    {
        int x = line.p1.x;
        line.p1.x = line.p2.x;
        line.p2.x = x;
    }

    if (line.p1.y > line.p2.y)
    {
        int y = line.p1.y;
        line.p1.y = line.p2.y;
        line.p2.y = y;
    }

    return line;
}

int os_drawline_ledmatrix_hsv(os_ledmatrix_t *matrix, os_2d_line_t line, hsv_t hsv)
{
    rgb_t col = hsv2rgb(hsv);
    return os_drawline_ledmatrix(matrix, line, col);
}

int os_drawline_ledmatrix(os_ledmatrix_t *matrix, os_2d_line_t line, rgb_t rgb)
{

    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    // Make sure line is valid to rasterize
    line = os_make_line_valid(line);

    int x1 = line.p1.x;
    int x2 = line.p2.x;
    int y1 = line.p1.y;
    int y2 = line.p2.y;

    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    for (int x = x1, y = y1; x <= x2; x++)
    {
        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0)
        {
            y++;
            slope_error_new -= 2 * (x2 - x1);
        }
        // os_printf("x:%d, y:%d\n", x, y);
        matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);
    }

    return OS_RET_OK;
}

int os_init_ledmatrix(os_ledmatrix_init_t matrix_init, os_ledmatrix_t *matrix)
{

    if (matrix == NULL)
    {
        Serial.println("Matrix null");
        return OS_RET_NULL_PTR;
    }

    // Basic checking of the structure to make sure none of the parameters are off
    if ((matrix_init.init_func == NULL) |
        (matrix_init.setpixel_func == NULL) |
        (matrix_init.update_func == NULL) |
        (matrix_init.matrix_ptr == NULL) |
        (matrix_init.height == 0) |
        (matrix_init.width == 0))
    {

        return OS_RET_INVALID_PARAM;
    }

    matrix->init_func = matrix_init.init_func;
    matrix->setpixel_func = matrix_init.setpixel_func;
    matrix->update_fun = matrix_init.update_func;
    matrix->height = matrix_init.height;
    matrix->width = matrix_init.width;
    matrix->data_ptr = matrix_init.matrix_ptr;

    matrix->matrix_mut = malloc(sizeof(os_mut_t));
    int ret = os_mut_init((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    // Calls the initialization function
    return matrix->init_func(matrix->data_ptr, matrix->width, matrix->height);
}

static inline int os_drawcircle_ledmatrix_outline(os_ledmatrix_t *matrix, os_2d_circle_t circle, rgb_t rgb)
{
    int x0 = circle.p.x;
    int y0 = circle.p.y;
    int r = circle.intensity;

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    matrix->setpixel_func(matrix->data_ptr, x0, y0 + r, rgb.r, rgb.g, rgb.b);
    matrix->setpixel_func(matrix->data_ptr, x0, y0 - r, rgb.r, rgb.g, rgb.b);
    matrix->setpixel_func(matrix->data_ptr, x0 + r, y0, rgb.r, rgb.g, rgb.b);
    matrix->setpixel_func(matrix->data_ptr, x0 - r, y0, rgb.r, rgb.g, rgb.b);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        matrix->setpixel_func(matrix->data_ptr, x0 + x, y0 + y, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 - x, y0 + y, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 + x, y0 - y, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 - x, y0 - y, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 + y, y0 + x, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 - y, y0 + x, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 + y, y0 - x, rgb.r, rgb.g, rgb.b);
        matrix->setpixel_func(matrix->data_ptr, x0 - y, y0 - x, rgb.r, rgb.g, rgb.b);
    }
    return OS_RET_OK;
}

static inline int os_drawcircle_ledmatrix_fill(os_ledmatrix_t *matrix, os_2d_circle_t circle, rgb_t rgb)
{
    os_2d_point_t point = circle.p;
    int r = circle.intensity;
    point.y = point.y - r;
    // Drawin center line hehe
    os_matrix_draw_vline(matrix, 2 * r + 1, point, rgb);

    int corners = 3;
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    int16_t px = x;
    int16_t py = y;
    int x0 = circle.p.x;
    int y0 = circle.p.y;

    int delta = 1;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if (x < (y + 1))
        {
            if (corners & 1)
            {
                point.x = x0 + x;
                point.y = y0 - y;
                os_matrix_draw_vline(matrix, 2 * y + delta, point, rgb);
            }

            if (corners & 2)
            {
                point.x = x0 - x;
                point.y = y0 - y;
                os_matrix_draw_vline(matrix, 2 * y + delta, point, rgb);
            }
        }
        if (y != py)
        {
            if (corners & 1)
            {
                point.x = x0 + py;
                point.y = y0 - px;
                os_matrix_draw_vline(matrix, 2 * px + delta, point, rgb);
            }
            if (corners & 2)
            {
                point.x = x0 - py;
                point.y = y0 - px;
                os_matrix_draw_vline(matrix, 2 * px + delta, point, rgb);
            }
            py = y;
        }
        px = x;
    }

    return OS_RET_OK;
}

int os_drawcircle_ledmatrix(os_ledmatrix_t *matrix, os_2d_circle_t circle, rgb_t rgb, os_ledmatrix_fill_type_t fill_type)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    switch (fill_type)
    {
    case MATRIX_2D_FILL_OUTLINE:
        return os_drawcircle_ledmatrix_outline(matrix, circle, rgb);

    case MATRIX_2D_FILL_FULL:
        return os_drawcircle_ledmatrix_fill(matrix, circle, rgb);

    default:
        return OS_RET_INVALID_PARAM;
    }
}

int os_setpixel_ledmatrix(os_ledmatrix_t *matrix, int x, int y, rgb_t rgb)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if ((x > matrix->width) | (y > matrix->height))
    {
        return OS_RET_INVALID_PARAM;
    }

    int final_ret = OS_RET_OK;
    int ret = os_mut_entry_wait_indefinite((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    final_ret = matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);
    ret = os_mut_exit((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    return final_ret;
}

int os_setpixel_ledmatrix_hsv(os_ledmatrix_t *matrix, int x, int y, hsv_t hsv)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if ((x > matrix->width) | (y > matrix->height))
    {
        return OS_RET_INVALID_PARAM;
    }
    rgb_t rgb = hsv2rgb(hsv);

    int final_ret;
    int ret = os_mut_entry_wait_indefinite((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    final_ret = matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);
    ret = os_mut_exit((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    return final_ret;
}

int os_ledmatrix_update(os_ledmatrix_t *matrix)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    int final_ret;
    int ret = os_mut_entry_wait_indefinite((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }
    final_ret = matrix->update_fun(matrix->data_ptr);
    ret = os_mut_exit((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    return final_ret;
}

int os_setpixel_ledmatrix_hsv_image(os_ledmatrix_t *matrix, hsv_t *hsv_range)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    int final_ret = OS_RET_OK;
    int ret = os_mut_entry_wait_indefinite((os_mut_t *)matrix->matrix_mut);

    for (int x = 0; x < matrix->width; x++)
    {
        for (int y = 0; y < matrix->height; y++)
        {
            rgb_t rgb = hsv2rgb(hsv_range[x * matrix->width + y]);
            ret = matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);

            // Failiure to update LED matrix
            if (ret != OS_RET_OK)
            {
                int final_ret = os_mut_exit((os_mut_t *)matrix->matrix_mut);
                if (final_ret != OS_RET_OK)
                {
                    return final_ret;
                }
                return ret;
            }
        }
    }

    ret = os_mut_exit((os_mut_t *)matrix->matrix_mut);
    if (ret != OS_RET_OK)
    {
        return ret;
    }

    return final_ret;
}