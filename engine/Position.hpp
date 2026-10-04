#pragma once

#include "Piece.hpp"
#include "Square.hpp"
#include <optional>

struct Position
{
    Piece squares[8][8];
    Color turn;
    std::optional<Square> enPassantTarget;

    bool wkCastle=true;  // White kingside
    bool wqCastle=true;  // White queenside
    bool bkCastle=true;  // Black kingside
    bool bqCastle=true;  // Black queenside
};