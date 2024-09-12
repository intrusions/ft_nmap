#include "inc.h"

int main(int ac, char **av)
{
    t_global_data g_data;
    ac--, av++;

    if (!ac) {
        print_man();
        return EXIT_FAILURE;
    }

    if (!parse_arg(ac, av, &g_data.opts)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
