#pragma once

#include "Board.hpp"
#include "Move.hpp"

class ChessGame{
    private: 
    Board board;
    Color turn=Color::White;

    public:
    ChessGame();

    void makeMove(const Move& move);
    const Board& getBoard()const;
    Color getTurn()const;
};