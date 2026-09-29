#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

struct Square
{
    int row;
    int col;
};

class Input{
    
    public:
    static std::optional<Square> getClickedSquare(const sf::Event& event);
};