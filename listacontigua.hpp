#ifndef LISTACONTIGUA_HPP
#define LISTACONTIGUA_HPP

#define HISTORY_NAME_MAX 21  // 20 chars + null terminator

struct HistoryEntry {
    char name[HISTORY_NAME_MAX];
    int  score;
};

struct ListaContigua {
    HistoryEntry *data;
    int           size;
    int           capacity;
};

void lc_initialize(ListaContigua *list);
void lc_append(ListaContigua *list, const char *name, int score);
bool lc_load(ListaContigua *list, const char *path);
bool lc_save(const ListaContigua *list, const char *path);
void lc_destroy(ListaContigua *list);

#endif
