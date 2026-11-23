#include <cstdlib>
#include <iostream>
#include "lista.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "hash.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "timer.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << " <pedidos> <historico>\n";
        return 1;
    }

    Game game;
    game_init(&game, argv[1], argv[2]);

    int option = 0;
    char input_ingredient;

    show_menu(&game);

    bool running = true;
    while(running) {
        switch(game.state) {

            case STATE_INIT_ORDER: {
                Customer current_customer;
                if(!queue_front(&game.customers, &current_customer)) {
                    game.state = STATE_GAME_OVER;
                    break;
                }

                Recipe selected_recipe{};
                bool cache_hit = hashSearch(game.cache, current_customer.order_code, &selected_recipe);
                bool recipe_found = cache_hit;

                if(!cache_hit) {
                    avl_contador_comparacoes = 0;
                    Timer search_timer;
                    timer_iniciar(&search_timer);

                    NodoAvl *auxNode = avlBuscar(game.root_avl, current_customer.order_code);

                    game.avl_tempo_buscas      += timer_parar(&search_timer);
                    game.avl_total_buscas++;
                    game.avl_total_comparacoes += avl_contador_comparacoes;

                    if(auxNode != nullptr) {
                        selected_recipe = auxNode->recipe;
                        recipe_found = true;

                        if(!hashInsert(game.cache, selected_recipe)) {
                            cout << "Erro ao inserir pedido no cache.\n";
                        }
                    }
                }

                if(recipe_found) {
                    for(char c : selected_recipe.ingredients) {
                        list_insertAtEnd(&game.recipe, c);
                    }
                }

                game.state = STATE_WAIT_ACTION;
                break;
            }

            case STATE_WAIT_ACTION: {
                Customer front;
                queue_front(&game.customers, &front);

                cout << "\n=== DADO BURGER ===\n";
                cout << "Turno: " << game.current_turn
                     << " | Cliente " << front.id
                     << " | Paciencia: " << front.patience << "\n";
                cout << "Pedido:    ";
                game_print_recipe(&game);
                cout << "Hamburguer: ";
                game_print_burguer(&game);
                game_print_stock(&game);
                cout << "Escolha uma acao:\n";
                cout << "1 - Adicionar ingrediente\n";
                cout << "2 - Remover ingrediente do topo\n";
                cout << "3 - Validar pedido\n";
                cout << "4 - Preparar ingrediente\n";
                cout << "0 - Sair do jogo\n";
                cout << "Opcao: ";
                cin >> option;

                switch(option) {
                    case 1:
                        game.state = STATE_ADD_INGREDIENT;
                        break;
                    case 2:
                        game.state = STATE_REMOVE_INGREDIENT;
                        break;
                    case 3:
                        game.state = STATE_VALIDATE_ORDER;
                        break;
                    case 4:
                        game.state = STATE_PREPARE_INGREDIENT;
                        break;
                    case 0:
                        game.state = STATE_GAME_OVER;
                        break;
                    default:
                        cout << "Opcao invalida.\n";
                        break;
                }
                break;
            }

            case STATE_ADD_INGREDIENT:
                cout << "\nHamburguer atual:\n";
                game_print_burguer(&game);

                cout << "\nDigite o ingrediente a adicionar:\n";
                cout << "k - Ketchup | m - Mostarda | p - Picles | a - Alface\n";
                cout << "s - Queijo suico | q - Cheddar | c - Cebola | t - Tomate\n";
                cout << "n - Carne | o - Ovo frito | b - Bacon | z - Pao de cima\n";
                cout << "Ingrediente: ";
                cin >> input_ingredient;

                if(!game_add_ingredient(&game, input_ingredient)) {
                    cout << "Sem estoque desse ingrediente.\n";
                    game.state = STATE_WAIT_ACTION;
                    break;
                }

                if(!game_consume_turn(&game)) {
                    cout << "O cliente perdeu a paciencia! Fim de jogo.\n";
                    game.state = STATE_GAME_OVER;
                } else {
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_REMOVE_INGREDIENT:
                cout << "\nHamburguer atual:\n";
                game_print_burguer(&game);

                if(game_remove_ingredient(&game)) {
                    cout << "Ingrediente removido.\n";
                } else {
                    cout << "Nada para remover.\n";
                }

                if(!game_consume_turn(&game)) {
                    cout << "O cliente perdeu a paciencia! Fim de jogo.\n";
                    game.state = STATE_GAME_OVER;
                } else {
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_PREPARE_INGREDIENT: {
                cout << "\nQual ingrediente deseja preparar?\n";
                cout << "n - Carne | o - Ovo frito | b - Bacon\n";
                cout << "s - Queijo suico | q - Cheddar | c - Cebola | t - Tomate\n";
                cout << "Ingrediente: ";
                cin >> input_ingredient;

                if(!game_prepare_ingredient(&game, input_ingredient)) {
                    cout << "Ingrediente invalido para preparar.\n";
                    game.state = STATE_WAIT_ACTION;
                    break;
                }
                cout << "Ingrediente preparado.\n";

                if(!game_consume_turn(&game)) {
                    cout << "O cliente perdeu a paciencia! Fim de jogo.\n";
                    game.state = STATE_GAME_OVER;
                } else {
                    game.state = STATE_WAIT_ACTION;
                }
                break;
            }

            case STATE_VALIDATE_ORDER:
                if(game_validate_order(&game)) {
                    cout << "Pedido correto! Concluindo atendimento...\n";
                    game.state = STATE_ORDER_SUCCESS;
                } else {
                    cout << "Pedido incorreto.\n";
                    game.state = STATE_WAIT_ACTION;
                }
                break;

            case STATE_ORDER_SUCCESS:
                game.served_customers++;
                cout << "Pedido concluido com sucesso!\n";
                cout << "Clientes atendidos: " << game.served_customers
                     << "/" << CUSTOMERS_PER_GAME << "\n";

                game_reset_order(&game);
                Customer completed_customer;
                queue_dequeue(&game.customers, &completed_customer);

                if(!queue_isEmpty(&game.customers)) {
                    game.state = STATE_INIT_ORDER;
                } else {
                    cout << "Todos os clientes foram atendidos. Voce venceu!\n";
                    cout << "Pontuacao final: " << game.served_customers << "\n";
                    game.state = STATE_GAME_OVER;
                }
                break;

            case STATE_GAME_OVER: {
                cout << "Fim de jogo. Pontuacao final: " << game.served_customers << "\n";

                cout << "Digite seu nome: ";
                string player_name;
                cin >> player_name;
                game_save_result(&game, player_name.c_str());

                game_print_report(&game);
                game_save_log(&game, player_name.c_str());

                cout << "Resultado salvo. Log gravado em medicoes.log\n";
                running = false;
                break;
            }

            default:
                break;
        }
    }

    game_destroy(&game);
    return 0;
}
