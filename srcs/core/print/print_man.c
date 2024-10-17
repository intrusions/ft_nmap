#include <stdio.h>

void print_man(void)
{
    printf(
        "Usage\n"
        "   ft_nmap [options] \n"
        "\n"
        "Options:\n"
        "   --help          print this help screen\n"
        "   --ports         ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n"
        "   --ip            ip addresses to scan\n"
        "   --file          file name containing IP addresses to scan\n"
        "   --speedup       [250 max] number of parallel threads to use\n"
        "   --scan          SYN/NULL/FIN/XMAS/ACK/UDP\n"
        "   --show-all      [TRUE | FALSE] show response for every scan type\n"
        "   --shuffle-ports [TRUE | FALSE] shuffle ports\n"
        "   --debug         [TRUE | FALSE] debug mode\n"
    );
}
