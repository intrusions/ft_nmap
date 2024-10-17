#ifndef __INC_H__
# define __INC_H__

// ========================================================================= //
//                                   Header                                  //
// ========================================================================= //

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <pcap.h>


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

#define SERVICES_FILE_PATH  "./services/nmap-services"

#define MAX_SIZE_SERVICE_NAME   20
#define MAX_SIZE_PROTO_NAME     10
#define MAX_PORT_VALUE          65535
#define MAX_SPEEDUP_VALUE       250


#define SIZE_PORTS_ARRAY        1024

#define DEFAULT_SOURCE_PORT     1337

#define SCAN_TYPE_SYN       0x1 << 0
#define SCAN_TYPE_NULL      0x1 << 1
#define SCAN_TYPE_ACK       0x1 << 2
#define SCAN_TYPE_FIN       0x1 << 3
#define SCAN_TYPE_XMAS      0x1 << 4
#define SCAN_TYPE_UDP       0x1 << 5
#define SCAN_TYPE_UNKNOWN   0x1 << 6

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


// ========================================================================= //
//                                   Macro                                   //
// ========================================================================= //

#define __log_error(error) (void)fprintf(stderr, "%s: %s\n", error, strerror(errno))


// ========================================================================= //
//                                  Typedef                                  //
// ========================================================================= //

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct sockaddr_in      sockaddr_in;
typedef struct sockaddr         sockaddr;
typedef struct addrinfo         addrinfo;
typedef struct tcphdr           tcphdr;
typedef struct udphdr           udphdr;
typedef struct timespec         timespec;
typedef struct timeval          timeval;
typedef struct bpf_program      bpf_program;


// ========================================================================= //
//                                  Structure                                //
// ========================================================================= //

typedef struct {
    char **addr_in;
    char **addr;
    char *file;
    u8 speedup;
    u16 ports[SIZE_PORTS_ARRAY];
    u16 n_ports;
    u32 scan_type;

    bool debug_mode;
    bool badsum;
    bool show_all;
    bool shuffle_ports;
    u16 source_port;
    FILE *output;
} t_options;

typedef struct t_services_node {
    char service[MAX_SIZE_SERVICE_NAME];
    char protocol[MAX_SIZE_PROTO_NAME];
    u16 port;

    struct t_services_node *left;
    struct t_services_node *right;
} t_services_node;

typedef struct pseudo_header {
    i32 source_address;
    i32 dest_address;
    i8 placeholder;
    i8 protocol;
    i16 tcp_length;
} t_pseudo_header;

typedef struct {
    tcphdr hdr;
} t_tcp_packet;

typedef struct {
    udphdr hdr;
} t_udp_packet;

typedef struct {
    char src_ip[INET_ADDRSTRLEN];
    pcap_t *handle;

    t_options       opts;
    t_services_node *services;
} t_global_data;


// ========================================================================= //
//                                  Prototype                                //
// ========================================================================= //

/*
* Parse the command-line arguments and store them in the global data structure.
* @param ac: argument count.
* @param av: array of arguments.
* @param data: pointer to the global data structure.
* @return true if arguments were parsed successfully, false otherwise.
*/
bool parse_arg(i32 ac, char **av, t_global_data *data);

/*
* Parse the `--ports` argument, converting it to a valid ports list.
* @param arg: argument string for ports.
* @param opts: pointer to the options structure where parsed values will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_ports_from_arg(char *arg, t_options *opts);

/*
* Parse the `--ip` argument and store the IP address in the global data structure.
* @param ip: argument string representing the IP address.
* @param data: pointer to the global data structure, 
*   containing opts structure where the IP will be stored.
* @param ip_is_set: boolean flag to track if IPs have already been set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_ip_from_arg(char *ip, t_global_data *data, bool *ip_is_set);

/*
* Parse the `--file` argument, loading IPs or hosts from a specified file.
* @param file: file name or path to be parsed.
* @param opts: pointer to the options structure.
* @param ip_is_set: boolean flag to track if IPs have already been set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set);

/*
* Parse the `--speedup` argument, which define the number of threads for the scan.
* @param speedup: string representing the speedup level.
* @param opts: pointer to the options structure where the value will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_speedup_from_arg(char *speedup, t_options *opts);

/*
* Parse the `--scan` argument, specifying the types of scans to be performed (e.g., SYN, ACK).
* @param scan: string representing the scan types.
* @param opts: pointer to the options structure where scan types will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_scan_from_arg(char *scan, t_options *opts);

/*
* Parse the `--debug` argument to enable debugging mode.
* @param debug: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where debug mode will be toggled.
* @return true if parsing was successful, false otherwise.
*/
bool parse_debug_from_arg(char *debug, t_options *opts);

/*
* Parse the `--show-all` argument, toggling visibility of all scan results, including filtered ports.
* @param show_all: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_show_all_from_arg(char *show_all, t_options *opts);

/*
* Parse the `--shuffle-ports` argument to randomize the order of port scanning.
* @param shuffle_ports: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_shuffle_ports_from_arg(char *shuffle_ports, t_options *opts);

/*
* Parse the `--source-port` argument to specify a custom source port for the scan.
* @param source_port: string representing the source port.
* @param opts: pointer to the options structure where the source port will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_source_port_from_arg(char *source_port, t_options *opts);

/*
* Parse the `--badsum` argument to introduce packet checksum errors.
* @param badsum: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_badsum_from_arg(char *badsum, t_options *opts);

/*
* Parse the `--output` argument to specify an output file for scan results.
* @param file: string representing the output file path.
* @param opts: pointer to the options structure where the `FILE *` will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_output_from_arg(char *file, t_options *opts);

/*
* Set default values for the options structure `t_options`, such as scan types and ports.
* @param opts: pointer to the options structure where default values will be set.
*/
void set_default_opts_val(t_options *opts);

