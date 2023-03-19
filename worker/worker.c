#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "zmq.h"

int main(int argc, char* argv[]) {
    if (argc < 2){
        printf("Error, not enough arguments");
        return -1;
    }

    printf("ok: %d\n",getpid());
    void* context = zmq_ctx_new();
    void* pusher = zmq_socket(context,ZMQ_PUSH);
    void* puller = zmq_socket(context,ZMQ_PULL);

    char my_adress[50];
    sprintf(my_adress,"tcp://*:%d",5555+(atoi)(argv[1]));
    zmq_bind(puller,my_adress);

    char parent_adress[50];
    sprintf(parent_adress,"tcp://localhost%d",5555+(atoi)(argv[1]));
    zmq_connect(pusher,parent_adress);

    while (1){
        char message[100];
        zmq_recv(puller,)
    }
    // zmq_msg_t message;
    // zmq_msg_init_size(&message,strlen("пиписька"));
    // memcpy(zmq_msg_data(&message),"пиписька",strlen("пиписька"));
    // zmq_msg_send(&message,pusher,0);
    // zmq_msg_close(&message);
    zmq_send(pusher,"hui",4,0);
    zmq_close(pusher);
    zmq_ctx_destroy(context);
    return 0;
}