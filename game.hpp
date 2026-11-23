#ifndef GAME_HPP
#define GAME_HPP

#include "pilha.hpp"
#include "lista.hpp"
#include "fila.hpp"
#include "heap.hpp"
#include <string>

static const int MAX_PATIENCE        = 15;
static const int CUSTOMERS_PER_GAME  = 5;
static const int MAX_LOADED_ORDERS   = 100000;
// Validity (in turns) of perishable ingredients after preparation.
static const int VALIDITY_MEAT       = 3;
static const int VALIDITY_EGG        = 2;
static const int VALIDITY_BACON      = 3;

typedef enum {
    STATE_INIT_ORDER,
    STATE_WAIT_ACTION,
    STATE_ADD_INGREDIENT,
    STATE_REMOVE_INGREDIENT,
    STATE_PREPARE_INGREDIENT,
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

    // Array of loaded order codes for random selection.
    int loaded_codes[MAX_LOADED_ORDERS];
    int loaded_codes_count;

    // Perishable stock (min-heap by expiry_turn).
    Heap stock_meat;    // 'n'
    Heap stock_egg;     // 'o'
    Heap stock_bacon;   // 'b'

    // Perene stock (simple counters).
    int stock_swiss;    // 's'
    int stock_cheddar;  // 'q'
    int stock_onion;    // 'c'
    int stock_tomato;   // 't'
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
void game_print_stock(Game *g);
bool game_prepare_ingredient(Game* g, char ingredient);
int  game_generate_random_number(int min, int max);


#endif
