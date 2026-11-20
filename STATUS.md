# Dado Burger - Project Status

## Implemented

### Project structure

- Source code is organized by module in `.cpp` and `.hpp` files.
- The project compiles with C++17.
- The program receives the input files through command-line arguments:

  ```bash
  ./dado_burger pedidos.txt historico.txt
  ```

- `argv[1]` is used as the pedidos file path.
- `argv[2]` is reserved for the historico file path.
- User-facing messages added recently are written in English.

### AVL tree

- Recipe records are loaded from the pedidos file.
- Each record contains a numeric code and an ingredient string.
- Insertion, search, removal, rotations, height updates, and destruction are implemented.
- Recipes are stored in AVL nodes.

### Linked list

- A linked list stores the current recipe.
- Each node stores one ingredient.
- The list starts with the bottom bread (`p`).
- Insertion at the end, size calculation, initialization, and destruction are implemented.

### Stack

- A stack stores the burger being assembled.
- The bottom bread (`p`) is inserted when the stack is initialized.
- Push, pop, initialization, and empty-check operations are implemented.
- Removing the top ingredient is supported.
- The bottom bread cannot be removed from an otherwise empty burger.

### Order validation

- The burger stack is moved to an auxiliary stack.
- The auxiliary stack is used to compare the burger from bottom to top.
- The original burger stack is rebuilt during the comparison.
- The stack remains intact after both valid and invalid validations.
- The recipe and burger must contain exactly the same ingredients in the same order.

### Game state flow

- Basic states exist for:
  - Initializing an order.
  - Waiting for an action.
  - Adding an ingredient.
  - Removing an ingredient.
  - Validating an order.
  - Completing an order.
  - Ending the game.
- A valid order transitions to `STATE_ORDER_SUCCESS`.
- A successful order increments the number of served customers.
- The current burger and recipe are reset after a successful order.
- A temporary limit of three customers is used.
- The project displays a provisional victory message after three successful orders.

### Random order selection

- A random number generator is implemented using `std::mt19937`.
- The current code searches for a random recipe code in the AVL.

### Other structures already present

- A queue module exists with initialization, enqueue, dequeue, empty-check, and size operations.
- The hash table stores recipes by order code using separate chaining.
- Its implementation uses the professor-provided
  `hash_algorithms.cpp` and `hash_algorithms.hpp`, using division hashing and
  separate chaining.
- Hash lookup is attempted before AVL lookup during order initialization.
- Hash hits, misses, collisions, and occupied entries are counted in the table.
- The hash table is initialized and destroyed with the game.
- A heap module exists with a fixed-size array representation.
- A Splay tree module exists with search, insertion, removal, destruction, and in-order traversal.
- Timer files exist with a C++ timing interface.

## Not implemented or incomplete

### Main menu

The required initial menu is still missing:

1. New game
2. How to play
3. History

The current program enters the game action menu directly.

### Customer queue

The queue is not integrated into the game yet. It still needs to:

- Create all customers at the beginning of a match.
- Preserve the arrival order.
- Serve the customer at the front of the queue.
- Remove a customer after a successful order.
- Move the next customer to the front.
- Replace the temporary `MAX_CUSTOMERS` control.

### Order selection

The current code assumes that valid order codes are in the fixed interval
`1..837253`. This must be replaced with a selection based on the orders
actually loaded from the pedidos file.

The program must not assume:

- A fixed maximum code.
- Consecutive order codes.
- That every code in the interval exists.

### Customer patience and turns

The following requirements are still missing:

- Each player action must consume one turn.
- The front customer's patience must decrease after each action.
- Customers waiting in the queue must not lose patience.
- The game must display the current turn and remaining patience.
- The game must end in defeat when the front customer's patience reaches zero.
- The score must equal the number of customers served.

### Ingredient preparation and stock

The current interface allows direct insertion of a character and does not
implement the stock rules. It still needs:

- Preparation actions.
- Infinite stock for non-preparable ingredients.
- Permanent stock for prepared non-perishable ingredients.
- Stock consumption when ingredients are added.
- Rejection when a prepared ingredient is unavailable.
- Display of the current stock.

