#include "inc.h"

static bool process_scan_type(t_global_data *data, i32 sockfd, sockaddr_in *dest, u32 scan_type)
{
    for (u16 port_index = 0; port_index < data->opts.n_ports; port_index++) {
        u16 port = data->opts.ports[port_index];

        if (scan_type == SCAN_TYPE_UDP) {
            if (!send_udp_packet(sockfd, dest, port))
                return false;
        } else {
            if (!send_tcp_packet(sockfd, dest, port, scan_type))
                return false;
        }

        // TODO
        // if (!recv_tcp_packet())
        //     return false;
    }
    
    return true;
}

bool process_nmap_scans(t_global_data *data)
{
    u32 scan_types[NUM_SCAN_TYPE] = {
        SCAN_TYPE_SYN,
        SCAN_TYPE_FIN,
        SCAN_TYPE_NULL,
        SCAN_TYPE_XMAS,
        SCAN_TYPE_ACK,
        SCAN_TYPE_UDP,
    };


    for (u8 addr_index = 0; data->opts.addr[addr_index]; addr_index++) {
        fprintf(stdout, "[*] %s (%s) scan :\n",
                data->opts.addr_in[addr_index],
                data->opts.addr[addr_index]);

        i32 tcp_sockfd = 0, udp_sockfd = 0;
        if (!open_tcp_sockfd(&tcp_sockfd) || !open_udp_sockfd(&udp_sockfd))
            clean_all_and_exit(data, tcp_sockfd, udp_sockfd);

        sockaddr_in dest;
        memset(&dest, 0, sizeof(sockaddr_in));
        dest.sin_family = AF_INET;  
        dest.sin_addr.s_addr = inet_addr(data->opts.addr[addr_index]);

        for (u8 i = 0; i < NUM_SCAN_TYPE; i++) {
            
            if (data->opts.scan_type & scan_types[i]) {
               
                i32 sockfd;
                if (scan_types[i] == SCAN_TYPE_UDP)
                    sockfd = udp_sockfd;
                else
                    sockfd = tcp_sockfd;

                if (!process_scan_type(data, sockfd, &dest, scan_types[i]))
                    clean_all_and_exit(data, tcp_sockfd, udp_sockfd);
            }
        }

        close(tcp_sockfd);
    }

    return true;
}
