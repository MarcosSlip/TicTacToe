#ifndef BOARD_H
#define BOARD_H

class Board{
    //
public:
    Board();
    // ~Board();
    Board(const Board& other);
    void printBoard() const;
    char checkWin() const;
    bool isValid(int row, int col) const;
    void playMove(int, int);

    int turn = 0;
    char board[3][3];
};


#endif