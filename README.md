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
    - Mostly function declarations, and maybe some platform generic calls for the SPI bus interface.
    - Setup such that you need to first initialize a SPI bus, then you can "add" hosts onto the bus, ergo setting up a chip select pin and connecting it to a selected SPI bus on whatever gpio pins(or whatever the platform supports)
- Bluetooth ```os_bt.h```
     - Mostly function declarations, bluetooth endpoints and descripter information. 
     - Helps send data, setup callbacks for received data from specific endpoints and descripters. 
     - Non BLE interface information
- GPIO ```os_gpio.h```
    - General purpose IO function declarations, and maybe some helper code that's platform agnostic.
- I2S ```os_i2s.h```
     - Mostly function declarations, and maybe some platform generic calls for the I2C bus interface.
     - Sets up device on bus(based off chip select pin), send data to that device
- I2C ```os_i2c.h```
    - Mostly function declarations, and maybe some platform generic calls for the I2C bus interface.
     - Basic interface, you can send out data to a specific address on the bus.
- UART ```os_uart.h```
    - Mostly function declarations, and maybe some platform generic calls for the I2C bus interface.
     - Basic interface, you setup the gpios(if supported on the platform, otherwise it's whatever gpio they are set on) and send data, no device or address
- WiFi ```os_wifi.h```
    - Mostly function declarations, and maybe some platform generic calls for the WiFi interface
    - Currently only designed for a singular WiFi interfaces, and no ethernet
    - Construct and deconstruct connectionst to WiFi interfaces
    - Hosting TCP and UDP socket servers, also supports TCP and UDP socket clients
- ADC ```os_adc.h```
    - General purpose IO function declarations, and maybe some helper code that's platform agnostic.