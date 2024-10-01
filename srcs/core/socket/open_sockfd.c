#include "inc.h"

bool open_tcp_sockfd(i32 *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    return (!(*sockfd < 0));
}
