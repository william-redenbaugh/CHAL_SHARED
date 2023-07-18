#ifndef _CSAL_LEDMATRIX_H
#define _CSAL_LEDMATRIX_H

#include "global_includes.h"
#include "color_conv.h"

/**
 * @brief function pointer for initializing a led matrix
 * @param void *ptr to whatever data struct holding the actual ledmatrix implementation data
 * @param int width
 * @param int height
 */
typedef int (*os_init_ledmatrix_ptr)(void *ptr, int width, int height);

/**
 * @brief Function pointer to set a specific pixel to a specific color
 * @param void *ptr to whatever data struct holding the actual ledmatrix implementation data
 * @param int x pos
 * @param int y pos
 * @param rgb_t col color
 */
typedef int (*os_matrix_setpixel_ptr)(void *ptr, int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Function pointer to update the led matrix
 * @param void *ptr to whatever data struct holding the actual ledmatrix implementation data
 */
typedef int (*os_matrix_update_ptr)(void *ptr);

/**
 * @brief Populate these with the relevant matrix update commands
 * @param os_init_ledmatrix_ptr init_func: pointer to function that will initialize the led matrix
 * @param os_matrix_setpixel_ptr setpixel_func: pointer to the function that will set
 * @param os_matrix_update_ptr update fun: Function that updates the led matrix to the specific color
 * @param int width width of led matrix
 * @param int height height of led matrix
 * @param void *matrix_ptr pointer to data structure used for whatever eld matrix
 */
typedef struct os_ledmatrix_init
{
    os_init_ledmatrix_ptr init_func;
    os_matrix_setpixel_ptr setpixel_func;
    os_matrix_update_ptr update_func;

    int width;
    int height;
    void *matrix_ptr;
} os_ledmatrix_init_t;

/**
 * @brief LED matrix handler
 */
typedef struct os_ledmatrix
{
    os_init_ledmatrix_ptr init_func;
    os_matrix_setpixel_ptr setpixel_func;
    os_matrix_update_ptr update_fun;

    void *data_ptr;
    int width;
    int height;
} os_ledmatrix_t;

/**
 * @brief Initialize matrix
 * @param os_ledmatrix_init_t matrix initialization structure
 * @param os_ledmatrix_t *matrix that we want to initialize
 */
int os_init_ledmatrix(os_ledmatrix_init_t matrix_init, os_ledmatrix_t *matrix);

/**
 * @brief Set pixel ledmatrix
 * @param os_ledmatrix_t *matrix that we want to initialize
 * @param int x pos
 * @param int y pos
 * @param rgb_t col color
 */
int os_setpixel_ledmatrix(os_ledmatrix_t *matrix, int x, int y, rgb_t rgb);

/**
 * @brief Set pixel ledmatrix to specific hsv value
 * @param os_ledmatrix_t *matrix that we want to initialize
 * @param int x pos
 * @param int y pos
 * @param hsv_t col color
 */
int os_setpixel_ledmatrix_hsv(os_ledmatrix_t *matrix, int x, int y, hsv_t hsv);

/**
 * @brief Updates the ledmatrix
 * @param os_ledmatrix_t *matrix that we want to initialize
 */
int os_ledmatrix_update(os_ledmatrix_t *matrix);

#endif