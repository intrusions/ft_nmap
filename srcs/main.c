#include "inc.h"

bool nmap(t_global_data *data)
{
    print_nmap_infos(data->opts);

    timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    if (!process_nmap_scans(data))
        return false;
    
    timespec end_time; 
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double time_spent;
    time_spent = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    print_dash_line();
    fprintf(stdout, "Scan took %.5f secs\n", time_spent);

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

    if (getuid()) {
        fprintf(stderr, "program must be started in sudo mode.\n");
        return EXIT_FAILURE;
    }

    set_default_opts_val(&g_data.opts);
    if (!parse_arg(ac, av, &g_data) || !reverse_all_dns(&g_data))
        return EXIT_FAILURE;
    
    if (!nmap(&g_data)) {
        fprintf(stderr, "an error occured.\n");
        return EXIT_FAILURE;
    }

    clean_all(&g_data);
    return EXIT_SUCCESS;
}
