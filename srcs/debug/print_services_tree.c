#include "services.h"
#include "stdio.h"
#include <stdint.h>

void print_services_tree(t_services_node *node, int32_t depth)
{
    if (!node)
        return ;

    print_services_tree(node->left, depth + 1);

    for (int32_t i = 0; i < depth; i++)
        printf(" ");
    printf("[%s] [%s] [%d]\n", node->service, node->protocol, node->port);

    print_services_tree(node->right, depth + 1);
}
