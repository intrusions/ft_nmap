#include "inc.h"

static void recv_packet_handler(u_char *state, const struct pcap_pkthdr *header, const u_char *packet)
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

bool recv_packet(pcap_t *handle, u8 *response_state)
{
    timeval tv = {0, 250000};
    fd_set readfds;
    FD_ZERO(&readfds);
    
    i32 pcap_fd = pcap_fileno(handle);
    if (pcap_fd == PCAP_ERROR) {
        fprintf(stderr, "pcap_fileno error");
        return false;
    }

    FD_SET(pcap_fd, &readfds);
    
    i32 retval = select(pcap_fd + 1, &readfds, NULL, NULL, &tv);
    if (retval == -1) {
        __log_error("socket error:");
        return false;
    }
    
    if (!retval) {
        *response_state = NO_RESPONSE;
        return true;
    }
    
    if (FD_ISSET(pcap_fd, &readfds)) {
        if (pcap_dispatch(handle, 1, recv_packet_handler, (u8 *)response_state) == PCAP_ERROR) {
            fprintf(stderr, "Error dispatching packet: %s\n", pcap_geterr(handle));
            return false;
        }
    }

    return true;
}
