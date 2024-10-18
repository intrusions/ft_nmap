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
void random_usleep(void);

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
* Check if the provided string represents a digit.
* @param str: string to check.
* @return true if the string contains only digits, false otherwise.
*/
bool str_is_digit(char *str);

void print_dash_line(FILE *output);
void print_man();
void free_str_arr(char **arr);
void print_options(t_options *opts);
bool is_odd(int32_t n);
char **split(char *str, char *charset);
void cleanup_resources(t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd);
void print_scan_ip_header(t_global_data *data, uint8_t addr_index);
bool is_sudo_mode();



#endif /* UTILS_H */
