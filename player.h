#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include <vector>
#include <iostream>
#include "board.h"


class Player {
public:
    virtual std::pair<int, int> getMove(const Board& board) = 0;
    virtual ~Player() = default;
};

class HumanPlayer : public Player {

public:
    std::pair<int, int> getMove(const Board& board) override {
        int row, col;
        do {
            std::cout << "Enter your move (row and column): ";
            std::cin >> row >> col;
        } while (!board.isValid(row, col));
        return {row, col};
    }
};

class AIPlayer : public Player {
    std::pair<int, int> getMove(const Board& board){
        return getBestMove(const_cast<Board&>(board));
    }
    
    std::pair<bool, int> evaluate(const Board& board) {
        char winner = board.checkWin();
        if (winner == 'X') return {true, 10}; // AI is 'X'
        if (winner == 'O') return {true, -10}; // Opponent is 'O'
        if (winner == 'T') return {true, 0}; // Draw
        return {false, 0}; // Game not over
    }

    std::vector<std::pair<int, int>> getLegalMoves(const Board& board) {
        std::vector<std::pair<int, int>> moves;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.isValid(i, j)) {
                    moves.emplace_back(i, j);
                }
            }
        }
        return moves;
    }

    /*
    4) Write the Minimax recurrence
A function that returns a numeric score for the current position (from the root player’s perspective).
Base case: If the position is terminal, return the evaluation from step 2 (evaluate to score).
Recursive case:
If it’s the root player’s turn (maximizer):
Initialize best score to −∞.
For each legal move: apply → evaluate child → undo.
Keep the maximum child score.
Return that maximum.
If it’s the other player’s turn (minimizer):
Initialize best score to +∞.
For each legal move: apply → evaluate child → undo.
Keep the minimum child score.
Return that minimum.
    */
    int minimax(Board& board, bool isMaximizing) {
        auto [isTerminal, score] = evaluate(board);
        if (isTerminal) return score;

        if (isMaximizing) {
            int bestScore = -1000;
            for (const auto& move : getLegalMoves(board)) {
                board.playMove(move.first, move.second);
                bestScore = std::max(bestScore, minimax(board, false));
                board.board[move.first][move.second] = ' '; // Undo move
                board.turn--;
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (const auto& move : getLegalMoves(board)) {
                board.playMove(move.first, move.second);
                bestScore = std::min(bestScore, minimax(board, true));
                board.board[move.first][move.second] = ' '; // Undo move
                board.turn--;
            }
            return bestScore;
        }
    }

    /*
    
At the top level, iterate over each legal move:
Apply the move,
Call the Minimax function (which returns a score),
Undo the move,
Keep the move with the best score for the root player.
    */
    std::pair<int, int> getBestMove(Board& board) {
        int bestValue = -1000;
        std::pair<int, int> bestMove = {-1, -1};

        for (const auto& move : getLegalMoves(board)) {
            board.playMove(move.first, move.second);
            int moveValue = minimax(board, false);
            board.board[move.first][move.second] = ' '; // Undo move
            board.turn--;

            if (moveValue > bestValue) {
                bestMove = move;
                bestValue = moveValue;
            }
        }
        return bestMove;
    }


};



#endif