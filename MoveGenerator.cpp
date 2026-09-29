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

    else if(piece.type==PieceType::Rook){

        int directions[4][2]={{0,1},{0,-1},{-1,0},{1,0}};

        for(int i=0;i<4;i++){
            int dr=directions[i][0];
            int dc=directions[i][1];
            Square nextSquare{from.row+dr, from.col+dc};
            while(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None){
                    moves.push_back({from,nextSquare});
                    nextSquare.row+=dr;
                    nextSquare.col+=dc;
                }
                else if(p.color!=piece.color){
                    moves.push_back({from,nextSquare});
                    break;
                }
                else break;
            }
        }
    }

    else if(piece.type==PieceType::Bishop){

        int directions[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};

        for(int i=0;i<4;i++){
            int dr=directions[i][0];
            int dc=directions[i][1];
            Square nextSquare{from.row+dr, from.col+dc};
            while(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None){
                    moves.push_back({from,nextSquare});
                    nextSquare.row+=dr;
                    nextSquare.col+=dc;
                }
                else if(p.color!=piece.color){
                    moves.push_back({from,nextSquare});
                    break;
                }
                else break;
            }
        }
    }

    return moves;
}

bool MoveGenerator::isInside(const Board& board, const Square& square){
    return square.row>=0 && square.row<board.SIZE && 
           square.col>=0 && square.col<board.SIZE ;
}