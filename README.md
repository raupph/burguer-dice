# Dado Burger

Trabalho Prático Final — INF01203 Estruturas de Dados — UFRGS 2026/2

## Compilar

```
g++ -o dado_burger main.cpp avl.cpp hash.cpp heap.cpp pilha.cpp fila.cpp lista.cpp timer.cpp game.cpp listacontigua.cpp ordenacao.cpp menu.cpp -Wall -std=c++17
```

## Rodar

```
./dado_burger pedidos.txt historico.txt
```

Ao encerrar a partida o programa exibe o Relatório de Desempenho na tela e grava `medicoes.log` no diretório atual.

## Testes

```
g++ -o test/tests test/tests.cpp game.cpp avl.cpp hash.cpp lista.cpp pilha.cpp fila.cpp heap.cpp listacontigua.cpp ordenacao.cpp timer.cpp menu.cpp -std=c++17
./test/tests
```
