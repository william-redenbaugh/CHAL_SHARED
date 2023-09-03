#ifndef _OS_WIFI_H
#define _OS_WIFI_H

#include "global_includes.h"

#ifdef OS_WIFI
#define OS_WIFI_CHECK_PACKET_INTERVAL (20)

/**
 * @brief Connects the device to a Wi-Fi network in station (client) mode.
 *
 * This function attempts to connect the device to the specified Wi-Fi network
 * using the provided SSID and password. The device will operate in station mode,
 * allowing it to act as a client and connect to an existing Wi-Fi network.
 *
 * @param ssid The SSID (network name) of the Wi-Fi network to connect to.
 * @param password The password for the Wi-Fi network.
 * @return Returns an integer value indicating the success or failure of the connection attempt.
 *         A return value of 0 indicates successful connection, while a non-zero value represents an error code.
 */
int os_wifi_connect_sta(char *ssid, char *password);

/**
 * @brief Disconnects the device from the currently connected Wi-Fi network in station (client) mode.
 *
 * This function disconnects the device from the currently connected Wi-Fi network
 * when operating in station mode. It terminates the existing network connection,
 * allowing the device to no longer be associated with the Wi-Fi network.
 *
 * @return Returns an integer value indicating the success or failure of the disconnection attempt.
 *         A return value of 0 indicates successful disconnection, while a non-zero value represents an error code.
 */
int os_wifi_disconnect_sta(void);

/**
 * @brief Sets up a UDP server for WiFi communication.
 *
 * @param port The port number for the UDP server.
 *
 * @return A pointer to the UDP server structure on success, or NULL on failure.
 */
os_udp_server_t *os_wifi_setup_udp_server(int port);

/**
 * @brief Deconstructs the UDP server and releases the allocated memory.
 *
 * This function deconstructs the UDP server and frees the allocated memory.
 *
 * @param udp Pointer to the UDP server structure.
 * @return A pointer to the freed memory. Use NULL to indicate success.
 */
int os_wifi_deconstruct_udp_server(os_udp_server_t *udp);

/**
 * @brief Starts UDP transmission to a specified IP address and port.
 *
 * @param udp The UDP server to use for transmission.
 * @param ip The IP address of the destination.
 * @param port The port number of the destination.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_wifi_start_udp_transmission(os_udp_server_t *udp, char *ip, uint16_t port);

/**
 * @brief Stops UDP transmission on the specified UDP server.
 *
 * @param udp The UDP server to stop transmission on.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_wifi_stop_udp_transmission(os_udp_server_t *udp);

/**
 * @brief Transmits a UDP packet on the specified UDP server.
 *
 * @param udp The UDP server to use for transmission.
 * @param packet_size The size of the packet to transmit.
 * @param arr The array containing the packet data.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_wifi_transmit_udp_packet(os_udp_server_t *udp, uint16_t packet_size, uint8_t *arr);

/**
 * @brief Receives a UDP packet on the specified UDP server.
 *
 * @param udp The UDP server to use for receiving.
 * @param packet_size A pointer to the variable to store the received packet size.
 * @note Whatever value inside of packetsize passed in at first is the max value
 * @param arr The array to store the received packet data.
 * @param timeout_ms The timeout value in milliseconds for receiving the packet.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int os_wifi_receive_packet(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr, uint32_t timeout_ms);

/**
 * @brief Receives a Wi-Fi packet indefinitely.
 *
 * This function receives a Wi-Fi packet using the specified UDP server until
 * a packet is successfully read.
 *
 * @param udp The UDP server to receive the packet from.
 * @param packet_size Pointer to a variable to store the size of the received packet.
 * @param arr Pointer to an array to store the received packet data.
 *
 * @return Returns OS_RET_OK when a packet is successfully received.
 */
int os_wifi_receive_packet_indefinite(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr);

/**
 * @brief Deconstructs a UDP server associated with the Wi-Fi functionality.
 *
 * This function deconstructs a UDP server object, freeing any resources
 * associated with it and cleaning up the server's state.
 *
 * @param udp Pointer to the UDP server object to deconstruct.
 * @return Returns an integer value indicating the result of the deconstruction:
 *         - 0 if the deconstruction was successful.
 *         - A non-zero value if an error occurred during the deconstruction.
 *
 * @note The UDP server object being deconstructed must have been previously
 *       initialized and used with the appropriate functions.
 *
 * @see os_udp_server_t
 * @see os_wifi_initialize_udp_server
 * @see os_wifi_send_udp_packet
 */
int os_wifi_deconstruct_udp_server(os_udp_server_t *udp);
#endif
#endif