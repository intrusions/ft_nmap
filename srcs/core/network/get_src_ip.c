#include "inc.h"

bool get_src_ip(char *src_ip)
{
    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevsp;
    pcap_if_t *device;

    if (pcap_findalldevs(&alldevsp, errbuff) == -1) {
        printf("pcap_findalldevs error: %s\n", errbuff);
        return false;
    }
    
    for (device = alldevsp; device; device = device->next) {
        for (pcap_addr_t *pcap_addr = device->addresses; pcap_addr; pcap_addr = pcap_addr->next) {
            if (pcap_addr->addr->sa_family == AF_INET) {
                sockaddr_in *ipv4_addr = (sockaddr_in *)pcap_addr->addr;
                inet_ntop(AF_INET, &ipv4_addr->sin_addr, src_ip, INET_ADDRSTRLEN);
                
                goto success;
            }
        }
    }

    goto error;

error:
    pcap_freealldevs(alldevsp);
    return false;

success:
    pcap_freealldevs(alldevsp);
    return true;
}
