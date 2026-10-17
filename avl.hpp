#ifndef AVL_HPP
#define AVL_HPP

#include "product.hpp"

typedef struct str_NodoAVL NodoAVL;

struct str_NodoAVL {
    NodoAVL *left;
    NodoAVL *right;
    int      height;
    Product  data;
};

typedef struct {
    NodoAVL *root;
} AVL;

void    initializeAVL(AVL *avl);
int     insertAVL(AVL *avl, Product product);
Product searchAVL(const AVL *avl, int code);
void    destroyAVL(AVL *avl);

#endif
