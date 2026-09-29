#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Renderer.hpp"

int main(){
    Board board;
    Renderer renderer;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");

    while(window.isOpen()){

        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        
        window.clear();
        renderer.drawBoard(window,board);
        window.display();
    }
}