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

    Square promotionFrom{-1, -1};
    Square promotionTo{-1, -1};
    bool promotionPending=false;

    std::string pieceName(PieceType type);
    
public:
    ChessController(ChessGame& game);

    bool handleChessInput(const Input& input,const sf::Event& event, const BoardLayout& layout);

    void startPromotion(const Square& square, const Square& target);
    void choosePromotion(MoveFlag flag);

    void clearSelection();
    
    const std::optional<Square>& getSelectedSquare() const;
    const std::vector<Move>& getLegalMoves() const;

    std::optional<Move> findLegalMove(const Square& to) const;
    bool isPromotionPending();
    void resetPromotionPending();

    bool isThisMovePromotion(const MoveFlag& moveflag);
};