/**
 * @file csal_ipc_message_publishqueue.h
 * @brief This file contains the definition of the IPC message publish queue module.
 * 
 * The IPC message publish queue module is responsible for managing the IPC message publications.
 * It provides functions for pushing and popping messages from the queue, signaling new events,
 * waiting for new events, publishing messages, and receiving acknowledgments.
 */
#ifndef IPC_MESSAGE_PUBLISHQUEUE_H
#define IPC_MESSAGE_PUBLISHQUEUE_H
#define IPC_MESSAGE_PUBLISHQUEUE_H

#include "csal_ipc.h"
#include "global_includes.h"

#ifdef OS_IPC_H

#define IPC_QUEUE_MAX_NUM_ELEMENTS 16
#define TASK1_BIT (1UL << 0UL) // zero shift for bit0

typedef enum ipc_message_callback_status
{
    IPC_MESSAGE_COMPLETE_SUCCESS,
    IPC_MESSAGE_COMPLETE_FAIL,
    IPC_MESSAGE_COMPLETE_FAIL_TIMEOUT,
} ipc_message_callback_status_t;

typedef struct ipc_message_callback
{
    ipc_message_callback_status_t ipc_status;
} ipc_message_ret_t;

typedef void (*ipc_message_complete_callback_t)(ipc_message_ret_t);

typedef struct ipc_message_node
{
    ipc_message_header_t message_header;
    uint8_t *buffer_ptr;
    ipc_message_complete_callback_t callback_func;
} ipc_message_node_t;

typedef struct ipc_message_publish_module
{
    ipc_message_node_t *node_list;
    int max_size;
    int current_size;
    int head_pos;
    int tail_pos;
    os_mut_t ipc_message_node_muttx;

    // Signal handler detecting new message
    os_setbits_t new_msg_cv;
    os_setbits_t ack_msg_mp;
    os_mut_t new_msg_mp;
} ipc_message_publish_module_t;

extern ipc_message_publish_module_t *ipc_publush_queue_module;

/**
 * @brief Allows us to add a message to the message queue.
 * @note Thread safe!!!
 * @note internal call only
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 * @param ipc_message_node_t message that we are pushing
 */
/**
 * @brief Adds a message to the message queue of a specific module.
 * 
 * This function adds a specified message to the message queue of the specified module.
 * 
 * @param module The module to which the message will be added.
 * @param node The message to be added.
 * @return true if the operation was successful, false otherwise.
 */
bool _ipc_push_message_queue(ipc_message_publish_module_t *module, ipc_message_node_t node);

/**
 * @brief Allows us to add a message to the message queue.
 * @note Thread safe!!!
 * @note internal call only
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 * @param ipc_message_node_t pointer *message that we are consuming
 */
/**
 * @brief Removes a message from the message queue of a specific module.
 * 
 * This function removes a message from the message queue of the specified module.
 * 
 * @param module The module from which the message will be removed.
 * @param node A pointer to the message to be removed.
 * @return true if the operation was successful, false otherwise.
 */
bool _ipc_pop_message_queue(ipc_message_publish_module_t *module, ipc_message_node_t *node);

/**
 * @brief Sets up our IPC message queue
 */
/**
 * @brief Initializes the IPC message queue.
 * 
 * This function initializes the IPC message queue by setting up the necessary data structures.
 */
void init_ipc_message_queue(void);

/**
 * @brief Signals that a new event has been published to the module
 * @note internal call only!!!
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 */
/**
 * @brief Signals that a new event has been published to a specific module.
 * 
 * This function signals that a new event has been published to the specified module.
 * 
 * @param module The module to which the new event has been published.
 * @return 0 on success, or a negative error code on failure.
 */
int _signal_new_event(ipc_message_publish_module_t *module);
/**
 * @brief Signals that a new event has ben published to the module
 */
/**
 * @brief Signals that a new event has been published.
 * 
 * This function signals that a new event has been published to the main IPC module.
 * 
 * @return 0 on success, or a negative error code on failure.
 */
int signal_new_event(void);

/**
 * @brief Blocks until a new event has been published
 * @note internal call only!!!
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 */
/**
 * @brief Blocks until a new event has been published to a specific module.
 * 
 * This function blocks the current thread until a new event has been published to the specified module.
 * 
 * @param module The module to which the new event has been published.
 */
void _ipc_msg_queue_wait_new_event(ipc_message_publish_module_t *module);

/**
 * @brief Blocks until a new event has been published
 */
/**
 * @brief Blocks until a new event has been published.
 * 
 * This function blocks the current thread until a new event has been published to the main IPC module.
 */
void ipc_msg_queue_wait_new_event(void);

/**
 * @brief submits a new event to the message publish mmodule
 * @note internal call only
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 * @param ipc_message_node_t pointer *message that we are consuming
 */
