#include "ChessGame.hpp"

ChessGame::ChessGame(){}

void ChessGame::makeMove(const Move& move){
    board.setPiece(move.to, board.getPiece(move.from));
    board.setPiece(move.from,{PieceType::None, Color::None});
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