#include "lib_manager.h"

#include <stdio.h>

#include "list.h"

void printmenu() {
    printf("1.Create new root\n");
    printf("2.Create new node\n");
}

struct node* node_exists(struct node** roots, int root_count, int element_id) {
    struct node* list_node;
    for (int i = 0; i < root_count; ++i) {
        list_node = find_element(roots[i], element_id);
        if (list_node != NULL) {
            break;
        }
    }

    return list_node;
}