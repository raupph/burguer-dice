#include <stdlib.h>
#include "pilha.hpp"

void stack_initialize(Pilha *stack) {
    stack->top = nullptr;
    stack_push(stack, 'p');
}

int stack_isEmpty(const Pilha *stack) {
    return stack->top == nullptr;
}

int stack_push(Pilha *stack, char value) {
    NodoPilha *newNode = (NodoPilha*) malloc(sizeof(NodoPilha));
    if (newNode == nullptr)
        return 0;

    newNode->ingredient = value;
    newNode->next = stack->top; // points to the previous top
    stack->top = newNode;        // the new node becomes the top
    return 1;
}

char stack_pop(Pilha *stack) {
    NodoPilha *removed;
    char value_removed;

    if (stack_isEmpty(stack)) // underflow
        return 0;

    removed = stack->top;
    value_removed = removed->ingredient;
    stack->top = removed->next;
    free(removed);
    return value_removed;
}

// int peek(Stack *stack, Product *value) {
//     if (isEmpty(stack))
//         return 0;

//     *value = stack->top->data;
//     return 1;
// }

// int size(Stack *stack) {
//     NodoPilha *current = stack->top;
//     int count = 0;

//     while (current != nullptr) {
//         count++;
//         current = current->next;
//     }

//     return count;
//}
