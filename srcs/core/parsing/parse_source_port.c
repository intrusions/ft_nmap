#include "inc.h"

static bool is_valid_source_port(char *source_port_str, u16 *source_port_val)
{
    if  (!str_is_digit(source_port_str)) {
        fprintf(stderr, "source port must only contain digits.\n");
        return false;
    }

    i64 val = atoll(source_port_str);
    if (val > MAX_PORT_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_PORT_VALUE);
        return false;
    }

    *source_port_val = (u16)val;
    return true;
}

bool parse_source_port_from_arg(char *source_port, t_options *opts)
{
    u16 source_port_val;

    if (!is_valid_source_port(source_port, &source_port_val))
        return false;
    
    opts->source_port = source_port_val;
    return true;
}
