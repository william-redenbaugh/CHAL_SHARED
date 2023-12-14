#ifndef _OS_ST_AP_H
#define _OS_ST_AP_H

#include "string.h"
#include "stdint.h"

typedef enum{
    AP_STATION_EVENT_CONNECTED, 
    AP_STATION_EVENT_DISCONNECTED
} ap_station_event_t;

typedef void (*ap_station_cb)(ap_station_event_t event, uint8_t mac[6]);

/**
 * @brief Sets the local access point to 
*/
int os_start_local_ap(char *ssid, char *password, int max_clients, uint16_t channel, ap_station_cb cb);

#endif