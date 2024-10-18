#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool parse_shuffle_ports_from_arg(char *shuffle_ports, t_options *opts)
{
    if (!strcmp(shuffle_ports, "true")) {
        opts->shuffle_ports = true;
        return true;
    } else if (!strcmp(shuffle_ports, "false")) {
        opts->shuffle_ports = false;
        return true;
    }
 
    fprintf(stderr, "%s value is not valid, check man for more details.\n", shuffle_ports);
    return false;
}
