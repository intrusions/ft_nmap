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

SRCS :=                                \
    core/print/print_man.c             \
    core/print/print_nmap_infos.c      \
    core/print/print_utils.c           \
    core/parsing/parse_arg.c           \
    core/parsing/parse_ports.c         \
    core/parsing/parse_ip.c            \
    core/parsing/parse_file.c          \
    core/parsing/parse_speedup.c       \
    core/parsing/parse_scan.c          \
    core/parsing/parse_debug.c         \
    core/parsing/set_default_opts.c    \
    core/scans/process_nmap_scans.c    \
    core/scans/send_packet.c           \
    core/network/reverse_dns.c         \
    core/socket/open_sockfd.c          \
    core/utils/ft_split.c              \
    core/utils/str_is_digit.c          \
    core/utils/free_str_arr.c          \
    core/utils/is_odd.c                \
    core/utils/checksum.c              \
    core/utils/clean_all.c             \
    lib/ngnl/get_next_line.c           \
    lib/ngnl/get_next_line_utils.c     \
    debug/print_options.c