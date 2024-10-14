#include "inc.h"

static bool process_port_scan(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd, sockaddr_in *dest, i16 port)
{
    u32 scan_types[NUM_SCAN_TYPE] = {
        SCAN_TYPE_SYN,
        SCAN_TYPE_FIN,
        SCAN_TYPE_NULL,
        SCAN_TYPE_XMAS,
        SCAN_TYPE_ACK,
        SCAN_TYPE_UDP,
    };

    for (u8 i = 0; i < NUM_SCAN_TYPE; i++) {
        bool packed_sended = false;

        if ((scan_types[i] == SCAN_TYPE_UDP) && (data->opts.scan_type & SCAN_TYPE_UDP)) {
            if (!send_udp_packet(udp_sockfd, dest, port))
                return false;

            packed_sended = true;
        } else if (data->opts.scan_type & scan_types[i]){
            if (!send_tcp_packet(tcp_sockfd, dest, port, data->src_ip, scan_types[i]))
                return false;

            packed_sended = true;
        }

        if (!packed_sended)
            continue ;

        
        // receive_response function, return his state (open, closed, filtered, etc)
        u8 state = PORT_STATE_OPEN;
        print_scan_line(data, port, scan_types[i], state);
        random_usleep();
    }
    
    return true;
}

bool process_nmap_scans(t_global_data *data)
{
    i32 tcp_sockfd = 0, udp_sockfd = 0;
    if (!open_tcp_sockfd(&tcp_sockfd) || !open_udp_sockfd(&udp_sockfd))
        goto error;

    fprintf(stdout, "[*] [SCANNING]");
    for (u8 addr_index = 0; data->opts.addr[addr_index]; addr_index++) {
        print_scan_ip_header(data, addr_index);

        sockaddr_in dest;
        memset(&dest, 0, sizeof(sockaddr_in));
        dest.sin_family = AF_INET;  
        dest.sin_addr.s_addr = inet_addr(data->opts.addr[addr_index]);

        for (u16 port_index = 0; port_index < data->opts.n_ports; port_index++) {
            u16 port = data->opts.ports[port_index];

            if (!process_port_scan(data, tcp_sockfd, udp_sockfd, &dest, port))
                goto error;
        }
    }
    goto success;

error:
    cleanup_resources(data, tcp_sockfd, udp_sockfd);
    return false;

success:
    cleanup_resources(data, tcp_sockfd, udp_sockfd);
    return true;
}
