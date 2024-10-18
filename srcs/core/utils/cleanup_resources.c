#include "utils.h"
#include "services.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

void cleanup_resources(t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd)
{
    free_str_arr(data->opts.addr_in);
    free_str_arr(data->opts.addr);
    free_services_tree(data->services);

    if (tcp_sockfd)
        close(tcp_sockfd);
    
    if (udp_sockfd)
        close(udp_sockfd);

    if (data->handle)
        pcap_close(data->handle);
}
