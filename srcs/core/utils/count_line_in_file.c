#include "get_next_line.h"
#include "utils.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

bool count_line_in_file(char *file, int16_t *file_line_count)
{
    int32_t fd;
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
