#include "inc.h"

void cleanup_resources(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd, pcap_t *handle)
{
    free_str_arr(data->opts.addr_in);
    free_str_arr(data->opts.addr);
    free_services_tree(data->services);

    if (tcp_sockfd)
        close(tcp_sockfd);
    
    if (udp_sockfd)
        close(udp_sockfd);

    if (handle)
        pcap_close(handle);
}
