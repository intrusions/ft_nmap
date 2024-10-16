#include "inc.h"

static void serv_response_handler(u_char *state, const struct pcap_pkthdr *header, const u_char *packet)
{
    (void)header;
    u8 *response_state = (u8 *)state;

    const u_char *ip_header;
    const u_char *tcp_header;
    const u_char *icmp_header;

    int ethernet_header_length = 14;
    int ip_header_length;
    int tcp_header_length;

    ip_header = packet + ethernet_header_length;
    ip_header_length = ((*ip_header) & 0x0F) * 4;

	if (*(ip_header + 9) == IPPROTO_TCP) {

        tcp_header = packet + ethernet_header_length + ip_header_length;
        tcp_header_length = ((*(tcp_header + 12)) & 0xF0) >> 4;
        tcp_header_length = tcp_header_length * 4;

        struct tcphdr *tcp_hdr = (struct tcphdr *)tcp_header;
        unsigned char flags = tcp_hdr->th_flags;

		if (flags & TCP_RST_FLAG) {
            *response_state = TCP_RST_PCKT;
            return ;
		} 
		if ((flags & TCP_SYN_FLAG) && (flags & TCP_ACK_FLAG)) {
            *response_state = TCP_SYN_ACK_PCKT;
            return ;
		}
    }
    else if (*(ip_header + 9) == IPPROTO_ICMP) {

        icmp_header = packet + ethernet_header_length + ip_header_length;
        struct icmphdr *icmp_hdr = (struct icmphdr *)icmp_header;

		// destination unreachable && port unreachable
        if (icmp_hdr->type == 3 && icmp_hdr->code == 3) {
            *response_state = ICMP_PCKT_T3_C3;
            return ; 
        }

        *response_state = ICMP_PCKT_T3;
        return ;     
    }

    *response_state = NO_RESPONSE;
}

static void recv_and_save_serv_response(pcap_t *handle, u8 *response_state)
{
	struct timeval tv = {0, 250000};

	fd_set readfds;
	FD_ZERO(&readfds);
	int pcap_fd = pcap_fileno(handle);
	FD_SET(pcap_fd, &readfds);

	int retval = select(pcap_fd + 1, &readfds, NULL, NULL, &tv);

	if (retval == -1) {
		perror("select error");
		exit(EXIT_FAILURE);
	} else if (retval == 0)
		return;
	else if (FD_ISSET(pcap_fd, &readfds))
		pcap_dispatch(handle, 1, serv_response_handler, (u_char *)response_state);
}

static void _pcap_init(pcap_t **handle)
{
	char	*devs;
	char	err_buf[PCAP_ERRBUF_SIZE];
	struct	bpf_program filter;
	// char	filter_str[] = "tcp";
	char filter_str[] = "(tcp[tcpflags] & tcp-rst != 0) or (tcp[tcpflags] & (tcp-syn | tcp-ack) == (tcp-syn | tcp-ack)) or icmp";

	devs = pcap_lookupdev(err_buf);
	if (!devs) {
		fprintf(stderr, "error finding device");
		// TODO: - Free and exit
		exit(EXIT_FAILURE);
	}

	*handle =  pcap_open_live(devs, BUFSIZ, 1, 200, err_buf);
	if (!*handle)
	{
		fprintf(stderr, "couldn t open device\n");
		// TODO: - Free and exit
		exit(EXIT_FAILURE);
	}

	if (pcap_compile(*handle, &filter, filter_str, 0, PCAP_NETMASK_UNKNOWN) == -1) {
		fprintf(stderr, "Bad filter - %s\n", pcap_geterr(*handle));
		// TODO: - Free and exit
		pcap_close(*handle);
		exit(EXIT_FAILURE);
	}

	if (pcap_setfilter(*handle, &filter) == -1) {
		fprintf(stderr, "Error setting filter - %s\n", pcap_geterr(*handle));
		// TODO: - Free and exit
		pcap_close(*handle);
		exit(EXIT_FAILURE);
	}

}

static u8 get_port_state(u32 scan_type, u8 response)
{
    printf("------------ scan type - [%d]\n", scan_type);

    if (scan_type == SCAN_TYPE_SYN)
    {
        if (response == NO_RESPONSE) return PORT_STATE_FILTERED;
        if (response == TCP_SYN_ACK_PCKT) return PORT_STATE_OPEN;
        if (response == TCP_RST_PCKT) return PORT_STATE_CLOSED;
    }

    if (scan_type == SCAN_TYPE_ACK)
    {
        if (response == TCP_RST_PCKT) return PORT_STATE_UNFILTERED;
        return PORT_STATE_FILTERED;
    }

    if (scan_type == SCAN_TYPE_UDP)
    {
        if (response == NO_RESPONSE) return PORT_STATE_OPEN_FILTERED;
        if (response == ICMP_PCKT_T3_C3) return PORT_STATE_CLOSED;
        if (response == ICMP_PCKT_T3) return PORT_STATE_FILTERED;
        return PORT_STATE_OPEN;
    }

    if (scan_type == SCAN_TYPE_NULL || scan_type == SCAN_TYPE_FIN || scan_type == SCAN_TYPE_XMAS)
    {
        if (response == NO_RESPONSE) return PORT_STATE_OPEN_FILTERED;
        if (response == TCP_RST_PCKT) return PORT_STATE_CLOSED;
        return PORT_STATE_FILTERED;
    }

    return SCAN_TYPE_UNKNOW;
}

static bool process_port_scan(t_global_data *data, i32 tcp_sockfd, i32 udp_sockfd, sockaddr_in *dest, i16 port, pcap_t *handle)
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
        recv_and_save_serv_response(handle, &scan_response);
        u8 port_state = get_port_state(scan_types[i], scan_response);
        print_scan_line(data, port, scan_types[i], port_state);
        random_usleep();
    }
    
    return true;
}

bool process_nmap_scans(t_global_data *data)

{
    i32 tcp_sockfd = 0, udp_sockfd = 0;
    pcap_t *handle = NULL;
    _pcap_init(&handle);
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

            if (!process_port_scan(data, tcp_sockfd, udp_sockfd, &dest, port, handle))
                goto error;
        }
    }
    pcap_close(handle);
    goto success;

error:
    cleanup_resources(data, tcp_sockfd, udp_sockfd);
    return false;

success:
    cleanup_resources(data, tcp_sockfd, udp_sockfd);
    return true;
}
