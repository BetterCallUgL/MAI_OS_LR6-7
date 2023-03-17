#ifndef LIB_MANAGER
#define LIB_MANAGE

#include "list.h"

void printmenu();
void input1(int* parent_id, int* new_id);
struct node* node_exists(struct node** roots, int root_count, int element_id);
#endif