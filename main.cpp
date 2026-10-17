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

int main(int argc, char *argv[]) {

    Game game;
    int option = 0;
    char input_ingredient;

    game_init(&game);

    while (game.state != GAME_OVER) {
        switch (game.state) {

            case INIT_ORDER:
            
            while(game.recipe )

                break;

            case WAIT_ACTION:
                // TODO: Exibir o estado da bancada e ler a acao do jogador
                break;

            case ADD_INGREDIENT:
                // TODO: Processar a adicao de um ingrediente na pilha
                break;

            case REMOVE_INGREDIENT:
                // TODO: Processar a remocao do ingrediente do topo
                break;

            case VALIDATE_ORDER:
                // TODO: Validar se a pilha do hamburguer bate com a receita
                break;

            case ORDER_SUCCESS:
                // TODO: Tratar sucesso da entrega e chamar proximo cliente
                break;

            case GAME_OVER:
                // TODO: Exibir tela de encerramento do jogo
                break;

            default:
                break;
        }
    }

    game_destroy(&game);
    return 0;
}