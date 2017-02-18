//Initialize with pointer to top of stack = 0
void init(int *top){
  *top = 0;
}

// Assign the stack[top] -> element, increment top
void push(char *s, int* top, char element){
  s[(*top)++] = element;
}

// decrement top pointer, return stack[top]
char pop(char *s, int *top){
  return s[--(*top)];
}

// return 1(true) if the top pointer is 0
int empty(int *top){
  return *top == 0 ? 1 : 0;
}

// return the top element of the stack
char peek(char*s, int* top){
  return s[*top-1];
}
