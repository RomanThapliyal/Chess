#pragma once
#include "ChessGame.hpp"

class ChessAi{
    public:
    int evaluate(const Board& board);
    Move findBestMove(ChessGame& game, const std::vector<Move>& legalMoves, int depth);
    int miniMax(ChessGame& game, int depth);

    private:
    int getPointsOf(const Piece& piece);
};