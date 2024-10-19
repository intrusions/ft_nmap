#ifndef __TREE_NODE_H__
# define __TREE_NODE_H__

#include <stdint.h>

#define MAX_SIZE_SERVICE_NAME   20
#define MAX_SIZE_PROTO_NAME     10

struct s_services_node {
    char service[MAX_SIZE_SERVICE_NAME];
    char protocol[MAX_SIZE_PROTO_NAME];
    uint16_t port;
    struct s_services_node *left;
    struct s_services_node *right;
};

typedef struct s_services_node t_services_node;

#endif  /* __TREE_NODE_H__ */
