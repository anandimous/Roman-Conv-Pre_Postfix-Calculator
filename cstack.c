//stack method
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cstack.h"

struct node {
  char node_val;
  struct node* ptr_next;
  int size_ctr;
};

/***
  push()
  pop()
  isEmpty()
  size()
  */

// struct node* head;
// int size_ctr;

void init(struct node* head) {
  head = NULL;
  head->size_ctr = 0;
}

bool isEmpty(struct node* head) {
  return head->size_ctr == 0;
}

void push(struct node* head,char inp) {
    struct node* element = (struct node*) malloc(sizeof(struct node));
    if(isEmpty(element)){
      element->node_val = inp;
      element->ptr_next = NULL;
      head->size_ctr = head->size_ctr + 1;
    }
    else {
      element->node_val = inp;
      element->ptr_next = head;
      head->size_ctr = head->size_ctr + 1;
    }
    head = element;
}

char pop(struct node *head) {
  if(isEmpty(head)) {
    perror("%sOPERATION ERROR: Nothing to pop; stack is empty!\n");
  }
  else {
    struct node* rm = head;
    head = head->ptr_next;
    return rm->node_val;
    free(rm);
    head->size_ctr = head->size_ctr - 1;
  }
}

char peek(struct node* head) {
  if(isEmpty(head)) {
    perror("%sOPERATION ERROR: Nothing to peek; stack is empty!\n");
  }
  else {
    struct node* rm = head;
    return rm->node_val;
  }
}

int size(struct node* head) {
  return head->size_ctr;
}
