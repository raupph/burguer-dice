#include <cstdio>
#include <cstdlib>
#include "lista.hpp"
#include "pilha.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"
#include "timer.hpp"

int main(int argc, char *argv[]) {
    if (argc < 7) {
        fprintf(stderr, "Uso: %s arg1 arg2 arg3 arg4 <pedidos> <historico>\n", argv[0]);
        return 1;
    }

    const char *arquivoPedidos   = argv[5];
    const char *arquivoHistorico = argv[6];

    printf("Pedidos  : %s\n", arquivoPedidos);
    printf("Historico: %s\n", arquivoHistorico);

    Timer t;
    timerStart(&t);

    /* --- Lista encadeada --- */
    LinkedList lista;
    initialize(&lista);
    Product p1 = {1, "X-Burguer", 15.90f};
    Product p2 = {2, "Hot-Dog",   10.50f};
    insertAtEnd(&lista, p1);
    insertAtEnd(&lista, p2);
    Product achado = find(&lista, 1);
    printf("[Lista]  encontrado: %s (R$ %.2f)\n", achado.name, achado.price);
    removeByCode(&lista, 1);
    printf("[Lista]  tamanho apos remocao: %d\n", size(&lista));
    destroy(&lista);

    /* --- Pilha --- */
    LinkedStack pilha;
    initialize(&pilha);
    Product p3 = {3, "Batata Frita", 8.00f};
    push(&pilha, p3);
    Product topo;
    if (peek(&pilha, &topo))
        printf("[Pilha]  topo: %s (R$ %.2f)\n", topo.name, topo.price);
    Product removidoPilha;
    pop(&pilha, &removidoPilha);
    printf("[Pilha]  removido: %s | vazia: %d\n", removidoPilha.name, isEmpty(&pilha));

    /* --- Fila --- */
    LinkedQueue fila;
    initialize(&fila);
    Product p4 = {4, "Refrigerante", 6.50f};
    Product p5 = {5, "Suco",         7.00f};
    enqueue(&fila, p4);
    enqueue(&fila, p5);
    Product atendido;
    if (dequeue(&fila, &atendido))
        printf("[Fila]   atendido: %s (R$ %.2f)\n", atendido.name, atendido.price);
    printf("[Fila]   restantes: %d\n", size(&fila));

    /* --- AVL (stub) --- */
    AVL avl;
    initializeAVL(&avl);
    insertAVL(&avl, p1);
    destroyAVL(&avl);
    printf("[AVL]    stub ok\n");

    /* --- Hash (stub) --- */
    HashTable hash;
    initializeHash(&hash);
    insertHash(&hash, p2);
    destroyHash(&hash);
    printf("[Hash]   stub ok\n");

    /* --- Heap (stub) --- */
    Heap heap;
    initializeHeap(&heap);
    insertHeap(&heap, p3);
    destroyHeap(&heap);
    printf("[Heap]   stub ok\n");

    double elapsed = timerStop(&t);
    printf("[Timer]  %.6f s\n", elapsed);

    return 0;
}
