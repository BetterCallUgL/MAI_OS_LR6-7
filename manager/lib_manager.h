#ifndef LIB_MANAGER
#define LIB_MANAGE

#include "../list/list.h"

void printmenu();
struct node* node_exists(struct node** roots, int root_count, int element_id);
int find_root(struct node** roots, int root_count, int parent_id);
#endif