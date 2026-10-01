#include "Board.hpp"

Board::Board(){
    for(int row=0;row<SIZE;row++){
        for(int col=0;col<SIZE;col++){
            squares[row][col]={PieceType::None,Color::None};
        }
    }

    squares[0][0]={PieceType::Rook,Color::Black};
    squares[0][1]={PieceType::Knight,Color::Black};
    squares[0][2]={PieceType::Bishop,Color::Black};
    squares[0][3]={PieceType::Queen,Color::Black};
    squares[0][4]={PieceType::King,Color::Black};
    squares[0][5]={PieceType::Bishop,Color::Black};
    squares[0][6]={PieceType::Knight,Color::Black};
    squares[0][7]={PieceType::Rook,Color::Black};
    
    for(int col=0;col<SIZE;col++){
        squares[1][col]={PieceType::Pawn,Color::Black};
    }

    squares[7][0]={PieceType::Rook,Color::White};
    squares[7][1]={PieceType::Knight,Color::White};
    squares[7][2]={PieceType::Bishop,Color::White};
    squares[7][3]={PieceType::Queen,Color::White};
    squares[7][4]={PieceType::King,Color::White};
    squares[7][5]={PieceType::Bishop,Color::White};
    squares[7][6]={PieceType::Knight,Color::White};
    squares[7][7]={PieceType::Rook,Color::White};
    
    for(int col=0;col<SIZE;col++){
        squares[6][col]={PieceType::Pawn,Color::White};
    }
}

const Piece& Board::getPiece(Square square) const{
    return squares[square.row][square.col];
}

void Board::setPiece(Square square, Piece piece){
    squares[square.row][square.col]=piece;
}

std::optional<Square> Board::getEnPassantTarget() const{
    return enPassantTarget;
}

void Board::setEnPassantTarget(std::optional<Square> square) {
        enPassantTarget = square;
}
