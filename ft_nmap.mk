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
    -lpcap                          \
    -Wno-deprecated-declarations    \

CFLAGS_DBG :=                       \
    -g3                             \
    -O0                             \
    -fsanitize=address              \
    -fsanitize=undefined            \
    -fno-omit-frame-pointer         \
    -fstack-protector-strong        \
    -fno-optimize-sibling-calls 

SRCS :=                                  \
    core/print/print_man.c               \
    core/print/print_nmap_infos.c        \
    core/print/print_nmap_resume.c       \
    core/print/print_scan_line.c         \
    core/print/print_scan_ip_header.c    \
    core/print/print_utils.c             \
    core/parsing/parse_arg.c             \
    core/parsing/parse_ports.c           \
    core/parsing/parse_ip.c              \
    core/parsing/parse_file.c            \
    core/parsing/parse_source_port.c     \
    core/parsing/parse_speedup.c         \
    core/parsing/parse_scan.c            \
    core/parsing/parse_debug.c           \
    core/parsing/parse_show_all.c        \
    core/parsing/parse_shuffle_ports.c   \
    core/parsing/parse_badsum.c          \
    core/parsing/parse_output.c          \
    core/parsing/set_default_opts.c      \
    core/services/create_services_tree.c \
    core/services/tree_utils.c           \
    core/scans/process_nmap_scans.c      \
    core/scans/pcap_initialization.c     \
    core/scans/initialize_thread_args.c   \
    core/scans/send_packet.c             \
    core/scans/recv_packet.c             \
    core/scans/set_pcap_filter.c         \
    core/network/reverse_dns.c           \
    core/network/get_src_ip.c            \
    core/socket/open_sockfd.c            \
    core/utils/ft_split.c                \
    core/utils/str_is_digit.c            \
    core/utils/free_str_arr.c            \
    core/utils/is_odd.c                  \
    core/utils/is_sudo_mode.c            \
    core/utils/checksum.c                \
    core/utils/cleanup_resources.c       \
    core/utils/open_fd.c                 \
    core/utils/count_line_in_file.c      \
    core/utils/shuffle_ports.c           \
    core/utils/random_usleep.c           \
    lib/ngnl/get_next_line.c             \
    lib/ngnl/get_next_line_utils.c       \
    debug/print_options.c                \
    debug/print_services_tree.c