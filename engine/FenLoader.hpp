#pragma once

#include "Position.hpp"
#include <string>

class FenLoader{
    public:
    Position load(const std::string& fen)const;

    private:
    bool decodeBoard(const std::string& boardStr, Position& pos)const;
    bool decodeTurn(const std::string& turnStr, Position& pos)const;
    bool decodeCastle(const std::string& castleStr, Position& pos)const;
    bool decodeenPassant(const std::string& enPassantStr, Position& pos)const;

    Piece getPiece(char pieceName)const;
};