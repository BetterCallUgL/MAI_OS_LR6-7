#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib_manager.h"
#include "list.h"
#include "zmq.h"

int main() {
    struct node** roots = malloc(sizeof(struct node*));
    void* context = zmq_ctx_new();
    void** pushers = malloc(sizeof(void*));
    void* puller = zmq_socket(context,ZMQ_PULL);
    zmq_bind(puller, "tcp://localhost:5555");
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
                pushers[root_count - 1] = zmq_socket(context, ZMQ_PUSH);
                char adress[50];
                sprintf(adress, "tcp://localhost:%d", 10000 + root_id);
                zmq_connect(pushers[root_count - 1], adress);
                int process_id = fork();
                if (!process_id) {
                    char id[10];
                    sprintf(id, "%d", root_id);
                    if (execl(path, path, id, "-1", NULL) == -1) {
                        printf("Root hasn't created\n");
                        return -1;
                    }
                }
            }
        }

        // // Create New Node
        // if (!(strcmp(command, "node"))) {
        //     int parent_id, new_id;
        //     struct node* parent = node_exists(roots, root_count, parent_id);

        //     printf("Enter parent id\n");
        //     scanf("%d", &parent_id);
        //     if (parent == NULL) {
        //         printf("This Parent doesn't exists\n");
        //         continue;
        //     }
        //     printf("Enter new id\n");
        //     scanf("%d", &new_id);
        //     if (node_exists(roots, root_count, new_id) != NULL) {
        //         printf("This Node already exists\n");
        //         continue;
        //     }

        //     add_element(parent, new_id);
        //     int process_id = fork();
        //     char line_id[10];
        //     sprintf(line_id, "%d", new_id);
        //     if (!process_id) {
        //         printf("ok: %d\n", getpid());
        //         if (execl("/home/ugl/OS/worker/worker", "/home/ugl/OS/worker/worker", line_id, NULL) == -1)
        //         {
        //             printf("Node hasn't created");
        //             return -1;
        //         }
        //     }
        // }

        // zmq_msg_t message;
        // zmq_msg_init(&message);
        // char m
        char message[100];
        int check = zmq_recv(puller,message,100,ZMQ_DONTWAIT);
        zmq_sleep(5);
        if (check == -1) {
            printf("Мужик чё за хуйня)");
        } else {
            printf("ураа я получил:%s\n", message);
        }
    }
}