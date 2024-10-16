#include "inc.h"

static char *state_to_str(u8 state)
{
    if (state == PORT_STATE_CLOSED)
        return "closed";
    else if (state == PORT_STATE_FILTERED)
        return "filtered";
    else if (state == PORT_STATE_OPEN)
        return "open";
    else if (state == PORT_STATE_OPEN_FILTERED)
        return "open|filtered";
    else if (state == PORT_STATE_CLOSED_FILTERED)
        return "closed|filtered";
    else
        return NULL;
}

void print_scan_line(t_global_data *data, u16 port, u32 scan_type, u8 port_state)
{
    printf("%d\n", port_state);
    char *state_str = state_to_str(port_state);
    printf("%s\n", state_str);
    char *scan_type_str = scan_type & SCAN_TYPE_UDP 
        ? "udp"
        : "tcp";
    t_services_node *node = search_node(data->services, port, scan_type_str);

    char port_proto[11];
    snprintf(port_proto, sizeof(port_proto), "%d/%s", port, scan_type_str);

    fprintf(stdout, "%-10s %-15s  %s\n",
        port_proto,
        state_str,
        node ? node->service : "unknown"
    );
}
