#include "game.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "avl.hpp"

void game_init(Game *g) {
    g->state = STATE_INIT_ORDER;
    stack_initialize(&g->burger);
    list_initialize(&g->recipe);
    g->current_turn = 0;
    g->current_patience = 0;
    g->served_customers = 0;
    g->is_running = true;
    g->root_avl = NULL;

    std::ifstream file("pedidos.txt");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    Recipe curr_recipe;
    std::string code_str;

    while (std::getline(file, code_str)) {
        curr_recipe.code = std::stoi(code_str);
        std::getline(file, curr_recipe.ingredients);
        g->root_avl = avlInserir(g->root_avl, curr_recipe);
    }

    file.close();

}

bool game_add_ingredient(Game *g, char ingredient) {
    if(stack_push(&g->burger, ingredient)){
        return true;
    }
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

void game_print_burguer(Game *g){
    if (stack_isEmpty(&g->burger) || (g->burger.top->next == nullptr && g->burger.top->ingredient == 'p')) {
        std::cout << "The burger has no added ingredients.\n";
        return;
    }

    Pilha aux_stack;
    stack_initialize(&aux_stack);
    stack_pop(&aux_stack);

    while(!stack_isEmpty(&g->burger)) {
        char ingredient = stack_pop(&g->burger);
        stack_push(&aux_stack, ingredient);
    }

    while(!stack_isEmpty(&aux_stack)) {
        char ingredient = stack_pop(&aux_stack);
        std::cout << ingredient << ' ';
        stack_push(&g->burger, ingredient);
    }

    std::cout << '\n';
}