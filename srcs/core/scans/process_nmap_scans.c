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

bool process_nmap_scans(t_global_data *data)
{
    for (u8 addr_index = 0; data->opts.addr[addr_index]; addr_index++) {
    
        i32 tcp_sockfd;
        if (!open_tcp_sockfd(&tcp_sockfd)) {
            __log_error("socket error");
            clean_all_and_exit(data, 0);
        }

        sockaddr_in dest;
        memset(&dest, 0, sizeof(sockaddr_in));
        dest.sin_family = AF_INET;  
        dest.sin_addr.s_addr = inet_addr(data->opts.addr[addr_index]);

        for (u16 port_index = 0; port_index < data->opts.n_ports; port_index++) {
            u16 port = data->opts.ports[port_index];
            
            if (data->opts.scan_type & SCAN_TYPE_SYN && !send_syn_packet(tcp_sockfd, &dest, port))
                clean_all_and_exit(data, tcp_sockfd);
        }

        close(tcp_sockfd);
    }

    return true;
}
