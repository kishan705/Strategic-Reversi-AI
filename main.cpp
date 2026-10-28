#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int SIZE = 8;
const char EMPTY = '.';
const char PLAYER_X = 'X'; // Human (Black)
const char PLAYER_O = 'O'; // AI (White)

// 8-way directional vectors
const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

class Board {
public:
    vector<vector<char>> grid;

    Board() {
        grid = vector<vector<char>>(SIZE, vector<char>(SIZE, EMPTY));
        grid[3][3] = PLAYER_O;
        grid[3][4] = PLAYER_X;
        grid[4][3] = PLAYER_X;
        grid[4][4] = PLAYER_O;
    }

    void display() const {
        cout << "  ";
        for (int i = 0; i < SIZE; ++i) cout << i << " ";
        cout << "\n";
        for (int i = 0; i < SIZE; ++i) {
            cout << i << " ";
            for (int j = 0; j < SIZE; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool isOnBoard(int r, int c) const {
        return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
    }

    bool isValidMove(int r, int c, char player) const {
        if (!isOnBoard(r, c) || grid[r][c] != EMPTY) return false;
        char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;

        for (int i = 0; i < 8; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            bool foundOpponent = false;

            while (isOnBoard(nr, nc) && grid[nr][nc] == opponent) {
                nr += dr[i];
                nc += dc[i];
                foundOpponent = true;
            }
            if (foundOpponent && isOnBoard(nr, nc) && grid[nr][nc] == player) {
                return true;
            }
        }
        return false;
    }

    void makeMove(int r, int c, char player) {
        char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
        grid[r][c] = player;

        for (int i = 0; i < 8; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            vector<pair<int, int>> toFlip;

            while (isOnBoard(nr, nc) && grid[nr][nc] == opponent) {
                toFlip.push_back({nr, nc});
                nr += dr[i];
                nc += dc[i];
            }
            if (isOnBoard(nr, nc) && grid[nr][nc] == player) {
                for (auto p : toFlip) {
                    grid[p.first][p.second] = player;
                }
            }
        }
    }

    vector<pair<int, int>> getValidMoves(char player) const {
        vector<pair<int, int>> moves;
        for (int r = 0; r < SIZE; ++r) {
            for (int c = 0; c < SIZE; ++c) {
                if (isValidMove(r, c, player)) {
                    moves.push_back({r, c});
                }
            }
        }
        return moves;
    }

    bool isGameOver() const {
        return getValidMoves(PLAYER_X).empty() && getValidMoves(PLAYER_O).empty();
    }

    int evaluate() const {
        int score = 0;
        // Simple heuristic: Corners are highly valuable, edges are good, inner pieces are standard
        int weights[8][8] = {
            {100, -20, 10,  5,  5, 10, -20, 100},
            {-20, -50, -2, -2, -2, -2, -50, -20},
            { 10,  -2,  1,  1,  1,  1,  -2,  10},
            {  5,  -2,  1,  1,  1,  1,  -2,   5},
            {  5,  -2,  1,  1,  1,  1,  -2,   5},
            { 10,  -2,  1,  1,  1,  1,  -2,  10},
            {-20, -50, -2, -2, -2, -2, -50, -20},
            {100, -20, 10,  5,  5, 10, -20, 100}
        };

        for (int r = 0; r < SIZE; ++r) {
            for (int c = 0; c < SIZE; ++c) {
                if (grid[r][c] == PLAYER_O) score += weights[r][c]; // AI wants to maximize
                else if (grid[r][c] == PLAYER_X) score -= weights[r][c];
            }
        }
        return score;
    }
};

class AI {
public:
    int minimax(Board board, int depth, int alpha, int beta, bool isMaximizing) {
        if (depth == 0 || board.isGameOver()) {
            return board.evaluate();
        }

        char currentPlayer = isMaximizing ? PLAYER_O : PLAYER_X;
        vector<pair<int, int>> moves = board.getValidMoves(currentPlayer);

        if (moves.empty()) {
            return minimax(board, depth - 1, alpha, beta, !isMaximizing);
        }

        if (isMaximizing) {
            int maxEval = numeric_limits<int>::min();
            for (auto move : moves) {
                Board tempBoard = board;
                tempBoard.makeMove(move.first, move.second, PLAYER_O);
                int eval = minimax(tempBoard, depth - 1, alpha, beta, false);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) break; // Alpha-Beta Pruning
            }
            return maxEval;
        } else {
            int minEval = numeric_limits<int>::max();
            for (auto move : moves) {
                Board tempBoard = board;
                tempBoard.makeMove(move.first, move.second, PLAYER_X);
                int eval = minimax(tempBoard, depth - 1, alpha, beta, true);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) break; // Alpha-Beta Pruning
            }
            return minEval;
        }
    }

    pair<int, int> getBestMove(const Board& board, int depth) {
        int bestVal = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};
        vector<pair<int, int>> moves = board.getValidMoves(PLAYER_O);

        for (auto move : moves) {
            Board tempBoard = board;
            tempBoard.makeMove(move.first, move.second, PLAYER_O);
            int moveVal = minimax(tempBoard, depth - 1, numeric_limits<int>::min(), numeric_limits<int>::max(), false);
            if (moveVal > bestVal) {
                bestVal = moveVal;
                bestMove = move;
            }
        }
        return bestMove;
    }
};

int main() {
    Board board;
    AI ai;
    int depth = 5; // Adjust depth for AI difficulty

    cout << "--- Strategic Reversi AI Game Engine ---\n";
    
    while (!board.isGameOver()) {
        board.display();
        vector<pair<int, int>> xMoves = board.getValidMoves(PLAYER_X);
        vector<pair<int, int>> oMoves = board.getValidMoves(PLAYER_O);

        if (!xMoves.empty()) {
            int r, c;
            cout << "Player X's turn. Enter row and column (0-7): ";
            cin >> r >> c;
            
            while (!board.isValidMove(r, c, PLAYER_X)) {
                cout << "Invalid move. Try again: ";
                cin >> r >> c;
            }
            board.makeMove(r, c, PLAYER_X);
        } else {
            cout << "Player X has no valid moves. Skipping turn.\n";
        }

        if (board.isGameOver()) break;

        if (!oMoves.empty()) {
            cout << "AI (O) is thinking...\n";
            pair<int, int> aiMove = ai.getBestMove(board, depth);
            board.makeMove(aiMove.first, aiMove.second, PLAYER_O);
            cout << "AI placed at " << aiMove.first << ", " << aiMove.second << "\n";
        } else {
            cout << "AI (O) has no valid moves. Skipping turn.\n";
        }
    }

    board.display();
    cout << "Game Over!\n";
    
    int xCount = 0, oCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board.grid[i][j] == PLAYER_X) xCount++;
            if (board.grid[i][j] == PLAYER_O) oCount++;
        }
    }
    cout << "Player X: " << xCount << " | AI O: " << oCount << "\n";
    if (xCount > oCount) cout << "Player X wins!\n";
    else if (oCount > xCount) cout << "AI O wins!\n";
    else cout << "It's a tie!\n";

    return 0;
}