The complete ingredient set is:

| Ingredient | Symbol | Requires preparation | Perishable |
|---|---:|---:|---:|
| Top bread | `z` | No | No |
| Ketchup | `k` | No | No |
| Mustard | `m` | No | No |
| Pickles | `p` | No | No |
| Lettuce | `a` | No | No |
| Swiss cheese | `s` | Yes | No |
| Cheddar cheese | `q` | Yes | No |
| Onion | `c` | Yes | No |
| Tomato | `t` | Yes | No |
| Meat | `n` | Yes | Yes |
| Fried egg | `o` | Yes | Yes |
| Bacon | `b` | Yes | Yes |

### Minimum heaps for perishable ingredients

The heap implementation is incomplete:

- `insertHeap` is not implemented.
- `extractMax` is not implemented.
- The current operation name does not represent the required minimum heap
  behavior.
- `Product` does not model an ingredient expiration turn.
- Separate heaps are required for meat, fried egg, and bacon.
- Expired ingredients must be discarded at the beginning of each turn.
- Consumption must remove the item with the earliest expiration turn.

### Hash table cache

The hash table cache is integrated at a basic level, but still needs:

- A load-factor calculation and report.
- A hit-rate calculation and report.
- Integration with valid loaded order-code selection instead of the fixed
  `1..837253` interval.
- Inclusion of cache metrics in `medicoes.log`.

### History

The historico file is received through `argv[2]` but is not loaded or saved.
The following is still required:

- A dynamically allocated contiguous list for history records.
- Loading name and score pairs from the historico file.
- Handling a missing historico file as an empty history.
- Adding a new record after a game ends.
- Preserving all previous records when saving.
- Displaying the history alphabetically or by descending score.
- Sorting a copy so the stored order is not modified.
- Measuring the sorting time.

The linked list currently used for recipes does not replace the required
contiguous history list.

### Performance metrics

The timer exists but is not integrated. The project still needs to collect:

- AVL nodes inserted.
- Final AVL height.
- Rotations during insertion.
- AVL loading time.
- AVL search comparisons.
- Number of AVL searches.
- Average comparisons per search.
- Total AVL search time.
- Hash hits and misses.
- Hash hit rate.
- Hash collisions.
- Hash load factor.
- History sorting time.

### Performance report

The required `medicoes.log` file is not generated yet. The program must:

- Create or overwrite the log at the start of each execution.
- Record all required metrics in English.
- Display the complete report on game termination.
- Append history sorting measurements when the History option is accessed.

### Game termination

The final-state handling still needs adjustment. The main loop currently exits
when `STATE_GAME_OVER` is assigned, so a `case STATE_GAME_OVER` inside that
loop may not execute. The final report, score, and history update must happen
before returning to the main menu or exiting the program.

### Memory cleanup

Most current structures have basic cleanup, but the final integration still
needs to verify destruction of:

- The customer queue.
- The hash table.
- All perishable heaps.
- The contiguous history list.
- The AVL tree.
- The current burger stack.
- The current recipe list.

## Recommended implementation order

1. Integrate the queue and replace the temporary customer limit.
2. Store and select only valid order codes loaded from the pedidos file.
3. Implement turns, patience, victory, and defeat.
4. Implement ingredient preparation and stock management.
5. Complete the minimum heaps for perishable ingredients.
6. Complete and integrate the hash cache.
7. Implement the contiguous history list and sorting.
8. Add the main menu and the How to Play screen.
9. Integrate AVL, hash, and sorting metrics.
10. Generate and display `medicoes.log`.
11. Complete final cleanup and test with both development and presentation files.

## Current validation

The project currently compiles with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp game.cpp avl.cpp \
hash.cpp hash_algorithms.cpp heap.cpp pilha.cpp fila.cpp lista.cpp \
timer.cpp splay.cpp -o dado_burger
```

The command-line interface is tested with:

```bash
./dado_burger pedidos.txt historico.txt
```
