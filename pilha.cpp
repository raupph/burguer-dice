#include <stdlib.h>
#include "pilha.hpp"

void stack_initialize(Pilha *stack) {
    stack->top = nullptr;
}

// int isEmpty(Stack *stack) {
//     return stack->top == nullptr;
// }

// int push(Stack *stack, Product value) {
//     NodoPilha *newNode = (NodoPilha*) malloc(sizeof(NodoPilha));
//     if (newNode == nullptr)
//         return 0;

//     newNode->data = value;
//     newNode->next = stack->top; // points to the previous top
//     stack->top = newNode;        // the new node becomes the top
//     return 1;
// }

// int pop(Stack *stack, Product *removedValue) {
//     NodoPilha *removed;

//     if (isEmpty(stack)) // underflow
//         return 0;

//     removed = stack->top;
//     *removedValue = removed->data;
//     stack->top = removed->next;
//     free(removed);
//     return 1;
// }

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
