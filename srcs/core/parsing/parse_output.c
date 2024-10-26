#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool open_file(char *file, FILE **stream)
{
    char *mode = "a";

    *stream = fopen(file, mode);
    if (!*stream) {
        perror("fopen error");
        return false;
    }

    return true;
}

bool parse_output_from_arg(char *file, t_options *opts)
{
    FILE *stream;
    if (!open_file(file, &stream))
        return false;

    opts->output = stream;
    return true;
}
