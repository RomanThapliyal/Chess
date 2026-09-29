#include <SFML/Graphics.hpp>

#include "Input.hpp"
#include "ChessGame.hpp"
#include "MoveGenerator.hpp"
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
    MoveGenerator generator;
    Renderer renderer;

    std::optional <Square> selectedSquare;

    std::vector<Move>legalMoves;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");

    while(window.isOpen()){

        while(const std::optional event=window.pollEvent()){

            if(event->is<sf::Event::Closed>()){
                window.close();
            }

            if(auto square=input.getClickedSquare(*event)){
                if(!selectedSquare){
                    const Piece& piece=game.getBoard().getPiece({square->row,square->col});

                    if(piece.type!=PieceType::None){
                        selectedSquare=square;
                        legalMoves=generator.getMoves(game.getBoard(),*selectedSquare);
                        std::cout<<"Selected: "<<pieceName(piece.type)<<" Coord: "<<square->row<<", "<<square->col<<"\n";
                    }
                }
                else{
                    if(square->row!=selectedSquare->row||square->col!=selectedSquare->col){
                        for(const Move& move:legalMoves){
                            if(move.to.row==square->row&&move.to.col==square->col){
                                std::cout<<"From: "<<move.from.row<<","<<move.from.col<<" -> To: "<<move.to.row<<","<<move.to.col<<"\n";
                                Move move{*selectedSquare,*square};
                                game.makeMove(move);
                            }
                        }
                    }
                    selectedSquare=std::nullopt;
                    legalMoves.clear();
                }
            }
        }
        
        window.clear();
        renderer.drawBoard(window,game.getBoard(),selectedSquare,legalMoves);
        window.display();
    }
}