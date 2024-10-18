#ifndef __GLOBAL_DATA_H__
# define __GLOBAL_DATA_H__

#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include "options.h"
#include "tree_node.h"

#define __log_error(error) (void)fprintf(stderr, "%s: %s\n", error, strerror(errno))

typedef struct timespec timespec;

typedef struct global_data {
    char src_ip[INET_ADDRSTRLEN];
    pcap_t *handle;
    t_options opts;
    t_services_node *services;
} t_global_data;


void print_nmap_infos(t_global_data *data);

void print_nmap_resume(timespec start_time, timespec end_time, FILE *output);

#endif /* GLOBAL_DATA_H */
