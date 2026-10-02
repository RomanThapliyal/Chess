#include "ChessController.hpp"

ChessController::ChessController(ChessGame& game):game(game){}

bool ChessController::handleChessInput(const Input& input,const sf::Event& event, const BoardLayout& layout){

    if(game.getGameState()==GameState::Checkmate||game.getGameState()==GameState::Stalemate){ //if someone lost or won
        if(input.getPressedKey(event)==sf::Keyboard::Key::E){
            return false;
        }
        return true;
    }

    auto clickedSquare=input.getClickedSquare(event,layout);

    if(!clickedSquare) return true;  //no sq clicked nothing to do

    const Piece& clickedPiece=game.getBoard().getPiece(*clickedSquare);

    //no piece selected yet and the clicked piece is of the player in turn
    if(!selectedSquare.has_value() && clickedPiece.color==game.getTurn()){
        selectedSquare=clickedSquare;
        legalMoves=game.getLegalMoves(*clickedSquare);
        return true;
    }

    //a piece is already selected 

    if(selectedSquare==clickedSquare){  //if clicked the same sqaure 
        clearSelection();               //deselect
        return true;
    }


    if(clickedPiece.color==game.getTurn()){ //clicked another piece of same color -> change selection
        selectedSquare=clickedSquare;
        legalMoves=game.getLegalMoves(*clickedSquare);
        return true;
    }

    //clicked empty or enemy square -> makeMove()

    if(clickedPiece.color!=game.getTurn()){
        if(auto move=findLegalMove(*clickedSquare)){
            std::cout<<"From: "<<move->from.row<<","<<move->from.col<<" -> To: "<<move->to.row<<","<<move->to.col<<"\n";

            if(isThisMovePromotion(move->flag)){
                startPromotion(move->from,move->to);
            }
            else{
                game.makeMove(*move);
                clearSelection();
            }

            if(game.getGameState()==GameState::Checkmate){
                std::cout<<((game.getTurn()==Color::White)?"Black ":"White ")<<"wins\n";
            }
            else if(game.getGameState()==GameState::Stalemate){
                std::cout<<"StaleMate  tie\n";
            }
        }
    }

    // Clicked empty/enemy but not a legal move → deselect
    clearSelection();
    return true;

}



void ChessController::startPromotion(const Square& from,const Square& to) {
    promotionFrom = from;
    promotionTo = to;
    promotionPending = true;
}

void ChessController::choosePromotion(MoveFlag flag){
    Move move{promotionFrom, promotionTo, flag};
    game.makeMove(move);
    clearSelection();
    promotionPending=false;
}

void ChessController::clearSelection(){
    selectedSquare = std::nullopt;   // clear selection
    legalMoves.clear();             // clear move list
}

const std::optional<Square>& ChessController::getSelectedSquare() const{
    return  selectedSquare;
}

const std::vector<Move>& ChessController::getLegalMoves()const{
    return legalMoves;
}


std::string ChessController::pieceName(PieceType type)
{
    switch(type)
    {
        case PieceType::Pawn: return "Pawn";
        case PieceType::Knight: return "Knight";
        case PieceType::Bishop: return "Bishop";
        case PieceType::Rook: return "Rook";
        case PieceType::Queen: return "Queen";
        case PieceType::King: return "King";
        default: return "None";
    }
}

std::optional<Move> ChessController::findLegalMove(const Square& to) const
{
    for(const Move& move:legalMoves){
        if(move.to==to)
            return move;
    }
    return std::nullopt;
}

bool ChessController::isPromotionPending(){
    return promotionPending;
}

void ChessController::resetPromotionPending(){
    promotionPending=false;
}

bool ChessController::isThisMovePromotion(const MoveFlag& moveflag){
    switch(moveflag){
        case MoveFlag::PromotionQueen: return true;
        case MoveFlag::PromotionRook: return true;
        case MoveFlag::PromotionKnight: return true;
        case MoveFlag::PromotionBishop: return true;

        default: return false;
    }
}