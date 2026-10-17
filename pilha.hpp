#ifndef PILHA_HPP
#define PILHA_HPP

struct NodoPilha {
    NodoPilha* next;
    char ingredient;
};

struct Pilha {
    struct NodoPilha* top;
};

//typedef struct Pilha Stack;

void stack_initialize(Pilha* stack);
// int  stack_isEmpty(const Pilha* stack);
// int  stack_push(Pilha* stack, char ingredient);
// int  stack_pop(Pilha* stack, char* removedValue);
// int  stack_peek(const Pilha* stack, char* value);
// int  stack_size(const Pilha* stack);
// void stack_destroy(Pilha* stack);

#endif
