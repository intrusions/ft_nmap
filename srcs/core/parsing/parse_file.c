#include "inc.h"
#include "get_next_line.h"

static bool open_fd(char *file, i32 *fd)
{
    *fd = open(file, O_RDONLY);
    if (*fd == -1) {
        __log_error("open error");
        return false;
    }
    return true;
}

static bool count_line_in_file(char *file, i16 *file_line_count)
{
    i32 fd;
    if (!open_fd(file, &fd))
        return false;

    char *line = get_next_line(fd);
    if (!line) {
        close(fd);
        return false;
    }

    while (line) {
        (*file_line_count)++;
        free(line);

        line = get_next_line(fd);
    }

    close(fd);
    return true;
}

bool parse_file_from_arg(char *file, t_options *opts, bool *ip_is_set)
{
    if (*ip_is_set) {

        fprintf(stderr, "you can't use `--ip` and `--file` at the same time.\n");
        free_str_arr(opts->addr_in);
        return false;
    }

    i16 file_line_count = 0;
    if (!count_line_in_file(file, &file_line_count))
        return false;

    opts->addr_in = malloc((file_line_count + 1) * sizeof(char *));
    if (!opts->addr_in)
        return false;

    i32 fd;
    if (!open_fd(file, &fd))
        return false;

    i16 addr_in_index = 0;
    while ((opts->addr_in[addr_in_index] = get_next_line(fd)) != NULL) {
        addr_in_index++;
    }
    opts->addr_in[addr_in_index] = NULL;

    close(fd);
    *ip_is_set = true;
    return true;
}
