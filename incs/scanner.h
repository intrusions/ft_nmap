#ifndef __SCANNER_H__
# define __SCANNER_H__

#include <stdint.h>
#include <stdbool.h>
#include <global_data.h>

#define SCAN_TYPE_SYN       0x01 << 0
#define SCAN_TYPE_NULL      0x01 << 1
#define SCAN_TYPE_ACK       0x01 << 2
#define SCAN_TYPE_FIN       0x01 << 3
#define SCAN_TYPE_XMAS      0x01 << 4
#define SCAN_TYPE_UDP       0x01 << 5
#define SCAN_TYPE_UNKNOWN   0x01 << 6

#define NUM_SCAN_TYPE   6

#define TCP_SYN_FLAG    0x02
#define TCP_RST_FLAG    0x04
#define TCP_ACK_FLAG    0x10

#define PORT_STATE_CLOSED           0x1 << 0
#define PORT_STATE_OPEN             0x1 << 1
#define PORT_STATE_FILTERED         0x1 << 2
#define PORT_STATE_UNFILTERED       0x1 << 3
#define PORT_STATE_OPEN_FILTERED    0x1 << 4
#define PORT_STATE_CLOSED_FILTERED  0x1 << 5

#define NO_RESPONSE         0x1 << 0
#define ICMP_PCKT_T3_C3     0x1 << 1
#define ICMP_PCKT_T3        0x1 << 2
#define TCP_RST_PCKT        0x1 << 3
#define TCP_SYN_ACK_PCKT    0x1 << 4


/*
* Process the nmap scan using the options and global data provided.
* @param data: pointer to the global data structure containing scan parameters.
* @return true if the scan was successful, false otherwise.
*/
bool process_nmap_scans(t_global_data *data);

/*
* Print a single line of scan results for a given port.
* @param data: pointer to the global data structure.
* @param port: port number.
* @param scan_type: type of scan used for this result.
* @param port_state: state of the port (e.g., open, closed).
*/
void print_scan_line(t_global_data *data, uint16_t port, uint32_t scan_type, uint8_t port_state);

#endif /* SCANNER_H */
