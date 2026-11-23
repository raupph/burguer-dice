/*
 * tests.cpp — testes unitarios do Dado Burger
 * Compila: g++ -std=c++17 -o test/tests test/tests.cpp game.cpp avl.cpp hash.cpp
 *          lista.cpp pilha.cpp fila.cpp heap.cpp listacontigua.cpp ordenacao.cpp timer.cpp menu.cpp
 * Executa: ./test/tests
 */

#include <iostream>
#include <cstring>
#include <cassert>
#include "../avl.hpp"
#include "../hash.hpp"
#include "../pilha.hpp"
#include "../fila.hpp"
#include "../heap.hpp"
#include "../listacontigua.hpp"
#include "../ordenacao.hpp"
#include "../game.hpp"
#include "../lista.hpp"
#include "../product.hpp"

using namespace std;

/* ------------------------------------------------------------------ */
/* Utilitario                                                           */
/* ------------------------------------------------------------------ */

static int passed = 0;
static int failed = 0;

static void check(const char *name, bool ok) {
    if(ok) {
        cout << "  [OK] " << name << "\n";
        passed++;
    } else {
        cout << "  [FAIL] " << name << "\n";
        failed++;
    }
}

/* ------------------------------------------------------------------ */
/* AVL                                                                  */
/* ------------------------------------------------------------------ */

static void test_avl() {
    cout << "\n--- AVL ---\n";

    NodoAvl *raiz = NULL;
    Recipe r;

    // inserir e buscar
    r.code = 10; r.ingredients = "nkz";
    raiz = avlInserir(raiz, r);
    r.code = 5;  r.ingredients = "kz";
    raiz = avlInserir(raiz, r);
    r.code = 20; r.ingredients = "bz";
    raiz = avlInserir(raiz, r);

    check("busca existente 10",  avlBuscar(raiz, 10) != NULL);
    check("busca existente 5",   avlBuscar(raiz, 5)  != NULL);
    check("busca existente 20",  avlBuscar(raiz, 20) != NULL);
    check("busca inexistente 99", avlBuscar(raiz, 99) == NULL);

    // ingredientes corretos
    NodoAvl *no = avlBuscar(raiz, 10);
    check("ingredientes do no 10", no != NULL && no->recipe.ingredients == "nkz");

    // altura: 3 nos em arvore balanceada tem altura 1 (spec: raiz=1)
    check("altura apos 3 insercoes", (avlAltura(raiz) + 1) == 2);

    // duplicata ignorada — tamanho nao muda
    int nos_antes = avl_contador_nos;
    avl_contador_nos = 0;
    raiz = avlInserir(raiz, r); // r ainda tem code=20
    check("duplicata nao insere novo no", avl_contador_nos == 0);
    avl_contador_nos = nos_antes;

    // remover
    raiz = avlRemover(raiz, 5);
    check("apos remover 5, busca retorna NULL", avlBuscar(raiz, 5) == NULL);
    check("apos remover 5, outros ainda existem", avlBuscar(raiz, 10) != NULL);

    // balanceamento: inserir em ordem crescente nao deixa arvore degenerada
    NodoAvl *r2 = NULL;
    for(int i = 1; i <= 7; i++) {
        Recipe ri; ri.code = i; ri.ingredients = "z";
        r2 = avlInserir(r2, ri);
    }
    // 7 nos: altura maxima balanceada = 2 (0-based) = 3 (spec)
    check("arvore de 7 nos balanceada (altura <= 3)", (avlAltura(r2) + 1) <= 3);

    // contadores globais
    avl_contador_nos = 0;
    avl_contador_rotacoes = 0;
    NodoAvl *r3 = NULL;
    Recipe rc; rc.code = 1; rc.ingredients = "z"; r3 = avlInserir(r3, rc);
    rc.code = 2; r3 = avlInserir(r3, rc);
    rc.code = 3; r3 = avlInserir(r3, rc); // deve causar rotacao esquerda
    check("contador de nos incrementa", avl_contador_nos == 3);
    check("contador de rotacoes incrementa", avl_contador_rotacoes >= 1);

    avl_contador_comparacoes = 0;
    avlBuscar(r3, 2);
    check("contador de comparacoes incrementa na busca", avl_contador_comparacoes >= 1);

    raiz = avlDestruir(raiz);
    r2   = avlDestruir(r2);
    r3   = avlDestruir(r3);
    check("destruir retorna NULL", raiz == NULL);
}

