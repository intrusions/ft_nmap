#include "inc.h"

u16 checksum(void *b, int len)
{
    u16 *buf = b;
    u32 sum = 0;
    u16 result;

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    
    if (len == 1) {
        sum += *(u8*)buf;
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    
    result = ~sum;
    return result;
}

bool tcp_checksum(sockaddr_in *dest, t_tcp_packet *packet)
{
    t_pseudo_header psh;
    
    psh.source_address = inet_addr("192.168.0.24");
    psh.dest_address = dest->sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcphdr));

    char *pseudogram = malloc(sizeof(t_pseudo_header) + sizeof(tcphdr));
    if (!pseudogram)
        return false;

    memcpy(pseudogram, &psh, sizeof(t_pseudo_header));
    memcpy(pseudogram + sizeof(t_pseudo_header), &packet->hdr, sizeof(tcphdr));

    packet->hdr.check = checksum((u8 *)pseudogram, sizeof(t_pseudo_header) + sizeof(tcphdr));
    
    return true;
}
