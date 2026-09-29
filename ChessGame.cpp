#include "ChessGame.hpp"

ChessGame::ChessGame(){}

void ChessGame::makeMove(const Move& move){
    board.setPiece(move.to, board.getPiece(move.from));
    board.setPiece(move.from,{PieceType::None, Color::None});
    turn=(turn==Color::White)?Color::Black:Color::White;
}

const Board& ChessGame::getBoard()const{
    return board;
}

Color ChessGame::getTurn() const
{
    return turn;
}