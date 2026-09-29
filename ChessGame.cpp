#include "ChessGame.hpp"

ChessGame::ChessGame(){}

const Board& ChessGame::getBoard()const{
    return board;
}

void ChessGame::makeMove(Move& move){
    board.setPiece(move.to, board.getPiece(move.from));
    board.setPiece(move.from,{PieceType::None, Color::None});
}