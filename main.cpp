#include <iostream>
#include <utility>
#include "board.h"
#include "player.h"

int main(){
    Board board;
    int& turn = board.turn;

    Player* p2 = new HumanPlayer();
    Player* p1 = new AIPlayer(); // Change to AI for AI opponent
    board.printBoard();

    for( ; ; ){
        std::pair<int, int> move;
        int row, col;

        if(turn % 2 == 0){
            std::cout << "Player 1's turn (X):" << std::endl;
            move = p1->getMove(board);
        } else {
            std::cout << "Player 2's turn (O):" << std::endl;
            move = p2->getMove(board);
        }
        row = move.first;
        col = move.second;

        board.playMove(row, col);
        board.printBoard();

        // Check for a win
        char winner = board.checkWin();
        if(winner == 'T'){
            std::cout << "It's a draw!" << std::endl;
            return 0;
        }
        if(winner != ' '){
            std::cout << "Player " << (winner == 'X' ? "1" : "2") << " wins!" << std::endl;
            return 0;
        }
    }

    return 0;
}