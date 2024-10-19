#include "global_data.h"
#include "scanner.h"
#include "utils.h"
#include "options.h"
#include <stdbool.h>

void print_nmap_infos(t_global_data *data)
{
    fprintf(data->opts.output, "[*] [SCAN CONFIGURATIONS]\n");

    /* ip address */
    fprintf(data->opts.output, "[*] Target Ip-Address :\n");
    for (uint8_t i = 0; data->opts.addr_in[i]; i++)
        fprintf(data->opts.output, "       - %s\n", data->opts.addr_in[i]);
    fprintf(data->opts.output, "\n");


    /* ports */
    fprintf(data->opts.output, "[*] No of Ports to scan  : %d\n", data->opts.n_ports);
    
    /* scans */
    fprintf(data->opts.output, "[*] Scan to be performed : ");
    if (data->opts.scan_type & SCAN_TYPE_SYN)
        fprintf(data->opts.output, "SYN ");
    if (data->opts.scan_type & SCAN_TYPE_NULL)
        fprintf(data->opts.output, "NULL ");
    if (data->opts.scan_type & SCAN_TYPE_ACK)
        fprintf(data->opts.output, "ACK ");
    if (data->opts.scan_type & SCAN_TYPE_FIN)
        fprintf(data->opts.output, "FIN ");
    if (data->opts.scan_type & SCAN_TYPE_XMAS)
        fprintf(data->opts.output, "XMAS ");
    if (data->opts.scan_type & SCAN_TYPE_UDP)
        fprintf(data->opts.output, "UDP ");
    fprintf(data->opts.output, "\n");

    /* threads */
    fprintf(data->opts.output, "[*] No of threads        : %d\n", data->opts.speedup);
    
    /* self info */
    fprintf(data->opts.output, "[*] Source Ip-Address    : %s\n", data->src_ip);
    fprintf(data->opts.output, "[*] Source Port          : %d\n", data->opts.source_port);
    
    print_dash_line(data->opts.output);
}
