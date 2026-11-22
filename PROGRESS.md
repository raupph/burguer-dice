# Dado Burger — Progress Summary

Spec: INF01203 – Estruturas de Dados, UFRGS, 2026/2 — Trabalho Prático Final

---

## Estruturas de Dados

| Estrutura | Papel no Jogo | Status | Observações |
|---|---|:---:|---|
| **AVL** | Armazenamento e busca de pedidos | ✅ Feito | Inserção, busca, remoção, rotações e destruição implementados. Receitas carregadas do arquivo na inicialização. |
| **Lista encadeada** | Receita do pedido atual | ✅ Feito | Cada nó armazena um ingrediente. Usada para comparar com a pilha na validação. |
| **Pilha** | Montagem do hambúrguer | ✅ Feito | Push/pop/isEmpty implementados. Pão de baixo (`p`) pré-inserido. Remoção do fundo bloqueada. |
| **Fila (FIFO)** | Clientes esperando atendimento | ✅ Feito | Enqueue/dequeue/front/isEmpty/size/destroy implementados e integrados ao fluxo do jogo. |
| **Tabela hash** | Cache de pedidos buscados | ✅ Básico | Encadeamento separado, hits/misses/colisões contados. Falta relatório de fator de carga e taxa de acerto no log. |
| **Heap mínimo** | Estoque de ingredientes perecíveis | ❌ Incompleto | `insertHeap` e `extractMax` são stubs vazios. `Product` não modela turno de vencimento. Heaps separados por ingrediente ainda não existem. |
| **Lista contígua** | Histórico de partidas | ❌ Não implementado | `argv[2]` é recebido mas ignorado. Nenhuma estrutura contígua existe para histórico. |
| **Splay Tree** | Extra opcional (comparação com AVL) | 🟡 Estrutura existe | Módulo presente com busca, inserção, remoção e travessia, mas **não usa** `Recipe` — armazena só `int`. Não integrado ao jogo. |
| **Timer** | Medição de tempo | 🟡 Estrutura existe | Arquivos `timer.cpp/hpp` presentes e corretos. Nenhuma medição está sendo feita ainda. |

---

## Mecânicas do Jogo

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Leitura de pedidos via `argv[1]` | ✅ Feito | Carregado na AVL na inicialização. |
| Leitura de histórico via `argv[2]` | ❌ Não implementado | Argumento recebido, arquivo nunca aberto. |
| Fluxo de estados do jogo | ✅ Feito | Estados: INIT_ORDER → WAIT_ACTION → ADD/REMOVE/VALIDATE → ORDER_SUCCESS → GAME_OVER. |
| Fila de clientes (FIFO) | ✅ Feito | 3 clientes enfileirados na inicialização; fila drena corretamente. |
| Seleção do código do pedido (baseado nos pedidos carregados) | ❌ Incompleto | Código sorteado em `1..837253` fixo — deve ser restrito aos códigos realmente presentes na AVL. |
| Busca com cache (hash → AVL) | ✅ Feito | Hit retorna da hash sem consultar a AVL; miss busca na AVL e insere na hash. |
| Validação do pedido (pilha vs lista) | ✅ Feito | Pilha invertida em auxiliar, comparada ingrediente a ingrediente, reconstruída ao final. |
| Turnos (cada ação consome 1 turno) | ❌ Não implementado | `current_turn` existe na struct `Game` mas nunca é incrementado. |
| Paciência do cliente (decremento por turno) | ❌ Não implementado | `current_patience` existe mas nunca é decrementado nem exibido. |
| Derrota por paciência zerada | ❌ Não implementado | Nenhuma verificação de paciência existe. |
| Vitória ao atender todos os clientes | ✅ Feito | Detectada quando a fila fica vazia. |
| Preparação de ingredientes (ação separada de adicionar) | ❌ Não implementado | O jogador adiciona diretamente o caractere sem etapa de preparo. |
| Estoque de ingredientes (infinito / perene / perecível) | ❌ Não implementado | Nenhum controle de estoque existe. Qualquer caractere é aceito. |
| Descarte automático de perecíveis vencidos a cada turno | ❌ Não implementado | Depende do heap e dos turnos, que ainda não estão implementados. |
| Exibição do pedido, hambúrguer, estoque e turnos restantes | 🟡 Parcial | Hambúrguer é exibido; pedido, estoque e turnos não são exibidos ao jogador. |

---

## Menu e Interface

| Funcionalidade | Status | Observações |
|---|:---:|---|
| Menu principal (Novo jogo / Como jogar / Histórico) | ❌ Não implementado | Programa entra direto no loop de ação. |
| Tela "Como jogar" | ❌ Não implementado | — |
| Histórico com ordenação (alfabética / pontuação desc.) | ❌ Não implementado | Depende da lista contígua. |
| Salvar nova entrada no histórico ao encerrar partida | ❌ Não implementado | — |
| Preservar entradas anteriores ao gravar histórico | ❌ Não implementado | — |

---

## Medições e Relatório de Desempenho

| Métrica | Status | Observações |
|---|:---:|---|
| Nós inseridos na AVL | ❌ Não coletado | — |
| Altura final da AVL | ❌ Não coletado | Função `avlAltura` existe mas não é chamada para log. |
| Rotações durante inserção na AVL | ❌ Não coletado | Contador não existe. |
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

1. Corrigir seleção de código de pedido (usar códigos reais da AVL, não `1..837253`)
2. Implementar turnos e decremento de paciência; derrota por paciência zerada
3. Implementar preparação de ingredientes e controle de estoque
4. Completar heap mínimo (insert/extractMin) e integrar para perecíveis
5. Implementar lista contígua para histórico + carregamento + salvamento
6. Implementar algoritmo de ordenação e medir tempo
7. Adicionar menu principal, tela "Como jogar" e tela de histórico
8. Integrar todas as métricas (AVL rotações, comparações, timer em todo fluxo)
9. Gerar `medicoes.log` e exibir Relatório de Desempenho ao encerrar
10. Integrar Splay Tree para comparação extra (opcional)
