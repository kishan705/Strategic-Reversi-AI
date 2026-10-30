# Strategic Reversi AI Game Engine: Algorithmic Decision Architecture

![OOP](https://img.shields.io/badge/OOP-Paradigms-34495e)
![Minimax Search](https://img.shields.io/badge/Minimax_Search-Game_AI-27ae60)
![Alpha-Beta Pruning](https://img.shields.io/badge/Alpha--Beta-Pruning-9b59b6)
![Game Trees](https://img.shields.io/badge/Game_Trees-Architectures-2e7d32)

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
