#include <stdio.h>

void print_man(void)
{
    printf(
        "Usage\n"
        "   ft_nmap [options] \n"
        "\n"
        "Options:\n"
        "   --help      print this help screen\n"
        "   --ports     ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n"
        "   --ip        ip addresses to scan in dot format\n"
        "   --file      file name containing IP addresses to scan\n"
        "   --speedup   [250 max] number of parallel threads to use\n"
        "   --scan      SYN/NULL/FIN/XMAS/ACK/UDP\n"
        "   --debug     debug mode (eg: 1 or 0)\n"
    );
}