/*
* Perform reverse DNS lookups for all IP addresses in the global data structure.
* @param data: pointer to the global data structure containing the IP addresses.
* @return true if reverse DNS lookups were successful, false otherwise.
*/
bool reverse_all_dns(t_global_data *data);

/*
* Open a raw TCP socket for sending custom-crafted packets.
* @param sockfd: pointer to the socket file descriptor to be initialized.
* @return true if the socket was successfully opened, false otherwise.
*/
bool open_tcp_sockfd(i32 *sockfd);

/*
* Open a raw UDP socket for sending custom-crafted packets.
* @param sockfd: pointer to the socket file descriptor to be initialized.
* @return true if the socket was successfully opened, false otherwise.
*/
bool open_udp_sockfd(i32 *sockfd);

/*
* Perform the nmap scan using the options and global data provided.
* @param data: pointer to the global data structure containing scan parameters.
* @return true if the scan was successful, false otherwise.
*/
bool process_nmap_scans(t_global_data *data);

/*
* Send a custom TCP packet to a specific port using a specified scan type (e.g., SYN, ACK).
* @param data: pointer to the global data structure containing the scan configuration.
* @param sockfd: the TCP socket file descriptor.
* @param dest: pointer to the destination address structure.
* @param port: the destination port to which the packet will be sent.
* @param scan_type: type of scan (e.g., SYN, ACK).
* @return true if the packet was successfully sent, false otherwise.
*/
bool send_tcp_packet(t_global_data *data, i32 sockfd, sockaddr_in *dest, u16 port, u8 scan_type);

/*
* Send a custom UDP packet to a specific port.
* @param sockfd: the UDP socket file descriptor.
* @param dest: pointer to the destination address structure.
* @param port: the destination port to which the packet will be sent.
* @param src_port: the source port to be used in the packet.
* @return true if the packet was successfully sent, false otherwise.
*/
bool send_udp_packet(i32 sockfd, sockaddr_in *dest, u16 port, u16 src_port);

/*
* Load the `nmap-services` file, building a binary tree of known services for port scanning.
* @param data: pointer to the global data structure where the tree will be stored.
* @return true if the services tree was created successfully, false otherwise.
*/
bool create_services_tree(t_global_data *data);

/*
* Clean up all allocated resources including IP addresses, sockets, pcap handle and binary trees.
* @param data: pointer to the global data structure.
* @param tcp_sockfd: TCP socket file descriptor to be closed.
* @param udp_sockfd: UDP socket file descriptor to be closed.
*/
void cleanup_resources(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd);

/*
* Display the program's manual (help page) to the user.
*/
void print_man(void);

/*
* Print summary information before starting the scan.
* @param data: pointer to the global data structure containing scan configuration.
*/
void print_nmap_infos(t_global_data *data);

/*
* Print a summary of the scan results after the scan has completed.
* @param start_time: start time of the scan.
* @param end_time: end time of the scan.
* @param output: file pointer for writing the scan results.
*/
void print_nmap_resume(timespec start_time, timespec end_time, FILE *output);

/*
* Print a single line of scan results for a given port.
* @param data: pointer to the global data structure.
* @param port: port number.
* @param scan_type: type of scan used for this result.
* @param port_state: state of the port (e.g., open, closed).
*/
void print_scan_line(t_global_data *data, u16 port, u32 scan_type, u8 port_state);

/*
* Print the header before starting a scan on a specific IP.
* @param data: pointer to the global data structure.
* @param addr_index: index of the IP address in `addr` being scanned.
*/
void print_scan_ip_header(t_global_data *data, u8 addr_index);

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
* Sleep for a random interval between 1000 and 2000 microseconds.
*/
void random_usleep(void);

/*
* Randomize the order of ports in the provided array.
* @param array: pointer to the array of ports.
* @param n: number of elements in the array.
*/
void shuffle_ports(u16 *array, u16 n);

/*
* Initialize pcap for packet capture.
* @param handle: pointer to the pcap handle that will be initialized.
* @return true if pcap was initialized successfully, false otherwise.
*/
bool pcap_initialization(pcap_t **handle);

/*
* Set a pcap filter for capturing packets related to a specific destination address 
*   and type of scan.
* @param handle: pointer to the pcap handle.
* @param dest_addr: destination IP address as a string.
* @return true if the filter was successfully set, false otherwise.
*/
bool set_pcap_filter(pcap_t **handle, char *dest_addr);

/*
* Receive packets and analyze their state (open, closed, filtered, etc.).
* @param handle: pointer to the pcap handle for capturing packets.
* @param response_state: pointer to the variable where the packet state will be stored.
* @return true if a packet was successfully received and analyzed, false otherwise.
*/
bool recv_packet(pcap_t *handle, u8 *response_state);


/*
* service binary tree function.
*/
t_services_node *create_node_from_line(char *line);
t_services_node *search_node(t_services_node *root, u16 port, char *protocol);
void free_services_tree(t_services_node *node);


/*
* debug function.
*/
void print_options(t_options *opts);
void print_services_tree(t_services_node *node, int depth);


/*
* some utils.
*/
char **split(char *str, char *charset);
void free_str_arr(char **arr);
bool str_is_digit(char *str);
bool is_odd(i32 n);
bool is_sudo_mode();
void print_dash_line(FILE *output);
u16 checksum(void *b, int len);

bool count_line_in_file(char *file, i16 *file_line_count);
bool open_fd(char *file, i32 *fd);


#endif /* __INC_H__ */
