#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

int main() {
    struct node** roots = malloc(sizeof(struct node*));
    int list_size = 1, flag = 0;
    int command = -1;
    printf("0.menu\n1.create new list\n2.add\n3.delete\n4.print\n5.destroy\n6.leave\n");
    while (command != 5) {
        scanf("%d", &command);
        switch (command) {
            case 0: {
                printf("0.menu\n1.create new list\n2.add\n3.delete\n4.print\n5.destroy\n6.leave\n");
                break;
            }

            case 1: {
                int id;
                printf("enter id of parent\n");
                scanf("%d", &id);
                if (flag == 0) {
                    init(roots, id);
                    flag = 1;
                } else {
                    roots = realloc(roots, (++list_size) * sizeof(struct node*));
                    init(roots + list_size - 1, id);
                }
                break;
            }

            case 2: {
                int parent_id, new_id;
                printf("enter parent id\n");
                scanf("%d", &parent_id);
                printf("enter new id\n");
                scanf("%d", &new_id);

                struct node* tmp1;
                struct node* tmp2;

                for (int i = 0; i < list_size; ++i) {
                    tmp1 = find_element(roots[i], parent_id);
                    if (tmp1 != NULL) {
                        break;
                    }
                }

                for (int i = 0; i < list_size; ++i) {
                    tmp2 = find_element(roots[i], new_id);
                    if (tmp2 != NULL) {
                        break;
                    }
                }

                if (tmp2 != NULL) {
                    printf("ALREADY EXISTS\n");
                } else if (tmp1 == NULL) {
                    printf("NOT FOUND\n");
                } else {
                    add_element(tmp1, new_id);
                }

                break;
            }

            case 3: {
                int id;
                printf("enter id\n");
                scanf("%d", &id);
                struct node* tmp;
                struct node* root;

                for (int i = 0; i < list_size; ++i) {
                    tmp = find_element(roots[i], id);
                    if (tmp != NULL) {
                        root = roots[i];
                        break;
                    }
                }

                if (tmp == NULL) {
                    printf("NOT FOUND\n");
                } else {
                    printf("%dHAHAHHA\n", tmp->id);
                    delete_elem(root, tmp->id);
                }

                break;
            }

            case 4: {
                for (int i = 0; i < list_size; ++i) {
                    print_list(roots[i]);
                }

                break;
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