#include "csal_ipc_thread.h"
#include "csal_ipc_message_publishqueue.h"
#include "csal_ipc_message_subscribequeue.h"
#include "CSAL_SHARED/os_error.h"
#include "os_wifi.h"

static ipc_interface_type_t sel_interface_type = IPC_TYPE_UDP;
os_udp_server_t *udp_interface; 
static char ip_str[] = "1.1.1.1";
int ip_port = 6969;
uint8_t content_buffer_arr_in[BUFF_ARR_MAX_SIZE] = {0};
uint8_t content_buffer_arr_out[BUFF_ARR_MAX_SIZE] = {0};

void ipc_set_interface_type(ipc_interface_type_t interface_type){
    sel_interface_type = interface_type;
}

void uart_ipc_publish_init(void *params)
{
    init_ipc_message_queue();
}


ipc_message_header_t get_message_from_interface(void){
    ipc_message_header_t header; 
    memset(&header, 0, sizeof(header));
    int ret = OS_RET_INT_ERR;

    uint16_t size_u16 = BUFF_ARR_MAX_SIZE;
    int size = 0;
    switch(sel_interface_type){
        case IPC_TYPE_UDP:
            os_wifi_receive_packet_indefinite(udp_interface, &size_u16, content_buffer_arr_in);
        break;
        default:
        return header;
        break;
    }

    header = deserialize_message_header(content_buffer_arr_in, sizeof(IPC_MESSAGE_HANDLER_SIZE));

    if(header.message_len != size_u16){
        header.message_len = -1;
    }

    return header;
}

static inline int ipc_handle_data_from_udp(ipc_message_header_t header){
    // No flushing needed since it's just a single UDP packet.
    if(header.message_len > BUFF_ARR_MAX_SIZE || header.message_len < 0){
        // Publish message saying that the message was invalid or damaged
        ipc_msg_publish_fail();
        return OS_RET_INT_ERR;
    }

    ipc_run_all_sub_cb(header, &content_buffer_arr_in[9]);
    return OS_RET_OK;
}

int ipc_handle_data_from_interface(ipc_message_header_t header){ 
    int ret = OS_RET_INVALID_PARAM;
    switch(sel_interface_type){
        case IPC_TYPE_UDP:
            ret = ipc_handle_data_from_udp(header);
        break;
        default:
        break;
    }

    return ret;
}

static inline int ipc_publish_udp(ipc_message_node_t node){
    ipc_message_ret_t callback_ret;
    callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_SUCCESS;

    // Copy header into buffer
    memcpy(content_buffer_arr_out, &node.message_header, sizeof(ipc_message_header_t));
    // Copy content into buffer
    memcpy(&content_buffer_arr_in[sizeof(ipc_message_header_t)], node.buffer_ptr, node.message_header.message_len);

    int ret = os_wifi_start_udp_transmission(udp_interface, ip_str, 6969);

    if(ret != OS_RET_OK){
        callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_FAIL_TIMEOUT;   
    }

    if (node.callback_func != NULL){
        // Any cleanup needed for the published event!
        node.callback_func(callback_ret);
    }   

    return ret;
}

static int ipc_publish_msg(ipc_message_node_t node){
    int ret = OS_RET_INVALID_PARAM;
    switch(sel_interface_type){
        case IPC_TYPE_UDP:
            ret = ipc_publish_udp(node);
        break;
        default:
        break;
    }

    return ret;
}

void uart_ipc_publish_thread(void *params)
{
    for (;;)
    {
        
        // Wait until we can consume the entire node
        ipc_message_node_t event_node = ipc_block_consume_new_event();

        ipc_publish_msg(event_node);
        /*
        // ipc_message_callback_status
        ipc_message_ret_t callback_ret;
        callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_SUCCESS;

        // Writes the message header to UART first!
        int write_size = write(uart_fd, (void *)&event_node.message_header, sizeof(ipc_message_header_t));

        // If we couldn't write complete header, say we failed to publish!
        if (write_size != sizeof(ipc_message_header_t))
        {
            callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_FAIL;
        }

        // Write message contents after
        if (event_node.message_header.message_len > 0 | event_node.buffer_ptr != NULL)
        {
            write_size = write(uart_fd, (void *)&event_node.buffer_ptr, event_node.message_header.message_len);
            // If we couldn't write entire message, say we failed to publish!
            if (write_size != sizeof(ipc_message_header_t))
            {
                callback_ret.ipc_status = IPC_MESSe_
        switch(k){
            case 0:
                callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_SUCCESS;
            break;
            case ETIMEDOUT:
                callback_ret.ipc_status = IPC_MESSAGE_COMPLETE_FAIL_TIMEOUT;
                printf("Timeout upon message!\n");
            break;
        }

        if (event_node.callback_func != NULL)
            // Any cleanup needed for the published event!
            event_node.callback_func(callback_ret);
        */
    }
}

void uart_ipc_consume_thread_init(void *params)
{
    switch(sel_interface_type){
        case IPC_TYPE_UDP:
            udp_interface = os_wifi_setup_udp_server(IPC_PORT_UDP);
        break;
        default:
        return;
        break;
    }
    init_ipc_module();
}

void uart_ipc_consume_thread(void *params)
{

    for (;;)
    {
        
        ipc_message_header_t header = get_message_from_interface();
        ipc_handle_data_from_interface(header);

    }
}