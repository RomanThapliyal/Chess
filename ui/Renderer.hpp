#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "BoardLayout.hpp"
#include "StartScreenLayout.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Move.hpp"
#include <vector>

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

    sf::Font gameFont;

    public:

    Renderer();

    void drawBoard(sf::RenderWindow& window,const Board& board, const std::optional<Square>& selectedSquare, const std::vector<Move>& legalMoves, const BoardLayout& layout);
    
    void drawStartScreen(sf::RenderWindow& window,const StartScreenLayout& layout);
    void drawEndScreen(sf::RenderWindow& window);

    void drawTiles(sf::RenderWindow& window, float boardX, float boardY, float tileSize);
    void drawOverlays(sf::RenderWindow& window, const std::optional<Square>& selectedSquare, const std::vector<Move>& legalMoves, float boardX, float boardY, float tileSize);
    void drawPieces(sf::RenderWindow& window,const Board& board, float boardX, float boardY, float tileSize);

    void drawCenteredText(sf::RenderWindow& window, const std::string& content, sf::Vector2f position, float size);
    void drawButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float outline, const std::string& label, float textSize);
    sf::Texture& getTexture(const Piece& piece);
};