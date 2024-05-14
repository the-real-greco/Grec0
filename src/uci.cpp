#include "uci.h"
#include <iostream>
#include <sstream>
#include <vector>

namespace UCI {

Board board;  // Define the board object

void setPosition(const std::string& positionCommand) {
    std::istringstream iss(positionCommand);
    std::string token;

    // Skip the "position" token
    iss >> token;

    // Determine the position type (fen or startpos)
    iss >> token;
    if (token == "startpos") {
        // Handle startpos case
        board.reset();

        // Read moves if any
        if (iss >> token && token == "moves") {
            std::string move;
            while (iss >> move) {
                board.applyMove(move);
            }
        }
    } else if (token == "fen") {
        // Handle FEN string case
        std::string fen;
        std::getline(iss, fen);
        board.setFromFEN(fen);
    } else {
        std::cerr << "Unknown position type: " << token << std::endl;
    }
}

void loop() {
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "uci") {
            std::cout << "id name Grec0" << std::endl;
            std::cout << "id author YourName" << std::endl;
            std::cout << "uciok" << std::endl;
        } else if (input == "isready") {
            std::cout << "readyok" << std::endl;
        } else if (input == "ucinewgame") {
            // Initialize or reset the engine state for a new game
            board.reset();
        } else if (input.rfind("position", 0) == 0) {
            // Handle position command
            setPosition(input);
        } else if (input.rfind("go", 0) == 0) {
            // Handle go command (start searching for the best move)
        } else if (input == "quit") {
            break;
        } else {
            std::cerr << "Unknown command: " << input << std::endl;
        }
    }
}

} // namespace UCI
