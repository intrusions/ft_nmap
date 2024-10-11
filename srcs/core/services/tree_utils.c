#include "inc.h"

static t_services_node *create_node(u16 port, char *service, char *protocol)
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

    return node;
}

t_services_node *create_node_from_line(char *line)
{
    char **line_splitted = split(line, "/	");
    if (!line_splitted)
        return NULL;
    
    u16 port = atoi(line_splitted[1]);
    char *service = line_splitted[0];
    char *protocol = line_splitted[2];

    t_services_node *node = create_node(port, service, protocol);

    free_str_arr(line_splitted);
    return node;
}

t_services_node *search_node(t_services_node *root, u16 port, char *protocol)
{
    if (!root)
        return NULL;

    if ((root->port == port) && (!strcmp(root->protocol, protocol)))
        return root;

    if (port < root->port)
        return search_node(root->left, port, protocol);

    if (port == root->port) {
        
        if (strcmp(protocol, root->protocol) < 0)
            return search_node(root->left, port, protocol);
        else
            return search_node(root->right, port, protocol);
    }

    return search_node(root->right, port, protocol);
}

void free_services_tree(t_services_node *node)
{
    if (!node)
        return ;

    free_services_tree(node->left);
    free_services_tree(node->right);

    free(node);
}
