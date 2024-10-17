#include "inc.h"

void print_nmap_infos(t_global_data *data)
{
    fprintf(stdout, "[*] [SCAN CONFIGURATIONS]\n");

    /* ip address */
    fprintf(stdout, "[*] Target Ip-Address :\n");
    for (u8 i = 0; data->opts.addr_in[i]; i++)
        fprintf(stdout, "       - %s\n", data->opts.addr_in[i]);
    fprintf(stdout, "\n");


    /* ports */
    fprintf(stdout, "[*] No of Ports to scan  : %d\n", data->opts.n_ports);
    
    /* scans */
    fprintf(stdout, "[*] Scan to be performed : ");
    if (data->opts.scan_type & SCAN_TYPE_SYN)
        fprintf(stdout, "SYN ");
    if (data->opts.scan_type & SCAN_TYPE_NULL)
        fprintf(stdout, "NULL ");
    if (data->opts.scan_type & SCAN_TYPE_ACK)
        fprintf(stdout, "ACK ");
    if (data->opts.scan_type & SCAN_TYPE_FIN)
        fprintf(stdout, "FIN ");
    if (data->opts.scan_type & SCAN_TYPE_XMAS)
        fprintf(stdout, "XMAS ");
    if (data->opts.scan_type & SCAN_TYPE_UDP)
        fprintf(stdout, "UDP ");
    fprintf(stdout, "\n");

    /* threads */
    fprintf(stdout, "[*] No of threads        : %d\n", data->opts.speedup);
    
    /* self info */
    fprintf(stdout, "[*] Source Ip-Address    : %s\n", data->src_ip);
    fprintf(stdout, "[*] Source Port          : %d\n", data->opts.source_port);
    
    print_dash_line();
}
