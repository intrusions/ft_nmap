#include "get_next_line.h"
#include "global_data.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

bool open_fd(char *file, int32_t *fd)
{
    *fd = open(file, O_RDONLY);
    if (*fd == -1) {
        __log_error("open error");
        return false;
    }
    return true;
}
