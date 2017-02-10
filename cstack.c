//stack method
#include <stdio.h>
#include <stdlib.h>
#include "cstack.h"

struct node {
  int node_val;
  struct node* ptr_next;
};

/***
  push()
  pop()
  isEmpty()
  size()
  */

struct node* head;
int size_ctr = 0;

void init() {
  head = NULL;
}

bool isEmpty() {
  if(head == NULL) {
    return true;
  }
  return false;
}

void push(int inp) {
    struct node* element = (struct node*) malloc(sizeof(struct node));
    if(isEmpty() == TRUE){
      element->node_val = inp;
      element->ptr_next = NULL;
      size_ctr = size_ctr + 1;
    }
    else {
      element->node_val = inp;
      element->ptr_next = head;
      size_ctr = size_ctr + 1;
    }
    head = element;
}

int pop() {
  if(isEmpty()) {
    printf("%sOPERATION ERROR: Nothing to pop; stack is empty!\n", );
  }
  else {
    struct node* rm = head;
    head = head->next;
    return rm->node_val;
    free(rm);
    size_ctr = size_ctr - 1;
  }
}

int size() {
  return size_ctr;
}
