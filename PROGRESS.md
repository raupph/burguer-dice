# Dado Burger — Progress Summary

Spec: INF01203 – Estruturas de Dados, UFRGS, 2026/2 — Trabalho Prático Final

---

## Estruturas de Dados

| Estrutura | Papel no Jogo | Status | Observações |
|---|---|:---:|---|
| **AVL** | Armazenamento e busca de pedidos | ✅ Feito | Inserção, busca, remoção, rotações e destruição implementados. Receitas carregadas do arquivo na inicialização. |
| **Lista encadeada** | Receita do pedido atual | ✅ Feito | Cada nó armazena um ingrediente. Sem `p` implícito — representa só os ingredientes do arquivo. |
| **Pilha** | Montagem do hambúrguer | ✅ Feito | Push/pop/isEmpty implementados. Pão de baixo (`B`) pré-inserido e nunca removível. Fix: `p` era confundido com picles. |
| **Fila (FIFO)** | Clientes esperando atendimento | ✅ Feito | Enqueue/dequeue/front/isEmpty/size/destroy implementados e integrados. `Customer` definido em `fila.hpp`. |
| **Tabela hash** | Cache de pedidos buscados | ✅ Básico | Encadeamento separado, hits/misses/colisões contados. Falta relatório de fator de carga e taxa de acerto no log. |
| **Heap mínimo** | Estoque de ingredientes perecíveis | ✅ Feito | Min-heap por ingrediente (`n`, `o`, `b`). Inserção com `expiry_turn = turno + validade`. Descarte automático no início de cada turno. `extractMin` consome a unidade mais velha. |
| **Lista contígua** | Histórico de partidas | ✅ Feito | Alocação dinâmica com `realloc`. Carrega `historico.txt` na inicialização, appenda nova entrada ao encerrar e grava tudo de volta no arquivo. |
| **Splay Tree** | Extra opcional (comparação com AVL) | 🟡 Estrutura existe | Módulo presente mas armazena só `int`, não `Recipe`. Não integrado ao jogo. |
| **Timer** | Medição de tempo | 🟡 Estrutura existe | Arquivos `timer.cpp/hpp` presentes e corretos. Nenhuma medição está sendo feita ainda. |

---

## Mecânicas do Jogo

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Leitura de pedidos via `argv[1]` | ✅ Feito | Carregado na AVL na inicialização. Suporta qualquer nome de arquivo. |
| Leitura de histórico via `argv[2]` | ✅ Feito | Carregado na lista contígua na inicialização. Se arquivo não existir (primeira execução), começa vazio. |
| Fluxo de estados do jogo | ✅ Feito | INIT_ORDER → WAIT_ACTION → ADD/REMOVE/VALIDATE → ORDER_SUCCESS → GAME_OVER. |
| Fila de clientes (FIFO) | ✅ Feito | `CUSTOMERS_PER_GAME` clientes enfileirados na inicialização; fila drena corretamente. |
| Seleção do código do pedido | ✅ Feito | Sorteio usa `MIN_ORDER_CODE`/`MAX_ORDER_CODE` — constantes ajustáveis em `game.hpp`. |
| Busca com cache (hash → AVL) | ✅ Feito | Hit retorna da hash sem consultar a AVL; miss busca na AVL e insere na hash. |
| Validação do pedido (pilha vs lista) | ✅ Feito | Pilha invertida em auxiliar, pão de baixo (`B`) pulado, comparada com a lista da receita, reconstruída ao final. |
| Turnos (cada ação consome 1 turno) | ✅ Feito | Add e remove chamam `game_consume_turn`. Validate e consultas não consomem turno. |
| Paciência do cliente (decremento por turno) | ✅ Feito | Paciência do cliente da frente decrementa a cada turno. Clientes na fila não são afetados. |
| Derrota por paciência zerada | ✅ Feito | `game_consume_turn` retorna `false` quando paciência chega a 0; jogo vai para `STATE_GAME_OVER`. |
| Vitória ao atender todos os clientes | ✅ Feito | Detectada quando a fila fica vazia após `STATE_ORDER_SUCCESS`. |
| Exibição do pedido e hambúrguer | ✅ Feito | `game_print_recipe` e `game_print_burguer` chamadas no `STATE_WAIT_ACTION`. Pão de baixo não aparece na exibição. |
| Preparação de ingredientes (ação separada) | ✅ Feito | `game_prepare_ingredient` adiciona ao heap (perecível) ou incrementa contador (perene). Opção 4 no menu. Consome 1 turno. |
| Estoque de ingredientes (infinito / perene / perecível) | ✅ Feito | Sem estoque: `k m p a z`. Perenes com contador: `s q c t`. Perecíveis com heap: `n o b`. `game_add_ingredient` verifica estoque antes de empilhar. |
| Descarte automático de perecíveis vencidos | ✅ Feito | No início de cada turno, `game_consume_turn` descarta itens com `expiry_turn < current_turn` de cada heap. |
| Exibição do estoque | ✅ Feito | `game_print_stock` exibe contagem de cada ingrediente no `STATE_WAIT_ACTION`. |

