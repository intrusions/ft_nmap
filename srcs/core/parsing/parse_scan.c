#include "inc.h"

static u32 what_type_scan(char *scan_str)
{
    if (!strcmp(scan_str, "SYN")) {
        return SCAN_TYPE_SYN;
    } else if (!strcmp(scan_str, "NULL")) {
        return SCAN_TYPE_NULL;
    } else if (!strcmp(scan_str, "ACK")) {
        return SCAN_TYPE_ACK;
    } else if (!strcmp(scan_str, "FIN")) {
        return SCAN_TYPE_FIN;
    } else if (!strcmp(scan_str, "XMAS")) {
        return SCAN_TYPE_XMAS;
    } else if (!strcmp(scan_str, "UDP")) {
        return SCAN_TYPE_UDP;
    } else {
        return SCAN_TYPE_UNKNOW;
    }
}

static bool process_scan_string(char *scan_str, t_options *opts)
{
    u32 scan_type_bit = what_type_scan(scan_str);
    
    if (scan_type_bit == SCAN_TYPE_UNKNOW) {
        fprintf(stderr, "%s scan is not valid.\n", scan_str);
        return false;
    }

    opts->scan_type |= scan_type_bit;
    return true;
}

bool parse_scan_from_arg(char *scan, t_options *opts)
{
    char **comma_splitted = split(scan, ",");
    if (!comma_splitted)
        return false;
    
    for (u8 i = 0; comma_splitted[i]; i++) {
        if (!process_scan_string(comma_splitted[i], opts))
            return false;
    }

    return true;
}