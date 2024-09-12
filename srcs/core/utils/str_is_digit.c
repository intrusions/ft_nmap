#include "inc.h"

bool str_is_digit(char *str)
{
    for (u8 i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}