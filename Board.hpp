#pragma once

#include "Input.hpp"

enum class PieceType{
    None,
    Pawn,
    Knight,
    Bishop,
    Rook,
    King,
    Queen
};

enum class Color{
    None,
    White,
    Black
};

struct Piece{
    PieceType type=PieceType::None;
    Color color=Color::None;
};

class Board{
    public:
    
    static constexpr int SIZE=8;
    Board();
    const Piece& getPiece(Square square)const;
    void setPiece(Square square, Piece piece);

    private:
    Piece squares[SIZE][SIZE];
};