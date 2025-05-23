#include "utils.h"
#include "network.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static bool resolve_one_dns(char *addr_in, char *addr)
{
    addrinfo hints;
    addrinfo *addr_info, *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int32_t status;
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
                perror("inet_ntop error");
                return false;
            }
            break ;
        }
    }

    freeaddrinfo(addr_info);
    return true;
}

bool resolve_dns(t_global_data *data)
{
    uint8_t nb_addr_in = 0;
    while (data->opts.addr_in[nb_addr_in])
        nb_addr_in++;
        
    data->opts.addr = malloc((nb_addr_in + 1) * sizeof(char *));
    if (!data->opts.addr)
        return false;
    data->opts.addr[nb_addr_in] = NULL;


    for (uint8_t i = 0 ; i < nb_addr_in; i++) {
        data->opts.addr[i] = malloc(INET6_ADDRSTRLEN * sizeof(char));
        if (!data->opts.addr[i])
            return false;
    }

    
    for (uint8_t i = 0; i < nb_addr_in; i++) {
        if (!resolve_one_dns(data->opts.addr_in[i], data->opts.addr[i])) {
            free_str_arr(data->opts.addr_in);
            free_str_arr(data->opts.addr);
            return false;
        }
    }
    return true;
}
