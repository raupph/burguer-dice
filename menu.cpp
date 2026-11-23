#include "menu.hpp"
#include "ordenacao.hpp"
#include "timer.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void show_how_to_play() {
    cout << "\n=== COMO JOGAR ===\n";
    cout << "Monte hamburgeres para " << CUSTOMERS_PER_GAME << " clientes antes que a paciencia deles acabe.\n";
    cout << "Cada acao (adicionar, remover, preparar) consome 1 turno.\n";
    cout << "A cada turno, a paciencia do cliente da frente diminui 1.\n\n";
    cout << "Ingredientes:\n";
    cout << "  Infinitos (sem preparo):    k Ketchup | m Mostarda | p Picles | a Alface | z Pao de cima\n";
    cout << "  Perenes  (preparar uma vez): s Queijo suico | q Cheddar | c Cebola | t Tomate\n";
    cout << "  Pereciveis (expiram):        n Carne (" << VALIDITY_MEAT  << " turnos)"
         <<                               " | o Ovo frito ("  << VALIDITY_EGG   << " turnos)"
         <<                               " | b Bacon (" << VALIDITY_BACON << " turnos)\n\n";
    cout << "Pressione Enter para voltar...\n";
    cin.ignore();
    cin.get();
}

void show_history(Game *game) {
    if(game->history.size == 0) {
        cout << "\nNenhuma partida registrada ainda.\n";
        return;
    }

    // Sort a copy so the original list and file are never modified.
    HistoryEntry *copy = (HistoryEntry *) malloc(game->history.size * sizeof(HistoryEntry));
    if(copy == nullptr){
        return;
    }

    for (int i = 0; i < game->history.size; i++){
        copy[i] = game->history.data[i];
    }

    cout << "\nOrdenar por:\n";
    cout << "1 - Pontuacao (decrescente)\n";
    cout << "2 - Nome (alfabetico)\n";
    cout << "Opcao: ";
    int opt;
    cin >> opt;

    Timer t;
    timer_iniciar(&t);

    switch (opt) {
        case 1:
            mergeSort(copy, game->history.size);
            break;
        case 2:
            quickSort(copy, game->history.size);
            break;
        default:
            mergeSort(copy, game->history.size);
            break;
    }

    double elapsed = timer_parar(&t);

    cout << "\n--- Historico (" << game->history.size << " entradas) ---\n";

    int limit = 20;
    if (game->history.size < 20){
        limit = game->history.size;
    }

    for(int i = 0; i < limit; i++) {
        cout << (i + 1) << ". " << copy[i].name << " - " << copy[i].score << "\n";
    }

    if(game->history.size > 20){
        cout << "... e mais " << (game->history.size - 20) << " entradas.\n";
    }

    cout << "Tempo de ordenacao: " << elapsed << " s\n";

    free(copy);
}

void show_menu(Game *game) {
    int option = 0;
    bool quit  = false;

    while(!quit) {
        cout << "\n=== DADO BURGER ===\n";
        cout << "1 - Novo jogo\n";
        cout << "2 - Como jogar\n";
        cout << "3 - Historico\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> option;

        switch (option) {
            case 1:
                quit = true;
                break;
            case 2:
                show_how_to_play();
                break;
            case 3:
                show_history(game);
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "Opcao invalida.\n";
                break;
        }
    }
}
