#include "lib_manager.h"

#include <stdio.h>

void printmenu() { printf("1.create new id\n"); }

void input1(int *parent_id, int *new_id) {
    printf("enter parent id: ");
    scanf("%d", parent_id);
    if (*parent_id != -1) {
        printf("enter new node id: ");
        scanf("%d", new_id);
    }
}