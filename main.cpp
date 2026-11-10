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
    
    Game game;
    int option = 0;
    char input_ingredient;

    game_init(&game);

    

    while (game.state != STATE_GAME_OVER) {
        switch (game.state) {

            case STATE_INIT_ORDER:
                //Mock values for testing
                list_insertAtEnd(&game.recipe, 'k'); // Ketchup 
                list_insertAtEnd(&game.recipe, 'a'); // Alface 
                list_insertAtEnd(&game.recipe, 'q'); // Queijo 
                list_insertAtEnd(&game.recipe, 'z'); // Pão de cima
                
                game.state = STATE_WAIT_ACTION;

                break;

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
                // TODO: Processar a remocao do ingrediente do topo
                break;

            case STATE_VALIDATE_ORDER:
                // TODO: Validar se a pilha do hamburguer bate com a receita
                break;

            case STATE_ORDER_SUCCESS:
                // TODO: Tratar sucesso da entrega e chamar proximo cliente
                break;

            case STATE_GAME_OVER:
                // TODO: Exibir tela de encerramento do jogo
                break;

            default:
                break;
        }
    }

    game_destroy(&game);
    return 0;
}