#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

void init(int *top);
void push(char *s, int* top, char element);
char pop(char *s, int *top);
int full(int *top, const int size);
int empty(int *top);
char peek(char*s, int* top);

#endif //ARRAYSTACK_H
