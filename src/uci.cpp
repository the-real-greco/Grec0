#include "uci.h"
#include "board.h"
#include <iostream>
#include <sstream>

void UCI::loop() {
    std::string line;
    Board board;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "uci") {
            std::cout << "id name Grec0" << std::endl;
            std::cout << "id author YourName" << std::endl;
            std::cout << "uciok" << std::endl;
        } else if (token == "isready") {
            std::cout << "readyok" << std::endl;
        } else if (token == "ucinewgame") {
            board.reset();
            std::cout << "Board reset to starting position." << std::endl;
        } else if (token == "position") {
            std::string subtoken;
            iss >> subtoken;

            if (subtoken == "startpos") {
                board.reset();
                std::string moves;
                if (iss >> moves) {
                    if (moves == "moves") {
                        while (iss >> moves) {
                            board.makeMove(moves);
                        }
                    }
                }
            } else if (subtoken == "fen") {
                std::string fen;
                std::getline(iss, fen);
                board.setPositionFromFEN(fen);
            }
        } else if (token == "go") {
            // Implement engine calculation logic here
            // For now, we'll just return a dummy move
            std::cout << "bestmove e2e4" << std::endl;
        } else if (token == "quit") {
            break;
        } else {
            std::cout << "Unknown command: " << line << std::endl;
        }
    }
}
