#include <stdbool.h>
#include "get_next_line.h"
#include "options.h"
#include "utils.h"

bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set)
{
    if (*ip_is_set) {
        fprintf(stderr, "you can't use `--ip` and `--file` at the same time.\n");
        return false;
    }

    int16_t file_line_count = 0;
    if (!count_line_in_file(file, &file_line_count))
        return false;

    opts->addr_in = malloc((file_line_count + 1) * sizeof(char *));
    if (!opts->addr_in)
        return false;

    int32_t fd;
    if (!open_fd(file, &fd))
        return false;

    int16_t addr_in_index = 0;
    while ((opts->addr_in[addr_in_index] = get_next_line(fd)) != NULL) {
        addr_in_index++;
    }
    opts->addr_in[addr_in_index] = NULL;

    close(fd);
    *ip_is_set = true;
    return true;
}
