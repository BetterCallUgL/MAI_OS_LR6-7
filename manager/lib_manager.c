#include "lib_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>

#include "../list/list.h"

void printmenu() {
    printf("1.\"menu\"- Print menu\n");
    printf("2.\"root id\"- Create new root\n");
    printf("3.\"node id parent\"- Create new node\n");
    printf("4.\"list\"- Print List\n");
    printf("5.\"exec id name value\" - map command\n");
}

struct node* node_exists(struct node** roots, int root_count, int element_id) {
    struct node* list_node;
    for (int i = 0; i < root_count; ++i) {
        list_node = find_element(roots[i], element_id);
        if (list_node != NULL) {
            break;
        }
    }

    return list_node;
}

int find_root(struct node** roots, int root_count, int parent_id) {
    int root_number = -1;
    for (int i = 0; i < root_count; ++i) {
        if (find_element(roots[i], parent_id) != NULL) {
            root_number = i;
            break;
        }
    }

    return root_number;
}

void* hearbit(void* args) {
    struct node* list = NULL;
    struct node* copy = NULL;
    struct arguments* info = (struct arguments*)args;
    fflush(stdout);
    for (int i = 0; i < info->root_count; i++) {
        char message[100];
        sprintf(message, "hearbit %d", info->delay);
        zmq_send(info->pushers[i], message, sizeof(message), 0);
    }
    zmq_sleep(1);
    char reply[100];
    fflush(stdout);
    int first_time = 1;
    while (1) {
        int flag = 0;
        int ok = 1;
        while (zmq_recv(info->puller, reply, sizeof(reply), ZMQ_DONTWAIT) != -1) {
            if (first_time){
                if (flag == 0){
                    init(&copy,atoi(reply));
                    flag = 1;
                } else {
                    add_element(copy,atoi(reply));
                }
            } else {
                if (flag == 0) {
                    init(&list, atoi(reply));
                    flag = 1;
                } else {
                    add_element(list, atoi(reply));
                }
            }
        }

        // print_list(info->roots[0]);
        // print_list(list);
        // printf("а копия:\n");
        // print_list(copy);
        // print_list(copy);
        // print_list(list);
        if (!first_time){
            struct node* tmp = copy;
            while (tmp != NULL) {
                if (find_element(list, tmp->id) == NULL) {
                    printf("hearbit: %d is unavailable\n", tmp->id);
                    fflush(stdout);
                    ok = 0;
                }
                tmp = tmp->next;
            }
        }
        if (ok) {
            printf("hearbit: ok\n");
            fflush(stdout);
        }
        destroy_list(list);
        list = NULL;
        fflush(stdout);
        first_time = 0;
        zmq_sleep(info->delay);
    }
    return NULL;
}