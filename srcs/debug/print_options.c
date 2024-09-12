#include "inc.h"

void print_options(t_options *opts)
{
    printf("[DEBUG]:\n\n");

    printf("Ports: %d \n    ", opts->n_ports);
    for (u16 i = 0; i < opts->n_ports; i++) {
        printf("%d", opts->ports[i]);
        
        if (i != opts->n_ports - 1)
            printf(",");
    }
    printf("\n\n");

    printf("Address:\n");
    printf("    - addr_in  : %s\n", opts->addr_in);
    printf("    - addr     : %s\n\n", opts->addr);

    printf("Speedup:\n");
    printf("    - value    : %d\n", opts->speedup);

    printf("Scan type:\n    - ");
    if (opts->scan_type & SCAN_TYPE_SYN)
        printf("SYN ");
    if (opts->scan_type & SCAN_TYPE_NULL)
        printf("NULL ");
    if (opts->scan_type & SCAN_TYPE_ACK)
        printf("ACK ");
    if (opts->scan_type & SCAN_TYPE_FIN)
        printf("FIN ");
    if (opts->scan_type & SCAN_TYPE_XMAS)
        printf("XMAS ");
    if (opts->scan_type & SCAN_TYPE_UDP)
        printf("UDP ");

    printf("\n\n");
    
}
