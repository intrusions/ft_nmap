#include "inc.h"
#include "get_next_line.h"

bool open_fd(char *file, i32 *fd)
{
    *fd = open(file, O_RDONLY);
    if (*fd == -1) {
        __log_error("open error");
        return false;
    }
    return true;
}
