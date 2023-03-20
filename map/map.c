#include <map.h>
#include <stdlib.h>
#include <string.h>

int find_value(struct item* items,int* size, char input[40]){
    for (int i = 0;i < size;i++){
        if (!strcmp(items[i].key,input)){
            return items[i].key;
        }
    }
    return -1;
}

struct item* add_value(struct item** items,int* size,char input[40]){
    if (size = 0){
        *items = malloc(sizeof(struct item)*(++size));
    } else {
        int tmp = find_value(*items,size,input);
        if (tmp == -1){
            *items = realloc(*items,sizeof(struct item)*(++size));
            (*(*items+*size-1)).
        }
    }
}