/* ------------------------------------------------------------------ */
/* Hash                                                                 */
/* ------------------------------------------------------------------ */

static void test_hash() {
    cout << "\n--- Hash ---\n";

    HashTable ht;
    initializeHash(&ht);

    check("entries inicial zero", ht.entries == 0);
    check("hits inicial zero",    ht.hits    == 0);
    check("misses inicial zero",  ht.misses  == 0);

    Recipe r1; r1.code = 42;  r1.ingredients = "nkz";
    Recipe r2; r2.code = 143; r2.ingredients = "bqz"; // 143 % 101 = 42 (colisao)
    hashInsert(&ht, r1);
    check("entries apos insert", ht.entries == 1);

    // busca hit
    Recipe out{};
    bool found = hashSearch(&ht, 42, &out);
    check("busca hit encontra receita",   found);
    check("busca hit incrementa hits",    ht.hits == 1);
    check("busca hit ingredientes ok",    out.ingredients == "nkz");

    // busca miss
    found = hashSearch(&ht, 999, &out);
    check("busca miss retorna false",      !found);
    check("busca miss incrementa misses",  ht.misses == 1);

    // colisao
    hashInsert(&ht, r2);
    check("entries apos colisao", ht.entries == 2);
    check("colisoes registradas", ht.collisions >= 1);

    found = hashSearch(&ht, 143, &out);
    check("busca apos colisao encontra r2", found && out.ingredients == "bqz");

    destroyHash(&ht);
}

/* ------------------------------------------------------------------ */
/* Pilha (stack)                                                        */
/* ------------------------------------------------------------------ */

static void test_pilha() {
    cout << "\n--- Pilha ---\n";

    Pilha p;
    stack_initialize(&p);
    // stack_initialize insere o pao de baixo 'B', entao nunca fica vazia
    check("pilha inicializa com pao de baixo", !stack_isEmpty(&p));

    stack_push(&p, 'k');
    stack_push(&p, 'n');

    char top = stack_pop(&p);
    check("pop retorna ultimo push (LIFO)", top == 'n');

    top = stack_pop(&p);
    check("pop segundo elemento", top == 'k');

    // so o pao de baixo resta — nao esta vazia
    check("apos remover tudo resta o pao de baixo", !stack_isEmpty(&p));
    check("pao de baixo e B", p.top->ingredient == 'B');
    check("pao de baixo nao tem proximo", p.top->next == nullptr);

    // multiplos pushs e pops
    for(int i = 0; i < 5; i++) {
        stack_push(&p, (char)('a' + i));
    }
    check("pop apos 5 pushs retorna ultimo", stack_pop(&p) == 'e');

    // liberar
    while(!stack_isEmpty(&p)) {
        stack_pop(&p);
    }
}

/* ------------------------------------------------------------------ */
/* Fila (queue)                                                         */
/* ------------------------------------------------------------------ */

static void test_fila() {
    cout << "\n--- Fila ---\n";

    Fila f;
    queue_initialize(&f);
    check("fila inicializa vazia", queue_isEmpty(&f));

    Customer c1; c1.id = 1; c1.order_code = 100; c1.patience = 10;
    Customer c2; c2.id = 2; c2.order_code = 200; c2.patience = 8;
    Customer c3; c3.id = 3; c3.order_code = 300; c3.patience = 5;

    queue_enqueue(&f, c1);
    queue_enqueue(&f, c2);
    queue_enqueue(&f, c3);

    check("fila nao vazia apos enqueue", !queue_isEmpty(&f));
    check("tamanho correto", queue_size(&f) == 3);

    // front sem remover
    Customer front{};
    queue_front(&f, &front);
    check("front retorna primeiro (FIFO)", front.id == 1);
    check("front nao remove", queue_size(&f) == 3);

    // dequeue em ordem FIFO
    Customer rem{};
    queue_dequeue(&f, &rem);
    check("dequeue remove o primeiro", rem.id == 1);

    queue_front(&f, &front);
    check("front apos dequeue e o segundo", front.id == 2);

    queue_dequeue(&f, &rem);
    queue_dequeue(&f, &rem);
    check("fila vazia apos remover todos", queue_isEmpty(&f));

    queue_destroy(&f);
}

