#include "inc.h"

bool open_tcp_sockfd(i32 *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (*sockfd < 0) {
        __log_error("socket creation failed");
        return false;
    }

    i32 optval = 1024 * 1024;
    if (setsockopt(*sockfd, SOL_SOCKET, SO_SNDBUFFORCE, &optval, sizeof(optval)) < 0) {
        __log_error("setsockopt failed");
        return false;
    }

    return true;
}

bool open_udp_sockfd(i32 *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (*sockfd < 0) {
        __log_error("socket creation failed");
        return false;
    }

    i32 optval = 1024 * 1024;
    if (setsockopt(*sockfd, SOL_SOCKET, SO_SNDBUFFORCE, &optval, sizeof(optval)) < 0) {
        __log_error("setsockopt failed");
        return false;
    }
    return true;
}
