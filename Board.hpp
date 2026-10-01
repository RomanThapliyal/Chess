#pragma once

#include "Position.hpp"

#include "Piece.hpp"
#include "Square.hpp"
#include <optional>

enum class CastlingSide{
    KingSide,
    QueenSide
};

class Board{
    public:
    
    static constexpr int SIZE=8;
    Board();
    void setPosition(const Position& pos);
    const Piece& getPiece(Square square)const;
    void setPiece(Square square, Piece piece);
    std::optional<Square> getEnPassantTarget()const;
    void setEnPassantTarget(std::optional<Square> square);

    bool canCastle(Color color) const;
    bool canCastleOnSide(Color color, CastlingSide side) const;
    void setCastlingRight(Color color, CastlingSide side, bool value);

    private:
    Piece squares[SIZE][SIZE];
    std::optional<Square> enPassantTarget;

    bool wkCastle=true;  // White kingside
    bool wqCastle=true;  // White queenside
    bool bkCastle=true;  // Black kingside
    bool bqCastle=true;  // Black queenside
};