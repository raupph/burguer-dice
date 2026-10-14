#ifndef HEAP_HPP
#define HEAP_HPP

#include "produto.hpp"

#define HEAP_MAX 100

typedef struct {
    Product data[HEAP_MAX];
    int     size;
} Heap;

void initializeHeap(Heap *heap);
int  insertHeap(Heap *heap, Product product);
int  extractMax(Heap *heap, Product *removed);
void destroyHeap(Heap *heap);

#endif
