#pragma once


#include <SFML/Graphics.hpp>
#include <algorithm>

class BoardLayout{
    public: 
    float boardSize;
    float boardX;
    float boardY;
    float tileSize;

    static BoardLayout calculate(const sf::RenderWindow& window) {

        sf::Vector2u windowSize = window.getSize();
        float windowWidth = static_cast<float>(windowSize.x);
        float windowHeight = static_cast<float>(windowSize.y);

        const float margin = 50.f;

        float boardSize = std::min(windowWidth, windowHeight) - 2 * margin;

        boardSize = std::max(boardSize,1.f);

        float boardX = (windowWidth - boardSize) / 2.f;
        float boardY = (windowHeight - boardSize) / 2.f;

        float tileSize = boardSize / 8.f;

        return {
            boardSize,
            boardX,
            boardY,
            tileSize
        };
    }
};