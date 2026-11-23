# Dado Burger — Progress Summary

Spec: INF01203 – Estruturas de Dados, UFRGS, 2026/2 — Trabalho Prático Final

---

## Estruturas de Dados

| Estrutura | Papel no Jogo | Status | Observações |
|---|---|:---:|---|
| **AVL** | Armazenamento e busca de pedidos | ✅ Feito | Inserção, busca, remoção, rotações e destruição implementados. Receitas carregadas do arquivo na inicialização. |
| **Lista encadeada** | Receita do pedido atual | ✅ Feito | Cada nó armazena um ingrediente. |
| **Pilha** | Montagem do hambúrguer | ✅ Feito | Push/pop/isEmpty implementados. Pão de baixo (`B`) pré-inserido e nunca removível. |
| **Fila (FIFO)** | Clientes esperando atendimento | ✅ Feito | Enqueue/dequeue/front/isEmpty/size/destroy implementados e integrados. |
| **Tabela hash** | Cache de pedidos buscados | ✅ Básico | Encadeamento separado, hits/misses/colisões contados. Falta relatório no log. |
| **Heap mínimo** | Estoque de ingredientes perecíveis | ✅ Feito | Min-heap por ingrediente (`n`, `o`, `b`). Inserção com `expiry_turn = turno + validade`. Descarte automático no início de cada turno. |
| **Lista contígua** | Histórico de partidas | ✅ Feito | Alocação dinâmica com `realloc`. Carrega `historico.txt` na inicialização, appenda nova entrada ao encerrar e grava tudo de volta no arquivo. |
| **Splay Tree** | Extra opcional (comparação com AVL) | 🟡 Estrutura existe | Módulo presente mas não integrado ao jogo. |
| **Timer** | Medição de tempo | ✅ Corrigido | API corrigida para `timer_iniciar`/`timer_parar` conforme spec do professor. Usada em `show_history`. |

---

## Mecânicas do Jogo

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Leitura de pedidos via `argv[1]` | ✅ Feito | Carregado na AVL na inicialização. Suporta qualquer nome de arquivo. |
| Leitura de histórico via `argv[2]` | ✅ Feito | Carregado na lista contígua na inicialização. Se arquivo não existir, começa vazio. |
| Fluxo de estados do jogo | ✅ Feito | INIT_ORDER → WAIT_ACTION → ADD/REMOVE/PREPARE/VALIDATE → ORDER_SUCCESS → GAME_OVER. |
| Fila de clientes (FIFO) | ✅ Feito | `CUSTOMERS_PER_GAME` clientes enfileirados na inicialização; fila drena corretamente. |
| Seleção do código do pedido | ✅ Feito | Sorteio usa array `loaded_codes` preenchido durante leitura do arquivo — funciona com qualquer arquivo. |
| Busca com cache (hash → AVL) | ✅ Feito | Hit retorna da hash sem consultar a AVL; miss busca na AVL e insere na hash. |
| Validação do pedido (pilha vs lista) | ✅ Feito | Pilha invertida em auxiliar, pão de baixo (`B`) pulado, comparada com a lista da receita. |
| Turnos (cada ação consome 1 turno) | ✅ Feito | Add, remove e prepare chamam `game_consume_turn`. |
| Paciência do cliente (decremento por turno) | ✅ Feito | Paciência do cliente da frente decrementa a cada turno. |
| Derrota por paciência zerada | ✅ Feito | `game_consume_turn` retorna `false` quando paciência chega a 0. |
| Vitória ao atender todos os clientes | ✅ Feito | Detectada quando a fila fica vazia após `STATE_ORDER_SUCCESS`. |
| Exibição do pedido e hambúrguer | ✅ Feito | `game_print_recipe` e `game_print_burguer` chamadas no `STATE_WAIT_ACTION`. |
| Preparação de ingredientes | ✅ Feito | `game_prepare_ingredient` adiciona ao heap (perecível) ou incrementa contador (perene). Consome 1 turno. |
| Estoque de ingredientes | ✅ Feito | Sem estoque: `k m p a z`. Perenes com contador: `s q c t`. Perecíveis com heap: `n o b`. |
| Descarte automático de perecíveis vencidos | ✅ Feito | No início de cada turno, descarta itens com `expiry_turn <= current_turn`. |
| Exibição do estoque | ✅ Feito | `game_print_stock` exibe contagem de cada ingrediente. |

