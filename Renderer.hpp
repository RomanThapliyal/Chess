#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Input.hpp"
#include "Constants.hpp"

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

    const float tileSize=TILE_SIZE;

    Renderer();
    void drawBoard(sf::RenderWindow& window,const Board& board, std::optional<Square>& selectedSquare);
    sf::Texture& getTexture(const Piece& piece);
};