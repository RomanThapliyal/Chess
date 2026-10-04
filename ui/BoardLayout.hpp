#pragma once


#include <SFML/Graphics.hpp>
#include <algorithm>

class BoardLayout{
    public: 
    float boardSize;
    float boardX;
    float boardY;
    float tileSize;

    static BoardLayout calculate(sf::Vector2u size) {

        float windowWidth = size.x;
        float windowHeight = size.y;

        const float margin = 50.f;

        float boardSize = std::min(windowWidth, windowHeight) - 2 * margin;

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

    static BoardLayout calculate(const sf::RenderWindow& window) {
        return calculate(window.getSize());
    }
};