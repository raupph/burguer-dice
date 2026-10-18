#include <stdlib.h>
#include "fila.hpp"

void queue_initialize(Fila *queue) {
    queue->front = nullptr;
    queue->back  = nullptr;
}

int queue_isEmpty(Fila *queue) {
    return queue->front == nullptr;
}

int queue_enqueue(Fila *queue, char value) {
    NodoFila *newNode = (NodoFila*) malloc(sizeof(NodoFila));
    if (newNode == nullptr)
        return 0;

    newNode->data = value;
    newNode->next = nullptr;

    if (queue->back != nullptr)
        queue->back->next = newNode; // the old back now points to the new node
    else
        queue->front = newNode;      // the queue was empty: new node is also the front

    queue->back = newNode;
    return 1;
}

int queue_dequeue(Fila *queue, char *removedValue) {
    NodoFila *removed;

    if (queue_isEmpty(queue)) // underflow
        return 0;

    removed = queue->front;
    *removedValue = removed->data;
    queue->front = removed->next;

    if (queue->front == nullptr) // the queue became empty
        queue->back = nullptr;

    free(removed);
    return 1;
}

int queue_size(Fila *queue) {
    NodoFila *current = queue->front;
    int count = 0;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}
