#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board {
public:
    void reset();
    void setFromFEN(const std::string& fen);
    void applyMove(const std::string& move);
    void printBoard();  // For debugging purposes
};

#endif // BOARD_H
