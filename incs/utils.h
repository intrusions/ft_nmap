#ifndef __UTILS_H__
# define __UTILS_H__

#include "options.h"
#include "global_data.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


/*
* Sleep for a random interval between 1000 and 2000 microseconds.
*/
void tcp_random_usleep(void);

/*
* Sleep for a random interval between 750000 and 1500000 microseconds.
*/
void udp_random_usleep(void);


/*
* Randomize the order of ports in the provided array.
* @param array: pointer to the array of ports.
* @param n: number of elements in the array.
*/
void shuffle_ports(uint16_t *array, uint16_t n);

/*
* Open a file descriptor for the specified file.
* @param file: path to the file.
* @param fd: pointer to the file descriptor to be initialized.
* @return true if the file was opened successfully, false otherwise.
*/
bool open_fd(char *file, int32_t *fd);

/*
* Count the number of lines in the specified file.
* @param file: path to the file.
* @param file_line_count: pointer to store the number of lines.
* @return true if the file was read successfully, false otherwise.
*/
bool count_line_in_file(char *file, int16_t *file_line_count);

/*
* Check if the *
 provided string represents a digit.
* @param str: string to check.
* @return true if the string contains only digits, false otherwise.
*/
bool str_is_digit(char *str);

/*
* Print a dashed line to the specified output.
* @param output: the file or stream where the dashed line should be printed.
*/
void print_dash_line(FILE *output);

/*
* Display the manual/help page for the program.
*/
void print_man(void);

/*
* Free an array of strings.
* @param arr: pointer to the array of strings to free.
*/
void free_str_arr(char **arr);

/*
* Print the selected options for the scan.
* @param opts: pointer to the structure containing the options to print.
*/
void print_options(t_options *opts);

/*
* Check if a number is odd.
* @param n: the number to check.
* @return true if the number is odd, false if it's even.
*/
bool is_odd(int32_t n);

/*
* Split a string into an array of strings based on the specified delimiters.
* @param str: the string to split.
* @param charset: the set of delimiter characters.
* @return a dynamically allocated array of strings. Each string represents a part of the original string.
*         Remember to free the array using free_str_arr() once you're done.
*/
char **split(char *str, char *charset);

/*
* Clean up allocated resources and close sockets.
* @param data: pointer to the global data structure to clean up.
* @param tcp_sockfd: the TCP socket file descriptor to close.
* @param udp_sockfd: the UDP socket file descriptor to close.
*/
void cleanup_resources(t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd);

/*
* Print the header information for scanning a specific IP address.
* @param data: pointer to the global data structure.
* @param addr_index: the index of the address in the list to be scanned.
*/
void print_scan_ip_header(t_global_data *data, uint8_t addr_index);

/*
* Check if the program is running in sudo mode (with root privileges).
* @return true if the program is running with sudo, false otherwise.
*/
bool is_sudo_mode(void);

#endif /* UTILS_H */
