#include "global_data.h"
#include <stdlib.h>
#include <string.h>

bool parse_ip_from_arg(char *ip, t_global_data *data, bool *ip_is_set)
{
    if (*ip_is_set) {
        fprintf(stderr, "you can't use `--ip` and `--file` at the same time.\n");
        return false;
    }
    
    data->opts.addr_in = malloc(2 * sizeof(char *));
    if (!data->opts.addr_in)
        return false;
    
    data->opts.addr_in[0] = strdup(ip);
    if (!data->opts.addr_in[0])
        return false;

    data->opts.addr_in[1] = NULL;
    *ip_is_set = true;
    return true;
}
