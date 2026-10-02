#include "Input.hpp"

std::optional<Square> Input::getClickedSquare(const sf::Event& event, const BoardLayout& layout) const {

    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button != sf::Mouse::Button::Left)
            return std::nullopt;

        float mouseX = mouse->position.x;
        float mouseY = mouse->position.y;

        if (mouseX >= layout.boardX && mouseX < layout.boardX + layout.boardSize &&
            mouseY >= layout.boardY && mouseY < layout.boardY + layout.boardSize) {

            int col = (mouseX - layout.boardX) / layout.tileSize;
            int row = (mouseY - layout.boardY) / layout.tileSize;

            return Square{row, col};
        }
    }

    return std::nullopt;
}


 std::optional<sf::Keyboard::Key> Input::getPressedKey(const sf::Event& event) const{
    if(const auto* key=event.getIf<sf::Event::KeyPressed>())
        return key->code;

    return std::nullopt;
 }