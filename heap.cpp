#include "heap.hpp"

void initializeHeap(Heap *heap) {
    heap->size = 0;
}

int insertHeap(Heap *heap, Product product) {
    (void)heap;
    (void)product;
    return 0;
}

int extractMax(Heap *heap, Product *removed) {
    (void)heap;
    (void)removed;
    return 0;
}

void destroyHeap(Heap *heap) {
    heap->size = 0;
}
