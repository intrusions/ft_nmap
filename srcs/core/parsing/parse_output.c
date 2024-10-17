#include "inc.h"
#include "get_next_line.h"

bool open_file(char *file, FILE **flux)
{
    char *mode = "a";
    *flux = fopen(file, mode);

    if (!*flux) {
        perror("fopen error");
        return false;
    }

    return true;
}

bool parse_output_from_arg(char *file, t_options *opts)
{
    FILE *flux;
    if (!open_file(file, &flux))
        return false;

    opts->output = flux;
    return true;
}
