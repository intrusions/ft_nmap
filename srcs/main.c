#include "inc.h"

void set_default_opts_val(t_options *opts)
{
    opts->speedup = 0;
    opts->n_ports = 1024;
    opts->debug_mode = false;
    opts->scan_type = SCAN_TYPE_ACK
                        | SCAN_TYPE_FIN
                        | SCAN_TYPE_NULL
                        | SCAN_TYPE_SYN
                        | SCAN_TYPE_UDP
                        | SCAN_TYPE_XMAS;
    
    for (u16 i = 0; i < SIZE_PORTS_ARRAY; i++)
        opts->ports[i] = i + 1;
}

int main(int ac, char **av)
{
    t_global_data g_data;
    set_default_opts_val(&g_data.opts);

    ac--, av++;

    if (!ac) {
        print_man();
        return EXIT_FAILURE;
    }

    if (!parse_arg(ac, av, &g_data)
            // || !reverse_dns(g_data.opts.addr_in, g_data.opts.addr)
            // || !socket_initialization(&g_data)
            )
        return EXIT_FAILURE;
    
    // process nmap

    free_str_arr(g_data.opts.addr_in);
    return EXIT_SUCCESS;
}
