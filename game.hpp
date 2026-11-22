#ifndef GAME_HPP
#define GAME_HPP

#include "pilha.hpp"
#include "lista.hpp"
#include "fila.hpp"
#include <string>

static const int MAX_PATIENCE       = 15;
static const int CUSTOMERS_PER_GAME = 5;
static const int MIN_ORDER_CODE     = 1;
static const int MAX_ORDER_CODE     = 837253;

typedef enum {
    STATE_INIT_ORDER,
    STATE_WAIT_ACTION,
    STATE_ADD_INGREDIENT,
    STATE_REMOVE_INGREDIENT,
    STATE_VALIDATE_ORDER,
    STATE_ORDER_SUCCESS,
    STATE_GAME_OVER
} GameState;

struct Recipe{
    int code;
    std::string ingredients;
};

struct NodoAvl;
struct HashTable;

struct Game {
    GameState state;
    Pilha burger;
    Lista recipe;
    int current_turn;
    int current_patience;
    int served_customers;
    bool is_running;
    Fila customers;
    NodoAvl *root_avl;
    HashTable *cache;
};

void game_init(Game* g, const char* pedidos_path, const char* historico_path);
void game_reset_order(Game* g);
bool game_add_ingredient(Game* g, char ingredient);
bool game_remove_ingredient(Game* g);
bool game_validate_order(Game* g);
bool game_consume_turn(Game* g);
void game_destroy(Game* g);
void game_print_recipe(Game* g);
void game_print_burguer(Game *g);
int game_generate_random_number(int min, int max);


#endif
