#ifndef _CSAL_IPC_THREAD_H
#define _CSAL_IPC_THREAD_H

/**
 * Module explaination!
 * So this is the  IPC module!
 *
 * There are two separate threads for the IPC transaction: the Publish and Consume threads
 *
 * The Publish thread sits and waits for messages to be added to a queue
 * Then will go through each message, process the data, implement the forward error correction(eventually)
 * And then push the data through the  interface
 *
 * The consume thread will wait for any data through the  bus
 * Manage error correction, then any callbacks that are subscribed can then runs those callbacks!
 */

typedef enum ipc_interface_type
{
    IPC_TYPE_UART,
    IPC_TYPE_SPI,
    IPC_TYPE_I2C,
    IPC_TYPE_UDP,
    IPC_TYPE_TCP
} ipc_interface_type_t;

#define IPC_PORT_UDP (6969)

/**
 * @brief Set's the specific interface we are using for our ipc.
 */
void ipc_set_interface_type(ipc_interface_type_t interface_type);

/**
 * @brief Initialization module for the publish module for the  IPC
 * @note See top for more information
 */
void ipc_publish_init(void *params);

/**
 * @brief Publish thread! See note at top of file for more information
 */
void ipc_publish_thread(void *params);

/**
 * @brief Thread intialization for the consumption thread
 */
void ipc_consume_thread_init(void *params);
/**
 * @brief Consume thread! Get's  events from the bus
 * And runs callbacks based off those
 * Will also publish events
 */
void ipc_consume_thread(void *params);
#endif