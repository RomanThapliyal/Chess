#include "ChessGame.hpp"

ChessGame::ChessGame(){}

const Board& ChessGame::getBoard()const{
    return board;
}

void ChessGame::makeMove(Move& move){
    board.squares[move.to.row][move.to.col]=board.squares[move.from.row][move.from.col];
    board.squares[move.from.row][move.from.col]={PieceType::None,Color::None};
}