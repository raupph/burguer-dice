#include <new>
#include "hash.hpp"
#include "hash_algorithms.hpp"

/*
 * Adapted from the professor's hashDivisao function.
 * The cache uses separate chaining, as in TabelaEnc.
 */
static int hashDivision(int key, int table_size) {
    return hashDivisao(key, table_size);
}

void initializeHash(HashTable *table) {
    table->size = HASH_SIZE;

    for (int i = 0; i < table->size; i++) {
        table->buckets[i] = nullptr;
    }

    table->entries = 0;
    table->hits = 0;
    table->misses = 0;
    table->collisions = 0;
}

int hashInsert(HashTable *table, const Recipe& recipe) {
    int index = hashDivision(recipe.code, table->size);
    HashNode *current = table->buckets[index];

    if (current != nullptr) {
        table->collisions++;
    }

    while (current != nullptr) {
        if (current->recipe.code == recipe.code) {
            current->recipe = recipe;
            return 1;
        }
        current = current->next;
    }

    HashNode *newNode = new (std::nothrow) HashNode;
    if (newNode == nullptr) {
        return 0;
    }

    newNode->recipe = recipe;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->entries++;
    return 1;
}

bool hashSearch(HashTable *table, int code, Recipe *recipe) {
    int index = hashDivision(code, table->size);
    HashNode *current = table->buckets[index];

    while (current != nullptr) {
        if (current->recipe.code == code) {
            *recipe = current->recipe;
            table->hits++;
            return true;
        }
        current = current->next;
    }

    table->misses++;
    return false;
}

void destroyHash(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        HashNode *current = table->buckets[i];
        while (current != nullptr) {
            HashNode *next = current->next;
            delete current;
            current = next;
        }
        table->buckets[i] = nullptr;
    }

    table->size = 0;
    table->entries = 0;
}
