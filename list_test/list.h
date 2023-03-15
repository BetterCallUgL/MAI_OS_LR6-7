#ifndef LIST_H
#define LIST_H

struct node {
    int id;
    int available;
    struct node* next;
};

void init(struct node** root, int id);
struct node* add_element(struct node* root,int id);
struct node* find_element(struct node* root, int id);
struct node* delete_elem(struct node* root, int id);
void print_list(struct node* root);
#endif