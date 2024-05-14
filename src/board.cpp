#include "board.h"
#include <vector>

Board::Board() : enPassantSquare(-1), 
                 whiteCanCastleKingside(true), whiteCanCastleQueenside(true), 
                 blackCanCastleKingside(true), blackCanCastleQueenside(true) {}

// Utility to check if a position is on the board
bool isOnBoard(int pos) {
    return pos >= 0 && pos < 64;
}

// Helper function to generate sliding piece moves (bishop, rook, queen)
void generateSlidingMoves(std::vector<Move>& moves, Board& board, int pos, const std::vector<int>& directions) {
    for (int direction : directions) {
        int to = pos;
        while (true) {
            to += direction;
            if (!isOnBoard(to) || (to % 8 == 0 && direction % 8 != 0) || (to % 8 == 7 && direction % 8 != 0)) {
                break; // Stop if off board or wrap around the board edges
            }
            if (board.board[to].type == EMPTY) {
                moves.push_back({pos, to, EMPTY});
            } else {
                if (board.board[to].color != board.sideToMove) {
                    moves.push_back({pos, to, EMPTY});
                }
                break; // Stop if a piece is blocking
            }
        }
    }
}

std::vector<Move> Board::generatePawnMoves(int pos) {
    std::vector<Move> moves;
    int direction = (sideToMove == WHITE) ? 1 : -1;
    int startRank = (sideToMove == WHITE) ? 1 : 6;
    int promotionRank = (sideToMove == WHITE) ? 6 : 1;

    // Single move forward
    int to = pos + 8 * direction;
    if (isOnBoard(to) && board[to].type == EMPTY) {
        if ((pos / 8) == promotionRank) {
            moves.push_back({pos, to, QUEEN});
            moves.push_back({pos, to, ROOK});
            moves.push_back({pos, to, BISHOP});
            moves.push_back({pos, to, KNIGHT});
        } else {
            moves.push_back({pos, to, EMPTY});
            // Double move forward
            if ((pos / 8) == startRank) {
                to += 8 * direction;
                if (isOnBoard(to) && board[to].type == EMPTY) {
                    moves.push_back({pos, to, EMPTY});
                }
            }
        }
    }

    // Captures
    int captures[2] = {7 * direction, 9 * direction};
    for (int capture : captures) {
        to = pos + capture;
        if (isOnBoard(to) && board[to].type != EMPTY && board[to].color != sideToMove) {
            if ((pos / 8) == promotionRank) {
                moves.push_back({pos, to, QUEEN});
                moves.push_back({pos, to, ROOK});
                moves.push_back({pos, to, BISHOP});
                moves.push_back({pos, to, KNIGHT});
            } else {
                moves.push_back({pos, to, EMPTY});
            }
        }

        // En passant capture
        if (to == enPassantSquare) {
            moves.push_back({pos, to, EMPTY});
        }
    }

    return moves;
}

std::vector<Move> Board::generateKnightMoves(int pos) {
    std::vector<Move> moves;
    int knightMoves[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

    for (int move : knightMoves) {
        int to = pos + move;
        if (isOnBoard(to) && (board[to].type == EMPTY || board[to].color != sideToMove)) {
            moves.push_back({pos, to, EMPTY});
        }
    }

    return moves;
}

std::vector<Move> Board::generateBishopMoves(int pos) {
    std::vector<Move> moves;
    int bishopDirections[4] = {-9, -7, 7, 9};
    generateSlidingMoves(moves, *this, pos, bishopDirections);
    return moves;
}

std::vector<Move> Board::generateRookMoves(int pos) {
    std::vector<Move> moves;
    int rookDirections[4] = {-8, -1, 1, 8};
    generateSlidingMoves(moves, *this, pos, rookDirections);
    return moves;
}

std::vector<Move> Board::generateQueenMoves(int pos) {
    std::vector<Move> moves;
    int queenDirections[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    generateSlidingMoves(moves, *this, pos, queenDirections);
    return moves;
}

std::vector<Move> Board::generateKingMoves(int pos) {
    std::vector<Move> moves;
    int kingMoves[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

    for (int move : kingMoves) {
        int to = pos + move;
        if (isOnBoard(to) && (board[to].type == EMPTY || board[to].color != sideToMove)) {
            moves.push_back({pos, to, EMPTY});
        }
    }

    // Castling
    if (sideToMove == WHITE) {
        if (whiteCanCastleKingside && board[61].type == EMPTY && board[62].type == EMPTY && !isSquareAttacked(60, BLACK) && !isSquareAttacked(61, BLACK) && !isSquareAttacked(62, BLACK)) {
            moves.push_back({60, 62, EMPTY});
        }
        if (whiteCanCastleQueenside && board[59].type == EMPTY && board[58].type == EMPTY && board[57].type == EMPTY && !isSquareAttacked(60, BLACK) && !isSquareAttacked(59, BLACK) && !isSquareAttacked(58, BLACK)) {
            moves.push_back({60, 58, EMPTY});
        }
    } else {
        if (blackCanCastleKingside && board[5].type == EMPTY && board[6].type == EMPTY && !isSquareAttacked(4, WHITE) && !isSquareAttacked(5, WHITE) && !isSquareAttacked(6, WHITE)) {
            moves.push_back({4, 6, EMPTY});
        }
        if (blackCanCastleQueenside && board[3].type == EMPTY && board[2].type == EMPTY && board[1].type == EMPTY && !isSquareAttacked(4, WHITE) && !isSquareAttacked(3, WHITE) && !isSquareAttacked(2, WHITE)) {
            moves.push_back({4, 2, EMPTY});
        }
    }

    return moves;
}

std::vector<Move> Board::generateLegalMoves() {
    std::vector<Move> moves;

    for (int pos = 0; pos < 64; ++pos) {
        if (board[pos].type == EMPTY || board[pos].color != sideToMove) {
            continue;
        }

        std::vector<Move> pieceMoves;
        switch (board[pos].type) {
            case PAWN:
                pieceMoves = generatePawnMoves(pos);
                break;
            case KNIGHT:
                pieceMoves = generateKnightMoves(pos);
                break;
            case BISHOP:
                pieceMoves = generateBishopMoves(pos);
                break;
            case ROOK:
                pieceMoves = generateRookMoves(pos);
                break;
            case QUEEN:
                pieceMoves = generateQueenMoves(pos);
                break;
            case KING:
                pieceMoves = generateKingMoves(pos);
                break;
            default:
                break;
        }

        // Validate and add legal moves
        for (const Move& move : pieceMoves) {
            makeMove(move);
            if (!isSquareAttacked(findKingPosition(sideToMove), !sideToMove)) {
                moves.push_back(move);
            }
            unmakeMove(move);
        }
    }

    return moves;
}

// Dummy implementations for these functions
bool Board::isSquareAttacked(int square, Color attackerColor) {
    // Implement this function
    return false;
}

void Board::makeMove(const Move& move) {
    // Implement this function
}

void Board::unmakeMove(const Move& move) {
    // Implement this function
}

int Board::findKingPosition(Color color) {
    // Implement this function
    return -1;
}
