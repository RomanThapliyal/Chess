#pragma once

#include "Position.hpp"
#include <string>

class FenLoader{
    public:
    Position load(const std::string& fen)const;

    private:
    bool handlePiece(char ch,Position& pos,int& section,int& k1,int& k2)const;
    bool handelTurn(char ch,Position& pos,int& section)const;

    Piece getPiece(char pieceName, Color pieceColor)const;
};