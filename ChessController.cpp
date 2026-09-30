#include "ChessController.hpp"

ChessController::ChessController(ChessGame& game):game(game){}


bool ChessController::handleChessInput(const Input& input,const sf::Event& event){

    if(game.getGameState()==GameState::Checkmate || game.getGameState()==GameState::Stalemate){

        if(input.getPressedKey(event)==sf::Keyboard::Key::E){
            return false;     //game is over change the UIState to End
        }
        return true;
    }


    if(auto square=input.getClickedSquare(event)){
        if(!selectedSquare){
            const Piece& piece=game.getBoard().getPiece({square->row,square->col});
    
            if(piece.type!=PieceType::None && piece.color==game.getTurn()){
                selectedSquare=square;
                legalMoves=game.getLegalMoves(*selectedSquare);
                std::cout<<"Selected: "<<pieceName(piece.type)<<" Coord: "<<square->row<<", "<<square->col<<'\n';
                std::cout << "Piece moves: " << legalMoves.size() << '\n';
                std::cout <<"Game state: "<<game.getGameStateName() << '\n';
            }
        }
        else if(game.getBoard().getPiece({square->row,square->col}).color==game.getTurn()){
            const Piece& piece=game.getBoard().getPiece({square->row,square->col});
            selectedSquare=square;
            legalMoves=game.getLegalMoves(*selectedSquare);
            std::cout<<"Selected: "<<pieceName(piece.type)<<" Coord: "<<square->row<<", "<<square->col<<"\n";
            std::cout << "Piece moves: " << legalMoves.size() << '\n';
            std::cout <<"Game state: "<<game.getGameStateName()<< '\n';
        }
        else{
            if(square->row!=selectedSquare->row||square->col!=selectedSquare->col){
                for(const Move& move:legalMoves){
                    if(move.to.row==square->row&&move.to.col==square->col){
                        std::cout<<"From: "<<move.from.row<<","<<move.from.col<<" -> To: "<<move.to.row<<","<<move.to.col<<"\n";
                        if(move.flag==MoveFlag::PromotionQueen){
                            game.makeMove(move);
                        }
                        if(move.flag==MoveFlag::Normal){
                            game.makeMove(move);
                        }
                        if(game.getGameState()==GameState::Checkmate){
                            std::cout<<((game.getTurn()==Color::White)?"Black ":"White ")<<"wins\n";
                        }
                        else if(game.getGameState()==GameState::Stalemate){
                            std::cout<<"StaleMate  tie\n";
                        }
                        
                        if(move.flag==MoveFlag::PromotionQueen || move.flag==MoveFlag::Normal) break;
                    }
                }
             }
            selectedSquare=std::nullopt;
            legalMoves.clear();                           
        }
    }
    return true;
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

bool ChessController::isPromotionPending(){
    return promotionPending;
}