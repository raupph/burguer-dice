#include "game.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "avl.hpp"
#include "hash.hpp"
#include "listacontigua.hpp"
#include <random>

void game_init(Game *g, const char *pedidos_path, const char *historico_path) {
    g->state            = STATE_INIT_ORDER;
    g->current_turn     = 0;
    g->current_patience = 0;
    g->served_customers = 0;
    g->is_running       = true;
    g->loaded_codes_count = 0;
    g->historico_path   = historico_path;
    g->loaded_codes     = new int[MAX_LOADED_ORDERS];

    lc_initialize(&g->history);
    lc_load(&g->history, historico_path);

    stack_initialize(&g->burger);
    list_initialize(&g->recipe);
    queue_initialize(&g->customers);

    g->root_avl = NULL;
    g->cache    = new HashTable;
    initializeHash(g->cache);

    // Perishable stock: one min-heap per ingredient type, all start empty.
    initializeHeap(&g->stock_meat);
    initializeHeap(&g->stock_egg);
    initializeHeap(&g->stock_bacon);

    // Perene stock: simple counters, start at zero.
    g->stock_swiss   = 0;
    g->stock_cheddar = 0;
    g->stock_onion   = 0;
    g->stock_tomato  = 0;

    // Load all orders from the pedidos file into the AVL tree.
    std::ifstream file(pedidos_path);
    if (!file.is_open()) {
        std::cerr << "Error opening the pedidos file: " << pedidos_path << std::endl;
        return;
    }

    Recipe curr_recipe;
    std::string code_str;

    while (std::getline(file, code_str)) {
        curr_recipe.code = std::stoi(code_str);
        std::getline(file, curr_recipe.ingredients);
        g->root_avl = avlInserir(g->root_avl, curr_recipe);
        if (g->loaded_codes_count < MAX_LOADED_ORDERS)
            g->loaded_codes[g->loaded_codes_count++] = curr_recipe.code;
    }

    file.close();

    // Enqueue customers, each assigned a random order from the loaded codes.
    for (int i = 1; i <= CUSTOMERS_PER_GAME; i++) {
        Customer customer;
        customer.id         = i;
        customer.patience   = MAX_PATIENCE;
        int idx             = game_generate_random_number(0, g->loaded_codes_count - 1);
        customer.order_code = g->loaded_codes[idx];

        if (!queue_enqueue(&g->customers, customer)) {
            std::cerr << "Error adding customer " << customer.id << " to the queue." << std::endl;
            break;
        }
    }
}

// Removes all units from a perishable heap whose expiry has passed.
// Called at the start of every turn, before the player acts (spec 4.7).
static void discard_expired(Heap *heap, int current_turn) {
    while (heap->size > 0 && heap->data[0].expiry_turn <= current_turn) {
        Product discarded;
        extractMin(heap, &discarded);
    }
}

// Advances the game by one turn. Discards expired perishables, then
// decrements the front customer's patience. Returns false when patience
// reaches zero (game over condition).
bool game_consume_turn(Game *g) {
    g->current_turn++;

    discard_expired(&g->stock_meat,  g->current_turn);
    discard_expired(&g->stock_egg,   g->current_turn);
    discard_expired(&g->stock_bacon, g->current_turn);

    if (g->customers.front == nullptr)
        return true;

    // Only the front customer loses patience while waiting (spec 3.3).
    g->customers.front->customer.patience--;
    g->current_patience = g->customers.front->customer.patience;

    return g->customers.front->customer.patience > 0;
}

// Checks stock before pushing the ingredient onto the burger stack.
// Infinite ingredients (k m p a z) always succeed.
// Perishables (n o b) consume the oldest unit from their heap.
// Perenes (s q c t) decrement their counter.
// Returns false if stock is empty or the ingredient is unknown.
bool game_add_ingredient(Game *g, char ingredient) {
    switch (ingredient) {
        case 'k':
        case 'm':
        case 'p':
        case 'a':
        case 'z':
            return stack_push(&g->burger, ingredient) != 0;

        case 'n':
            if (g->stock_meat.size == 0)
                return false;
            {
                Product p;
                extractMin(&g->stock_meat, &p);
            }
            return stack_push(&g->burger, ingredient) != 0;

        case 'o':
            if (g->stock_egg.size == 0)
                return false;
            {
                Product p;
                extractMin(&g->stock_egg, &p);
            }
            return stack_push(&g->burger, ingredient) != 0;

        case 'b':
            if (g->stock_bacon.size == 0)
                return false;
            {
                Product p;
                extractMin(&g->stock_bacon, &p);
            }
            return stack_push(&g->burger, ingredient) != 0;

        case 's':
            if (g->stock_swiss == 0)
                return false;
            g->stock_swiss--;
            return stack_push(&g->burger, ingredient) != 0;

        case 'q':
            if (g->stock_cheddar == 0)
                return false;
            g->stock_cheddar--;
            return stack_push(&g->burger, ingredient) != 0;

        case 'c':
            if (g->stock_onion == 0)
                return false;
            g->stock_onion--;
            return stack_push(&g->burger, ingredient) != 0;

        case 't':
            if (g->stock_tomato == 0)
                return false;
            g->stock_tomato--;
            return stack_push(&g->burger, ingredient) != 0;

        default:
            return false;
    }
}

