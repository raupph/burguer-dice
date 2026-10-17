#ifndef FILA_HPP
#define FILA_HPP

#include "product.hpp"

typedef struct str_NodoFila NodoFila;

struct str_NodoFila {
    NodoFila *next;
    Product   data;
};

typedef struct {
    NodoFila *front;
    NodoFila *back;
} LinkedQueue;

void initialize(LinkedQueue *queue);
int  isEmpty(LinkedQueue *queue);
int  enqueue(LinkedQueue *queue, Product value);
int  dequeue(LinkedQueue *queue, Product *removedValue);
int  size(LinkedQueue *queue);

#endif
