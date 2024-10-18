#include <stdlib.h>
#include <stdint.h>

void free_str_arr(char **arr)
{
    for (uint16_t i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
