#include "inc.h"

static char *create_pcap_filter(char *dest_addr)
{
    const char pckt_filter_str1[] = "(src host ";
    const char pckt_filter_str2[] = ") and ((tcp[tcpflags] & tcp-rst != 0) " \
        "or ((tcp[tcpflags] & (tcp-syn | tcp-ack)) == (tcp-syn | tcp-ack)) "\
        "or icmp)";

    char *filter_str_p1 = str_join(pckt_filter_str1, dest_addr);
    if (!filter_str_p1)
        return NULL;

    char *filter_str = str_join(filter_str_p1, pckt_filter_str2);
    free(filter_str_p1);
    
    if (!filter_str)
        return NULL;

    return filter_str;
}

bool set_pcap_filter(pcap_t **handle, char *dest_addr)
{
    bpf_program filter;

    char *filter_str = create_pcap_filter(dest_addr);
    if (!filter_str)
        goto error;

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
    free(filter_str);
    return false;

success:
    pcap_freecode(&filter);
    return true;
}

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

    return true;
}
