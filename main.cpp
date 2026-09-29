#include <SFML/Graphics.hpp>

#include "Input.hpp"
#include "ChessGame.hpp"
#include "Renderer.hpp"

#include <iostream>

std::string pieceName(PieceType type)
{
    switch(type)
    {
        case PieceType::Pawn: return "Pawn";
        case PieceType::Knight: return "Knight";
        case PieceType::Bishop: return "Bishop";
        case PieceType::Rook: return "Rook";
        case PieceType::Queen: return "Queen";
        case PieceType::King: return "King";
        default: return "None";
    }
}

int main(){
    Input input;
    ChessGame game;
    Renderer renderer;

    std::optional <Square> selectedSquare;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");

    while(window.isOpen()){

        while(const std::optional event=window.pollEvent()){

            if(event->is<sf::Event::Closed>()){
                window.close();
            }

            if(auto square=input.getClickedSquare(*event)){
                if(!selectedSquare){
                    const Piece& piece=game.getBoard().squares[square->row][square->col];

                    if(piece.type!=PieceType::None){
                        selectedSquare=square;
                        std::cout<<"Selected: "<<pieceName(piece.type)<<" Coord: "<<square->row<<", "<<square->col<<"\n";
                    }
                }
                else{
                    if(square->row!=selectedSquare->row||square->col!=selectedSquare->col){
                        Move move{*selectedSquare,*square};
                        game.makeMove(move);
                    }
                    selectedSquare=std::nullopt;
                }
            }
        }
        
        window.clear();
        renderer.drawBoard(window,game.getBoard(),selectedSquare);
        window.display();
    }
}