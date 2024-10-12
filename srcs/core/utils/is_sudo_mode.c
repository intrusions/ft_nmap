#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

bool is_sudo_mode()
{
    if (getuid()) {
        fprintf(stderr, "program must be started in sudo mode.\n");
        return false;
    }
    return true;
}
