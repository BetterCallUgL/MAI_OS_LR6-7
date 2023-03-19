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
    void* context = zmq_ctx_new();
    void* pusher = zmq_socket(context,ZMQ_PUSH);
    void* puller = zmq_socket()
    char adress[50];
    printf("%d\n",(atoi)(argv[1]));
    zmq_connect(pusher,"tcp://localhost:5554");
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