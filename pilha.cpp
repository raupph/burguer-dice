#include <stdlib.h>
#include "pilha.hpp"

void initialize(LinkedStack *stack) {
    stack->top = nullptr;
}

// int isEmpty(LinkedStack *stack) {
//     return stack->top == nullptr;
// }

// int push(LinkedStack *stack, Product value) {
//     NodoPilha *newNode = (NodoPilha*) malloc(sizeof(NodoPilha));
//     if (newNode == nullptr)
//         return 0;

//     newNode->data = value;
//     newNode->next = stack->top; // points to the previous top
//     stack->top = newNode;        // the new node becomes the top
//     return 1;
// }

// int pop(LinkedStack *stack, Product *removedValue) {
//     NodoPilha *removed;

//     if (isEmpty(stack)) // underflow
//         return 0;

//     removed = stack->top;
//     *removedValue = removed->data;
//     stack->top = removed->next;
//     free(removed);
//     return 1;
// }

// int peek(LinkedStack *stack, Product *value) {
//     if (isEmpty(stack))
//         return 0;

//     *value = stack->top->data;
//     return 1;
// }

// int size(LinkedStack *stack) {
//     NodoPilha *current = stack->top;
//     int count = 0;

//     while (current != nullptr) {
//         count++;
//         current = current->next;
//     }

//     return count;
//}
