/**
 * @file i2s_library.h
 * @brief I2S Library for audio data transfer.
 */

#ifndef I2S_LIBRARY_H
#define I2S_LIBRARY_H

#ifdef OS_I2S
/**
 * @brief Pinmap for i2s devices
 */
typedef struct os_i2s_pinmap
{
    int serial_clk;
    int left_right_clk;
    int serial_data;
    int serial_data_cs;
} os_i2s_pinmap_t;

/**
 * @brief Enumeration for I2S sample data size in bits.
 */
typedef enum
{
    I2S_SAMPLE_32BITS, /**< 32 bits per sample */
    I2S_SAMPLE_16BITS, /**< 16 bits per sample */
    I2S_SAMPLE_8BITS   /**< 8 bits per sample */
} os_i2s_sample_bits_t;

/**
 * @brief Enumeration for I2S audio channel configuration.
 */
typedef enum
{
    I2S_CHANNEL_LEFT,  /**< Left audio channel */
    I2S_CHANNEL_RIGHT, /**< Right audio channel */
    I2S_CHANNEL_BOTH   /**< Both audio channels (stereo) */
} os_i2s_channels_t;

/**
 * @brief I2S host initialization function.
 *
 * This function initializes the I2S host with the provided configuration.
 *
 * @param host Pointer to the I2S host structure.
 * @param bus The I2S bus number to be used.
 * @param chan The audio channel configuration (left, right, or both).
 * @param bits The sample data size in bits (8, 16, or 32 bits).
 * @param sample_rate The desired audio sample rate in Hz.
 * @return 0 on success, -1 on failure.
 */
int i2s_host_init(os_i2s_host_t *host, int bus, os_i2s_pinmap_t pinmap, os_i2s_channels_t chan, os_i2s_sample_bits_t bits, uint32_t sample_rate);

/**
 * @brief Read audio data from the I2S host.
 *
 * This function reads audio data from the I2S host into the provided buffer.
 *
 * @param host Pointer to the I2S host structure.
 * @param ptr Pointer to the destination buffer where the audio data will be stored.
 * @param len Number of bytes to read from the I2S host.
 * @return The number of bytes read, which can be less than len if there's not enough data available.
 */
int i2s_host_read(os_i2s_host_t *host, void *ptr, size_t *len);

/**
 * @brief Add's a device to the bus interface
 * @param os_i2s_host_t *host bus interface we are using
 * @param os_i2s_device_t *device
 * @param int chip_select_gpio for whatever is selected device
 */
int i2s_device_host_couple(os_i2s_host_t *host, os_i2s_device_t *device, int chip_select_gpio);

#endif // I2S_LIBRARY_H
#endif