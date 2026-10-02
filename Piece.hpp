#pragma once

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

inline bool operator==(const Piece& a,const Piece& b)
{
    return a.type==b.type && a.color==b.color;
}