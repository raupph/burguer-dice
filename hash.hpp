#ifndef HASH_HPP
#define HASH_HPP

#include "game.hpp"

#define HASH_SIZE 100

typedef struct str_NodoHash NodoHash;

struct str_NodoHash {
    NodoHash *next;
    Product   data;
};

typedef struct {
    NodoHash *buckets[HASH_SIZE];
} HashTable;

void    initializeHash(HashTable *table);
int     insertHash(HashTable *table, Product product);
Product searchHash(const HashTable *table, int code);
void    destroyHash(HashTable *table);

#endif
