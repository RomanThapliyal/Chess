#pragma once

#include "Piece.hpp"
#include "Square.hpp"
#include "CastlingRights.hpp"
#include <optional>

struct Position
{
    Piece squares[8][8];
    Color turn;
    std::optional<Square> enPassantTarget;

    CastlingRights castlingRights;
};