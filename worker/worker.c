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
    char adress[100];
    printf("я люблю говно, а ещё :%d\n",atoi(argv[2]));
    sprintf(adress,"tcp://localhost:%d",5555);
    zmq_connect(pusher,adress);
    perror("бляха муха");
    // zmq_msg_t message;
    // zmq_msg_init_size(&message,strlen("пиписька"));
    // memcpy(zmq_msg_data(&message),"пиписька",strlen("пиписька"));
    // zmq_msg_send(&message,pusher,0);
    // zmq_msg_close(&message);
    zmq_send(pusher,"hui",4,0);
    perror("lol");
    zmq_close(pusher);
    zmq_ctx_destroy(context);
    return 0;
}