#ifndef PILHA_HPP
#define PILHA_HPP

#include "game.hpp"

typedef struct str_NodoPilha NodoPilha;

struct str_NodoPilha {
    NodoPilha *next;
    Product    data;
};

typedef struct {
    NodoPilha *top;
} LinkedStack;

void initialize(LinkedStack *stack);
int  isEmpty(LinkedStack *stack);
int  push(LinkedStack *stack, Product value);
int  pop(LinkedStack *stack, Product *removedValue);
int  peek(LinkedStack *stack, Product *value);
int  size(LinkedStack *stack);

#endif
