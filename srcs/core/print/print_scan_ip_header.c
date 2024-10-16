#include "inc.h"

void print_scan_ip_header(t_global_data *data, u8 addr_index)
{
    fprintf(data->opts.output, "\n[*] %s (%s) scan :\n",
            data->opts.addr_in[addr_index],
            data->opts.addr[addr_index]);
    fprintf(data->opts.output, "PORT       STATE            SERVICE         SCAN\n");
}