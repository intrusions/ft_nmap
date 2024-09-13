#include "inc.h"

static bool is_valid_port(char *port_str, u16 *port_val)
{
    if  (!str_is_digit(port_str)) {
        fprintf(stderr, "ports must only contain digits.\n");
        return false;
    }

    i64 val = atoll(port_str);
    if (val > MAX_PORT_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_PORT_VALUE);
        return false;
    }
    *port_val = (u16)val;

    return true;
}

static bool add_port(u16 *ports, u16 *port_index, u16 port_value)
{
    if (*port_index >= SIZE_PORTS_ARRAY) {
        fprintf(stderr, "Number of ports cannot exceed %d.\n", SIZE_PORTS_ARRAY);
        return false;
    }
    ports[(*port_index)++] = port_value;
    return true;
}

static bool validate_and_parse_port(char *port, u16 *ports, u16 *port_index)
{
    u16 val;
    if (!is_valid_port(port, &val)
            || !add_port(ports, port_index, val))
        return false;
    
    return true;
}

static bool validate_and_parse_port_range(char **port_range, u16 *ports, u16 *port_index)
{
    u16 min_val;
    u16 max_val;
    if (!is_valid_port(port_range[0], &min_val)
            || !is_valid_port(port_range[1], &max_val))
        return false;

    for (i64 val = min_val; val <= max_val; val++) {
        if (!add_port(ports, port_index, val))
            return false;
    }

    return true;
}

static bool process_port_string(char *port_string, u16 *ports, u16 *port_index)
{
    char **dash_splitted = split(port_string, "-");
    if (!dash_splitted)
        return false;
    
    if (!dash_splitted[1]) {
        if (!validate_and_parse_port(dash_splitted[0], ports, port_index))
            goto error;
    } else {
        if (!validate_and_parse_port_range(dash_splitted, ports, port_index))
            goto error;
    }

    free_split(dash_splitted);
    return true;

error:
    free_split(dash_splitted);
    return false;
}

bool parse_ports_from_arg(char *arg, t_options *opts)
{
    char **comma_splitted = split(arg, ",");
    if (!comma_splitted)
        return false;
    
    opts->n_ports = 0;

    for (u8 i = 0; comma_splitted[i]; i++) {
        if (!process_port_string(comma_splitted[i], opts->ports, &opts->n_ports)) {
            free_split(comma_splitted);
            return false;
        }
    }

    free_split(comma_splitted);
    return true;
}
