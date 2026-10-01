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