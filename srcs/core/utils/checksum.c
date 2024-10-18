#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "network.h"

uint16_t checksum(void *b, int len)
{
    uint16_t *buf = b;
    uint32_t sum = 0;
    uint16_t result;

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    
    if (len == 1) {
        sum += *(uint8_t*)buf;
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    
    result = ~sum;
    return result;
}

bool tcp_checksum(sockaddr_in *dest, t_tcp_packet *packet, char *src_ip)
{
    t_pseudo_header psh;

    psh.source_address = inet_addr(src_ip);
    psh.dest_address = dest->sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcphdr));

    char *pseudogram = malloc(sizeof(t_pseudo_header) + sizeof(tcphdr));
    if (!pseudogram)
        return false;

    memcpy(pseudogram, &psh, sizeof(t_pseudo_header));
    memcpy(pseudogram + sizeof(t_pseudo_header), &packet->hdr, sizeof(tcphdr));

    packet->hdr.check = checksum((uint8_t *)pseudogram, sizeof(t_pseudo_header) + sizeof(tcphdr));

    free(pseudogram);
    
    return true;
}
