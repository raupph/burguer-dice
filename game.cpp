#include "game.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "avl.hpp"
#include "hash.hpp"
#include <random>

static const int CUSTOMERS_PER_GAME = 3;

void game_init(Game *g, const char *pedidos_path, const char *historico_path) {
    (void)historico_path;

    g->state = STATE_INIT_ORDER;
    stack_initialize(&g->burger);
    list_initialize(&g->recipe);
    g->current_turn = 0;
    g->current_patience = 0;
    g->served_customers = 0;
    g->is_running = true;
    queue_initialize(&g->customers);
    g->root_avl = NULL;
    g->cache = new HashTable;
    initializeHash(g->cache);

    // Read orders from the pedidos file and store them in the AVL tree.
    std::ifstream file(pedidos_path);

    if (!file.is_open()) {
        std::cerr << "Error opening the pedidos file: "
                  << pedidos_path << std::endl;
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

    for (int i = 1; i <= CUSTOMERS_PER_GAME; i++) {
        Customer customer;
        customer.id = i;
        customer.order_code = game_generate_random_number(1, 837253);
        if (!queue_enqueue(&g->customers, customer)) {
            std::cerr << "Error adding customer " << customer.id
                      << " to the queue." << std::endl;
            break;
        }
    }
}

bool game_add_ingredient(Game *g, char ingredient) {
    if(stack_push(&g->burger, ingredient)){
        return true;
    }
    return false;
}

void game_reset_order(Game *g) {
    while (!stack_isEmpty(&g->burger)) {
        stack_pop(&g->burger);
    }
    stack_initialize(&g->burger);

    list_destroy(&g->recipe);
    list_initialize(&g->recipe);
}

bool game_remove_ingredient(Game *g) {
    if (stack_isEmpty(&g->burger) || (g->burger.top->ingredient == 'p' && g->burger.top->next == nullptr))
        return false;

    stack_pop(&g->burger);
    return true;
}

bool game_validate_order(Game *g) {
    Pilha to_compare;
    stack_initialize(&to_compare);
    stack_pop(&to_compare);

    /*
     * Moving the burger to the auxiliary stack reverses it.  Popping the
     * auxiliary stack therefore reads the burger from bottom to top.
     */
    while (!stack_isEmpty(&g->burger)) {
        stack_push(&to_compare, stack_pop(&g->burger));
    }

    bool valid = true;
    NodoLista *recipe_ingredient = g->recipe.head;

    while (!stack_isEmpty(&to_compare)) {
        char burger_ingredient = stack_pop(&to_compare);

        if (recipe_ingredient == nullptr ||
            burger_ingredient != recipe_ingredient->ingredient) {
            valid = false;
        } else {
            recipe_ingredient = recipe_ingredient->next;
        }

        /*
         * The ingredients are read from bottom to top, so pushing them
         * directly back reconstructs the original stack exactly.
         */
        stack_push(&g->burger, burger_ingredient);
    }

    if (recipe_ingredient != nullptr) {
        valid = false;
    }

    return valid;
}

void game_destroy(Game *g) {
    game_reset_order(g);
    queue_destroy(&g->customers);
    g->root_avl = avlDestruir(g->root_avl);
    destroyHash(g->cache);
    delete g->cache;
    g->cache = nullptr;
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

int game_generate_random_number(int min, int max) {
    // 'static' garante que o motor e a semente sejam inicializados APENAS UMA VEZ.
    // Isso evita gargalos de performance e garante uma distribuição perfeita.
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}