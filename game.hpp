#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include "pilha.hpp"
#include "lista.hpp"

typedef struct {
    int code;
    char name[50];
    float price;
} Product;

typedef enum {
    INIT_ORDER, 
    WAIT_ACTION, 
    ADD_INGREDIENT, 
    REMOVE_INGREDIENT, 
    VALIDATE_ORDER, 
    ORDER_SUCCESS,
    GAME_OVER
} GameState;

typedef struct{

    GameState state;
    LinkedStack burger;
    LinkedList recipe;

    int current_turn;
    int current_patience;
    int saved_costumers;
    bool is_running;

} Game;

void game_init(Game* g);
bool game_add_ingredient(Game* g, char ingredient);
bool game_remove_ingredient(Game* g);
bool game_validate_order(Game* g);
void game_destroy(Game* g);

#endif
