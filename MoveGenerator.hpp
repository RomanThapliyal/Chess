#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include <vector>

class MoveGenerator{
    public:
    std::vector<Move>getMoves(const Board& board,const Square& from);
    std::vector<Move>getLegalMoves(const Board& board,const Square& from);

    std::vector<Square>getAttackSquares(const Board& board,const Square& from);

    bool isSquareAttacked(const Board& board,const Square& target, Color& attackingColor);
    bool isInCheck(const Board& board, Color& color);

    bool isInside(const Board& board,const Square& square);

    void addSlidingMoves(const Board& board, const Square& from, const Piece& piece, const int (&directions)[4][2], std::vector<Move>& moves);
    void addSlidingSquares(const Board& board, const Square& from, const Piece& piece, const int (&directions)[4][2], std::vector<Square>& squares);
};