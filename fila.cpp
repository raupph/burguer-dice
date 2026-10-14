#include <stdlib.h>
#include "fila.hpp"

void initialize(LinkedQueue *queue) {
    queue->front = nullptr;
    queue->back  = nullptr;
}

int isEmpty(LinkedQueue *queue) {
    return queue->front == nullptr;
}

int enqueue(LinkedQueue *queue, Product value) {
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

int dequeue(LinkedQueue *queue, Product *removedValue) {
    NodoFila *removed;

    if (isEmpty(queue)) // underflow
        return 0;

    removed = queue->front;
    *removedValue = removed->data;
    queue->front = removed->next;

    if (queue->front == nullptr) // the queue became empty
        queue->back = nullptr;

    free(removed);
    return 1;
}

int size(LinkedQueue *queue) {
    NodoFila *current = queue->front;
    int count = 0;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}
