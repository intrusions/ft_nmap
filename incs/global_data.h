#ifndef __GLOBAL_DATA_H__
# define __GLOBAL_DATA_H__

#include "options.h"
#include "tree_node.h"
#include <pcap.h>
#include <stdio.h>
#include <string.h>

typedef struct timespec timespec;

typedef struct {
    char src_ip[INET_ADDRSTRLEN];
    t_options opts;
    t_services_node *services;
} t_global_data;


/*
 * Prints the Nmap scan configurations and options.
 * @param data Pointer to the global `t_global_data` structure containing the scan options.
 */
void print_nmap_infos(t_global_data *data);

/*
 *  Prints a summary of the Nmap scan results.
 * @param start_time   The timestamp representing when the scan started.
 * @param end_time     The timestamp representing when the scan ended.
 * @param output       Pointer to the output `FILE` where the summary will be printed (e.g., stdout or a file).
 */
void print_nmap_resume(timespec start_time, timespec end_time, FILE *output);

#endif /* GLOBAL_DATA_H */
