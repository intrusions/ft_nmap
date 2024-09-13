#include "inc.h"

static bool is_valid_arg(char *arg)
{
    if (strcmp(arg, "--debug")
            && strcmp(arg, "--ports")
            && strcmp(arg, "--ip")
            && strcmp(arg, "--speedup")
            && strcmp(arg, "--scan"))
            {
                fprintf(stderr, "%s is not a valid parameter. check man for more details.\n", arg);
                return false;
            }
    
    return true;
}

static bool process_arg_parsing(char **av, i32 ac, t_global_data *data)
{
    for (i32 i = 0; i < ac; i += 2) {

        if (!is_valid_arg(av[i]))
            return false;

        if ((!strcmp(av[i], "--ports") && !parse_ports_from_arg(av[i + 1], &data->opts))
                || ((!strcmp(av[i], "--ip") && !parse_ip_from_arg(av[i + 1], data)))
                || ((!strcmp(av[i], "--speedup") && !parse_speedup_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--scan") && !parse_scan_from_arg(av[i + 1], &data->opts)))
                || ((!strcmp(av[i], "--debug") && !parse_debug_from_arg(av[i + 1], &data->opts))))
            return false; 
    }

    return true;
}

bool parse_arg(i32 ac, char **av, t_global_data *data)
{
    if (!strcmp(av[0], "--help")) {
        print_man();
        exit(EXIT_SUCCESS);
    }

    if (is_odd(ac)) {
        fprintf(stderr, "each parameters (ex: --ports) need a value.\n");
        return false;
    }

    if (!process_arg_parsing(av, ac, data))
        return false;

    if (!data->opts.addr_in) {
        fprintf(stderr, "you need to specify an ip.\n");
        return false;
    }

    if (data->opts.debug_mode)
        print_options(&data->opts);

    return true;
}
