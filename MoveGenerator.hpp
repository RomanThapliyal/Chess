#pragma once

#include "board.hpp"
#include "Move.hpp"
#include <vector>

class MoveGenerator{
    public:
    std::vector<Move>getMoves(const Board& board,const Square& from);
    bool isInside(const Board& board,const Square& square);
};