#ifndef LISTA_HPP
#define LISTA_HPP

struct NodoLista { 
    NodoLista* next; 
    Product data;
};

struct LinkedList{
    NodoLista *head;
};

// void    initialize(LinkedList *list);
// void    print(const LinkedList *list);
// Product find(const LinkedList *list, int code);
// int     insertAtBeginning(LinkedList *list, Product product);
// int     insertAtEnd(LinkedList *list, Product product);
// int     removeByCode(LinkedList *list, int code);
// void    destroy(LinkedList *list);
// int     size(const LinkedList *list);

#endif
