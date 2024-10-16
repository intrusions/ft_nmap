#include "inc.h"

static u8 get_port_state(u32 scan_type, u8 response)
{
    if (scan_type == SCAN_TYPE_SYN) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_FILTERED;
        if (response == TCP_SYN_ACK_PCKT)
            return PORT_STATE_OPEN;
        if (response == TCP_RST_PCKT)
            return PORT_STATE_CLOSED;
    }

    if (scan_type == SCAN_TYPE_ACK) {
        
        if (response == TCP_RST_PCKT)
            return PORT_STATE_UNFILTERED;
        return PORT_STATE_FILTERED;
    }

    if (scan_type == SCAN_TYPE_UDP) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_OPEN_FILTERED;
        if (response == ICMP_PCKT_T3_C3)
            return PORT_STATE_CLOSED;
        if (response == ICMP_PCKT_T3)
            return PORT_STATE_FILTERED;
        return PORT_STATE_OPEN;
    }

    if (scan_type == SCAN_TYPE_NULL || scan_type == SCAN_TYPE_FIN || scan_type == SCAN_TYPE_XMAS) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_OPEN_FILTERED;
        if (response == TCP_RST_PCKT)
            return PORT_STATE_CLOSED;
        return PORT_STATE_FILTERED;
    }

    return SCAN_TYPE_UNKNOWN;
}

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

        u8 scan_response;
        if (!recv_packet(data->handle, &scan_response))
            return false;
        
        print_scan_line(
            data,
            port,
            scan_types[i],
            get_port_state(scan_types[i], scan_response)
        );

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
