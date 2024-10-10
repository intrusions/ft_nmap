#include "inc.h"
#include "get_next_line.h"

bool count_line_in_file(char *file, i16 *file_line_count)
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