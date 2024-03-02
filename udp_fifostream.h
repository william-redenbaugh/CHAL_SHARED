#ifndef _UDP_FIFOSTREAM_H
#define _UDO_FIFOSTREAM_H
#include "stdint.h"
#include "stdlib.h"

typedef struct udp_fifo_init{
    uint16_t port; 
}udp_fifo_init_t;
struct udp_fifo_t;

udp_fifo_t *generate_udp_fifo(udp_fifo_init_t init_params);
#endif