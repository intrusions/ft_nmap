#include "inc.h"

bool nmap(t_global_data *data)
{
    print_nmap_infos(data->opts);
    fprintf(stdout, "[Scanning]\n");

    
    (void)process_nmap_scans(data);

    return true;
}

int main(int ac, char **av)
{
    t_global_data g_data;
    ac--, av++;

    if (!ac) {
        print_man();
        return EXIT_FAILURE;
    }

    set_default_opts_val(&g_data.opts);
    if (!parse_arg(ac, av, &g_data) || !reverse_all_dns(&g_data))
        return EXIT_FAILURE;
    
    (void)nmap(&g_data);

    free_str_arr(g_data.opts.addr_in);
    free_str_arr(g_data.opts.addr);
    return EXIT_SUCCESS;
}
