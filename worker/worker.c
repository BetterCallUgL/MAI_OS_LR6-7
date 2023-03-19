#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "zmq.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error, not enough arguments");
        return -1;
    }

    printf("ok: %d", getpid());
    void* context = zmq_ctx_new();
    perror("lol");
    printf("govno");
    void* pusher = zmq_socket(context, ZMQ_PUSH);
    void* puller = zmq_socket(context, ZMQ_PULL);
    int my_id = (atoi)(argv[1]);
    int parent_id = (atoi)(argv[2]);
    // int has_child = 0;
    printf("hui");
    // printf("%d %d\n",my_id,parent_id);
    // if (argv[3] == NULL){
    //     printf("я бездетный");
    // } else {
    //     has_child = (atoi)(argv[3]);
    // }
    char my_adress[50];
    sprintf(my_adress, "tcp://*:%d", 5555 + my_id);
    zmq_bind(puller, my_adress);

    char parent_adress[50];
    sprintf(parent_adress, "tcp://localhost:%d", 5555 + parent_id);
    zmq_connect(pusher, parent_adress);

    while (1) {
        char message[50];
        int check = zmq_recv(puller, message, 50, ZMQ_DONTWAIT);
        while (check == -1){
            zmq_sleep(1);
            check = zmq_recv(puller, message, 50, ZMQ_DONTWAIT);
        }
        printf("%s",message);
        char* command = strtok(message, " ");
        if (!strcmp(command, "create")) {
            char* new_id = strtok(NULL, " ");
            char* creator_id = strtok(NULL, " ");
            printf("новый id - %s,айди папочки - %s", new_id, creator_id);
            fflush(stdout);
        }
    }
    
    zmq_close(pusher);
    zmq_close(puller);
    zmq_ctx_destroy(context);
    return 0;
}