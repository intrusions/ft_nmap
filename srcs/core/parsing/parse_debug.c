#include "inc.h"

bool parse_debug_from_arg(char *debug, t_options *opts)
{
    if (!strcmp(debug, "true")) {
        opts->debug_mode = true;
        return true;
    } else if (!strcmp(debug, "false")) {
        opts->debug_mode = false;
        return true;
    }
 
    fprintf(stderr, "%s value is not valid, check man for more details.\n", debug);
    return false;
}
