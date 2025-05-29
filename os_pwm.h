#ifndef _OS_PWM_H
#define _OS_PWM_H
#include "stdint.h"

/**
 * @brief Initializes a gpio pin to output a pwm signal of a specific duty cycle frequency, and resolution from 1 to 2^n bits resolution
 * @param int gpio to set
 * @param int frequency to control
 * @param int resolution of the gpio pin
 */
int os_pwm_gpio_init(int gpio, int freq, int resolution);

/**
 * @brief Sets a gpio pin to a value between 0->2^n set value, and it will run 0->2^n/2^n as a percentage of time at the duty cycle we run at
 * @param int gpio
 * @param int value between 0 and 2^n set during the initialization
 */
int os_pwm_gpio_set(int gpio, int value);

/**
 * @brief PWM deinitialize on a specified GPIO
 * @param int gpio
 */
int os_pwm_gpio_uninit(int gpio);

#endif