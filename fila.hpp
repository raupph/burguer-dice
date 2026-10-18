#ifndef FILA_HPP
#define FILA_HPP

struct NodoFila {
    NodoFila *next;
    char   data;
};

typedef struct {
    NodoFila *front;
    NodoFila *back;
} Fila;

void queue_initialize(Fila *queue);
int  queue_isEmpty(Fila *queue);
int  queue_enqueue(Fila *queue, char value);
int  queue_dequeue(Fila *queue, char *removedValue);
int  queue_size(Fila *queue);

#endif
