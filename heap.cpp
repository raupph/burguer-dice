#include "heap.hpp"

void initializeHeap(Heap *heap) {
    heap->size = 0;
}

static void swap(Product *a, Product *b) {
    Product tmp = *a;
    *a = *b;
    *b = tmp;
}

// Bubbles element at index i up to restore min-heap property.
static void sift_up(Heap *heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].expiry_turn <= heap->data[i].expiry_turn)
            break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

// Pushes element at index i down to restore min-heap property.
static void sift_down(Heap *heap, int i) {
    int n = heap->size;
    while (true) {
        int smallest = i;
        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        if (left  < n && heap->data[left].expiry_turn  < heap->data[smallest].expiry_turn)
            smallest = left;
        if (right < n && heap->data[right].expiry_turn < heap->data[smallest].expiry_turn)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
}

// Returns 1 on success, 0 if heap is full.
int insertHeap(Heap *heap, Product product) {
    if (heap->size >= HEAP_MAX)
        return 0;

    heap->data[heap->size] = product;
    sift_up(heap, heap->size);
    heap->size++;
    return 1;
}

// Removes and returns the minimum (lowest expiry_turn). Returns 1 on success, 0 if empty.
int extractMin(Heap *heap, Product *removed) {
    if (heap->size == 0)
        return 0;

    *removed = heap->data[0];
    heap->size--;

    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        sift_down(heap, 0);
    }

    return 1;
}

void destroyHeap(Heap *heap) {
    heap->size = 0;
}
