#include "network.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool create_pcap_filter(char **buffer, char *serv_addr, uint16_t port)
{
    char filter_str[] = "(src host %s) and ((src port %d and ((tcp[tcpflags] & tcp-rst != 0) \
                        or ((tcp[tcpflags] & (tcp-syn | tcp-ack)) == (tcp-syn | tcp-ack)))) \
                        or (icmp and icmp[8 + 20 + 2:2] == %d))";

    int32_t size = snprintf(NULL, 0, filter_str, serv_addr, port, port) + 1;

    *buffer = (char *)malloc(size);
    if (!*buffer)
        return false;

    snprintf(*buffer, size, filter_str, serv_addr, port, port);
    return true;
}

bool set_pcap_filter(pcap_t **handle, char *serv_addr, uint16_t port)
{
    char *filter_str;
    if (!create_pcap_filter(&filter_str, serv_addr, port))
        return false;

    struct bpf_program filter;
    if (pcap_compile(*handle, &filter, filter_str, 0, PCAP_NETMASK_UNKNOWN) == PCAP_ERROR) {
        fprintf(stderr, "pcap_compile error: %s\n", pcap_geterr(*handle));
        return false;
    }

    free(filter_str);

    if (pcap_setfilter(*handle, &filter) == PCAP_ERROR) {
        fprintf(stderr, "pcap_setfilter error: %s\n", pcap_geterr(*handle));
        pcap_freecode(&filter);
        return false;
    }

    pcap_freecode(&filter);
    return true;
}
