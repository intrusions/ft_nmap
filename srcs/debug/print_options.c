#include "inc.h"

void print_options(t_options *opts)
{
    printf("[DEBUG]:\n\n");
    printf("Ports: %d \n", opts->n_ports);

    for (u16 i = 0; i < opts->n_ports; i++) {
        printf("%d", opts->ports[i]);
        
        if (i != opts->n_ports - 1)
            printf(",");
    }
    printf("\n");
}