---

## Menu e Interface

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Menu principal | ✅ Feito | `show_menu` em `menu.cpp`. Opções: Novo jogo / Como jogar / Histórico / Sair. |
| Tela "Como jogar" | ✅ Feito | `show_how_to_play` em `menu.cpp`. Exibe ingredientes, regras e validades. |
| Histórico com ordenação | ✅ Feito | `show_history` em `menu.cpp`. Ordena cópia por pontuação (mergeSort) ou nome (quickSort). Exibe tempo de ordenação. |
| Salvar nova entrada no histórico ao encerrar | ✅ Feito | `game_save_result` appenda à lista e grava no arquivo. Nome pedido ao jogador. |
| Preservar entradas anteriores ao gravar | ✅ Feito | `lc_save` reescreve o arquivo completo — entradas anteriores preservadas. |

---

## Medições e Relatório de Desempenho (§5 da spec)

| Métrica | Status | Observações |
|---|:---:|---|
| Nós inseridos na AVL | ❌ Não coletado | Campo não existe na struct AVL. |
| Altura final da AVL | ❌ Não coletado | Função `avlAltura` existe mas não é chamada para log. |
| Rotações durante inserção na AVL | ❌ Não coletado | Contador não existe na struct. |
| Tempo de carregamento da AVL | ❌ Não coletado | Timer não chamado durante `game_init`. |
| Número de entradas carregadas no histórico | ❌ Não coletado | Valor existe em `game->history.size` mas não é logado. |
| Total de comparações nas buscas da AVL | ❌ Não coletado | Contador não existe. |
| Média de comparações por busca na AVL | ❌ Não coletado | — |
| Tempo total acumulado de buscas na AVL | ❌ Não coletado | — |
| Hits e misses da hash | 🟡 Contados | Campos `hits`/`misses` incrementados corretamente, mas não reportados. |
| Taxa de acerto da hash (%) | 🟡 Calculável | Dados disponíveis, falta cálculo e exibição. |
| Fator de carga da hash (λ = n/m) | 🟡 Calculável | `entries` e `size` existem, falta cálculo e exibição. |
| Total de colisões na hash | 🟡 Contado | Campo `collisions` incrementado, não reportado. |
| Tempo de execução da ordenação do histórico | 🟡 Medido | Medido em `show_history`, mas não gravado em `medicoes.log`. |
| Relatório de Desempenho na tela ao encerrar | ❌ Não implementado | Deve ser exibido automaticamente ao encerrar a partida. |
| Geração do arquivo `medicoes.log` | ❌ Não implementado | Obrigatório pela spec — criado (ou sobrescrito) a cada execução. |

---

## Compilação (Apêndice C da spec)

```
g++ -o dado_burger main.cpp avl.cpp hash.cpp heap.cpp pilha.cpp fila.cpp lista.cpp timer.cpp listacontigua.cpp ordenacao.cpp menu.cpp -Wall -std=c++17
./dado_burger pedidos.txt historico.txt
```

---

## Legenda

| Símbolo | Significado |
|:---:|---|
| ✅ | Implementado e funcional |
| 🟡 | Parcialmente implementado / estrutura existe mas incompleta |
| ❌ | Não implementado |

---

## Próximos passos

1. **Métricas da AVL**: adicionar contadores de nós inseridos, rotações e comparações na struct AVL; medir tempo de carregamento em `game_init`.
2. **Relatório de Desempenho**: exibir na tela e gravar em `medicoes.log` ao encerrar a partida (vitória, derrota ou saída voluntária).
3. **Testar e jogar**: compilar e rodar uma bateria de testes para validar o fluxo completo.
