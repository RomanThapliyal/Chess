#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Renderer{
    private:
    sf::Texture whitePawn;
    sf::Texture whiteKnight;
    sf::Texture whiteBishop;
    sf::Texture whiteRook;
    sf::Texture whiteQueen;
    sf::Texture whiteKing;

    sf::Texture blackPawn;
    sf::Texture blackKnight;
    sf::Texture blackBishop;
    sf::Texture blackRook;
    sf::Texture blackQueen;
    sf::Texture blackKing;

    public:
    Renderer();
    void drawBoard(sf::RenderWindow& window,const Board& board);
    sf::Texture& getTexture(const Piece& piece);
};