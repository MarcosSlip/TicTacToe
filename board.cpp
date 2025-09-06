#include <iostream>
#include "board.h"

Board::Board(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

Board::Board(const Board& other) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = other.board[i][j];
        }
    }
}


void Board::printBoard() const{
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << board[i][j];
            if(j < 2) std::cout << "|";
        }
        std::cout << std::endl;
        if(i < 2) std::cout << "-+-+-" << std::endl;
    }
}


/**
 * Returns 'X' if player 1 wins, 'O' if player 2 wins, 'T' for a tie, or ' ' if the game is still ongoing.
 */
char Board::checkWin() const{
    for(int i = 0; i < 3; i++){
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    if(turn >= 9)
        return 'T'; // Tie
    return ' '; // Game is still going
}

bool Board::isValid(int row, int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

void Board::playMove(int row, int col){
    if(!isValid(row, col))
        return;
    board[row][col] = turn % 2 ? 'O' : 'X';
    turn++;
}