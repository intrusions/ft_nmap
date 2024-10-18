#ifndef __SERVICES_H__
# define __SERVICES_H__

#include <stdint.h>
#include <stdbool.h>
#include "global_data.h"
#include "tree_node.h"


#define SERVICES_FILE_PATH  "./services/nmap-services"

/*
* Load the `nmap-services` file, building a binary tree of known services for port scanning.
* @param data: pointer to the global data structure where the tree will be stored.
* @return true if the services tree was created successfully, false otherwise.
*/
bool create_services_tree(t_global_data *data);

/*
* Create a binary tree node from a line in the services file.
* @param line: line from the services file.
* @return pointer to the newly created node.
*/
t_services_node *create_node_from_line(char *line);

/*
* Search for a node in the binary tree by port and protocol.
* @param root: pointer to the root of the binary tree.
* @param port: port number to search for.
* @param protocol: protocol (TCP or UDP) to search for.
* @return pointer to the found node, or NULL if not found.
*/
t_services_node *search_node(t_services_node *root, uint16_t port, char *protocol);

/*
* Free all nodes in the services binary tree.
* @param node: pointer to the root node of the binary tree.
*/
void free_services_tree(t_services_node *node);

#endif /* SERVICES_H */
