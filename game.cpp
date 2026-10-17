#include "game.hpp"

void game_init(Game *g) {
    // g->state = STATE_INIT_ORDER;
    // stack_initialize(&g->burger);
    // list_initialize(&g->recipe);
    // g->current_turn = 0;
    // g->current_patience = 0;
    // g->served_customers = 0;
    // g->is_running = true;
}

bool game_add_ingredient(Game *g, char ingredient) {
    (void)g;
    (void)ingredient;
    return false;
}

bool game_remove_ingredient(Game *g) {
    (void)g;
    return false;
}

bool game_validate_order(Game *g) {
    (void)g;
    return false;
}

void game_destroy(Game *g) {
    list_destroy(&g->recipe);
    g->is_running = false;
}