NAME         := ft_nmap
CC           := gcc
SRCS_DIR     := srcs
OBJS_DIR     := .objs
INCS_DIR     := incs
MAIN         := srcs/main.c

CFLAGS :=                           \
    -Wall                           \
    -Wextra                         \
    -Werror                         \
    -pedantic                       \
    -lpthread                       \

CFLAGS_DBG :=                       \
    -g3                             \
    -O0                             \
    -fsanitize=address              \
    -fsanitize=undefined            \
    -fno-omit-frame-pointer         \
    -fstack-protector-strong        \
    -fno-optimize-sibling-calls 

SRCS :=                             \
    core/print/print_man.c          \
    core/parsing/parse_arg.c        \
    core/parsing/parse_ports.c      \
    core/utils/ft_split.c           \
    core/utils/str_is_digit.c       \
    core/utils/free_split.c         \
    core/utils/is_odd.c             \
    debug/print_options.c