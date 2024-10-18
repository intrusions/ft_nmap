#include <stdint.h>
#include <stdlib.h>
#include "options.h"
#include "utils.h"

static bool is_valid_source_port(char *source_port_str, uint16_t *source_port_val)
{
    if  (!str_is_digit(source_port_str)) {
        fprintf(stderr, "source port must only contain digits.\n");
        return false;
    }

    int64_t val = atoll(source_port_str);
    if (val > MAX_PORT_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_PORT_VALUE);
        return false;
    }

    *source_port_val = (uint16_t)val;
    return true;
}

bool parse_source_port_from_arg(char *source_port, t_options *opts)
{
    uint16_t source_port_val;

    if (!is_valid_source_port(source_port, &source_port_val))
        return false;
    
    opts->source_port = source_port_val;
    return true;
}
