#include "global_data.h"
#include "network.h"
#include "scanner.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

bool send_tcp_packet(t_global_data *data, int32_t sockfd, sockaddr_in *dest, uint16_t port, uint8_t scan_type)
{
    t_tcp_packet packet;
    memset(&packet, 0, sizeof(t_tcp_packet));

    packet.hdr.source = htons(data->opts.source_port);
    packet.hdr.dest = htons(port);
    packet.hdr.doff = 5;
    packet.hdr.window = htons(1024);

    packet.hdr.syn = (scan_type == SCAN_TYPE_SYN);
    packet.hdr.fin = (scan_type == SCAN_TYPE_FIN
                        || scan_type == SCAN_TYPE_XMAS);
    packet.hdr.urg = (scan_type == SCAN_TYPE_XMAS);
    packet.hdr.psh = (scan_type == SCAN_TYPE_XMAS);
    packet.hdr.ack = (scan_type == SCAN_TYPE_ACK);

    if (data->opts.badsum) {
        if (!tcp_checksum(dest, &packet, "0.0.0.0"))
            return false;
    } else {
        if (!tcp_checksum(dest, &packet, data->src_ip))
            return false;
    }


    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        perror("sendto error");
        return false;        
    }

    return true;
}

bool send_udp_packet(t_global_data *data, int32_t sockfd, sockaddr_in *dest, uint16_t port)
{
    t_udp_packet packet;
    memset(&packet, 0, sizeof(t_udp_packet));

    packet.hdr.source = htons(data->opts.source_port);
    packet.hdr.dest = htons(port);
    packet.hdr.len = htons(sizeof(t_udp_packet));

    if (data->opts.badsum) {
        if (!udp_checksum(dest, &packet, "0.0.0.0"))
            return false;
    } else {
        if (!udp_checksum(dest, &packet, data->src_ip))
            return false;
    }
    
    if (sendto(sockfd, &packet, sizeof(packet), 0, (const sockaddr *)dest, sizeof(*dest)) <= 0) {
        perror("sendto error");
        return false;        
    }

    return true;
}
