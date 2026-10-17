#ifndef LISTA_HPP
#define LISTA_HPP

struct NodoLista { 
    NodoLista* next; 
    char ingredient;
};

struct LinkedList{
    NodoLista *head;
};

void list_initialize(LinkedList *list);
// void    print(const LinkedList *list);
// Product find(const LinkedList *list, int code);
// int     insertAtBeginning(LinkedList *list, Product product);
int list_insertAtEnd(LinkedList *list, char ingredient);
// int     removeByCode(LinkedList *list, int code);
void list_destroy(LinkedList *list);
// int     size(const LinkedList *list);

#endif
