#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib_manager.h"
#include "list.h"
#include "zmq.h"

int main() {
    struct node** roots = malloc(sizeof(struct node*));
    int root_count = 1, first_root = 1;
    char path[] = "/home/ugl/OS/worker/worker";
    printmenu();

    while (1) {
        printf("Enter command:\n");
        char command[100];
        scanf("%s", command);

        // Create New Root
        if (!strcmp(command, "root")) {
            int root_id, create_flag = 0;
            printf("Enter root id\n");
            scanf("%d", &root_id);

            if (first_root) {
                init(roots, root_id);
                first_root = 0;
                create_flag = 1;
            } else {
                if (node_exists(roots, root_count, root_id) != NULL) {
                    printf("This node already exists\n");
                } else {
                    roots = realloc(roots, (++root_count) * sizeof(struct node*));
                    init(roots + root_count - 1, root_id);
                    create_flag = 1;
                }
            }

            if (create_flag) {
                int process_id = fork();
                if (!process_id) {
                    printf("ok: %d\n", getpid());
                    char id[10];
                    sprintf(id, "%d", root_id);
                    if (execl(path, path, id, NULL) == -1) {
                        printf("Root hasn't created\n");
                        return -1;
                    }
                }
            }
        }

        // Create New Node
        if (!(strcmp(command, "node"))) {
            int parent_id, new_id;
            struct node* parent = node_exists(roots,root_count,parent_id);

            printf("Enter parent id\n");
            scanf("%d", &parent_id);
            if (parent == NULL){
                printf("This Parent doesn't exists\n");
                continue;
            }
            printf("Enter new id\n");
            scanf("%d", &new_id);
            if (node_exists(roots,root_count,new_id) != NULL){
                printf("This Node already exists\n");
                continue;
            }

            add_element(parent,new_id);
            int process_id = fork();
            char line_id[10];
            sprintf(line_id,"%d",new_id);
            if (!process_id) {
                printf("ok: %d\n", getpid());
                if (execl("/home/ugl/OS/worker/worker", "/home/ugl/OS/worker/worker", line_id, NULL) ==
                    -1) {
                    printf("Node hasn't created");
                    return -1;
                }
            }
        }
    }
}