#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "lista.hpp"
#include "pilha.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "lista.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //* Require both input file paths.
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <pedidos> <historico>\n";
        return 1;
    }
    
    Game game;
    int option = 0;
    char input_ingredient;

    //* Initialize the game and load its data.
    game_init(&game, argv[1], argv[2]);

    //* Process the game state machine.
    while (game.state != STATE_GAME_OVER) {
        switch (game.state) {

            case STATE_INIT_ORDER: {
                //* Get the current customer from the queue.
                Customer current_customer;
                if (!queue_front(&game.customers, &current_customer)) {
                    //* No customers remain.
                    game.state = STATE_GAME_OVER;
                    break;
                }

                //* Check the cache before searching the AVL.
                Recipe selected_recipe{};
                bool cache_hit = hashSearch(game.cache,
                                            current_customer.order_code,
                                            &selected_recipe);
                bool recipe_found = cache_hit;

                if (!cache_hit) {
                    //* Search the AVL on a cache miss.
                    NodoAvl *auxNode = avlBuscar(game.root_avl,
                                                 current_customer.order_code);
                    if (auxNode != nullptr) {
                        //* Copy and cache the found recipe.
                        selected_recipe = auxNode->recipe;
                        recipe_found = true;

                        if (!hashInsert(game.cache, selected_recipe)) {
                            cout << "Error inserting the order into the cache.\n";
                        }
                    }
                }

                //* Load the found recipe into the linked list.
                if (recipe_found) {
                    for (char c : selected_recipe.ingredients) {
                        list_insertAtEnd(&game.recipe, c);
                    }
                }

                game.state = STATE_WAIT_ACTION;
                break;
            }

            case STATE_WAIT_ACTION:
                cout << "\n=== BURGUER DICE ===\n";
                cout << "Choose an action:\n";
                cout << "1 - Add ingredient\n";
                cout << "2 - Remove ingredient\n";
                cout << "3 - Validate order\n";
                cout << "0 - Exit game\n";
                cout << "Option: ";
                cin >> option;

                switch (option) {
                    case 1:
                        game.state = STATE_ADD_INGREDIENT;
                        break;
                    case 2:
                        game.state = STATE_REMOVE_INGREDIENT;
                        break;
                    case 3:
                        game.state = STATE_VALIDATE_ORDER;
                        break;
                    case 0:
                        game.state = STATE_GAME_OVER;
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                break;

            case STATE_ADD_INGREDIENT:
                cout << "\nCurrent burger ingredients:\n";
                game_print_burguer(&game);

                cout << "\nEnter the ingredient to add:\n";
                cout << "k - Ketchup\n";
                cout << "a - Lettuce\n";
                cout << "q - Cheese\n";
                cout << "z - Top bun\n";
                cout << "Ingredient: ";
                cin >> input_ingredient;
                
                game_add_ingredient(&game, input_ingredient);
                game.state = STATE_WAIT_ACTION;
                break;

            case STATE_REMOVE_INGREDIENT:
                cout << "\nCurrent burger ingredients:\n";
                game_print_burguer(&game);

                if (game_remove_ingredient(&game)) {
                    cout << "Ingredient removed successfully.\n";
                } else {
                    cout << "No ingredients to remove.\n";
                }

                game.state = STATE_WAIT_ACTION;
                break;

            case STATE_VALIDATE_ORDER:
                //* Validate the burger against the recipe.
                if (game_validate_order(&game)) {
                    cout << "Order is valid. Completing order...\n";
                    game.state = STATE_ORDER_SUCCESS;
                } else {
                    cout << "Order is invalid.\n";
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_ORDER_SUCCESS:
                //* Complete the order and remove its customer.
                game.served_customers++;
                cout << "Order completed successfully.\n";
                cout << "Customers served: " << game.served_customers
                     << "/" << queue_size(&game.customers) + game.served_customers
                     << "\n";

                game_reset_order(&game);
                Customer completed_customer;
                queue_dequeue(&game.customers, &completed_customer);

                if (!queue_isEmpty(&game.customers)) {
                    game.state = STATE_INIT_ORDER;
                } else {
                    cout << "All customers were served. You won!\n";
                    cout << "Final score: " << game.served_customers << "\n";
                    game.state = STATE_GAME_OVER;
                }
                break;

            case STATE_GAME_OVER:
                cout << "Game over. Final score: "
                     << game.served_customers << "\n";
                break;

            default:
                break;
        }
    }

    game_destroy(&game);
    return 0;
}