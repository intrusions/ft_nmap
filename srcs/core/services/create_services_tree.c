#include "global_data.h"
#include "services.h"
#include "get_next_line.h"
#include "utils.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

static bool create_arr_from_services_file(char ***services_arr, int16_t *file_line_count)
{
    if (!count_line_in_file(SERVICES_FILE_PATH, file_line_count))
        return false;

    *services_arr = malloc((*file_line_count + 1) * sizeof(char *));
    if (!*services_arr)
        return false;

    int32_t fd;
    if (!open_fd(SERVICES_FILE_PATH, &fd))
        return false;

    int16_t index = 0;
    while (((*services_arr)[index] = get_next_line(fd)))
        index++;
    (*services_arr)[index] = NULL;

    close(fd);
    return true;
}

static t_services_node *create_tree_from_services_arr(char **services_arr, int16_t start, int16_t end)
{
    if (start > end)
        return NULL;

    int16_t mid = (start + end) / 2;

    while (services_arr[mid][0] == '#' && mid < end)
        mid++;

    if (mid > end || services_arr[mid][0] == '#')
        return NULL;

    t_services_node *node = create_node_from_line(services_arr[mid]);
    if (!node)
        return NULL;

    node->left = create_tree_from_services_arr(services_arr, start, mid - 1);
    node->right = create_tree_from_services_arr(services_arr, mid + 1, end);

    return node;
}


bool create_services_tree(t_global_data *data)
{
    char **services_arr = NULL;
    int16_t file_line_count = 0;

    if (!create_arr_from_services_file(&services_arr, &file_line_count))
        return false;

    if (!(data->services = create_tree_from_services_arr(services_arr, 0, file_line_count - 1)))
        return false;

    free_str_arr(services_arr);
    return true;
}
