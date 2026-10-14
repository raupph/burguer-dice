#ifndef LIST_HPP
#define LIST_HPP

typedef struct {
    int code;
    char name[50];
    float price;
} Product;

typedef struct str_Node Node;

struct str_Node {
    Node *next;
    Product data;
};

typedef struct {
    Node *head;
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
