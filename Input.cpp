#include "Input.hpp"

std::optional<Square> Input::getClickedSquare(const sf::Event& event){
    if(const auto* mouse=event.getIf<sf::Event::MouseButtonPressed>()){
        if(mouse->button!=sf::Mouse::Button::Left) return std::nullopt;

        int col=mouse->position.x/TILE_SIZE;
        int row=mouse->position.y/TILE_SIZE;

        if(row>=0 && row<8 && col>=0 && col<8)
            return Square{row,col};
    }
    return std::nullopt;
}