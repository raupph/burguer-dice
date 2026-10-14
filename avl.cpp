#include <stdlib.h>
#include "avl.hpp"

void initializeAVL(AVL *avl) {
    avl->root = nullptr;
}

int insertAVL(AVL *avl, Product product) {
    (void)avl;
    (void)product;
    return 0;
}

Product searchAVL(const AVL *avl, int code) {
    (void)avl;
    (void)code;
    Product empty = {0, "", 0.0f};
    return empty;
}

void destroyAVL(AVL *avl) {
    (void)avl;
}
