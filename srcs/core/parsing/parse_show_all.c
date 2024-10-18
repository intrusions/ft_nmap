#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool parse_show_all_from_arg(char *show_all, t_options *opts)
{
    if (!strcmp(show_all, "true")) {
        opts->show_all = true;
        return true;
    } else if (!strcmp(show_all, "false")) {
        opts->show_all = false;
        return true;
    }
 
    fprintf(stderr, "%s value is not valid, check man for more details.\n", show_all);
    return false;
}
