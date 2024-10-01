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
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

#define SIZE_PORTS_ARRAY       1024

#define MAX_PORT_VALUE         65535
#define MAX_SPEEDUP_VALUE      250

#define SOURCE_PORT            1337

#define SCAN_TYPE_SYN       0x1 << 0
#define SCAN_TYPE_NULL      0x1 << 1
#define SCAN_TYPE_ACK       0x1 << 2
#define SCAN_TYPE_FIN       0x1 << 3
#define SCAN_TYPE_XMAS      0x1 << 4
#define SCAN_TYPE_UDP       0x1 << 5
#define SCAN_TYPE_UNKNOW    0x1 << 6


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

typedef struct sockaddr_in  sockaddr_in;
typedef struct sockaddr     sockaddr;
typedef struct addrinfo     addrinfo;
typedef struct tcphdr       tcphdr;


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
} t_options;

typedef struct {
    tcphdr hdr;
} t_tcp_packet;

typedef struct {
    // i32 sockfd;
    // u16 pid;

    // sockaddr_in dest;
    t_options opts;
} t_global_data;


// ========================================================================= //
//                                  Prototype                                //
// ========================================================================= //

/*
* main function about arguments parsing.
*/
bool parse_arg(i32 ac, char **av, t_global_data *data);


/*
* dedicated function about ports argument parsing.
*/
bool parse_ports_from_arg(char *arg, t_options *opts);


/*
* dedicated function about ip argument parsing.
*/
bool parse_ip_from_arg(char *ip, t_global_data *data, bool *ip_is_set);


/*
* dedicated function about file argument parsing.
*/
bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set);


/*
* dedicated function about speedup argument parsing.
*/
bool parse_speedup_from_arg(char *speedup, t_options *opts);


/*
* dedicated function about speedup argument parsing.
*/
bool parse_scan_from_arg(char *scan, t_options *opts);


/*
* dedicated function about debug argument parsing.
*/
bool parse_debug_from_arg(char *debug, t_options *opts);


/*
* function to set the default value of t_options stuct.
*/
void set_default_opts_val(t_options *opts);


/*
* creat and initialize raw socket.
*/
bool socket_initialization(t_global_data *data);


/*
* reverse the dns for all `addr_in` in t_options struct 
* and fill `addr` with response.
*/
bool reverse_all_dns(t_global_data *data);


/*
* open tcp raw socket.
*/
bool open_tcp_sockfd(i32 *sockfd);


/*
* process nmap scans.
*/
bool process_nmap_scans(t_global_data *data);


/*
* send a packet specified per `type`, to `port`.
*/
bool send_syn_packet(i32 sockfd, sockaddr_in *dest, u16 port);
bool send_fin_packet(i32 sockfd, sockaddr_in *dest, u16 port);
bool send_null_packet(i32 sockfd, sockaddr_in *dest, u16 port);
bool send_xmas_packet(i32 sockfd, sockaddr_in *dest, u16 port);
bool send_ack_packet(i32 sockfd, sockaddr_in *dest, u16 port);


/*
* free `addr`, `addr_in` and `sockfd` if it open.
*/
void clean_all_and_exit(t_global_data *data, i32 sockfd);


/*
* print manual of the program.
*/
void print_man(void);


/*
* print first lines resume before the scan launch.
*/
void print_nmap_infos(t_options opts);


/*
* print t_options structure value.
*/
void print_options(t_options *opts);


/*
* some utils.
*/
char **split(char *str, char *charset);
void free_str_arr(char **arr);
bool str_is_digit(char *str);
bool is_odd(i32 n);


#endif /* __INC_H__ */