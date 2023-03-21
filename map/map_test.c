#include "map.h"

#include <stdio.h>
#include <stdlib.h>

void menu_print();

int main() {
    menu_print();
    int input = 0;
    struct item* dict;
    int size = 0;
    while (input != 3) {
        scanf("%d", &input);
        switch (input) {
            case 1: {
                char key[40];
                printf("enter key:\n");
                scanf("%s", key);
                int value;
                printf("enter value:\n");
                scanf("%d", &value);
                add_value(&dict, &size, key, value);
                break;
            }

            case 2: {
                char key[40];
                printf("enter key:\n");
                scanf("%s", key);
                int index = find_value(dict, size, key);
                if (index == -1) {
                    printf("not found\n");
                } else {
                    printf("ok: %d\n", dict[index].value);
                }
                break;
            }
        }
    }

    if (size > 0) {
        free(dict);
    }
}

void menu_print() {
    printf("1. Add value\n");
    printf("2. Check if key exists\n");
    printf("3. Leave\n");
}