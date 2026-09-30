#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

struct Square
{
    int row;
    int col;
};
inline bool operator==(const Square& a, const Square& b) {
    return a.row == b.row && a.col == b.col;
}

class Input{
    
    public:
    std::optional<Square> getClickedSquare(const sf::Event& event)const;
    std::optional<sf::Keyboard::Key> getPressedKey(const sf::Event& event)const;
};