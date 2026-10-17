#ifndef PILHA_HPP
#define PILHA_HPP

struct NodoPilha {
    NodoPilha* next;
    char ingredient;
};

struct LinkedStack {
    NodoPilha* top;
};

void stack_initialize(LinkedStack* stack);
int  stack_isEmpty(const LinkedStack* stack);
int  stack_push(LinkedStack* stack, char ingredient);
int  stack_pop(LinkedStack* stack, char* removedValue);
int  stack_peek(const LinkedStack* stack, char* value);
int  stack_size(const LinkedStack* stack);
void stack_destroy(LinkedStack* stack);

#endif
