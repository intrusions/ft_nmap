#include "inc.h"

void print_nmap_resume(timespec start_time, timespec end_time)
{
    double time_spent;
    time_spent = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    print_dash_line();
    fprintf(stdout, "Scan took %.5f secs\n", time_spent);
}
