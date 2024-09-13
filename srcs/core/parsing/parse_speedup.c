#include "inc.h"

static bool is_valid_speedup(char *speedup_str, u8 *speed_val)
{
    if  (!str_is_digit(speedup_str)) {
        fprintf(stderr, "speedup must only contain digits.\n");
        return false;
    }

    i64 val = atoll(speedup_str);
    if (val > MAX_SPEEDUP_VALUE) {
        fprintf(stderr, "%ld is not a valid value. max value is %d.\n", val, MAX_SPEEDUP_VALUE);
        return false;
    }

    *speed_val = (u8)val;
    return true;
}

bool parse_speedup_from_arg(char *speedup, t_options *opts)
{
    u8 speedup_val;

    if (!is_valid_speedup(speedup, &speedup_val))
        return false;
    
    opts->speedup = speedup_val;
    return true;
}
