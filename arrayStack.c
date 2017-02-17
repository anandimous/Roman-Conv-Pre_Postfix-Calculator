void init(int *top){
  *top = 0;
}

void push(char *s, int* top, char element){
  s[(*top)++] = element;
}

char pop(char *s, int *top){
  return s[--(*top)];
}

int full(int *top, const int size){
  return *top == size ? 1 : 0;
}

int empty(int *top){
  return *top == 0 ? 1 : 0;
}

char peek(char*s, int* top){
  return s[*top-1];
}
