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

    Serial.println("Drawing line");

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
        // Serial.printf("x:%d, y:%d\n", x, y);
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
    if (matrix_init.init_func == NULL |
        matrix_init.setpixel_func == NULL |
        matrix_init.update_func == NULL |
        matrix_init.matrix_ptr == NULL |
        matrix_init.height == 0 |
        matrix_init.width == 0)
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

int os_setpixel_ledmatrix(os_ledmatrix_t *matrix, int x, int y, rgb_t rgb)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if (x > matrix->width | y > matrix->height)
    {
        return OS_RET_INVALID_PARAM;
    }

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

int os_setpixel_ledmatrix_hsv(os_ledmatrix_t *matrix, int x, int y, hsv_t hsv)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if (x > matrix->width | y > matrix->height)
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

    int final_ret;
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