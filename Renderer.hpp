#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Renderer{
    public:
    void drawBoard(sf::RenderWindow& window,const Board& board);
};