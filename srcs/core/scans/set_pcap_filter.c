#include "inc.h"

static bool create_pcap_filter(char **buffer, const char *dest_addr)
{
    const char filter_str[] = "(src host %s) and ((tcp[tcpflags] & tcp-rst != 0) \
                                   or ((tcp[tcpflags] & (tcp-syn | tcp-ack)) == (tcp-syn | tcp-ack)) \
                                   or icmp)";

    i32 size = snprintf(NULL, 0, filter_str, dest_addr) + 1;

    *buffer = (char *)malloc(size);
    if (!*buffer)
        return false;

    snprintf(*buffer, size, filter_str, dest_addr);
    return true;
}

bool set_pcap_filter(pcap_t **handle, char *dest_addr)
{
    char *filter_str;
    if (!create_pcap_filter(&filter_str, dest_addr))
        return false;

    bpf_program filter;
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
