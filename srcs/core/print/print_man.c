#include <stdio.h>

void print_man() {
    printf(
        "Usage:\n"
        "   ft_nmap [options]\n"
        "\n"
        "Options:\n"
        "   --help                  Display this help screen and exit.\n"
        "   --ports <range>         Ports to scan. Specify as a range (e.g., 1-10),\n"
        "                           a comma-separated list (e.g., 1,2,3), or a combination\n"
        "                           of both (e.g., 1,5-15).\n"
        "   --ip <address>          IP address or hostname to scan.\n"
        "   --file <filename>       File containing a list of IP addresses or hostname to scan, one per line.\n"
        "   --speedup <num>         Specify the number of parallel threads to use for scanning\n"
        "                           (maximum 250).\n"
        "   --scan <type>           Type of scan to perform. Choose one or more from the following:\n"
        "                           SYN, NULL, FIN, XMAS, ACK, UDP (e.g., SYN,ACK,UDP).\n"
        "   --source-port <num>     Specify a custom source port to use in the TCP/UDP header.\n"
        "   --output <file>         Specify a file to write the scan results to.\n"
        "   --show-all <bool>       Display the response for every scan type.\n"
        "                           If false, only relevant results are shown.\n"
        "   --shuffle-ports <bool>  Randomize the order in which ports are scanned.\n"
        "   --badsum <bool>         Inject a bad checksum in the TCP/UDP header\n"
        "   --debug <bool>          Enable debug mode for detailed output and logging.\n"
    );
}
