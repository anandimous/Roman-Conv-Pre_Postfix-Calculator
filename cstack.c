//stack method
#include <stdio.h>
#include <stdlib.h>
#include "cstack.h"

struct node {
  char node_val;
  struct node* ptr_next;
};

/***
  push()
  pop()
  isEmpty()
  size()
  */

struct node* head;
int size_ctr;

void init() {
  head = NULL;
  size_ctr = 0;
}

bool isEmpty() {
  return size_ctr == 0;
}

void push(char inp) {
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

char pop() {
  if(isEmpty()) {
    perror("%sOPERATION ERROR: Nothing to pop; stack is empty!\n", );
  }
  else {
    struct node* rm = head;
    head = head->next;
    return rm->node_val;
    free(rm);
    size_ctr = size_ctr - 1;
  }
}

char peek() {
  if(isEmpty()) {
    perror("%sOPERATION ERROR: Nothing to peek; stack is empty!\n", );
  }
  else {
    struct node* pm = head;
    return rm->node_val;
  }
}

int size() {
  return size_ctr;
}