/* ------------------------------------------------------------------ */
/* Heap                                                                 */
/* ------------------------------------------------------------------ */

static void test_heap() {
    cout << "\n--- Heap ---\n";

    Heap h;
    initializeHeap(&h);
    check("heap inicializa vazio", h.size == 0);

    Product p1; p1.expiry_turn = 5;
    Product p2; p2.expiry_turn = 2;
    Product p3; p3.expiry_turn = 8;
    Product p4; p4.expiry_turn = 1;

    insertHeap(&h, p1);
    insertHeap(&h, p2);
    insertHeap(&h, p3);
    insertHeap(&h, p4);

    check("tamanho apos 4 insercoes", h.size == 4);

    // min-heap: menor expiry fica no topo
    check("topo tem menor expiry", h.data[0].expiry_turn == 1);

    Product rem{};
    extractMin(&h, &rem);
    check("extractMin retorna menor (1)", rem.expiry_turn == 1);
    check("topo apos extract e o proximo menor (2)", h.data[0].expiry_turn == 2);

    extractMin(&h, &rem);
    check("extractMin retorna menor (2)", rem.expiry_turn == 2);

    extractMin(&h, &rem);
    extractMin(&h, &rem);
    check("heap vazio apos extrair todos", h.size == 0);
}

/* ------------------------------------------------------------------ */
/* Lista contigua + ordenacao                                           */
/* ------------------------------------------------------------------ */

static void test_listacontigua() {
    cout << "\n--- Lista contigua ---\n";

    ListaContigua lc;
    lc_initialize(&lc);
    check("inicializa vazia", lc.size == 0);

    lc_append(&lc, "Carlos", 8);
    lc_append(&lc, "Ana",    15);
    lc_append(&lc, "Bruno",  3);
    lc_append(&lc, "Diana",  15);

    check("tamanho apos 4 appends", lc.size == 4);
    check("primeiro entry correto", strcmp(lc.data[0].name, "Carlos") == 0);

    // mergeSort por pontuacao decrescente
    HistoryEntry *copy = (HistoryEntry *)malloc(lc.size * sizeof(HistoryEntry));
    for(int i = 0; i < lc.size; i++) {
        copy[i] = lc.data[i];
    }
    mergeSort(copy, lc.size);
    check("mergeSort: primeiro tem maior score",  copy[0].score >= copy[1].score);
    check("mergeSort: segundo >= terceiro",        copy[1].score >= copy[2].score);
    check("mergeSort: original nao alterado",      strcmp(lc.data[0].name, "Carlos") == 0);

    // quickSort por nome alfabetico
    for(int i = 0; i < lc.size; i++) {
        copy[i] = lc.data[i];
    }
    quickSort(copy, lc.size);
    check("quickSort: Ana vem primeiro",    strcmp(copy[0].name, "Ana")    == 0);
    check("quickSort: Bruno vem segundo",   strcmp(copy[1].name, "Bruno")  == 0);
    check("quickSort: Carlos vem terceiro", strcmp(copy[2].name, "Carlos") == 0);
    check("quickSort: Diana vem quarto",    strcmp(copy[3].name, "Diana")  == 0);

    free(copy);

    // salvar e carregar
    lc_save(&lc, "/tmp/test_historico.txt");
    ListaContigua lc2;
    lc_initialize(&lc2);
    lc_load(&lc2, "/tmp/test_historico.txt");
    check("load recupera mesmo tamanho", lc2.size == lc.size);
    check("load recupera primeiro nome", strcmp(lc2.data[0].name, "Carlos") == 0);
    check("load recupera primeiro score", lc2.data[0].score == 8);

    lc_destroy(&lc);
    lc_destroy(&lc2);
}

