#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../map/map.h"
#include "zmq.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error, not enough arguments");
        return -1;
    }
    int my_id = (atoi)(argv[1]);
    int parent_id = (atoi)(argv[2]);
    printf("%d:Ok: %d\n", my_id, getpid());
    fflush(stdout);
    struct item* dict;
    int dict_size = 0;
    void* context = zmq_ctx_new();
    void* parent_pusher = zmq_socket(context, ZMQ_PUSH);
    void* puller = zmq_socket(context, ZMQ_PULL);
    void* child_pusher = zmq_socket(context, ZMQ_PUSH);
    char child_adress[50];
    int child_id = 0;

    if (argv[3] != NULL) {
        child_id = (atoi)(argv[3]);
        sprintf(child_adress, "tcp://localhost:%d", 5555 + child_id);
        zmq_connect(child_pusher, child_adress);
        // printf("%d:У меня есть ребёнок - %s\n", my_id, argv[3]);
        fflush(stdout);
    }

    char my_adress[50];
    sprintf(my_adress, "tcp://*:%d", 5555 + my_id);
    zmq_bind(puller, my_adress);

    char parent_adress[50];
    sprintf(parent_adress, "tcp://localhost:%d", 5555 + parent_id);
    zmq_connect(parent_pusher, parent_adress);

    while (1) {
        char message[100];
        zmq_recv(puller, message, 100, 0);
        printf("%d:Пришло новое сообщение\n", my_id, message);
        fflush(stdout);
        char copy_message[100];
        for (int i = 0; i < 100; i++) {
            copy_message[i] = message[i];
        }
        char* command = strtok(message, " ");

        if (!strcmp(command, "create")) {
            char* new_id = strtok(NULL, " ");
            char* creator_id = strtok(NULL, " ");
            fflush(stdout);
            if (child_id == 0 && my_id == (atoi)(creator_id)) {
                child_id = (atoi)(new_id);
                char child_adress[50];
                sprintf(child_adress, "tcp://localhost:%d", 5555 + child_id);
                child_pusher = zmq_socket(context, ZMQ_PUSH);
                zmq_connect(child_pusher, child_adress);
                int process_id = fork();
                if (!process_id) {
                    execl(argv[0], argv[0], new_id, creator_id, NULL);
                }
            } else if (child_id != 0 && my_id != (atoi)(creator_id)) {
                // printf("%d:Пересылаю %d\n", my_id, child_id);
                zmq_send(child_pusher, copy_message, sizeof(copy_message), 0);
            } else if (child_id != 0 && my_id == (atoi)(creator_id)) {
                char new_parent[50];
                // printf("%d:Вставляю %s перед %d\stdout_id, new_id, child_id);
                fflush(stdout);
                char old_child[10];
                sprintf(old_child, "%d", child_id);
                sprintf(new_parent, "parent %s", new_id);
                zmq_send(child_pusher, new_parent, sizeof(copy_message), 0);
                zmq_close(child_pusher);
                child_pusher = zmq_socket(context, ZMQ_PUSH);
                child_id = (atoi)(new_id);
                char child_adress[50];
                sprintf(child_adress, "tcp://localhost:%d", 5555 + child_id);
                zmq_connect(child_pusher, child_adress);
                int process_id = fork();
                if (!process_id) {
                    execl(argv[0], argv[0], new_id, creator_id, old_child, NULL);
                }
            }
        }

        if (!strcmp(command, "parent")) {
            char* new_parent = strtok(NULL, " ");
            parent_id = atoi(new_parent);
            zmq_close(parent_pusher);  // проблемная зона
            parent_pusher = zmq_socket(context, ZMQ_PUSH);
            sprintf(parent_adress, "tcp://localhost:%d", 5555 + parent_id);
            zmq_connect(parent_pusher, parent_adress);
            // printf("%d:Мой новый родитель теперь:%d \n", my_id, parent_id);
            fflush(stdout);
        }

        if (!strcmp(command, "child")) {
            char* new_child = strtok(NULL, " ");
            child_id = atoi(new_child);
            zmq_close(child_pusher);  // проблемная зона
            child_pusher = zmq_socket(context, ZMQ_PUSH);
            sprintf(child_adress, "tcp://localhost:%d", 5555 + child_id);
            zmq_connect(child_pusher, child_adress);
            // printf("%d:Мой новый родитель теперь:%d \n", my_id, parent_id);
            fflush(stdout);
        }

        if (!strcmp(command, "exec")) {
            char* id = strtok(NULL, " ");
            char reply[100];
            if (atoi(id) != my_id) {
                zmq_send(child_pusher, copy_message, sizeof(copy_message), 0);
            } else {
                char* key = strtok(NULL, " ");
                char* value = strtok(NULL, " ");
                fflush(stdout);
                if (value == NULL) {
                    fflush(stdout);
                    int index = find_value(dict, dict_size, key);
                    if (index == -1) {
                        sprintf(reply, "Ok: %d:'%s' Not found", my_id, key);
                    } else {
                        sprintf(reply, "Ok: %d: %d", my_id, dict[index].value);
                    }
                } else {
                    fflush(stdout);
                    char real_key[40];
                    strcpy(real_key, key);
                    int val = atoi(value);
                    add_value(&dict, &dict_size, real_key, val);
                    fflush(stdout);
                    sprintf(reply, "Ok: %d", my_id);
                }
                fflush(stdout);
                zmq_send(parent_pusher, reply, sizeof(reply), 0);
            }
        }

        if (!strcmp("remove", command)) {
            char* id = strtok(NULL, " ");
            if (my_id != atoi(id)) {
                zmq_send(child_pusher, copy_message, sizeof(copy_message), 0);
            } else {
                if (child_id == 0) {
                    zmq_send(parent_pusher, "dead", 5, 0);
                    break;
                } else{
                    char message[100];
                    sprintf(message,"parent %d",parent_id);
                    zmq_send(child_pusher,message,sizeof(message),0);
                    sprintf(message,"child %d",child_id);
                    zmq_send(parent_pusher,message,sizeof(message),0);
                    zmq_send(parent_pusher,"Ok",sizeof(message),0);
                    break;
                }
            }
        }

        if (!strcmp("dead", command)) {
            child_id = 0;
            zmq_close(child_pusher);
            zmq_send(parent_pusher, "Ok", 3, 0);
        }

        if (!strcmp(command, "Ok:") || !(strcmp(command, "Ok"))) {
            zmq_send(parent_pusher, copy_message, sizeof(copy_message), 0);
        }
    }

    if (dict_size > 0) {
        free(dict);
    }
    zmq_close(child_pusher);
    zmq_close(parent_pusher);
    zmq_close(puller);
    zmq_ctx_destroy(context);
    return 0;
}