#include "inc.h"

bool parse_badsum_from_arg(char *badsum, t_options *opts)
{
    if (!strcmp(badsum, "true")) {
        opts->badsum = true;
        return true;
    } else if (!strcmp(badsum, "false")) {
        opts->badsum = false;
        return true;
    }
 
    fprintf(stderr, "%s value is not valid, check man for more details.\n", badsum);
    return false;
}
