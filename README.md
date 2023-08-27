# CHAL_SHARED
Shared libraries for all our CHAL components

### Module Definitions

#### Color Conversion Module
- Files can be found under```color_conv.h/.cpp```
- Module allows for easy conversion between HSV and RGB colors
- Also converts between the Kelvin white balance value and it's RGB counter part

#### IPC Impleemntation
- Files can be found under ```csal_ipc_message_publishqueue.cpp/h cal_ipc_message_subscribequeue.cpp/.h csal_ipc_thread.cpp/.h csal_ipc.h.h/.cpp```
- IPC management layer to talk to other devices over serialized interfaces.  Implements both callbacks and queues for handling events/data sent over the IPC
- Subcribequeue and publish queue are separate threads handling data. 
- Relies on preconfigured enumerated messages

#### LED Matrix module
- Files can be found in ```csal_ledmatrix.cpp/.h```
- Generic LED matrix handler.

#### LED Strip modules
- Files can be found in ```os_led_strip.cpp/.h```
- Generic LED strip handler for all LED strip data

### Hardaware  Prototypes and declarations
All of our hardware modules that may or may not be implemented are wraped through modules defined inside here. 

- SPI ```os_spi.h```
- Bluetooth ```os_bt.h```
- GPIO ```os_gpio.h```
- I2S ```os_i2s.h```
- I2C ```os_i2c.h```
- UART ```os_uart.h```
- WiFi ```os_wifi.h```
- ADC ```os_adc.h```