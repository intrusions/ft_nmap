#include "inc.h"

void print_services_tree(t_services_node *node, int depth)
{
    if (!node)
        return ;

    print_services_tree(node->left, depth + 1);

    for (int i = 0; i < depth; i++)
        printf(" ");
    printf("[%s] [%s] [%d]\n", node->service, node->protocol, node->port);

    print_services_tree(node->right, depth + 1);
}
