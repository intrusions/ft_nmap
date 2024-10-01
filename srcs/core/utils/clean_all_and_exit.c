#include "inc.h"

void clean_all_and_exit(t_global_data *data, i32 sockfd)
{
    free_str_arr(data->opts.addr_in);
    free_str_arr(data->opts.addr);

    if (sockfd)
        close(sockfd);
    
    exit(EXIT_FAILURE);
}
