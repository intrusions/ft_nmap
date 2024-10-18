#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "global_data.h"

bool open_tcp_sockfd(int32_t *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (*sockfd < 0) {
        __log_error("socket error");
        return false;
    }

    int32_t optval = 1024 * 1024 * 10;
    if (setsockopt(*sockfd, SOL_SOCKET, SO_SNDBUFFORCE, &optval, sizeof(optval)) < 0) {
        __log_error("setsockopt error");
        return false;
    }

    return true;
}

bool open_udp_sockfd(int32_t *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (*sockfd < 0) {
        __log_error("socket error");
        return false;
    }

    int32_t optval = 1024 * 1024 * 10;
    if (setsockopt(*sockfd, SOL_SOCKET, SO_SNDBUFFORCE, &optval, sizeof(optval)) < 0) {
        __log_error("setsockopt error");
        return false;
    }
    
    return true;
}
