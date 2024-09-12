#include "inc.h"

bool parse_arg(i32 ac, char **av, t_options *opts)
{
    if (!strcmp(av[0], "--help")) {
        print_man();
        exit(EXIT_SUCCESS);
    }

    if (is_odd(ac)) {
        fprintf(stderr, "each parameters (ex: --ports) need a value.\n");
        return false;
    }

    for (i32 i = 0; i < ac; i++) {

        if (!strcmp(av[i], "--ports") && !parse_ports_from_arg(av[i + 1], opts)) {
            return false;
        }
    }

    return true;
}
