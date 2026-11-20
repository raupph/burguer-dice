#ifndef HASH_HPP
#define HASH_HPP

#include "game.hpp"

#define HASH_SIZE 101

struct HashNode {
    HashNode *next;
    Recipe recipe;
};

struct HashTable {
    HashNode *buckets[HASH_SIZE];
    int size;
    int entries;
    int hits;
    int misses;
    int collisions;
};

void initializeHash(HashTable *table);
int hashInsert(HashTable *table, const Recipe& recipe);
bool hashSearch(HashTable *table, int code, Recipe *recipe);
void destroyHash(HashTable *table);

#endif
