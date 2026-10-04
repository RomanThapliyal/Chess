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

struct UndoState{
    Position previousPosition;
    Color previousTurn;
    GameState previousGameState;
};

class ChessGame{
    private: 
    Board board;
    Position startingPosition;
    MoveGenerator generator;
    Color turn=Color::White;
    GameState gameState=GameState::Playing;
    bool gameStateUpToDate=false;

    std::vector<UndoState> gameHistory;

    public:
    ChessGame(const std::string& fen);

    void reset();
    void makeMove(const Move& move);
    void undoMove();
    const Board& getBoard()const;
    Color getTurn()const;

    void updateGameState();
    GameState getGameState();
    std::string getGameStateName();
    
    std::vector<Move> getLegalMoves(const Square& square);

};