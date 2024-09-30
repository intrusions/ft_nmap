#include "inc.h"

bool nmap(t_global_data *data)
{
    print_nmap_infos(data->opts);

    // (void)process_nmap(data);
    
    return true;
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
    
    (void)nmap(&g_data);

    free_str_arr(g_data.opts.addr_in);
    return EXIT_SUCCESS;
}
