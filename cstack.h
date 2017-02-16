//header file containing stack method definitions
#ifndef CSTACK_H_
#define CSTACK_H_

struct node* stack;
char c;

bool isEmpty(struct node* stack);
struct node* push(struct node* stack,char c);
struct node* pop(struct node* stack);
char peek(struct node* stack);

#endif //cstack.h
