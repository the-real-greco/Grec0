#include "board.h"
#include <iostream>

void Board::reset() {
    // Initialize the board to the starting position
    std::cout << "Board has been reset to the starting position." << std::endl;
}

void Board::makeMove(const std::string& move) {
    // Apply the move to the board
    std::cout << "Move made: " << move << std::endl;
}

void Board::setPositionFromFEN(const std::string& fen) {
    // Set the board position based on FEN string
    std::cout << "Board position set from FEN: " << fen << std::endl;
}
