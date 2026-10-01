#include <SFML/Graphics.hpp>

#include "Input.hpp"
#include "UIState.hpp"
#include "ChessGame.hpp"
#include "ChessController.hpp"

#include "Renderer.hpp"

std::string pieceColor(Color color){
    switch(color){
        case Color::White: return "White";
        case Color::Black: return "Black";
        default: return "None";
    }
}


void handleStartInput(const Input& input, const std::optional<sf::Event>& event,UIState& uiState, ChessGame& game, ChessController& controller){
    if(input.getPressedKey(*event)==sf::Keyboard::Key::Enter){
        uiState=UIState::Chess;
        game.reset();                     // back to starting position 
        controller.clearSelection();      // clear selection and move list
    }
}

void handlePromotionChoiceInput(const Input& input, const std::optional<sf::Event>& event, UIState& uiState, ChessController& controller){
    auto key=input.getPressedKey(*event);
    if(key==sf::Keyboard::Key::Num1){
        controller.choosePromotion(MoveFlag::PromotionQueen);
        uiState=UIState::Chess;
    }
    else if(key==sf::Keyboard::Key::Num2){
        controller.choosePromotion(MoveFlag::PromotionRook);
        uiState=UIState::Chess;
    }
    else if(key==sf::Keyboard::Key::Num3){
        controller.choosePromotion(MoveFlag::PromotionKnight);
        uiState=UIState::Chess;
    }
    else if(key==sf::Keyboard::Key::Num4){
        controller.choosePromotion(MoveFlag::PromotionBishop);
        uiState=UIState::Chess;
    }
}

void handleEndInput(const Input& input, const std::optional<sf::Event>& event,UIState& uiState, sf::RenderWindow& window){
    auto key=input.getPressedKey(*event);
    if(key==sf::Keyboard::Key::Enter){
        uiState=UIState::Start;
    }
    else if(key==sf::Keyboard::Key::X){
        window.close();
    }
}

int main(){
    Input input;
    std::string fen="1r1qkbr1/3bp1pp/3n1p2/3Q3P/1PpPpPn1/B5PR/P1P1K1B1/RNN5 b - - 2 25";
    ChessGame game(fen);
    ChessController controller(game);
    UIState uiState=UIState::Start;
    Renderer renderer;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");
    window.setFramerateLimit(60);

    while(window.isOpen()){

        window.clear();

        while(const std::optional event=window.pollEvent()){   //loop for input handeling

            if(event->is<sf::Event::Closed>()){       //for closing window using red cross button
                window.close();
                continue;
            }

            switch(uiState){
                case UIState::Start: handleStartInput(input, event, uiState, game, controller);
                                     break;

                case UIState::Chess: if(!controller.handleChessInput(input, *event)){
                                         uiState=UIState::End;
                                     }
                                     if(controller.isPromotionPending()){
                                        uiState=UIState::PromotionChoice;
                                     }
                                     break;

                case UIState::PromotionChoice: handlePromotionChoiceInput(input, *event, uiState, controller);
                                    break;

                case UIState::End:  handleEndInput(input, event, uiState, window);
                                    break;

                default: break;
            }
        }

        switch(uiState){                              //rendering 
            case UIState::Start: renderer.drawStartScreen(window);
                                 break;
            case UIState::Chess: renderer.drawBoard(window,game.getBoard(),controller.getSelectedSquare(),controller.getLegalMoves());
                                 break;

            case UIState::PromotionChoice:  renderer.drawBoard(window,game.getBoard(),controller.getSelectedSquare(),controller.getLegalMoves());
                                          break;                     
            
            case UIState::End: renderer.drawEndScreen(window);
                                 break;
            default: break;

        }

        window.display();
    }
}

