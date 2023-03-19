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

    printf("ok: %d\n", getpid());
    void* context = zmq_ctx_new();
    void* pusher = zmq_socket(context, ZMQ_PUSH);
    void* puller = zmq_socket(context, ZMQ_PULL);
    int my_id = (atoi)(argv[1]);
    int parent_id = (atoi)(argv[2]);
    int has_child = 0;

    printf("%d %d\n",my_id,parent_id);
    if (argv[3] == NULL){
        printf("я бездетный");
    } else {
        has_child = (atoi)(argv[3]);
    }
    printf("%d\n",has_child);
    char my_adress[50];
    sprintf(my_adress, "tcp://*:%d", 10000 + my_id);
    printf("%s\n",my_adress);
    zmq_bind(puller, my_adress);
    perror("child");

    char parent_adress[50];
    sprintf(parent_adress, "tcp://127.0.0.1:%d", 10000 + parent_id);
    zmq_connect(pusher, parent_adress);
    printf("ичё");
    perror("1");
    while (1) {
        char message[50];
        printf("pennys");
        int check = zmq_recv(puller, message, 50, ZMQ_DONTWAIT);
        printf("%d",check);
        while (check == -1){
            zmq_sleep(1);
            printf("ку чд");
            check = zmq_recv(puller, message,50,ZMQ_DONTWAIT);
        }
        printf("%s",message);
        printf("lol");

        // if (!strcmp(command, "create")) {
        //     char* new_id = strtok(message, " ");
        //     char* creator_id = strtok(message, " ");
        //     printf("новый id - %s,айди папочки - %s", new_id, creator_id);
        // }
    }

    zmq_close(pusher);
    zmq_close(puller);
    zmq_ctx_destroy(context);
    return 0;
}