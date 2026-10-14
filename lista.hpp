#ifndef LISTA_HPP
#define LISTA_HPP

#include "produto.hpp"

typedef struct str_NodoLista NodoLista;

struct str_NodoLista {
    NodoLista *next;
    Product    data;
};

typedef struct {
    NodoLista *head;
} LinkedList;

void    initialize(LinkedList *list);
void    print(const LinkedList *list);
Product find(const LinkedList *list, int code);
int     insertAtBeginning(LinkedList *list, Product product);
int     insertAtEnd(LinkedList *list, Product product);
int     removeByCode(LinkedList *list, int code);
void    destroy(LinkedList *list);
int     size(const LinkedList *list);

#endif
