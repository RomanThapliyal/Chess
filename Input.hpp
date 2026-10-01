#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Square.hpp"

class Input{
    
    public:
    std::optional<Square> getClickedSquare(const sf::Event& event)const;
    std::optional<sf::Keyboard::Key> getPressedKey(const sf::Event& event)const;
};