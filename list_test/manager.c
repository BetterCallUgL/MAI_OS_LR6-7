#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib_manager.h"
#include "list.h"
#include "zmq.h"

int main() {
    struct node** roots = sizeof(struct node * root);
    int* flags = malloc(sizeof(int));
    int list_size = 1;
    int command = -1;
    printf("0.menu\n1.create new list\n2.add\n3.delete\n4.\n5.leave\n");
    while (command != 5) {
        switch (command) {
            scanf("%d", &command);

            case 0: {
                printf("0.menu\n1.add\n2.print\n3.add new list\n4.delete\n5.destroy list\n6.leave\n");
                break;
            }

            case 1: {
                int id, num;
                printf("enter number of roots");
                scanf("%d", num);
                printf("enter id\n");
                scanf("%d", &id);
                if (flags[num] == 0) {
                    init(roots[num], id);
                    flags[num] = 1;
                }
            }

            case 2: {

            }

            default: {
                printf("There is no such command\n");
                break;
            }
        }
    }

    free(roots);
    return 0;
}