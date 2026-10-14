#include <stdlib.h>
#include "hash.hpp"

void initializeHash(HashTable *table) {
    for (int i = 0; i < HASH_SIZE; i++)
        table->buckets[i] = nullptr;
}

int insertHash(HashTable *table, Product product) {
    (void)table;
    (void)product;
    return 0;
}

Product searchHash(const HashTable *table, int code) {
    (void)table;
    (void)code;
    Product empty = {0, "", 0.0f};
    return empty;
}

void destroyHash(HashTable *table) {
    (void)table;
}
