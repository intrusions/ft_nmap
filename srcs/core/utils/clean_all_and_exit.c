#include "inc.h"

void clean_all_and_exit(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd)
{
    free_str_arr(data->opts.addr_in);
    free_str_arr(data->opts.addr);

    if (tcp_sockfd)
        close(tcp_sockfd);

    if (udp_sockfd)
        close(udp_sockfd);
    
    exit(EXIT_FAILURE);
}
