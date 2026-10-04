#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"

#include "FenLoader.hpp"

#include <string>

enum class GameState{
    Playing,
    Check,
    Checkmate,
    Stalemate
};

class ChessGame{
    private: 
    Board board;
    Position startingPosition;
    MoveGenerator generator;
    Color turn=Color::White;
    GameState gameState=GameState::Playing;

    public:
    ChessGame(const std::string& fen);

    void reset();
    void makeMove(const Move& move);
    const Board& getBoard()const;
    Color getTurn()const;

    GameState getGameState()const;
    std::string getGameStateName() const;
    
    std::vector<Move> getLegalMoves(const Square& square);

};