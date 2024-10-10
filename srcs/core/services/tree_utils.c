#include "inc.h"

t_services_node *create_node(u16 port, char *service, char *protocol)
{
    t_services_node *node = malloc(sizeof(t_services_node));
    if (!node)
        return NULL;

    strncpy(node->service, service, MAX_SIZE_SERVICE_NAME - 1);
    node->service[sizeof(node->service) - 1] = 0;

    strncpy(node->protocol, protocol, MAX_SIZE_PROTO_NAME - 1);
    node->protocol[sizeof(node->protocol) - 1] = 0;  
    
    node->port = port;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

t_services_node *create_node_from_line(char *line)
{
    char **line_splitted = split(line, "/	");
    if (!line_splitted)
        return NULL;
    
    u16 port = atoi(line_splitted[1]);
    char *service = line_splitted[0];
    char *protocol = line_splitted[2];

    return (create_node(port, service, protocol));
}
