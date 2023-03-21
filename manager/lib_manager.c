#include "lib_manager.h"

#include <stdio.h>

#include "../list/list.h"

void printmenu() {
    printf("1.\"menu\"- Print menu\n");
    printf("2.\"root id\"- Create new root\n");
    printf("3.\"node id parent\"- Create new node\n");
    printf("4.\"list\"- Print List\n");
    printf("5.\"exec id name value\" - map command\n");
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

int find_root(struct node** roots, int root_count, int parent_id) {
    int root_number = -1;
    for (int i = 0; i < root_count; ++i) {
        if (find_element(roots[i], parent_id) != NULL) {
            root_number = i;
            break;
        }
    }

    return root_number;
}