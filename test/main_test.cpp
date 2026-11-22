// Test binary: forces customer order codes to match the spec example.
#include <iostream>
#include "../game.hpp"
#include "../avl.hpp"
#include "../hash.hpp"
#include "../fila.hpp"

using namespace std;

int main() {
    Game game;
    game_init(&game, "test/pedidos_test.txt", "test/historico_test.txt");

    // Override the random queue with fixed codes from the spec example.
    queue_destroy(&game.customers);
    queue_initialize(&game.customers);
    int codes[] = {1001, 1001}; // C1 and C2 both get 1001 (spec example)
    for (int i = 0; i < 2; i++) {
        Customer c;
        c.id = i + 1;
        c.order_code = codes[i];
        c.patience = MAX_PATIENCE;
        queue_enqueue(&game.customers, c);
    }

    int option = 0;
    char ing;

    while (game.state != STATE_GAME_OVER) {
        switch (game.state) {

            case STATE_INIT_ORDER: {
                Customer cur;
                if (!queue_front(&game.customers, &cur)) {
                    game.state = STATE_GAME_OVER;
                    break;
                }
                Recipe recipe{};
                bool hit = hashSearch(game.cache, cur.order_code, &recipe);
                if (!hit) {
                    NodoAvl *node = avlBuscar(game.root_avl, cur.order_code);
                    if (node) {
                        recipe = node->recipe;
                        hashInsert(game.cache, recipe);
                    }
                }
                cout << (hit ? "[CACHE HIT]" : "[CACHE MISS]")
                     << " Order " << cur.order_code
                     << ": " << recipe.ingredients << "\n";
                for (char c : recipe.ingredients)
                    list_insertAtEnd(&game.recipe, c);
                game.state = STATE_WAIT_ACTION;
                break;
            }

            case STATE_WAIT_ACTION: {
                Customer front;
                queue_front(&game.customers, &front);
                cout << "\n=== BURGUER DICE ===\n";
                cout << "Turn: " << game.current_turn
                     << " | Customer " << front.id
                     << " | Patience: " << front.patience << "\n";
                cout << "Recipe: ";
                NodoLista *n = game.recipe.head;
                while (n) { cout << n->ingredient; n = n->next; }
                cout << "\nBurger:  ";
                game_print_burguer(&game);
                cout << "1-Add  2-Remove  3-Validate  0-Quit\nOption: ";
                cin >> option;
                switch (option) {
                    case 1: game.state = STATE_ADD_INGREDIENT; break;
                    case 2: game.state = STATE_REMOVE_INGREDIENT; break;
                    case 3: game.state = STATE_VALIDATE_ORDER; break;
                    case 0: game.state = STATE_GAME_OVER; break;
                    default: cout << "Invalid.\n"; break;
                }
                break;
            }

            case STATE_ADD_INGREDIENT:
                cout << "Ingredient: ";
                cin >> ing;
                game_add_ingredient(&game, ing);
                if (!game_consume_turn(&game)) {
                    cout << "Patience reached zero! Game over.\n";
                    game.state = STATE_GAME_OVER;
                } else {
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_REMOVE_INGREDIENT:
                if (game_remove_ingredient(&game))
                    cout << "Removed.\n";
                else
                    cout << "Nothing to remove.\n";
                if (!game_consume_turn(&game)) {
                    cout << "Patience reached zero! Game over.\n";
                    game.state = STATE_GAME_OVER;
                } else {
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_VALIDATE_ORDER:
                if (game_validate_order(&game)) {
                    cout << "Valid! Order complete.\n";
                    game.state = STATE_ORDER_SUCCESS;
                } else {
                    cout << "Invalid order.\n";
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_ORDER_SUCCESS: {
                game.served_customers++;
                game_reset_order(&game);
                Customer done;
                queue_dequeue(&game.customers, &done);
                cout << "Customers served: " << game.served_customers << "\n";
                if (!queue_isEmpty(&game.customers))
                    game.state = STATE_INIT_ORDER;
                else {
                    cout << "You won! Score: " << game.served_customers << "\n";
                    game.state = STATE_GAME_OVER;
                }
                break;
            }

            case STATE_GAME_OVER:
                cout << "Game over. Score: " << game.served_customers << "\n";
                break;

            default: break;
        }
    }

    game_destroy(&game);
    return 0;
}
