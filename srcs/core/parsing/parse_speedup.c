#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "utils.h"

static bool is_valid_speedup(char *speedup_str, uint8_t *speed_val)
{
    if  (!str_is_digit(speedup_str)) {
        fprintf(stderr, "speedup must only contain digits.\n");
        return false;
    }

    int64_t val = atoll(speedup_str);
    if (val > MAX_SPEEDUP_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_SPEEDUP_VALUE);
        return false;
    }

    *speed_val = (uint8_t)val;
    return true;
}

bool parse_speedup_from_arg(char *speedup, t_options *opts)
{
    uint8_t speedup_val;

    if (!is_valid_speedup(speedup, &speedup_val))
        return false;
    
    opts->speedup = speedup_val;
    return true;
}
