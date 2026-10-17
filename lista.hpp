#ifndef LISTA_HPP
#define LISTA_HPP

struct NodoLista { 
    NodoLista* next; 
    char ingredient;
};

struct Lista{
    NodoLista *head;
};

void list_initialize(Lista *list);
// void    print(const LinkedList *list);
// Product find(const LinkedList *list, int code);
// int     insertAtBeginning(LinkedList *list, Product product);
int list_insertAtEnd(Lista *list, char ingredient);
// int     removeByCode(LinkedList *list, int code);
void list_destroy(Lista *list);
// int     size(const LinkedList *list);

#endif
