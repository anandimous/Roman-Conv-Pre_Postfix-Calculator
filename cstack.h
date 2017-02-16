//header file containing stack method definitions
#ifndef CSTACK_H_
#define CSTACK_H_

struct node* stack;
char c;

void init(struct node* stack);
bool isEmpty(struct node* stack);
void push(struct node* stack,char c);
char pop(struct node* stack);
char peek(struct node* stack);
int size(struct node* stack);

#endif //cstack.h
