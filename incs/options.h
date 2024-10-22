#ifndef __OPTIONS_H__
# define __OPTIONS_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_PORT_VALUE      65535
#define MAX_SPEEDUP_VALUE   250
#define MIN_SPEEDUP_VALUE   1
#define DEFAULT_SOURCE_PORT 1337

#define SIZE_PORTS_ARRAY    1024

typedef struct options {
    char **addr_in;
    char **addr;
    char *file;
    uint8_t speedup;
    uint16_t ports[SIZE_PORTS_ARRAY];
    uint16_t n_ports;
    uint32_t scan_type;
    bool debug_mode;
    bool badsum;
    bool show_all;
    bool shuffle_ports;
    uint16_t source_port;
    FILE *output;
} t_options;

#endif /* OPTIONS_H */
