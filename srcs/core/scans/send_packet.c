#include "inc.h"

bool send_syn_packet(i32 sockfd, sockaddr_in *dest, u16 port)
{
    t_tcp_packet packet;

    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(SOURCE_PORT);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.syn = 1;
    packet.hdr.window = htons(5840);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}

bool send_fin_packet(i32 sockfd, sockaddr_in *dest, u16 port)
{
    t_tcp_packet packet;

    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(SOURCE_PORT);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.fin = 1;
    packet.hdr.window = htons(5840);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}


bool send_null_packet(i32 sockfd, sockaddr_in *dest, u16 port)
{
    t_tcp_packet packet;

    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(SOURCE_PORT);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.window = htons(5840);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}

bool send_xmas_packet(i32 sockfd, sockaddr_in *dest, u16 port)
{
    t_tcp_packet packet;

    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(SOURCE_PORT);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.fin = 1;
    packet.hdr.urg = 1;
    packet.hdr.psh = 1;
    packet.hdr.window = htons(5840);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}

bool send_ack_packet(i32 sockfd, sockaddr_in *dest, u16 port)
{
    t_tcp_packet packet;

    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(SOURCE_PORT);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.ack = 1;
    packet.hdr.window = htons(5840);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}
