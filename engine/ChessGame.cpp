#include "ChessGame.hpp"

ChessGame::ChessGame(const std::string& fen){
    FenLoader loader;
    startingPosition=loader.load(fen);
    board.setPosition(startingPosition);
    turn=startingPosition.turn;
;}

void ChessGame::reset(){
    board.setPosition(startingPosition);
    turn=startingPosition.turn;
    gameStateUpToDate=false;
    gameHistory.clear();
}

void ChessGame::makeMove(const Move& move){
    gameHistory.push_back({board.getPosition(),turn,gameState});

    const Piece& capturedPiece=board.getPiece(move.to);
    if(capturedPiece.type==PieceType::Rook){
        if(move.to.row==0&&move.to.col==0)
            board.setCastlingRight(Color::Black,CastlingSide::QueenSide,false);
        else if(move.to.row==0&&move.to.col==7)
            board.setCastlingRight(Color::Black,CastlingSide::KingSide,false);
        else if(move.to.row==7&&move.to.col==0)
            board.setCastlingRight(Color::White,CastlingSide::QueenSide,false);
        else if(move.to.row==7&&move.to.col==7)
            board.setCastlingRight(Color::White,CastlingSide::KingSide,false);
    }

    if(move.flag==MoveFlag::PromotionQueen){
        board.setPiece(move.to, {PieceType::Queen, turn});
        board.setPiece(move.from,{PieceType::None, Color::None});
    }
    else if(move.flag==MoveFlag::PromotionRook){
        board.setPiece(move.to, {PieceType::Rook, turn});
        board.setPiece(move.from,{PieceType::None, Color::None});
    }
    else if(move.flag==MoveFlag::PromotionKnight){
        board.setPiece(move.to, {PieceType::Knight, turn});
        board.setPiece(move.from,{PieceType::None, Color::None});
    }
    else if(move.flag==MoveFlag::PromotionBishop){
        board.setPiece(move.to, {PieceType::Bishop, turn});
        board.setPiece(move.from,{PieceType::None, Color::None});
    }
    else if(move.flag==MoveFlag::EnPassantTarget){

        board.setEnPassantTarget(move.to);    //saves the square where the double pushed pawn moved
        
        board.setPiece(move.to, board.getPiece(move.from));
        board.setPiece(move.from,{PieceType::None, Color::None});
    }
    else if(move.flag==MoveFlag::EnPassantCapture){

        board.setPiece(move.to, board.getPiece(move.from));
        board.setPiece(move.from,{PieceType::None, Color::None});
        board.setPiece(*board.getEnPassantTarget(),{PieceType::None, Color::None});    //removes the pawn captured by enpassant
    }
    else if(move.flag==MoveFlag::CastleKingSide || move.flag==MoveFlag::CastleQueenSide){

        const Piece& king=board.getPiece(move.from);

        board.setPiece(move.to, king);  //move the king to next Squrae

        if(move.flag==MoveFlag::CastleKingSide){
            if(king.color==Color::White){
                //Rook (7,7) -> (7,5)
                board.setPiece({7,5},{PieceType::Rook,king.color});
                board.setPiece({7,7},{PieceType::None,Color::None});
            }
            else if(king.color==Color::Black){
                //Rook (0,7) -> (0,5)
                board.setPiece({0,5},{PieceType::Rook,king.color});
                board.setPiece({0,7},{PieceType::None,Color::None});
            }
        }
        else {  //queen side castle
            if(king.color==Color::White){
                //Rook (7,0) -> (7,3)
                board.setPiece({7,3},{PieceType::Rook,king.color});
                board.setPiece({7,0},{PieceType::None,Color::None});
            }
            else if(king.color==Color::Black){
                //Rook (0,0) -> (0,3)
                board.setPiece({0,3},{PieceType::Rook,king.color});
                board.setPiece({0,0},{PieceType::None,Color::None});
            }
        }
        //castle done rights lost 
        board.setCastlingRight(king.color,CastlingSide::KingSide,false);
        board.setCastlingRight(king.color,CastlingSide::QueenSide,false);

        board.setPiece(move.from,{PieceType::None, Color::None}); //clear king's old square
    }
    else{
        const Piece& movingPiece=board.getPiece(move.from);  // the piece which is moving
        board.setPiece(move.to, movingPiece);   //moves the moving piece to next square

        if(movingPiece.type==PieceType::King){      //if king moves, it loses castel rights
            board.setCastlingRight(movingPiece.color,CastlingSide::KingSide,false);
            board.setCastlingRight(movingPiece.color,CastlingSide::QueenSide,false);
        }
        else if(movingPiece.type==PieceType::Rook){
        int homeRow=(movingPiece.color==Color::White)?7:0;
        if(move.from.row==homeRow&&move.from.col==0){
            board.setCastlingRight(movingPiece.color, CastlingSide::QueenSide,false);
        }
        else if(move.from.row==homeRow&&move.from.col==7){
            board.setCastlingRight(movingPiece.color, CastlingSide::KingSide,false);
        }
    }

        board.setPiece(move.from,{PieceType::None, Color::None}); //clear the previous sqaure of moved piece
    }

    if(move.flag!=MoveFlag::EnPassantTarget){
        board.setEnPassantTarget(std::nullopt);
    }

    turn=(turn==Color::White)?Color::Black:Color::White;

    gameStateUpToDate=false;
}

void ChessGame::undoMove(){
    if(gameHistory.empty()) return;

    const UndoState& state = gameHistory.back();
    board.setPosition(state.previousPosition);
    turn=state.previousTurn;
    gameState=state.previousGameState;

    gameHistory.pop_back();

    gameStateUpToDate=true;
}

const Board& ChessGame::getBoard()const{
    return board;
}

Color ChessGame::getTurn() const
{
    return turn;
}

void ChessGame::updateGameState(){
    if(generator.isCheckMate(board,turn)) gameState=GameState::Checkmate;
    else if(generator.isStaleMate(board,turn)) gameState=GameState::Stalemate;
    else if(generator.isInCheck(board,turn)) gameState=GameState::Check;
    else gameState=GameState::Playing;
    gameStateUpToDate=true;
}

GameState ChessGame::getGameState(){
    if(!gameStateUpToDate){
        updateGameState();
    }
    return gameState;
}

std::string ChessGame::getGameStateName()
{
    switch(getGameState())
    {
        case GameState::Playing: return "Playing";
        case GameState::Check: return "Check";
        case GameState::Checkmate: return "Checkmate";
        case GameState::Stalemate: return "Stalemate";
    }
    return "Unknown";
}

std::vector<Move> ChessGame::getLegalMoves(const Square& square){
    std::vector<Move> legalMoves;
    legalMoves=generator.getLegalMoves(board, square);
    return legalMoves;
}

std::vector<Move> ChessGame::getAllLegalMoves(){
    return generator.getAllLegalMoves(board,turn);
}