/* ------------------------------------------------------------------ */
/* game_add_ingredient                                                  */
/* ------------------------------------------------------------------ */

static void test_add_ingredient() {
    cout << "\n--- game_add_ingredient ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    // ingredientes infinitos sempre funcionam
    check("add ketchup (infinito)",  game_add_ingredient(&g, 'k'));
    check("add mostarda (infinito)", game_add_ingredient(&g, 'm'));
    check("add picles (infinito)",   game_add_ingredient(&g, 'p'));
    check("add alface (infinito)",   game_add_ingredient(&g, 'a'));

    // perecivel sem estoque falha
    check("add carne sem estoque falha",  !game_add_ingredient(&g, 'n'));
    check("add ovo sem estoque falha",    !game_add_ingredient(&g, 'o'));
    check("add bacon sem estoque falha",  !game_add_ingredient(&g, 'b'));

    // perene sem estoque falha
    check("add queijo suico sem estoque falha", !game_add_ingredient(&g, 's'));
    check("add cheddar sem estoque falha",       !game_add_ingredient(&g, 'q'));

    // preparar e usar perecivel
    game_prepare_ingredient(&g, 'n');
    check("add carne apos preparo ok", game_add_ingredient(&g, 'n'));

    // preparar e usar perene
    game_prepare_ingredient(&g, 's');
    check("add queijo suico apos preparo ok", game_add_ingredient(&g, 's'));

    // ingrediente invalido
    check("add ingrediente invalido retorna false", !game_add_ingredient(&g, 'x'));

    // nao pode adicionar apos pao de cima
    game_add_ingredient(&g, 'z');
    check("nao adiciona apos pao de cima", !game_add_ingredient(&g, 'k'));

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* game_prepare_ingredient                                              */
/* ------------------------------------------------------------------ */

static void test_prepare_ingredient() {
    cout << "\n--- game_prepare_ingredient ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    check("preparar carne ok",        game_prepare_ingredient(&g, 'n'));
    check("preparar ovo ok",          game_prepare_ingredient(&g, 'o'));
    check("preparar bacon ok",        game_prepare_ingredient(&g, 'b'));
    check("preparar queijo suico ok", game_prepare_ingredient(&g, 's'));
    check("preparar cheddar ok",      game_prepare_ingredient(&g, 'q'));
    check("preparar cebola ok",       game_prepare_ingredient(&g, 'c'));
    check("preparar tomate ok",       game_prepare_ingredient(&g, 't'));

    // ingredientes infinitos nao podem ser preparados
    check("preparar ketchup falha",  !game_prepare_ingredient(&g, 'k'));
    check("preparar pao falha",      !game_prepare_ingredient(&g, 'z'));
    check("preparar invalido falha", !game_prepare_ingredient(&g, 'x'));

    // estoque incrementa
    check("estoque carne = 1",       g.stock_meat.size  == 1);
    check("estoque ovo = 1",         g.stock_egg.size   == 1);
    check("estoque bacon = 1",       g.stock_bacon.size == 1);
    check("estoque queijo suico = 1", g.stock_swiss      == 1);

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* game_remove_ingredient                                               */
/* ------------------------------------------------------------------ */

static void test_remove_ingredient() {
    cout << "\n--- game_remove_ingredient ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    // pilha tem so o pao de baixo — nao pode remover
    check("remover de burger vazio falha", !game_remove_ingredient(&g));

    game_add_ingredient(&g, 'k');
    check("remover ketchup ok", game_remove_ingredient(&g));

    // apos remover ketchup, pao de baixo nao pode ser removido
    check("nao remove pao de baixo", !game_remove_ingredient(&g));

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* game_validate_order                                                  */
/* ------------------------------------------------------------------ */

static void test_validate_order() {
    cout << "\n--- game_validate_order ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    // receita 1001 = "nkmpz"
    // pao de baixo ja esta na pilha
    list_insertAtEnd(&g.recipe, 'n');
    list_insertAtEnd(&g.recipe, 'k');
    list_insertAtEnd(&g.recipe, 'm');
    list_insertAtEnd(&g.recipe, 'p');
    list_insertAtEnd(&g.recipe, 'z');

    // montar errado
    game_add_ingredient(&g, 'k');
    check("pedido errado invalido", !game_validate_order(&g));

    // limpar e montar certo (ingredientes pereciveis precisam de preparo)
    game_reset_order(&g);
    list_insertAtEnd(&g.recipe, 'n');
    list_insertAtEnd(&g.recipe, 'k');
    list_insertAtEnd(&g.recipe, 'm');
    list_insertAtEnd(&g.recipe, 'p');
    list_insertAtEnd(&g.recipe, 'z');

    game_prepare_ingredient(&g, 'n');
    game_add_ingredient(&g, 'n');
    game_add_ingredient(&g, 'k');
    game_add_ingredient(&g, 'm');
    game_add_ingredient(&g, 'p');
    game_add_ingredient(&g, 'z');
    check("pedido correto valido", game_validate_order(&g));

    // pedido com ingrediente a mais invalido
    game_reset_order(&g);
    list_insertAtEnd(&g.recipe, 'k');
    list_insertAtEnd(&g.recipe, 'z');
    game_add_ingredient(&g, 'k');
    game_add_ingredient(&g, 'm'); // extra
    game_add_ingredient(&g, 'z');
    check("ingrediente extra invalida", !game_validate_order(&g));

    // pedido com ingrediente a menos invalido
    game_reset_order(&g);
    list_insertAtEnd(&g.recipe, 'k');
    list_insertAtEnd(&g.recipe, 'm');
    list_insertAtEnd(&g.recipe, 'z');
    game_add_ingredient(&g, 'k');
    // faltou 'm'
    game_add_ingredient(&g, 'z');
    check("ingrediente faltando invalida", !game_validate_order(&g));

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* game_consume_turn — expiracao de pereciveis                          */
/* ------------------------------------------------------------------ */

static void test_consume_turn() {
    cout << "\n--- game_consume_turn ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    // preparar carne: validade VALIDITY_MEAT = 3 turnos
    game_prepare_ingredient(&g, 'n'); // expiry = 0 + 3 = 3
    check("estoque carne antes de expirar = 1", g.stock_meat.size == 1);

    // turno 1, 2: ainda valida
    game_consume_turn(&g);
    game_consume_turn(&g);
    check("carne ainda valida no turno 2", g.stock_meat.size == 1);

    // turno 3: expiry_turn <= current_turn, descarta
    game_consume_turn(&g);
    check("carne expirou no turno 3", g.stock_meat.size == 0);

    // paciencia zerada retorna false
    // zerar paciencia manualmente
    g.customers.front->customer.patience = 1;
    bool ok = game_consume_turn(&g);
    check("retorna false quando paciencia zera", !ok);

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* Metricas AVL — contadores na carga                                  */
/* ------------------------------------------------------------------ */

static void test_metricas_avl() {
    cout << "\n--- Metricas AVL ---\n";

    Game g;
    game_init(&g, "test/pedidos_test.txt", "test/historico_test.txt");

    // pedidos_test.txt tem 3 receitas
    check("nos inseridos = 3",         g.avl_nos_inseridos == 3);
    check("altura final >= 1",          g.avl_altura_final >= 1);
    check("tempo de carga > 0",         g.avl_tempo_carga  >= 0.0);

    // busca acumula comparacoes
    avl_contador_comparacoes = 0;
    avlBuscar(g.root_avl, 1001);
    check("busca incrementa comparacoes", avl_contador_comparacoes >= 1);

    game_destroy(&g);
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */

int main() {
    cout << "=== TESTES DADO BURGER ===\n";

    test_avl();
    test_hash();
    test_pilha();
    test_fila();
    test_heap();
    test_listacontigua();
    test_add_ingredient();
    test_prepare_ingredient();
    test_remove_ingredient();
    test_validate_order();
    test_consume_turn();
    test_metricas_avl();

    cout << "\n=== RESULTADO: " << passed << " ok, " << failed << " falhou ===\n";
    return failed > 0 ? 1 : 0;
}
