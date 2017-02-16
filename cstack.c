//stack method
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cstack.h"

struct node {
  char node_val;
  struct node* ptr_next;
};

/***
  push()
  pop()
  isEmpty()
  size() //redundant unused
  */

// struct node* head;
// int size_ctr;

bool isEmpty(struct node* head) {
  return head == NULL;
}

struct node* push(struct node* head,char inp) {
    struct node* element = (struct node*) malloc(sizeof(struct node));
    if(element == NULL) { printf("stack push malloc unsuccessul!\n"); }
    if(isEmpty(element)){
      element->node_val = inp;
      element->ptr_next = NULL;
      head = element;
    }
    else {
      element->node_val = inp;
      element->ptr_next = head;
      head = element;
    }
    free(element);
    return head;
}

struct node* pop(struct node *head) {
  if(isEmpty(head)) {
    printf("OPERATION ERROR: Nothing to pop; stack is empty!\n");
  }
  else {
    struct node* rm = head;
    head = rm->ptr_next;
    free(rm);
    return head;
  }
}

char peek(struct node* head) {
  if(isEmpty(head)) {
    printf("OPERATION ERROR: Nothing to peek; stack is empty!\n");
  }
  else {
    struct node* rm = head;
    return rm->node_val;
  }
}
