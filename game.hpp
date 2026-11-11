#ifndef GAME_HPP
#define GAME_HPP

#include "pilha.hpp"
#include "lista.hpp"
#include "fila.hpp"
#include <string>

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

struct Game {
    GameState state;
    Pilha burger;
    Lista recipe;
    int current_turn;
    int current_patience;
    int served_customers;
    bool is_running;
    NodoAvl *root_avl;
};

void game_init(Game* g);
bool game_add_ingredient(Game* g, char ingredient);
bool game_remove_ingredient(Game* g);
bool game_validate_order(Game* g);
void game_destroy(Game* g);
void game_print_burguer(Game *g);
int game_generate_random_number(int min, int max);


#endif
