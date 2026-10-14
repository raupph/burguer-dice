#include <stdio.h>
#include <stdlib.h>
#include "queue.hpp"

void initialize(LinkedQueue *queue) {
    queue->front = NULL;
    queue->back = NULL;
}

int isEmpty(LinkedQueue *queue) {
    return queue->front == NULL;
}

int enqueue(LinkedQueue *queue, Product value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL)
        return 0;

    newNode->data = value;
    newNode->next = NULL;

    if (queue->back != NULL)
        queue->back->next = newNode; // the old back now points to the new node
    else
        queue->front = newNode;      // the queue was empty: new node is also the front

    queue->back = newNode;
    return 1;
}

int dequeue(LinkedQueue *queue, Product *removedValue) {
    Node *removed;

    if (isEmpty(queue)) // underflow
        return 0;

    removed = queue->front;
    *removedValue = removed->data;
    queue->front = removed->next;

    if (queue->front == NULL) // the queue became empty
        queue->back = NULL;

    free(removed);
    return 1;
}

int size(LinkedQueue *queue) {
    Node *current = queue->front;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
