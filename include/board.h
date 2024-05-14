#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, EMPTY };
enum Color { WHITE, BLACK };

struct Move {
    int from;
    int to;
    PieceType promotion; // For pawn promotion
};

class Piece {
public:
    PieceType type;
    Color color;
    int position; // Position as a single integer (0-63)

    Piece(PieceType type, Color color, int position)
        : type(type), color(color), position(position) {}
};

class Board {
public:
    Piece board[64]; // 8x8 board represented as a 1D array
    Color sideToMove;

    std::vector<Move> generateLegalMoves();

private:
    std::vector<Move> generatePawnMoves(int pos);
    std::vector<Move> generateKnightMoves(int pos);
    std::vector<Move> generateBishopMoves(int pos);
    std::vector<Move> generateRookMoves(int pos);
    std::vector<Move> generateQueenMoves(int pos);
    std::vector<Move> generateKingMoves(int pos);

    bool isSquareAttacked(int square, Color attackerColor);
    void makeMove(const Move& move);
    void unmakeMove(const Move& move);
    int findKingPosition(Color color);
};

#endif // BOARD_H
