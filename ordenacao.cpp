#include "ordenacao.hpp"
#include <cstring>
#include <cstdlib>

// --- Merge Sort ---
// Codigo baseado no prof. Dennis Balreira (aula 21).

static void merge(HistoryEntry *a, HistoryEntry *aux, int ini, int meio, int fim) {
    int t, i, j, k;

    for (t = ini; t <= fim; t++)
        aux[t] = a[t];

    i = ini;
    j = meio + 1;
    k = ini;

    while (i <= meio && j <= fim) {
        if (aux[i].score >= aux[j].score)
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }
    while (i <= meio) a[k++] = aux[i++];
    while (j <= fim)  a[k++] = aux[j++];
}

static void mergeSortRec(HistoryEntry *a, HistoryEntry *aux, int ini, int fim) {
    if (ini >= fim) return;
    int meio = ini + (fim - ini) / 2;
    mergeSortRec(a, aux, ini, meio);
    mergeSortRec(a, aux, meio + 1, fim);
    merge(a, aux, ini, meio, fim);
}

void mergeSort(HistoryEntry *a, int n) {
    HistoryEntry *aux = (HistoryEntry *) malloc(n * sizeof(HistoryEntry));
    if (aux == nullptr) return;
    mergeSortRec(a, aux, 0, n - 1);
    free(aux);
}

// --- Quick Sort ---
// Codigo baseado no prof. Dennis Balreira (aula 21).

static void trocar(HistoryEntry *a, HistoryEntry *b) {
    HistoryEntry tmp = *a;
    *a = *b;
    *b = tmp;
}

static int particionar(HistoryEntry *a, int esq, int dir) {
    HistoryEntry *pivo = &a[dir];
    int i = esq - 1;

    for(int j = esq; j < dir; j++) {
        if(strcmp(a[j].name, pivo->name) <= 0) {
            i++;
            trocar(&a[i], &a[j]);
        }
    }
    trocar(&a[i + 1], &a[dir]);
    return i + 1;
}

static void quickSortAleatorio(HistoryEntry *a, int esq, int dir) {
    if (esq >= dir) return;

    int r = esq + rand() % (dir - esq + 1);
    trocar(&a[r], &a[dir]);

    int p = particionar(a, esq, dir);
    quickSortAleatorio(a, esq, p - 1);
    quickSortAleatorio(a, p + 1, dir);
}

void quickSort(HistoryEntry *a, int n) {
    if (n <= 1) return;
    quickSortAleatorio(a, 0, n - 1);
}
