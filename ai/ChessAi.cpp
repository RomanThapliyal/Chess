#include "ChessAi.hpp"
#include <iostream>

int ChessAi::evaluate(const Board& board){
    int whiteMaterial=0;
    int blackMaterial=0;

    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
            Square sq{row,col};
            const Piece& piece=board.getPiece(sq);
            if(piece.color==Color::White){
                whiteMaterial+=getPointsOf(piece);
            }
            else if(piece.color==Color::Black){
                blackMaterial+=getPointsOf(piece);
            }
        }
    }

    int evaluation = whiteMaterial-blackMaterial;
    std::cout<<"score="<<evaluation;
    return evaluation;
}

Move ChessAi::findBestMove(ChessGame& game, const Board& board, const std::vector<Move>& legalMoves){
    int maxPoints=-10000;
    Move bestMove;
    for(const Move& move:legalMoves){
        Board testBoard = board;
        game.makeMove(move);
        if(maxPoints<evaluate(testBoard)){
            maxPoints=evaluate(testBoard);
            bestMove=move;
        }
    }
    return bestMove;
}

int ChessAi::getPointsOf(const Piece& piece){
    switch(piece.type){
        case PieceType::Pawn: return 100;
        case PieceType::Bishop: return 330;
        case PieceType::Knight: return 320;
        case PieceType::Rook: return 500;
        case PieceType::King: return 0;
        case PieceType::Queen: return 900;

        default: return 0;
    }
}