#include "listacontigua.hpp"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>

void lc_initialize(ListaContigua *list) {
    list->size     = 0;
    list->capacity = 0;
    list->data     = nullptr;
}

// Adds an entry at the end. Doubles capacity when full (starts at 16).
void lc_append(ListaContigua *list, const char *name, int score) {
    if (list->size == list->capacity) {
        int new_capacity = (list->capacity == 0) ? 16 : list->capacity * 2;
        HistoryEntry *new_data = (HistoryEntry *) realloc(list->data, new_capacity * sizeof(HistoryEntry));
        if (new_data == nullptr)
            return;
        list->data     = new_data;
        list->capacity = new_capacity;
    }

    strncpy(list->data[list->size].name, name, HISTORY_NAME_MAX - 1);
    list->data[list->size].name[HISTORY_NAME_MAX - 1] = '\0';
    list->data[list->size].score = score;
    list->size++;
}

// Reads the history file into the list. Each entry is two lines: name then score.
// Returns false if the file cannot be opened (first run is not an error).
bool lc_load(ListaContigua *list, const char *path) {
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::string name_line;
    std::string score_line;

    while (std::getline(file, name_line)) {
        if (!std::getline(file, score_line))
            break;
        lc_append(list, name_line.c_str(), std::stoi(score_line));
    }

    return true;
}

// Writes the entire list back to the file, preserving all previous entries.
// The new entry must already be appended via lc_append before calling this.
bool lc_save(const ListaContigua *list, const char *path) {
    std::ofstream file(path);
    if (!file.is_open())
        return false;

    for (int i = 0; i < list->size; i++) {
        file << list->data[i].name  << '\n';
        file << list->data[i].score << '\n';
    }

    return true;
}

void lc_destroy(ListaContigua *list) {
    free(list->data);
    list->data     = nullptr;
    list->size     = 0;
    list->capacity = 0;
}
