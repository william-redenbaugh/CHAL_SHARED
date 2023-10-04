#include "global_includes.h"

#ifdef OS_TEST_SPI

static os_spi_t spi_bus;
static os_device_t spi_device;

void test_spi(void *parameters)
{
    int ret = os_spi_initialize(&spi_bus, 2, NULL);

    if (ret != 0)
    {
        Serial.printf("Failed to initialize spi: %d\n", ret);
    }

    os_device_init_params params = {
        .dma_buf_size = 2048,
        .spi_mode = 0,
        .cs_gpio = GPIO_NUM_9,
        .clk = 2000000,
        .bus = &spi_bus,
    };
    ret = os_spi_couple_device(params, &spi_device);
    if (ret != 0)
    {
        Serial.printf("Failed to initialize spi device: %d\n", ret);
    }

    uint8_t rx_buff[20];
    uint8_t tx_buff[20];
    ret = os_spi_transfer(&spi_device, rx_buff, tx_buff, sizeof(rx_buff));

    if (ret != 0)
    {
        Serial.printf("Failed to send data to spi: %d\n", ret);
    }
    // hal_ble_serial_init();
    //  eventqueue = new_local_eventqueue(20);
    //  attach_event(EVENT_LED_UPDATE, event_callback);
}

#endif
