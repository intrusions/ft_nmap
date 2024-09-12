#ifndef __INC_H__
# define __INC_H__

// ========================================================================= //
//                                   Header                                  //
// ========================================================================= //

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

#define SIZE_PORTS_ARRAY    1024
#define MAX_PORT_VALUE      65535


// ========================================================================= //
//                                   Macro                                   //
// ========================================================================= //



// ========================================================================= //
//                                  Typedef                                  //
// ========================================================================= //

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


// ========================================================================= //
//                                  Structure                                //
// ========================================================================= //

typedef struct {
    char    addr[INET6_ADDRSTRLEN];
    char    *file;
    u8      speedup;
    u16     ports[SIZE_PORTS_ARRAY];
    u16     n_ports;
} t_options;

typedef struct {
    t_options opts;

} t_global_data;

// ========================================================================= //
//                                  Prototype                                //
// ========================================================================= //

/*
* print manual of the program.
*/
void print_man(void);


/*
* main function about arguments parsing.
*/
bool parse_arg(i32 ac, char **av, t_options *opts);


/*
* dedicated function about ports argument parsing.
*/
bool parse_ports_from_arg(char *arg, t_options *opts);


/*
* [DEBUG]
* print t_options structure value.
*/
void print_options(t_options *opts);


/*
* some utils.
*/
char **split(char *str, char *charset);
void free_split(char **arr);
bool str_is_digit(char *str);
bool is_odd(i32 n);


#endif /* __INC_H__ */