---

## Menu e Interface

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Menu principal (Novo jogo / Como jogar / Histórico) | ❌ Não implementado | Programa entra direto no loop de jogo. |
| Tela "Como jogar" | ❌ Não implementado | — |
| Histórico com ordenação (alfabética / pontuação desc.) | ❌ Não implementado | Depende da lista contígua. |
| Salvar nova entrada no histórico ao encerrar partida | ✅ Feito | `game_save_result` appenda à lista e grava tudo no arquivo. Nome pedido ao jogador ao encerrar. |
| Preservar entradas anteriores ao gravar histórico | ✅ Feito | `lc_save` reescreve o arquivo completo — entradas anteriores são preservadas. |

---

## Medições e Relatório de Desempenho

| Métrica | Status | Observações |
|---|:---:|---|
| Nós inseridos na AVL | ❌ Não coletado | — |
| Altura final da AVL | ❌ Não coletado | Função `avlAltura` existe mas não é chamada para log. |
| Rotações durante inserção na AVL | ❌ Não coletado | Contador não existe na struct. |
| Tempo de carregamento da AVL | ❌ Não coletado | Timer não chamado. |
| Número de entradas carregadas no histórico | ❌ Não coletado | Histórico ainda não carregado. |
| Total de comparações nas buscas da AVL | ❌ Não coletado | Contador não existe. |
| Média de comparações por busca na AVL | ❌ Não coletado | — |
| Tempo total acumulado de buscas na AVL | ❌ Não coletado | Timer não chamado. |
| Hits e misses da hash | 🟡 Contados | Campos `hits`/`misses` incrementados corretamente, mas não reportados em log. |
| Taxa de acerto da hash (%) | 🟡 Calculável | Dados disponíveis, falta cálculo e exibição. |
| Fator de carga da hash (λ = n/m) | 🟡 Calculável | `entries` e `size` existem, falta cálculo e exibição. |
| Total de colisões na hash | 🟡 Contado | Campo `collisions` incrementado, não reportado. |
| Tempo de execução da ordenação do histórico | ❌ Não coletado | Ordenação e histórico não implementados. |
| Geração do arquivo `medicoes.log` | ❌ Não implementado | Arquivo não é criado nem gravado. |
| Exibição do Relatório de Desempenho ao encerrar partida | ❌ Não implementado | — |

---

## Legenda

| Símbolo | Significado |
|:---:|---|
| ✅ | Implementado e funcional |
| 🟡 | Parcialmente implementado / estrutura existe mas incompleta ou não integrada |
| ❌ | Não implementado |

---

## Ordem de Implementação Recomendada

1. Preparação de ingredientes + controle de estoque (infinito / perene / perecível)
2. Completar heap mínimo (`insertHeap`/`extractMin`) e integrar para carne, ovo e bacon
3. Implementar lista contígua para histórico + carregamento + salvamento
4. Implementar algoritmo de ordenação e medir tempo
5. Adicionar menu principal, tela "Como jogar" e tela de histórico
6. Integrar todas as métricas (AVL rotações, comparações, timer)
7. Gerar `medicoes.log` e exibir Relatório de Desempenho ao encerrar
8. Integrar Splay Tree para comparação extra (opcional)
