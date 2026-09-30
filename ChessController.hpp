#pragma once

#include "Input.hpp"
#include "ChessGame.hpp"
#include "Move.hpp"

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include <iostream>

class ChessController
{
private:
    ChessGame& game;
    std::optional <Square> selectedSquare;
    std::vector<Move>legalMoves;

    std::string pieceName(PieceType type);
    
public:
    ChessController(ChessGame& game);

    bool handleChessInput(const Input& input,const sf::Event& event);

    void clearSelection();
    
    const std::optional<Square>& getSelectedSquare() const;
    const std::vector<Move>& getLegalMoves() const;
};