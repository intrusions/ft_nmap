#ifndef __PARSE_H__
# define __PARSE_H__

#include "options.h"
#include "global_data.h"


/*
* Parse the command-line arguments and store them in the global data structure.
* @param ac: argument count.
* @param av: array of arguments.
* @param data: pointer to the global data structure.
* @return true if arguments were parsed successfully, false otherwise.
*/
bool parse_arg(int32_t ac, char **av, t_global_data *data);

/*
* Parse the `--ports` argument, converting it to a valid ports list.
* @param arg: argument string for ports.
* @param opts: pointer to the options structure where parsed values will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_ports_from_arg(char *arg, t_options *opts);

/*
* Parse the `--ip` argument and store the IP address in the global data structure.
* @param ip: argument string representing the IP address.
* @param data: pointer to the global data structure, 
*   containing opts structure where the IP will be stored.
* @param ip_is_set: boolean flag to track if IPs have already been set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_ip_from_arg(char *ip, t_global_data *data, bool *ip_is_set);

/*
* Parse the `--file` argument, loading IPs or hosts from a specified file.
* @param file: file name or path to be parsed.
* @param opts: pointer to the options structure.
* @param ip_is_set: boolean flag to track if IPs have already been set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set);

/*
* Parse the `--speedup` argument, which define the number of threads for the scan.
* @param speedup: string representing the speedup level.
* @param opts: pointer to the options structure where the value will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_speedup_from_arg(char *speedup, t_options *opts);

/*
* Parse the `--scan` argument, specifying the types of scans to be performed (e.g., SYN, ACK).
* @param scan: string representing the scan types.
* @param opts: pointer to the options structure where scan types will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_scan_from_arg(char *scan, t_options *opts);

/*
* Parse the `--debug` argument to enable debugging mode.
* @param debug: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where debug mode will be toggled.
* @return true if parsing was successful, false otherwise.
*/
bool parse_debug_from_arg(char *debug, t_options *opts);

/*
* Parse the `--show-all` argument, toggling visibility of all scan results, including filtered ports.
* @param show_all: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_show_all_from_arg(char *show_all, t_options *opts);

/*
* Parse the `--shuffle-ports` argument to randomize the order of port scanning.
* @param shuffle_ports: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_shuffle_ports_from_arg(char *shuffle_ports, t_options *opts);

/*
* Parse the `--source-port` argument to specify a custom source port for the scan.
* @param source_port: string representing the source port.
* @param opts: pointer to the options structure where the source port will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_source_port_from_arg(char *source_port, t_options *opts);

/*
* Parse the `--badsum` argument to introduce packet checksum errors.
* @param badsum: string argument representing the flag (e.g. true, false).
* @param opts: pointer to the options structure where the flag will be set.
* @return true if parsing was successful, false otherwise.
*/
bool parse_badsum_from_arg(char *badsum, t_options *opts);

/*
* Parse the `--output` argument to specify an output file for scan results.
* @param file: string representing the output file path.
* @param opts: pointer to the options structure where the `FILE *` will be stored.
* @return true if parsing was successful, false otherwise.
*/
bool parse_output_from_arg(char *file, t_options *opts);

/*
* Set default values for the options structure `t_options`, such as scan types and ports.
* @param opts: pointer to the options structure where default values will be set.
*/
void set_default_opts_val(t_options *opts);

#endif  /* __PARSE_H__ */
