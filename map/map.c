#include "map.h"

#include <stdlib.h>
#include <string.h>

int find_value(struct item* items, int size, char key[40]) {
    for (int i = 0; i < size; i++) {
        if (!strcmp(items[i].key, key)) {
            return i;
        }
    }
    return -1;
}

void add_value(struct item** items, int* size, char key[40], int value) {
    if (*size == 0) {
        *items = malloc(sizeof(struct item) * (++(*size)));
        strcpy((*(*items + (*size) - 1)).key, key);
        (*(*items + (*size) - 1)).value = value;
    } else {
        int index = find_value(*items, *size, key);
        if (index == -1) {
            (*size)++;
            *items = realloc(*items, (*size) * sizeof(struct item));
            strcpy((*(*items + (*size) - 1)).key, key);
            (*(*items + (*size) - 1)).value = value;
        } else {
            (*(*items + index)).value = value;
        }
    }
}