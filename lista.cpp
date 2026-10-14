#include <stdio.h>
#include <stdlib.h>
#include "lista.hpp"

void initialize(LinkedList *list) {
    list->head = nullptr;
}

int size(const LinkedList *list) {
    NodoLista *current = list->head;
    int count = 0;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

void print(const LinkedList *list) {
    NodoLista *current = list->head;

    while (current != nullptr) {
        printf("Code: %d\n", current->data.code);
        printf("Name: %s\n", current->data.name);
        printf("Price: %f\n", current->data.price);
        current = current->next;
    }
}

Product find(const LinkedList *list, int code) {
    NodoLista *current;
    Product product = {0, "", 0.0f};
    current = list->head;

    while (current != nullptr) {
        if (current->data.code == code)
            return current->data;
        current = current->next;
    }

    return product; // not found: empty product
}

int insertAtBeginning(LinkedList *list, Product product) {
    NodoLista *newNode = (NodoLista*) malloc(sizeof(NodoLista));
    if (newNode == nullptr)
        return 0; // allocation failure

    newNode->data = product;
    newNode->next = list->head; // the new node points to the previous head
    list->head = newNode;        // the new node becomes the head

    return 1;
}

int insertAtEnd(LinkedList *list, Product product) {
    NodoLista *newNode;
    NodoLista *current;

    newNode = (NodoLista*) malloc(sizeof(NodoLista));
    if (newNode == nullptr)
        return 0;

    newNode->data = product;
    newNode->next = nullptr;

    if (list->head == nullptr) { // empty list: the new node is also the head
        list->head = newNode;
    } else {
        current = list->head;
        while (current->next != nullptr) // walk to the last node
            current = current->next;
        current->next = newNode;
    }

    return 1;
}

int removeByCode(LinkedList *list, int code) {
    NodoLista *previous;
    NodoLista *current;

    previous = nullptr;
    current = list->head;

    while (current != nullptr && current->data.code != code) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) // not found
        return 0;

    if (previous == nullptr) // removing the first node
        list->head = current->next;
    else                     // removing from the middle or the end
        previous->next = current->next;

    free(current);
    return 1;
}

void destroy(LinkedList *list) {
    NodoLista *previous;
    NodoLista *current;
    current = list->head;

    while (current != nullptr) {
        previous = current;
        current = current->next;
        free(previous);
    }

    list->head = nullptr;
}
