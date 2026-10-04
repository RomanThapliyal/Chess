#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Square.hpp"

#include "BoardLayout.hpp"

class Input{
    
    public:
    std::optional<Square> getClickedSquare(const sf::Event& event,const BoardLayout& layout)const;
    std::optional<sf::Keyboard::Key> getPressedKey(const sf::Event& event)const;
};