/**
 * @brief Submits a new event to a specific module.
 * 
 * This function submits a new event to the specified module by adding the event to the module's message queue.
 * 
 * @param module The module to which the new event will be submitted.
 * @param node The event to be submitted.
 * @return true if the operation was successful, false otherwise.
 */
bool _ipc_publish_message(ipc_message_publish_module_t *module, ipc_message_node_t node);

/**
 * @brief submits a new event to the message publish mmodule
 * @param ipc_message_node_t pointer *message that we are consuming
 */
/**
 * @brief Submits a new event.
 * 
 * This function submits a new event to the main IPC module by adding the event to the module's message queue.
 * 
 * @param node The event to be submitted.
 * @return true if the operation was successful, false otherwise.
 */
bool ipc_publish_message(ipc_message_node_t node);

/**
 * @brief Signals that we have recieved our ack from the IPC layer that message was recieved
 * @note internal call only
 */
/**
 * @brief Signals that an acknowledgment has been received from the IPC layer for a specific module.
 * 
 * This function signals that an acknowledgment has been received from the IPC layer for the specified module.
 * 
 * @param module The module for which the acknowledgment has been received.
 * @return 0 on success, or a negative error code on failure.
 */
int _ipc_msg_ack_cmd_recv(ipc_message_publish_module_t *module);

/**
 * @brief Signals that we have recieved our ack from the IPC layer that message was recieved
 */
/**
 * @brief Signals that an acknowledgment has been received from the IPC layer.
 * 
 * This function signals that an acknowledgment has been received from the IPC layer for the main IPC module.
 * 
 * @return 0 on success, or a negative error code on failure.
 */
int ipc_msg_ack_cmd_recv(void);

/**
 * @brief Blocks until we recieve the call that our messsage ack has been recieved
 * @note internal call only
 */
/**
 * @brief Blocks until an acknowledgment has been received from the IPC layer for a specific module.
 * 
 * This function blocks the current thread until an acknowledgment has been received from the IPC layer for the specified module.
 * 
 * @param module The module for which the acknowledgment is expected.
 * @return true if the acknowledgment was received, false otherwise.
 */
bool _ipc_msg_wait_recieve_cmd_ack(ipc_message_publish_module_t *module);

/**
 * @brief Blocks until we recieve the call that our messsage ack has been recieved
 */
/**
 * @brief Blocks until an acknowledgment has been received from the IPC layer.
 * 
 * This function blocks the current thread until an acknowledgment has been received from the IPC layer for the main IPC module.
 * 
 * @return true if the acknowledgment was received, false otherwise.
 */
bool ipc_msg_wait_recieve_cmd_ack(void);

/**
 * @brief Blocks until there's an event in queue, then consumes that event
 * @param ipc_message_publish_module_t *module pointer to the module that we are publishing to
 * @note internal call only!
 */
/**
 * @brief Blocks until there's an event in the queue of a specific module, then consumes that event.
 * 
 * This function blocks the current thread until there's an event in the queue of the specified module, then removes and returns that event.
 * 
 * @param module The module whose event queue will be checked.
 * @return The event that was consumed.
 */
ipc_message_node_t _ipc_block_consume_new_event(ipc_message_publish_module_t *module);

/**
 * @brief Will a message send failiure message to the publish queue so that the other
 * side of the microcontroller knows that we failed at getting their message!
 * @return publish status
 */
/**
 * @brief Sends a failure message to the publish queue of a specific module.
 * 
 * This function sends a failure message to the publish queue of the specified module, indicating that a message was not received correctly.
 * 
 * @param module The module whose publish queue will receive the failure message.
 * @return 0 on success, or a negative error code on failure.
 */
int _ipc_msg_publish_fail(ipc_message_publish_module_t *module);

/**
 * @brief Will a message send failiure message to the publish queue so that the other
 * side of the microcontroller knows that we failed at getting their message!
 * @return publish status
 */
/**
 * @brief Sends a failure message to the main publish queue.
 * 
 * This function sends a failure message to the main publish queue, indicating that a message was not received correctly.
 * 
 * @return 0 on success, or a negative error code on failure.
 */
int ipc_msg_publish_fail(void);

/**
 * @brief Blocks until there's an event in queue, then consumes that event
 */
/**
 * @brief Blocks until there's an event in the main queue, then consumes that event.
 * 
 * This function blocks the current thread until there's an event in the main queue, then removes and returns that event.
 * 
 * @return The event that was consumed.
 */
ipc_message_node_t ipc_block_consume_new_event(void);

/**
 * @brief Initializes the ipc message queue to be used by all!
 */
/**
 * @brief Initializes the IPC message queue for a specific module.
 * 
 * This function initializes the IPC message queue for the specified module by setting up the necessary data structures.
 * 
 * @return A pointer to the initialized IPC message queue.
 */
ipc_message_publish_module_t *_ipc_message_queue_init(void);
#endif
#endif