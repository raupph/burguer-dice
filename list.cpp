#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"

void initialize(LinkedList *list) {
    list->head = NULL;
}

int size(const LinkedList *list) {
    Node *current = list->head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void print(const LinkedList *list) {
    Node *current = list->head;

    while (current != NULL) {
        printf("Code: %d\n", current->data.code);
        printf("Name: %s\n", current->data.name);
        printf("Price: %f\n", current->data.price);
        current = current->next;
    }
}

Product find(const LinkedList *list, int code) {
    Node *current;
    Product product = {0, "", 0.0f};
    current = list->head;

    while (current != NULL) {
        if (current->data.code == code)
            return current->data;
        current = current->next;
    }

    return product; // not found: empty product
}

int insertAtBeginning(LinkedList *list, Product product) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL)
        return 0; // allocation failure

    newNode->data = product;
    newNode->next = list->head; // the new node points to the previous head
    list->head = newNode;        // the new node becomes the head

    return 1;
}

int insertAtEnd(LinkedList *list, Product product) {
    Node *newNode;
    Node *current;

    newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL)
        return 0;

    newNode->data = product;
    newNode->next = NULL;

    if (list->head == NULL) { // empty list: the new node is also the head
        list->head = newNode;
    } else {
        current = list->head;
        while (current->next != NULL) // walk to the last node
            current = current->next;
        current->next = newNode;
    }

    return 1;
}

int removeByCode(LinkedList *list, int code) {
    Node *previous;
    Node *current;

    previous = NULL;
    current = list->head;

    while (current != NULL && current->data.code != code) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) // not found
        return 0;

    if (previous == NULL) // removing the first node
        list->head = current->next;
    else                  // removing from the middle or the end
        previous->next = current->next;

    free(current);
    return 1;
}

void destroy(LinkedList *list) {
    Node *previous;
    Node *current;
    current = list->head;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }

    list->head = NULL;
}
