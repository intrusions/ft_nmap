#include "inc.h"

void free_str_arr(char **arr)
{
    for (u16 i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
