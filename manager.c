#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zmq.h"
#include "lib_manager.h"
#include "list.h"

int main(){
    struct node** roots = malloc(sizeof(struct node*));
    int root_count = 1,already_created = 1;
    
    printmenu();

    while (1){
        printf("Enter command:\n");
        char command[100];
        scanf("%s",command);

        if (!strcmp(command,"root")){
            int parent_id, create_flag = 0;
            printf("Enter parent id\n");
            scanf("%d",&parent_id);

            if (already_created){
                init(roots, parent_id);
                already_created = 0;
                create_flag = 1;
            } else {
                struct node* list_node;
                for (int i = 0; i < root_count;i++){
                    list_node = find_element(roots[i],parent_id);
                    if (list_node != NULL){
                        break;
                    }
                }
                if (list_node != NULL){
                    printf("This node already exists\n");
                } else {
                    roots = realloc(roots,(++root_count)*sizeof(struct node*));
                    init(roots+root_count-1,parent_id);
                }
            }

            if (create_flag){
                printf("hui");
            }
        }
    }
}