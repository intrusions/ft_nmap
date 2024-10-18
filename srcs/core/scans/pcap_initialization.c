#include "network.h"
#include <pcap.h>
#include <stdio.h>
#include <stdbool.h>

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
