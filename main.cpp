#include <cstdio>
#include <cstdlib>
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


int main() {

    Game game;
    int option = 0;
    char input_ingredient;

    game_init(&game);

    while (game.state != STATE_GAME_OVER) {
        switch (game.state) {

            case STATE_INIT_ORDER:
            
            list_initialize(&game.recipe);
            list_insertAtEnd(&game.recipe, 'k'); // Ketchup 
            list_insertAtEnd(&game.recipe, 'a'); // Alface 
            list_insertAtEnd(&game.recipe, 'q'); // Queijo 
            list_insertAtEnd(&game.recipe, 'z'); // Pão de cima

                break;

            case STATE_WAIT_ACTION:
                // TODO: Exibir o estado da bancada e ler a acao do jogador
                break;

            case STATE_ADD_INGREDIENT:
                // TODO: Processar a adicao de um ingrediente na pilha
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