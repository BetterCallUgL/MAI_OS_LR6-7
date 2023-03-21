#ifndef MAP_H
#define MAP_H

struct item {
    char key[40];
    int value;
};
void add_value(struct item** items, int* size, char key[40], int value);
int find_value(struct item* items, int size, char key[40]);
#endif