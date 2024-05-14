#include "uci.h"
#include <iostream>
#include <string>

namespace UCI {

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
        } else if (input.rfind("position", 0) == 0) {
            // Handle position command
            // Format: "position [fen <fenstring> | startpos ]  moves <move1> ... <movei>"
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
