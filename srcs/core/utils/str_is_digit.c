#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

bool str_is_digit(char *str)
{
    for (uint8_t i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}