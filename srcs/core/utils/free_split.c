#include "inc.h"

void free_split(char **arr)
{
    for (u16 i = 0; arr[i]; i++) {
        free(arr[i]);
    }
    free(arr);
}
