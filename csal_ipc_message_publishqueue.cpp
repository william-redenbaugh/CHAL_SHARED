#include "csal_ipc_message_publishqueue.h"
#include "global_includes.h"
#include "ipc_enum.h"

#ifdef OS_IPC_H

ipc_message_publish_module_t *ipc_publish_queue_module = NULL;

bool ipc_publish_message(ipc_message_node_t node)
{
    return _ipc_publish_message(ipc_publish_queue_module, node);
}

bool _ipc_publish_message(ipc_message_publish_module_t *module, ipc_message_node_t node)
{
    // Pushes a new event.
    _signal_new_event(module);
    return _ipc_push_message_queue(module, node);
}

int _ipc_msg_publish_fail(ipc_message_publish_module_t *module)
{
    ipc_message_node_t fail_msg;
    fail_msg.buffer_ptr = NULL;
    fail_msg.callback_func = NULL;
    fail_msg.message_header.message_len = 0;
    fail_msg.message_header.message_type_enum = IPC_MESSAGE_ERROR;
    fail_msg.message_header.message_id = IPC_TYPE_ACK;

    if (_ipc_publish_message(module, fail_msg) == true)
    {
        return OS_RET_OK;
    }
    else
    {
        return OS_RET_LOW_MEM_ERROR;
    }
}

int ipc_msg_publish_fail(void)
{
    return _ipc_msg_publish_fail(ipc_publish_queue_module);
}

bool _ipc_push_message_queue(ipc_message_publish_module_t *module, ipc_message_node_t node)
{

    os_mut_entry_wait_indefinite(&module->new_msg_mp);
    if (module->max_size == module->current_size)
        return false;

    // Populate index of data
    module->node_list[module->head_pos] = node;

    // Increment positions and current size
    module->head_pos++;
    module->current_size++;

    // Rotate around the circular buffer
    if (module->head_pos == module->max_size)
        module->head_pos = 0;

    os_mut_exit(&module->new_msg_mp);
    return true;
}

bool _ipc_pop_message_queue(ipc_message_publish_module_t *module, ipc_message_node_t *node)
{

    os_mut_entry_wait_indefinite(&module->new_msg_mp);
    if (module->current_size == 0)
        return false;

    // Populate tail pointer
    *node = module->node_list[module->tail_pos];

    // We popped off a node, so our current size goes down
    module->current_size--;

    // Increment our tail pointer
    module->tail_pos++;

    // Rotate around the circular buffer
    if (module->tail_pos == module->max_size)
        module->tail_pos = 0;
    os_mut_exit(&module->new_msg_mp);

    return true;
}

int _signal_new_event(ipc_message_publish_module_t *module)
{
    os_setbits_signal(&module->new_msg_cv, 0);
    return 0;
}

void _ipc_msg_queue_wait_new_event(ipc_message_publish_module_t *module)
{
    os_mut_entry_wait_indefinite(&module->ipc_message_node_muttx);
    int num_msg = module->current_size;
    os_mut_exit(&module->ipc_message_node_muttx);

    // If there are no messages in queue
    if (num_msg == 0)
        os_waitbits_indefinite(&module->new_msg_cv, 0);

    os_clearbits(&module->new_msg_cv, 0);
}

ipc_message_node_t _ipc_block_consume_new_event(ipc_message_publish_module_t *module)
{
    _ipc_msg_queue_wait_new_event(module);
    ipc_message_node_t node;
    _ipc_pop_message_queue(module, &node);
    return node;
}

ipc_message_node_t ipc_block_consume_new_event(void)
{
    return _ipc_block_consume_new_event(ipc_publish_queue_module);
}

int signal_new_event(void)
{
    return _signal_new_event(ipc_publish_queue_module);
}

void ipc_msg_queue_wait_new_event(void)
{
    _ipc_msg_queue_wait_new_event(ipc_publish_queue_module);
}

int _ipc_msg_ack_cmd_recv(ipc_message_publish_module_t *module)
{
    int ret = 0;
    os_setbits_signal(&module->ack_msg_mp, 0);
    return ret;
}

int ipc_msg_ack_cmd_recv(void)
{
    return _ipc_msg_ack_cmd_recv(ipc_publish_queue_module);
}

bool _ipc_msg_wait_recieve_cmd_ack(ipc_message_publish_module_t *module)
{
    // os_setbits_signal
    os_waitbits_indefinite(&module->ack_msg_mp, 0);
    return true;
}

bool ipc_msg_wait_recieve_cmd_ack(void)
{
    return _ipc_msg_wait_recieve_cmd_ack(ipc_publish_queue_module);
}

ipc_message_publish_module_t *_ipc_message_queue_init(void)
{
    if (ipc_publish_queue_module != NULL)
        return NULL;
    ipc_message_publish_module_t *module = new ipc_message_publish_module_t;
    module->max_size = IPC_QUEUE_MAX_NUM_ELEMENTS;
    module->node_list = new ipc_message_node_t[20];
    module->current_size = 0;
    module->head_pos = 0;
    module->tail_pos = 0;

    os_mut_init(&module->ipc_message_node_muttx);
    os_setbits_init(&module->new_msg_cv);
    os_mut_init(&module->new_msg_mp);

    return module;
}

void init_ipc_message_queue(void)
{
    ipc_publish_queue_module = _ipc_message_queue_init();
}
#endif