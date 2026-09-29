#pragma once

#include "board.hpp"
#include "Move.hpp"
#include <vector>

class MoveGenerator{
    public:
    std::vector<Move>getMoves(const Board& board,const Square& from);
    bool isInside(const Board& board,const Square& square);
    void addSlidingMoves(const Board& board, const Square& from, const Piece& piece, const int (&directions)[4][2], std::vector<Move>& moves);
};