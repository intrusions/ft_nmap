#include "inc.h"

int main(int ac, char **av)
{
    t_global_data g_data;
    ac--, av++;

    memset(&g_data.opts, 0, sizeof(g_data.opts));

    if (!ac) {
        print_man();
        return EXIT_FAILURE;
    }

    if (!parse_arg(ac, av, &g_data))
        return EXIT_FAILURE;

    if (!reverse_dns(g_data.opts.addr_in, g_data.opts.addr)
            || !socket_initialization(&g_data))
        return EXIT_FAILURE;
    
    if (g_data.opts.debug_mode)
        print_options(&g_data.opts);
    
    // process nmap

    return EXIT_SUCCESS;
}
