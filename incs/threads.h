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


/*
 * Initializes the arguments for each port scanning thread.
 * @param args                Pointer to the `t_thread_args` structure used by the thread.
 * @param data                Pointer to the global `t_global_data` structure containing the scan options.
 * @param tcp_sockfd          TCP socket file descriptor used by the thread for sending TCP packets.
 * @param udp_sockfd          UDP socket file descriptor used by the thread for sending UDP packets.
 * @param dest                Destination address for the scan, as a `sockaddr_in` structure.
 * @param thread_index        Index of the current thread (used for determining the port range).
 * @param num_threads         Total number of threads being used for the scan.
 * @param current_port_index  Pointer to the current index in the port list, updated for each thread.
 * @param ports_per_thread    Number of ports assigned to each thread.
 * @param remainder_ports     Additional ports assigned to the last thread if the total number of ports is not divisible by `num_threads`.
 */
void initialize_thread_args(t_thread_args *args, t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd,
                            sockaddr_in dest, uint8_t thread_index, uint8_t num_threads, uint16_t *current_port_index,
                            uint16_t ports_per_thread, uint16_t remainder_ports);

#endif /* __THREADS_H__ */