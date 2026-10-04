#include "Board.hpp"
#include <iostream>

Board::Board(){
    for(int row=0;row<SIZE;row++){
        for(int col=0;col<SIZE;col++){
            squares[row][col]={PieceType::None,Color::None};
        }
    }

    /*squares[0][0]={PieceType::Rook,Color::Black};
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
    }*/
}


void Board::setPosition(const Position& pos){
    for(int row=0;row<SIZE;row++){
        for(int col=0;col<SIZE;col++){
            squares[row][col]=pos.squares[row][col];
        }
    }

    castlingRights.wkCastle=pos.castlingRights.wkCastle;
    castlingRights.wqCastle=pos.castlingRights.wqCastle;
    castlingRights.bkCastle=pos.castlingRights.bkCastle;
    castlingRights.bqCastle=pos.castlingRights.bqCastle;
    
    enPassantTarget=pos.enPassantTarget;
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


bool Board::canCastle(Color color) const{
    switch (color)
    {
    case Color::White: return castlingRights.wkCastle || castlingRights.wqCastle;
    case Color::Black: return castlingRights.bkCastle || castlingRights.bqCastle;

    default:std::cout<<"This piece is non existent error canCastel()------\n";
        return false;
    }
}

bool Board::canCastleOnSide(Color color, CastlingSide side) const{
    switch(color){

        case Color::White: return (side==CastlingSide::KingSide)?(castlingRights.wkCastle):(castlingRights.wqCastle);
        case Color::Black: return (side==CastlingSide::KingSide)?(castlingRights.bkCastle):(castlingRights.bqCastle);

        default: std::cout<<"This piece is non existent error canCastelOnSide()------\n";
                 return false;
    }
}
void Board::setCastlingRight(Color color, CastlingSide side, bool value){
    switch(color){
        case Color::White: (side==CastlingSide::KingSide)?(castlingRights.wkCastle=value):(castlingRights.wqCastle=value);
                            break;
        case Color::Black: (side==CastlingSide::KingSide)?(castlingRights.bkCastle=value):(castlingRights.bqCastle=value);
                            break;

        default: std::cout<<"This piece is non existent error setCastlingRight() ------\n";
                 break;
    }
}

Position Board::getPosition() const{
    Position position;
    position.castlingRights=castlingRights;
    position.enPassantTarget=enPassantTarget;
    
    for(int row=0;row<SIZE;row++){
        for(int col=0;col<SIZE;col++){
            position.squares[row][col]=squares[row][col];
        }
    }
    return position;
}