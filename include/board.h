#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board {
public:
    void reset();
    void makeMove(const std::string& move);
    void setPositionFromFEN(const std::string& fen);
};

#endif // BOARD_H
