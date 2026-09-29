#pragma once

#include "Board.hpp"
#include "Move.hpp"

class ChessGame{
    private: 
    Board board;

    public:
    ChessGame();

    const Board& getBoard()const;
    void makeMove(Move& move);
};