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
    gameState=GameState::Playing;
}

void ChessGame::makeMove(const Move& move){
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
    else{
        board.setPiece(move.to, board.getPiece(move.from));
        board.setPiece(move.from,{PieceType::None, Color::None});
    }

    if(move.flag!=MoveFlag::EnPassantTarget){
        board.setEnPassantTarget(std::nullopt);
    }

    turn=(turn==Color::White)?Color::Black:Color::White;

    if(generator.isCheckMate(board,turn)) gameState=GameState::Checkmate;
    else if(generator.isStaleMate(board,turn)) gameState=GameState::Stalemate;
    else if(generator.isInCheck(board,turn)) gameState=GameState::Check;
    else gameState=GameState::Playing;
}

const Board& ChessGame::getBoard()const{
    return board;
}

Color ChessGame::getTurn() const
{
    return turn;
}

GameState ChessGame::getGameState()const{
    return gameState;
}

std::string ChessGame::getGameStateName() const
{
    switch(gameState)
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

