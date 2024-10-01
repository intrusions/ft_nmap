#include "inc.h"

static bool reverse_one_dns(char *addr_in, char *addr)
{
    addrinfo hints;
    addrinfo *addr_info, *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    i32 status;
    if ((status = getaddrinfo(addr_in, NULL, &hints, &addr_info)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return false;
    }

    for (ptr = addr_info; ptr; ptr = ptr->ai_next) {
        void *curr_addr;

        if (ptr->ai_family == AF_INET) {
            sockaddr_in *ipv4 = (sockaddr_in *)ptr->ai_addr;
            curr_addr = &(ipv4->sin_addr);

            if (!inet_ntop(ptr->ai_family, curr_addr, addr, INET6_ADDRSTRLEN)) {
                __log_error("inet_ntop error");
                return false;
            }
            break ;
        }
    }

    freeaddrinfo(addr_info);
    return true;
}

bool reverse_all_dns(t_global_data *data)
{
    u8 nb_addr_in = 0;
    while (data->opts.addr_in[nb_addr_in])
        nb_addr_in++;
        
    data->opts.addr = malloc((nb_addr_in + 1) * sizeof(char *));
    if (!data->opts.addr)
        return false;
    data->opts.addr[nb_addr_in] = NULL;


    for (u8 i = 0 ; i < nb_addr_in; i++) {
        data->opts.addr[i] = malloc(INET6_ADDRSTRLEN * sizeof(char));
        if (!data->opts.addr[i])
            return false;
    }

    
    for (u8 i = 0; i < nb_addr_in; i++) {
        if (!reverse_one_dns(data->opts.addr_in[i], data->opts.addr[i])) {
            free_str_arr(data->opts.addr_in);
            free_str_arr(data->opts.addr);
            return false;
        }
    }
    return true;
}
