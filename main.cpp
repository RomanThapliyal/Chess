#include <SFML/Graphics.hpp>

#include "Input.hpp"
#include "Board.hpp"
#include "Renderer.hpp"

#include <iostream>

int main(){
    Input input;
    Board board;
    Renderer renderer;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");

    while(window.isOpen()){

        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if(auto square=input.getClickedSquare(*event)){
                std::cout<<"Clicked: "<<square->row<<", "<<square->col<<"\n";
            }
        }
        
        window.clear();
        renderer.drawBoard(window,board);
        window.display();
    }
}