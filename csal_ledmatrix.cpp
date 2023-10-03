#include "csal_ledmatrix.h"
#include "global_includes.h"

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

    return matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);
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

    return matrix->setpixel_func(matrix->data_ptr, x, y, rgb.r, rgb.g, rgb.b);
}

int os_ledmatrix_update(os_ledmatrix_t *matrix)
{
    if (matrix == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    return matrix->update_fun(matrix->data_ptr);
}