#ifndef LIB_MANAGER
#define LIB_MANAGE

#include "../list/list.h"

struct arguments {
    void** pushers;
    void* puller;
    int root_count;
    struct node** roots;
    int delay;
};

void* hearbit(void* args);
void printmenu();
struct node* node_exists(struct node** roots, int root_count, int element_id);
int find_root(struct node** roots, int root_count, int parent_id);
#endif