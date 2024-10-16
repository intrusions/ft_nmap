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

static char *scan_to_str(u8 scan)
{
    if (scan == SCAN_TYPE_SYN)
        return "SYN";
    else if (scan == SCAN_TYPE_FIN)
        return "FIN";
    else if (scan == SCAN_TYPE_ACK)
        return "ACK";
    else if (scan == SCAN_TYPE_NULL)
        return "NULL";
    else if (scan == SCAN_TYPE_XMAS)
        return "XMAS";
    else if (scan == SCAN_TYPE_UDP)
        return "UDP";
    else
        return NULL;
}

void print_scan_line(t_global_data *data, u16 port, u32 scan_type, u8 port_state)
{
    if (port_state != PORT_STATE_OPEN)
        return ;
    
    char *state_str = state_to_str(port_state);
    char *scan_type_str = scan_type & SCAN_TYPE_UDP 
        ? "udp"
        : "tcp";
    t_services_node *node = search_node(data->services, port, scan_type_str);

    char port_proto[11];
    snprintf(port_proto, sizeof(port_proto), "%d/%s", port, scan_type_str);

    fprintf(stdout, "%-10s %-15s  %-15s %s\n",
        port_proto,
        state_str,
        node ? node->service : "unknown",
        scan_to_str(scan_type)
    );
}
