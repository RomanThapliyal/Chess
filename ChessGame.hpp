#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"


enum class GameState{
    Playing,
    Check,
    Checkmate,
    Stalemate
};

class ChessGame{
    private: 
    Board board;
    MoveGenerator generator;
    Color turn=Color::White;
    GameState gameState=GameState::Playing;

    public:
    ChessGame();

    void reset();
    void makeMove(const Move& move);
    const Board& getBoard()const;
    Color getTurn()const;

    GameState getGameState()const;
    std::string getGameStateName() const;
    
    std::vector<Move> getLegalMoves(const Square& square);

};