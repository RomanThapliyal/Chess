#pragma once
#include "ChessGame.hpp"

class ChessAi{
    public:
    int evaluate(const Board& board);
    Move findBestMove(ChessGame& game,const Board& board,const std::vector<Move>& legalMoves);

    private:
    int getPointsOf(const Piece& piece);
};