#include "inc.h"

bool send_tcp_packet(i32 sockfd, sockaddr_in *dest, u16 port, char *src_ip, u16 src_port, u8 scan_type)
{
    t_tcp_packet packet;
    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(src_port);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.window = htons(1024);

    packet.hdr.syn = (scan_type == SCAN_TYPE_SYN);
    packet.hdr.fin = (scan_type == SCAN_TYPE_FIN
                        || scan_type == SCAN_TYPE_XMAS);
    packet.hdr.urg = (scan_type == SCAN_TYPE_XMAS);
    packet.hdr.psh = (scan_type == SCAN_TYPE_XMAS);
    packet.hdr.ack = (scan_type == SCAN_TYPE_ACK);

    if (!tcp_checksum(dest, &packet, src_ip))
        return false;

    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}

bool send_udp_packet(i32 sockfd, sockaddr_in *dest, u16 port, u16 src_port)
{
    t_udp_packet packet;
    memset(&packet, 0, sizeof(t_udp_packet));

    packet.hdr.source = htons(src_port);
    packet.hdr.dest = htons(port);
    packet.hdr.len = htons(sizeof(t_udp_packet));
    
    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        __log_error("sendto error");
        return false;        
    }

    return true;
}
