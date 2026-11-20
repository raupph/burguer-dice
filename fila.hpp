#ifndef FILA_HPP
#define FILA_HPP

struct Customer {
    int id;
    int order_code;
};

struct NodoFila {
    NodoFila *next;
    Customer customer;
};

typedef struct {
    NodoFila *front;
    NodoFila *back;
} Fila;

void queue_initialize(Fila *queue);
bool queue_isEmpty(const Fila *queue);
bool queue_enqueue(Fila *queue, Customer customer);
bool queue_dequeue(Fila *queue, Customer *removed_customer);
bool queue_front(const Fila *queue, Customer *customer);
int  queue_size(const Fila *queue);
void queue_destroy(Fila *queue);

#endif
