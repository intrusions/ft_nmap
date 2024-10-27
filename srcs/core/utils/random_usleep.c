#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void udp_random_usleep(void)
{
    srand(time(NULL));
    uint32_t delay = 750000 + rand() % 750000;
    usleep(delay);
}


void tcp_random_usleep(void)
{
    srand(time(NULL));
    uint32_t delay = 1000 + rand() % 1000;
    usleep(delay);
}
