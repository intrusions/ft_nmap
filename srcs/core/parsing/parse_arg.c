#include "inc.h"

static bool process_arg_parsing(char **av, i32 ac, t_global_data *data)
{
    for (i32 i = 0; i < ac; i++) {

        if (!strcmp(av[i], "--ports") && !parse_ports_from_arg(av[i + 1], &data->opts))
            return false;
        else if (!strcmp(av[i], "--ip") && !parse_ip_from_arg(av[i + 1], data))
            return false;
        else if (!strcmp(av[i], "--speedup") && !parse_speedup_from_arg(av[i + 1], &data->opts))
            return false;
        else if (!strcmp(av[i], "--scan") && !parse_scan_from_arg(av[i + 1], &data->opts))
            return false;
    }

    return true;
}

bool parse_arg(i32 ac, char **av, t_global_data *data)
{
    if (!strcmp(av[0], "--help")) {
        print_man();
        exit(EXIT_SUCCESS);
    } else if (!strcmp(av[0], "--debug"))
        data->opts.debug_mode = true;

    if (is_odd(ac) && strcmp(av[0], "--debug")) {
        fprintf(stderr, "each parameters (ex: --ports) need a value.\n");
        return false;
    }

    if (!process_arg_parsing(av, ac, data))
        return false;

    if (!data->opts.addr_in) {
        fprintf(stderr, "you need to specify an ip.\n");
        return false;
    } 

    return true;
}
