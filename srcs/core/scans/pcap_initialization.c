#include "inc.h"

bool pcap_initialization(pcap_t **handle)
{
    char *devs;
    char err_buf[PCAP_ERRBUF_SIZE];

    devs = pcap_lookupdev(err_buf);
    if (!devs) {
        fprintf(stderr, "pcap_lookupdev error: %s\n", err_buf);
        return false;
    }

    *handle = pcap_open_live(devs, BUFSIZ, 1, 200, err_buf);
    if (!*handle) {
        fprintf(stderr, "pcap_open_live error: %s\n", err_buf);
        return false;
    }

    bpf_program filter;
    char filter_str[] = "(tcp[tcpflags] & tcp-rst != 0) \
        or ((tcp[tcpflags] & (tcp-syn | tcp-ack)) == (tcp-syn | tcp-ack)) \
        or icmp";
    
    if (pcap_compile(*handle, &filter, filter_str, 0, PCAP_NETMASK_UNKNOWN) == PCAP_ERROR) {
        fprintf(stderr, "pcap_compile error: %s\n", pcap_geterr(*handle));
        goto error;
    }

    if (pcap_setfilter(*handle, &filter) == PCAP_ERROR) {
        fprintf(stderr, "pcap_setfilter error: %s\n", pcap_geterr(*handle));
        pcap_freecode(&filter);
        goto error;
    }

    goto success;

error:
    pcap_close(*handle);
    return false;

success:
    pcap_freecode(&filter);
    return true;
}
