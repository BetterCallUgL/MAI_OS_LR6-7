#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void init(struct node** root, int id) {
    struct node* tmp = malloc(sizeof(struct node));
    tmp->id = id;
    tmp->next = NULL;
    *root = tmp;
}

struct node* add_element(struct node* lst, int id) {
    struct node* tmp = malloc(sizeof(struct node));
    tmp->next = lst->next;
    lst->next = tmp;
    tmp->id = id;

    return tmp;
}

struct node* find_element(struct node* root, int id) {
    struct node* tmp = root;
    while (tmp != NULL && tmp->id != id) {
        tmp = tmp->next;
    }

    return tmp;
}


struct node* delete_elem(struct node* lst, int id) {
    struct node* tmp = lst;
    id = id;
    while (tmp->next->id != id) {
        tmp = tmp->next;
    }
    struct node* delete = tmp->next;
    tmp->next = delete->next;
    free(delete);

    return tmp;
}

void print_list(struct node* root) {
    while (root != NULL) {
        printf("%d ", root->id);
        root = root->next;
    }
    printf("\n");
}

void destroy_list(struct node* root) {
    while (root != NULL) {
        struct node* tmp = root;
        root = root->next;
        free(tmp);
        tmp = NULL;
    }
}