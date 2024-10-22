#include "threads.h"
#include "global_data.h"

void initialize_thread_args(t_thread_args *args, t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd,
                            sockaddr_in dest, uint8_t thread_index, uint8_t num_threads, uint16_t *current_port_index,
                            uint16_t ports_per_thread, uint16_t remainder_ports)
{
    uint16_t start_port_index = *current_port_index;
    *current_port_index += ports_per_thread;
    uint16_t end_port_index = *current_port_index - 1;

    if (thread_index == num_threads - 1)
        end_port_index += remainder_ports;

    args->data = data;
    args->tcp_sockfd = tcp_sockfd;
    args->udp_sockfd = udp_sockfd;
    args->dest = dest;
    args->start_port_index = start_port_index;
    args->end_port_index = end_port_index;
}
