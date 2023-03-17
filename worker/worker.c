#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("lol");
    } else {
        FILE* f = fopen("hui.txt", "w");
        fprintf(f, "hui from %d", (atoi)(argv[1]));
        fclose(f);
    }
    return 0;
}