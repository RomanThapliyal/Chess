#include "Renderer.hpp"

void Renderer::drawBoard(sf::RenderWindow& window,const Board& board){

    const float tileSize = 80.f;

    sf::RectangleShape tile({tileSize,tileSize});

    for(int row=0;row<Board::SIZE;row++){
        for(int col=0;col<Board::SIZE;col++){
            tile.setPosition({col*tileSize,row*tileSize});
            if((row+col)%2==0) tile.setFillColor(sf::Color::White);
            else  tile.setFillColor(sf::Color::Black);
            window.draw(tile);
        }
    }
}