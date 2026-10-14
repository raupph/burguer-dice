#ifndef STACK_HPP
#define STACK_HPP

typedef struct {
    int code;
    char name[50];
    float price;
} Product;

typedef struct str_Node Node;

struct str_Node {
    Node *next;
    Product data;
};

typedef struct {
    Node *top;
} LinkedStack;

void initialize(LinkedStack *stack);
int  isEmpty(LinkedStack *stack);
int  push(LinkedStack *stack, Product value);
int  pop(LinkedStack *stack, Product *removedValue);
int  peek(LinkedStack *stack, Product *value);
int  size(LinkedStack *stack);

#endif