// Clears the burger stack and recipe list, re-initializing both for the next order.
void game_reset_order(Game *g) {
    while (!stack_isEmpty(&g->burger))
        stack_pop(&g->burger);
    stack_initialize(&g->burger);

    list_destroy(&g->recipe);
    list_initialize(&g->recipe);
}

// Pops the top ingredient. The bottom bun ('B') is never removable.
bool game_remove_ingredient(Game *g) {
    if (stack_isEmpty(&g->burger))
        return false;
    if (g->burger.top->ingredient == 'B' && g->burger.top->next == nullptr)
        return false;

    stack_pop(&g->burger);
    return true;
}

// Compares the burger stack against the recipe list.
// The burger is reversed into an aux stack so we read bottom-to-top,
// then rebuilt in the original order while comparing.
// The bottom bun ('B') is skipped — it is not part of the recipe.
bool game_validate_order(Game *g) {
    Pilha to_compare;
    to_compare.top = nullptr;

    while (!stack_isEmpty(&g->burger))
        stack_push(&to_compare, stack_pop(&g->burger));

    bool valid = true;
    NodoLista *recipe_node = g->recipe.head;
    bool first = true;

    while (!stack_isEmpty(&to_compare)) {
        char ing = stack_pop(&to_compare);
        stack_push(&g->burger, ing);

        if (first) {
            first = false;
            continue; // skip bottom bun
        }

        if (recipe_node == nullptr || ing != recipe_node->ingredient)
            valid = false;
        else
            recipe_node = recipe_node->next;
    }

    // Recipe has more ingredients than the burger.
    if (recipe_node != nullptr)
        valid = false;

    return valid;
}

void game_destroy(Game *g) {
    game_reset_order(g);
    queue_destroy(&g->customers);
    g->root_avl = avlDestruir(g->root_avl);
    destroyHash(g->cache);
    delete g->cache;
    delete[] g->loaded_codes;
    lc_destroy(&g->history);
    g->cache        = nullptr;
    g->loaded_codes = nullptr;
    g->is_running   = false;
}

// Appends the game result to the history list and saves the full list to file.
void game_save_result(Game *g, const char *player_name) {
    lc_append(&g->history, player_name, g->served_customers);
    lc_save(&g->history, g->historico_path);
}

void game_print_recipe(Game *g) {
    NodoLista *current = g->recipe.head;
    while (current != nullptr) {
        std::cout << current->ingredient;
        current = current->next;
    }
    std::cout << '\n';
}

// Prints the burger contents from bottom to top, skipping the bottom bun.
// Uses an aux stack to reverse the order, then rebuilds the original stack.
void game_print_burguer(Game *g) {
    if (stack_isEmpty(&g->burger) ||
        (g->burger.top->next == nullptr && g->burger.top->ingredient == 'B')) {
        std::cout << "The burger has no added ingredients.\n";
        return;
    }

    Pilha aux;
    aux.top = nullptr;
    while (!stack_isEmpty(&g->burger))
        stack_push(&aux, stack_pop(&g->burger));

    bool first = true;
    while (!stack_isEmpty(&aux)) {
        char ing = stack_pop(&aux);
        stack_push(&g->burger, ing);
        if (first) {
            first = false;
            continue; // skip bottom bun
        }
        std::cout << ing << ' ';
    }
    std::cout << '\n';
}

// Adds one unit to stock. Perishables go into their min-heap with an expiry turn;
// perenes simply increment their counter.
bool game_prepare_ingredient(Game *g, char ingredient) {
    Product p;

    switch (ingredient) {
        case 'n':
            p.expiry_turn = g->current_turn + VALIDITY_MEAT;
            return insertHeap(&g->stock_meat, p) != 0;

        case 'o':
            p.expiry_turn = g->current_turn + VALIDITY_EGG;
            return insertHeap(&g->stock_egg, p) != 0;

        case 'b':
            p.expiry_turn = g->current_turn + VALIDITY_BACON;
            return insertHeap(&g->stock_bacon, p) != 0;

        case 's':
            g->stock_swiss++;
            return true;

        case 'q':
            g->stock_cheddar++;
            return true;

        case 'c':
            g->stock_onion++;
            return true;

        case 't':
            g->stock_tomato++;
            return true;

        default:
            return false;
    }
}

void game_print_stock(Game *g) {
    std::cout << "Stock:\n";
    std::cout << "  n (meat)     " << g->stock_meat.size  << "\n";
    std::cout << "  o (egg)      " << g->stock_egg.size   << "\n";
    std::cout << "  b (bacon)    " << g->stock_bacon.size << "\n";
    std::cout << "  s (swiss)    " << g->stock_swiss      << "\n";
    std::cout << "  q (cheddar)  " << g->stock_cheddar    << "\n";
    std::cout << "  c (onion)    " << g->stock_onion      << "\n";
    std::cout << "  t (tomato)   " << g->stock_tomato     << "\n";
}

int game_generate_random_number(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}
