#include "inc.h"

bool parse_ip_from_arg(char *ip, t_global_data *data)
{
    data->opts.addr_in = ip;
    
    return true;
}
