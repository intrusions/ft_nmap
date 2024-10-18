#include "global_data.h"
#include "network.h"
#include "parse.h"
#include "services.h"
#include "utils.h"
#include "scanner.h"
#include <stdlib.h>
#include <time.h>

bool nmap(t_global_data *data)
{
    timespec start_time;
    timespec end_time; 

    print_nmap_infos(data);
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    if (!process_nmap_scans(data))
        return false;
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    print_nmap_resume(start_time, end_time, data->opts.output);
    
    return true;
}

int main(int ac, char **av)
{
    t_global_data g_data;
    memset(&g_data, 0, sizeof(t_global_data));
    
    ac--, av++;

    if (!ac) {
        print_man();
        return EXIT_FAILURE;
    }

    if (!is_sudo_mode()
            || !parse_arg(ac, av, &g_data)
            || !reverse_all_dns(&g_data)
            || !create_services_tree(&g_data)
            || !get_src_ip(g_data.src_ip)
            || !pcap_initialization(&g_data.handle)
            || !nmap(&g_data))
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}
