#include "inc.h"

void print_nmap_infos(t_options opts)
{
    fprintf(stdout, "[*] [SCAN CONFIGURATIONS]\n");

    /* ip address */
    fprintf(stdout, "[*] Target Ip-Address :\n");
    for (u8 i = 0; opts.addr_in[i]; i++)
        fprintf(stdout, "       - %s\n", opts.addr_in[i]);
    fprintf(stdout, "\n");


    /* ports */
    fprintf(stdout, "[*] No of Ports to scan  : %d\n", opts.n_ports);
    
    /* scans */
    fprintf(stdout, "[*] Scan to be performed : ");
    if (opts.scan_type & SCAN_TYPE_SYN)
        fprintf(stdout, "SYN ");
    if (opts.scan_type & SCAN_TYPE_NULL)
        fprintf(stdout, "NULL ");
    if (opts.scan_type & SCAN_TYPE_ACK)
        fprintf(stdout, "ACK ");
    if (opts.scan_type & SCAN_TYPE_FIN)
        fprintf(stdout, "FIN ");
    if (opts.scan_type & SCAN_TYPE_XMAS)
        fprintf(stdout, "XMAS ");
    if (opts.scan_type & SCAN_TYPE_UDP)
        fprintf(stdout, "UDP ");
    fprintf(stdout, "\n");

    /* threads */
    fprintf(stdout, "[*] No of threads        : %d\n", opts.speedup);
    print_dash_line();
}
