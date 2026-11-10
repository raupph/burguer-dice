/* avl.h
 * Arvore AVL: BST com balanceamento automatico por rotacoes.
 * INF01203 - Estruturas de Dados - UFRGS
 */

#ifndef AVL_H
#define AVL_H
#include <string>
#include "game.hpp"

/* ------------------------------------------------------------------ */
/*  Estrutura de um nodo AVL                                            */
/* ------------------------------------------------------------------ */
typedef struct NodoAvl {
    Recipe recipe;
    int            altura;
    struct NodoAvl *esq;
    struct NodoAvl *dir;
} NodoAvl;

/* Altura e fator de balanceamento */
int      avlAltura(const NodoAvl *n);
int      avlFb(const NodoAvl *n);

/* Operacoes principais (retornam a nova raiz da subarvore) */
NodoAvl *avlBuscar(NodoAvl *raiz, int code);
NodoAvl *avlInserir(NodoAvl *raiz, Recipe r);
NodoAvl *avlRemover(NodoAvl *raiz, int code);
NodoAvl *avlDestruir(NodoAvl *raiz);

/* Caminhamento em-ordem (imprime em ordem crescente) */
void     avlEmOrdem(const NodoAvl *raiz);

#endif /* AVL_H */
