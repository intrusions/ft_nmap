#include "inc.h"

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
            
            if ((data->opts.scan_type & SCAN_TYPE_SYN && !send_syn_packet(tcp_sockfd, &dest, port))
                || (data->opts.scan_type & SCAN_TYPE_FIN && !send_fin_packet(tcp_sockfd, &dest, port))
                || (data->opts.scan_type & SCAN_TYPE_NULL && !send_null_packet(tcp_sockfd, &dest, port))
                || (data->opts.scan_type & SCAN_TYPE_XMAS && !send_xmas_packet(tcp_sockfd, &dest, port))
                || (data->opts.scan_type & SCAN_TYPE_ACK && !send_ack_packet(tcp_sockfd, &dest, port)))
                clean_all_and_exit(data, tcp_sockfd);
        }

        close(tcp_sockfd);
    }

    return true;
}
