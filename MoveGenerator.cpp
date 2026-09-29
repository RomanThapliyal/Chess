#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::getMoves(const Board& board,const Square& from){

    std::vector<Move>moves;
    const Piece& piece=board.getPiece(from);

    if(piece.type==PieceType::None) return moves;

    if(piece.type==PieceType::Pawn){

        int direction=(piece.color==Color::White)?-1:1;

        Square nextSquare{from.row+direction, from.col};

        if(isInside(board,nextSquare)&&board.getPiece(nextSquare).type==PieceType::None){

            moves.push_back({from,nextSquare});

            bool isOnStartRank=(piece.color==Color::White&&from.row==6)||(piece.color==Color::Black&&from.row==1);

            if(isOnStartRank){
                Square doubleStep{nextSquare.row+direction,nextSquare.col};
                if(isInside(board,doubleStep)&&board.getPiece(doubleStep).type==PieceType::None)
                    moves.push_back({from,doubleStep});
            }
        }

        Square captureLeft{from.row+direction,from.col-1};
        Square captureRight{from.row+direction,from.col+1};

        if(isInside(board,captureLeft)){
            const Piece& captured=board.getPiece(captureLeft);
            if(captured.type!=PieceType::None && captured.color!=piece.color)
                moves.push_back({from,captureLeft});
        }

        if(isInside(board,captureRight)){
            const Piece& captured = board.getPiece(captureRight);
            if(captured.type!=PieceType::None && captured.color!=piece.color)
                moves.push_back({from,captureRight});
        }
    }

    return moves;
}

bool MoveGenerator::isInside(const Board& board, const Square& square){
    return square.row>=0 && square.row<board.SIZE && 
           square.col>=0 && square.col<board.SIZE ;
}