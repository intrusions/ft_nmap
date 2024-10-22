#ifndef __THREADS_H__
# define __THREADS_H__

#include "global_data.h"
#include <netinet/in.h>

typedef struct sockaddr_in sockaddr_in;

typedef struct {
    t_global_data *data;
    uint32_t tcp_sockfd;
    uint32_t udp_sockfd;
    sockaddr_in dest;
    uint16_t start_port_index;
    uint16_t end_port_index;
} t_thread_args;

void initialize_thread_args(t_thread_args *args, t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd,
                            sockaddr_in dest, uint8_t thread_index, uint8_t num_threads, uint16_t *current_port_index,
                            uint16_t ports_per_thread, uint16_t remainder_ports);

#endif /* __THREADS_H__ */