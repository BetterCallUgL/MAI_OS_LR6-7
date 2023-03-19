#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "lib_manager.h"
#include "list.h"
#include "zmq.h"

int main() {
    struct node** roots = malloc(sizeof(struct node*));
    void* context = zmq_ctx_new();
    void** pushers = malloc(sizeof(void*));
    void* puller = zmq_socket(context,ZMQ_PULL);
    zmq_bind(puller, "tcp://*:5554");
    unsigned int error_code = zmq_errno();
    printf("server socket erro:%u,%s\n",error_code,zmq_strerror(error_code));
    int root_count = 1, first_root = 1;
    char path[] = "/home/ugl/OS/worker/worker";
    printmenu();

    while (1) {
        printf("Enter command:\n");
        char command[100];
        scanf("%s", command);
        
        //Print menu
        if (!strcmp(command,"menu")){
            printmenu();
        }
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
                    printf("This Node already exists\n");
                } else {
                    roots = realloc(roots, (++root_count) * sizeof(struct node*));
                    init(roots + root_count - 1, root_id);
                    create_flag = 1;
                }
            }

            if (create_flag) {
                pushers[root_count - 1] = zmq_socket(context, ZMQ_PUSH);
                char adress[50];
                sprintf(adress, "tcp://localhost:%d", 5555 + root_id);
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

        // Create New Node
        if (!(strcmp(command, "node"))) {
            int parent_id, new_id;

            scanf("%d", &new_id);
            scanf("%d", &parent_id);
            if (node_exists(roots, root_count, new_id) != NULL) {
                printf("This Node already exists\n");
                continue;
            }

            struct node* parent = node_exists(roots, root_count, parent_id);
            if (parent == NULL) {
                printf("This Parent doesn't exists\n");
                continue;
            }

            add_element(parent, new_id);
            char create_command[50];
            int root_number = find_root(roots,root_count,parent_id);
            sprintf(create_command,"create %d %d",new_id,parent_id);
            zmq_send(pushers[root_number],create_command,strlen(create_command) + 1,0);
        }

        // zmq_msg_t message;
        // zmq_msg_init(&message);
        // char m
//         char message[100];
//         int check = -1;
//         while (check == -1){
//             check = zmq_recv(puller,message,100,ZMQ_DONTWAIT);
//             zmq_sleep(1);
//             printf("ну и хуйн\n");
//         }
//         printf("ураа я получил:%s\n", message);
//         printf("%d",check);
// }
    }
}