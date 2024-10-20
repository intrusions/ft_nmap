#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool is_valid_port(char *port_str, uint16_t *port_val)
{
    if  (!str_is_digit(port_str)) {
        fprintf(stderr, "ports must only contain digits.\n");
        return false;
    }

    int64_t val = atoll(port_str);
    if (val > MAX_PORT_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_PORT_VALUE);
        return false;
    }

    *port_val = (uint16_t)val;
    return true;
}

static bool add_port(uint16_t *ports, uint16_t *port_index, uint16_t port_value)
{
    if (*port_index >= SIZE_PORTS_ARRAY) {
        fprintf(stderr, "Number of ports cannot exceed %d.\n", SIZE_PORTS_ARRAY);
        return false;
    }

    ports[(*port_index)++] = port_value;
    return true;
}

static bool validate_and_parse_port(char *port, uint16_t *ports, uint16_t *port_index)
{
    uint16_t val;
    if (!is_valid_port(port, &val)
            || !add_port(ports, port_index, val))
        return false;
    
    return true;
}

static bool validate_and_parse_port_range(char **port_range, uint16_t *ports, uint16_t *port_index)
{
    uint16_t min_val;
    uint16_t max_val;
    if (!is_valid_port(port_range[0], &min_val)
            || !is_valid_port(port_range[1], &max_val))
        return false;

    for (int64_t val = min_val; val <= max_val; val++) {
        if (!add_port(ports, port_index, val))
            return false;
    }

    return true;
}

static bool process_port_string(char *port_string, uint16_t *ports, uint16_t *port_index)
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

    free_str_arr(dash_splitted);
    return true;

error:
    free_str_arr(dash_splitted);
    return false;
}

bool parse_ports_from_arg(char *arg, t_options *opts)
{
    char **comma_splitted = split(arg, ",");
    if (!comma_splitted)
        return false;
    
    opts->n_ports = 0;

    for (uint8_t i = 0; comma_splitted[i]; i++) {
        if (!process_port_string(comma_splitted[i], opts->ports, &opts->n_ports)) {
            free_str_arr(comma_splitted);
            return false;
        }
    }

    free_str_arr(comma_splitted);
    return true;
}
