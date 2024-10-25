#ifndef __NETWORK_H__
# define __NETWORK_H__

#include "global_data.h"
#include <stdbool.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>

typedef struct sockaddr_in  sockaddr_in;
typedef struct sockaddr     sockaddr;
typedef struct addrinfo     addrinfo;
typedef struct tcphdr       tcphdr;
typedef struct udphdr       udphdr;

typedef struct pseudo_header {
    int32_t source_address;
    int32_t dest_address;
    int8_t  placeholder;
    int8_t  protocol;
    int16_t length;
} t_pseudo_header;

typedef struct {
    tcphdr hdr;
} t_tcp_packet;

typedef struct {
    udphdr hdr;
} t_udp_packet;


/*
* Open a raw TCP socket for sending custom-crafted packets.
* @param sockfd: pointer to the socket file descriptor to be initialized.
* @return true if the socket was successfully opened, false otherwise.
*/
bool open_tcp_sockfd(int32_t *sockfd);

/*
* Open a raw UDP socket for sending custom-crafted packets.
* @param sockfd: pointer to the socket file descriptor to be initialized.
* @return true if the socket was successfully opened, false otherwise.
*/
bool open_udp_sockfd(int32_t *sockfd);

/*
* Send a custom TCP packet to a specific port using a specified scan type (e.g., SYN, ACK).
* @param data: pointer to the global data structure containing the scan configuration.
* @param sockfd: the TCP socket file descriptor.
* @param dest: pointer to the destination address structure.
* @param port: the destination port to which the packet will be sent.
* @param scan_type: type of scan (e.g., SYN, ACK).
* @return true if the packet was successfully sent, false otherwise.
*/
bool send_tcp_packet(t_global_data *data, int32_t sockfd, sockaddr_in *dest, uint16_t port, uint8_t scan_type);

/*
* Send a custom UDP packet to a specific port.
* @param data: pointer to the global data structure containing the scan configuration.
* @param sockfd: the UDP socket file descriptor.
* @param dest: pointer to the destination address structure.
* @param port: the destination port to which the packet will be sent.
* @param src_port: the source port to be used in the packet.
* @return true if the packet was successfully sent, false otherwise.
*/
bool send_udp_packet(t_global_data *data, int32_t sockfd, sockaddr_in *dest, uint16_t port);

/*
* Retrieve the source IP address from the available network interfaces.
* @param src_ip: buffer to store the source IP in string format.
* @return true if an address was found and stored, false otherwise.
*/
bool get_src_ip(char *src_ip);

/*
* Calculate the checksum for the TCP header, including a pseudo-IP header for validation.
* @param dest: pointer to the destination address structure.
* @param packet: pointer to the TCP packet structure.
* @param src_ip: source IP address to be included in the checksum calculation.
* @return true if the checksum was calculated successfully, false otherwise.
*/
bool tcp_checksum(sockaddr_in *dest, t_tcp_packet *packet, char *src_ip);

/*
* Calculate the checksum for the UDP header, including a pseudo-IP header for validation.
* @param dest: pointer to the destination address structure.
* @param packet: pointer to the UDP packet structure.
* @param src_ip: source IP address to be included in the checksum calculation.
* @return true if the checksum was calculated successfully, false otherwise.
*/
bool udp_checksum(sockaddr_in *dest, t_udp_packet *packet, char *src_ip);

/*
* Receive packets and analyze their state (open, closed, filtered, etc.).
* @param handle: pointer to the pcap handle for capturing packets.
* @param response_state: pointer to the variable where the packet state will be stored.
* @return true if a packet was successfully received and analyzed, false otherwise.
*/
bool recv_packet(pcap_t *handle, uint8_t *response_state);

/*
* Set a pcap filter for capturing packets related to a specific destination address 
*   and type of scan.
* @param handle: pointer to the pcap handle.
* @param dest_addr: destination IP address as a string.
* @return true if the filter was successfully set, false otherwise.
*/
bool set_pcap_filter(pcap_t **handle, char *serv_addr, uint16_t port);

/*
* Initialize pcap for packet capture.
* @param handle: pointer to the pcap handle that will be initialized.
* @return true if pcap was initialized successfully, false otherwise.
*/
bool pcap_initialization(pcap_t **handle);

/*
* Perform resolve DNS lookups for all IP addresses/hostname in the global data structure.
* @param data: pointer to the global data structure containing the IP addresses/hostname.
* @return true if resolve DNS were successful, false otherwise.
*/
bool resolve_dns(t_global_data *data);

#endif /* NETWORK_H */
