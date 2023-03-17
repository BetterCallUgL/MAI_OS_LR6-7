#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, int *argv[]) {
    printf("Будет выполнена программа %s...\n\n", argv[0]);
    fflush(stdout);
    int id = fork();
    printf("KY\n");
    if (id == 0) {
        printf("AUF");
        execl("hello", " ", "Hello", "World!", NULL);
    }
    return 0;
}