#include "network.h"
#include "global_data.h"
#include "scanner.h"
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <netinet/ip_icmp.h>

static void recv_packet_handler(uint8_t *state, const struct pcap_pkthdr *header, const uint8_t *packet)
{
    (void)header;
    uint8_t *response_state = (uint8_t *)state;

    const uint8_t *ip_header;
    const uint8_t *tcp_header;
    const uint8_t *icmp_header;

    int32_t ethernet_header_length = 14;
    int32_t ip_header_length;
    int32_t tcp_header_length;

    ip_header = packet + ethernet_header_length;
    ip_header_length = ((*ip_header) & 0x0F) * 4;

    if (*(ip_header + 9) == IPPROTO_TCP) {

        tcp_header = packet + ethernet_header_length + ip_header_length;
        tcp_header_length = ((*(tcp_header + 12)) & 0xF0) >> 4;
        tcp_header_length = tcp_header_length * 4;

        tcphdr *tcp_hdr = (tcphdr *)tcp_header;
        uint8_t flags = tcp_hdr->th_flags;

        if (flags & TH_RST) {
            *response_state = TCP_RST_PCKT;
            return ;
        } 
        if ((flags & TH_SYN) && (flags & TH_ACK)) {
            *response_state = TCP_SYN_ACK_PCKT;
            return ;
        }
    }
    else if (*(ip_header + 9) == IPPROTO_ICMP) {

        icmp_header = packet + ethernet_header_length + ip_header_length;
        icmphdr *icmp_hdr = (icmphdr *)icmp_header;

        if (icmp_hdr->type == 3 && icmp_hdr->code == 3) {
            *response_state = ICMP_PCKT_T3_C3;
            return ; 
        }

        *response_state = ICMP_PCKT_T3;
        return ;     
    }

    *response_state = NO_RESPONSE;
}

bool recv_packet(pcap_t *handle, uint8_t *response_state)
{
    struct timeval tv = {0, 500000};
    fd_set readfds;
    FD_ZERO(&readfds);
    
    int32_t pcap_fd = pcap_fileno(handle);
    if (pcap_fd == PCAP_ERROR) {
        fprintf(stderr, "pcap_fileno error %s\n", pcap_geterr(handle));
        return false;
    }

    FD_SET(pcap_fd, &readfds);
    
    int32_t retval = select(pcap_fd + 1, &readfds, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select error:");
        return false;
    }
    
    if (!retval) {
        *response_state = NO_RESPONSE;
        return true;
    }
    
    if (FD_ISSET(pcap_fd, &readfds)) {
        if (pcap_dispatch(handle, 1, recv_packet_handler, (uint8_t *)response_state) == PCAP_ERROR) {
            fprintf(stderr, "pcap_dispatch error: %s\n", pcap_geterr(handle));
            return false;
        }
    }

    return true;
}
