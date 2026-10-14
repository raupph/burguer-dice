#ifndef QUEUE_HPP
#define QUEUE_HPP

typedef struct {
    int code;
    char name[50];
    float price;
} Product;

typedef struct str_Node Node;

struct str_Node {
    Node *next;
    Product data;
};

typedef struct {
    Node *front;
    Node *back;
} LinkedQueue;

void initialize(LinkedQueue *queue);
int  isEmpty(LinkedQueue *queue);
int  enqueue(LinkedQueue *queue, Product value);
int  dequeue(LinkedQueue *queue, Product *removedValue);
int  size(LinkedQueue *queue);

#endif
