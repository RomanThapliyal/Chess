#pragma once

#include "Piece.hpp"
#include "Square.hpp"
#include <optional>

class Board{
    public:
    
    static constexpr int SIZE=8;
    Board();
    const Piece& getPiece(Square square)const;
    void setPiece(Square square, Piece piece);
    std::optional<Square> getEnPassantTarget()const;
    void setEnPassantTarget(std::optional<Square> square);

    private:
    Piece squares[SIZE][SIZE];
    std::optional<Square> enPassantTarget;
};