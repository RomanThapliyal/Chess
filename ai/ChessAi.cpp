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
    return evaluation;
}

Move ChessAi::findBestMove(ChessGame& game, const std::vector<Move>& legalMoves, int depth){

    Color aiColor = game.getTurn();
    int maxPoints=INT_MIN;
    int minPoints=INT_MAX;
    Move bestMoveWhite;
    Move bestMoveBlack;
    for(const Move& move:legalMoves){
        game.makeMove(move);
        int score = miniMax(game,depth-1);
        if(maxPoints<score){
            maxPoints=score;
            bestMoveWhite=move;
        }
        if(minPoints>score){
            minPoints=score;
            bestMoveBlack=move;
        }
        game.undoMove();
    }
    if(aiColor==Color::White) return bestMoveWhite;
    return bestMoveBlack;
}

int ChessAi::miniMax(ChessGame& game, int depth){
    if(depth == 0) return evaluate(game.getBoard());

    std::vector<Move> legalMoves=game.getAllLegalMoves();
    if(legalMoves.empty()){
        game.updateGameState();
        if(game.getGameState()==GameState::Checkmate){
            if(game.getTurn()==Color::White){
                return -100000;
            }
            return 100000;
        }
        if(game.getGameState()==GameState::Stalemate){
            return 0;
        }
    }

    Color currentTurn = game.getTurn();
    int bestScore = (currentTurn==Color::White)?(INT_MIN):(INT_MAX);

    for(auto& move:legalMoves){
        game.makeMove(move);
        int score = miniMax(game,depth-1);
        game.undoMove();
        bestScore = (currentTurn==Color::White)?(std::max(score,bestScore)):(std::min(score,bestScore));
    }

    return bestScore;
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