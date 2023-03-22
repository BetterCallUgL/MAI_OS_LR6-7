#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../list/list.h"
#include "lib_manager.h"
#include "zmq.h"

int main() {
    struct node** roots = malloc(sizeof(struct node*));
    void* context = zmq_ctx_new();
    void** pushers = malloc(sizeof(void*));
    void* puller = zmq_socket(context, ZMQ_PULL);
    zmq_bind(puller, "tcp://*:5554");
    int root_count = 1, first_root = 1;
    char path[] = "/home/ugl/OS/worker/worker";
    printmenu();

    while (1) {
        char command[50];
        scanf("%s", command);

        // Print menu
        if (!strcmp(command, "menu")) {
            printmenu();
        }

        // Create New Root
        if (!strcmp(command, "root")) {
            int root_id;
            scanf("%d", &root_id);

            if (first_root) {
                init(roots, root_id);
                first_root = 0;
            } else {
                if (node_exists(roots, root_count, root_id) != NULL) {
                    printf("Error: This Node already exists\n");
                    continue;
                } else {
                    roots = realloc(roots, (++root_count) * sizeof(struct node*));
                    init(roots + root_count - 1, root_id);
                    pushers = realloc(pushers, root_count * sizeof(void*));
                }
            }

            pushers[root_count - 1] = zmq_socket(context, ZMQ_PUSH);
            char adress[50];
            sprintf(adress, "tcp://localhost:%d", 5555 + root_id);
            zmq_connect(pushers[root_count - 1], adress);
            int process_id = fork();
            if (!process_id) {
                char id[10];
                sprintf(id, "%d", root_id);
                if (execl(path, path, id, "-1", NULL) == -1) {
                    printf("Error: Root hasn't created\n");
                    return -1;
                }
            }
        }

        // Create New Node
        if (!(strcmp(command, "node"))) {
            int parent_id, new_id;

            scanf("%d", &new_id);
            scanf("%d", &parent_id);
            if (node_exists(roots, root_count, new_id) != NULL) {
                printf("Error: This Node already exists\n");
                continue;
            }

            struct node* parent = node_exists(roots, root_count, parent_id);
            if (parent == NULL) {
                printf("Error: This Parent doesn't exists\n");
                continue;
            }

            add_element(parent, new_id);
            char create_command[50];
            int root_number = find_root(roots, root_count, parent_id);
            sprintf(create_command, "create %d %d", new_id, parent_id);
            zmq_send(pushers[root_number], create_command, sizeof(create_command), 0);
        }

        if (!strcmp("list", command)) {
            for (int i = 0; i < root_count; i++) {
                print_list(roots[i]);
            }
        }

        // Exec command
        if (!strcmp("exec", command)) {
            char line[50];
            char message[120];
            int id;
            scanf("%d", &id);
            fgets(line, sizeof(line), stdin);
            line[strlen(line) - 1] = '\0';
            sprintf(message, "%s %d%s", command, id, line);

            if (node_exists(roots, root_count, id) == NULL) {
                printf("Error: Node doesn't exists\n");
                continue;
            }

            int root_number = find_root(roots, root_count, id);
            zmq_send(pushers[root_number], message, sizeof(message), 0);
            zmq_sleep(1);
            char reply[100];
            if (zmq_recv(puller, reply, 100, ZMQ_DONTWAIT) == -1) {
                printf("Error: Node is unavailable\n");
            } else {
                printf("%s\n", reply);
            }
        }

        // Remove command
        if (!strcmp("remove", command)) {
            int id;
            scanf("%d", &id);
            char message[100];

            if (node_exists(roots, root_count, id) == NULL) {
                printf("Error: Node doesn't exists\n");
                continue;
            }

            sprintf(message, "%s %d", command, id);
            int root_number = find_root(roots, root_count, id);
            zmq_send(pushers[root_number], message, sizeof(message), 0);
            zmq_sleep(1);
            char reply[100];
            if (zmq_recv(puller, reply, 100, ZMQ_DONTWAIT) == -1) {
                printf("Error: Node is unavailable\n");
            } else {
                delete_elem(roots[root_number], id);
                printf("%s\n", reply);
            }
        }
    }

    for (int i = 0; i < root_count; i++) {
        zmq_close(pushers[i]);
    }
    zmq_close(puller);
}