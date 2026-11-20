#include <stdlib.h>
#include "fila.hpp"

void queue_initialize(Fila *queue) {
    queue->front = nullptr;
    queue->back  = nullptr;
}

bool queue_isEmpty(const Fila *queue) {
    return queue->front == nullptr;
}

bool queue_enqueue(Fila *queue, Customer customer) {
    NodoFila *newNode = (NodoFila*) malloc(sizeof(NodoFila));
    if (newNode == nullptr)
        return false;

    newNode->customer = customer;
    newNode->next = nullptr;

    if (queue->back != nullptr)
        queue->back->next = newNode; // the old back now points to the new node
    else
        queue->front = newNode;      // the queue was empty: new node is also the front

    queue->back = newNode;
    return true;
}

bool queue_dequeue(Fila *queue, Customer *removed_customer) {
    NodoFila *removed;

    if (queue_isEmpty(queue)) // underflow
        return false;

    removed = queue->front;
    *removed_customer = removed->customer;
    queue->front = removed->next;

    if (queue->front == nullptr) // the queue became empty
        queue->back = nullptr;

    free(removed);
    return true;
}

bool queue_front(const Fila *queue, Customer *customer) {
    if (queue_isEmpty(queue)) {
        return false;
    }

    *customer = queue->front->customer;
    return true;
}

int queue_size(const Fila *queue) {
    NodoFila *current = queue->front;
    int count = 0;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

void queue_destroy(Fila *queue) {
    NodoFila *current = queue->front;
    while (current != nullptr) {
        NodoFila *next = current->next;
        free(current);
        current = next;
    }

    queue->front = nullptr;
    queue->back = nullptr;
}
