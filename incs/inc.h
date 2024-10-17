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

#define SIZE_PORTS_ARRAY        1024

#define MAX_PORT_VALUE          65535
#define MAX_SPEEDUP_VALUE       250

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
* main function about arguments parsing.
*/
bool parse_arg(i32 ac, char **av, t_global_data *data);


/*
* dedicated function about `--ports` argument parsing.
*/
bool parse_ports_from_arg(char *arg, t_options *opts);

/*
* dedicated function about `--ip` argument parsing.
*/
bool parse_ip_from_arg(char *ip, t_global_data *data, bool *ip_is_set);


/*
* dedicated function about `--file` argument parsing.
*/
bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set);


/*
* dedicated function about `--speedup` argument parsing.
*/
bool parse_speedup_from_arg(char *speedup, t_options *opts);


/*
* dedicated function about `--scan` argument parsing.
*/
bool parse_scan_from_arg(char *scan, t_options *opts);


/*
* dedicated function about `--debug` argument parsing.
*/
bool parse_debug_from_arg(char *debug, t_options *opts);


/*
* dedicated function about `--show-all` argument parsing.
*/
bool parse_show_all_from_arg(char *show_all, t_options *opts);


/*
* dedicated function about `--shuffle-ports` argument parsing.
*/
bool parse_shuffle_ports_from_arg(char *shuffle_ports, t_options *opts);


/*
* dedicated function about `--source-port` argument parsing.
*/
bool parse_source_port_from_arg(char *source_port, t_options *opts);


/*
* dedicated function about `--badsum` argument parsing.
*/
bool parse_badsum_from_arg(char *badsum, t_options *opts);


/*
* function to set the default value of `t_options` stuct.
*/
void set_default_opts_val(t_options *opts);


/*
* reverse the dns for all `addr_in` in `t_options` struct 
* and fill `addr` with response.
*/
bool reverse_all_dns(t_global_data *data);


/*
* open tcp raw socket.
*/
bool open_tcp_sockfd(i32 *sockfd);


/*
* open udp raw socket.
*/
bool open_udp_sockfd(i32 *sockfd);


/*
* process nmap scans.
*/
bool process_nmap_scans(t_global_data *data);


/*
* send a tcp packet specified per `scan_type`, to `port`.
*/
bool send_tcp_packet(t_global_data *data, i32 sockfd, sockaddr_in *dest, u16 port, u8 scan_type);


/*
* send a udp packet to `port`.
*/
bool send_udp_packet(i32 sockfd, sockaddr_in *dest, u16 port, u16 src_port);


/*
* open `./services/nmap-services` and create a binary tree
* containing all services possibility (one per node).
*/
bool create_services_tree(t_global_data *data);


/*
* free `addr` and `addr_in`, close `tcp_sockfd` and `udp_sockfd` if open,
* free all node from services binary tree and close pcap handle.
*/
void cleanup_resources(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd);

/*
* print manual of the program.
*/
void print_man(void);


/*
* print first lines resume before the scan launch.
*/
void print_nmap_infos(t_global_data *data);


/*
* print last lines after the end of the scans.
*/
void print_nmap_resume(timespec start_time, timespec end_time);


/*
* print one scan line.
* ex:
* 15/tcp     open     netstat
*/
void print_scan_line(t_global_data *data, u16 port, u32 scan_type, u8 port_state);


/*
* print ip header before ip scan.
* ex:
* [*] facebook.com (163.70.128.35) scan :
* PORT       STATE    SERVICE
*/
void print_scan_ip_header(t_global_data *data, u8 addr_index);


/*
* get our src ip.
*/
bool get_src_ip(char *src_ip);


/*
* calcul checksum for `check` field in `tcphdr`  (pseudo ip header + tcp header).
*/
bool tcp_checksum(sockaddr_in *dest, t_tcp_packet *packet, char *src_ip);


/*
* usleep between 1000 & 2000.
*/
void random_usleep();


/*
* randomize ports array.
*/
void shuffle_ports(u16 *array, u16 n);


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
void print_dash_line();
u16 checksum(void *b, int len);
bool pcap_initialization(pcap_t **handle);
bool recv_packet(pcap_t *handle, u8 *response_state);

bool count_line_in_file(char *file, i16 *file_line_count);
bool open_fd(char *file, i32 *fd);


#endif /* __INC_H__ */