# Strategic Reversi AI Game Engine: Algorithmic Decision Architecture

*C++, OOP, Minimax Search, Alpha-Beta Pruning, Game Trees*

Built a high-performance **Reversi AI engine** in **C++** utilizing recursive **Minimax decision trees** and **Alpha-Beta pruning** to aggressively cut redundant branches and accelerate optimal move selection. Implemented robust object-oriented game mechanics, including **8-way directional flips** and move validation.

## Features
*   **Minimax Algorithm**: Evaluates thousands of potential game states to determine the most strategically advantageous move.
*   **Alpha-Beta Pruning**: Drastically reduces the search space by cutting off branches that cannot possibly influence the final decision, allowing for greater search depth and faster execution.
*   **Object-Oriented Design**: Clean encapsulation of `Board` and `AI` logic.
*   **Positional Heuristics**: Evaluates board states based on piece placement strategy (e.g., heavily weighting corner capture and penalizing pre-corner placements).
*   **Complete Game Rules**: Strict adherence to Reversi mechanics, validating 8-way directional bounds before flipping adjacent tiles.

## Execution
Compile the C++ code using any standard compiler (e.g., g++):
```bash
g++ main.cpp -o reversi_ai
./reversi_ai
