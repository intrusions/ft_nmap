#include <string.h>
#include <stdlib.h>
#include "global_data.h"
#include "parse.h"
#include "utils.h"

static bool is_valid_arg(char *arg)
{
    if (strcmp(arg, "--debug")
            && strcmp(arg, "--ports")
            && strcmp(arg, "--ip")
            && strcmp(arg, "--speedup")
            && strcmp(arg, "--file")
            && strcmp(arg, "--show-all")
            && strcmp(arg, "--output")
            && strcmp(arg, "--source-port")
            && strcmp(arg, "--shuffle-ports")
            && strcmp(arg, "--badsum")
            && strcmp(arg, "--scan"))
            {
                fprintf(stderr, "%s is not a valid parameter. check man for more details.\n", arg);
                return false;
            }
    
    return true;
}

static bool process_arg_parsing(char **av, int32_t ac, t_global_data *data, bool *ip_is_set)
{
    for (int32_t i = 0; i < ac; i += 2) {

        if (!is_valid_arg(av[i]))
            return false;

        if ((!strcmp(av[i], "--ports") && !parse_ports_from_arg(av[i + 1], &data->opts))
                || ((!strcmp(av[i], "--ip") && !parse_ip_from_arg(av[i + 1], data, ip_is_set)))
                || ((!strcmp(av[i], "--speedup") && !parse_speedup_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--scan") && !parse_scan_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--source-port") && !parse_source_port_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--show-all") && !parse_show_all_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--badsum") && !parse_badsum_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--output") && !parse_output_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--shuffle-ports") && !parse_shuffle_ports_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--file") && !parse_file_from_arg(av[i + 1], &data->opts, ip_is_set)))
                || ((!strcmp(av[i], "--debug") && !parse_debug_from_arg(av[i + 1], &data->opts))))
            return false; 
    }

    return true;
}

bool parse_arg(int32_t ac, char **av, t_global_data *data)
{
    set_default_opts_val(&data->opts);

    if (!strcmp(av[0], "--help")) {
        print_man();
        exit(EXIT_SUCCESS);
    }

    if (is_odd(ac)) {
        fprintf(stderr, "each parameter (ex: --ports) needs a value.\n");
        return false;
    }

    bool ip_is_set = false;
    if (!process_arg_parsing(av, ac, data, &ip_is_set)) {
        if (ip_is_set)
            free_str_arr(data->opts.addr_in);
        return false;
    }

    if (!ip_is_set) {
        fprintf(stderr, "you need to specify an ip.\n");
        return false;
    }
    
    if (data->opts.shuffle_ports)
        shuffle_ports(data->opts.ports, data->opts.n_ports);

    if (data->opts.debug_mode)
        print_options(&data->opts);

    return true;
}
