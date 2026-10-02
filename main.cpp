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
    std::string fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessGame game(fen);
    ChessController controller(game);
    UIState uiState=UIState::Start;
    Renderer renderer;

    sf::RenderWindow window(sf::VideoMode({640,640}),"Chess");
    window.setFramerateLimit(60);

    while(window.isOpen()){

        BoardLayout layout = BoardLayout::calculate(window);

        window.clear();

        while(const std::optional event=window.pollEvent()){   //loop for input handeling

            if(event->is<sf::Event::Closed>()){       //for closing window using red cross button
                window.close();
                continue;
            }

            if(const auto* resized=event->getIf<sf::Event::Resized>()){
                sf::View view(sf::FloatRect({0.f,0.f},{static_cast<float>(resized->size.x),static_cast<float>(resized->size.y)}));
                window.setView(view);
                 std::cout << "RESIZED: "
              << resized->size.x << " x "
              << resized->size.y << '\n';
              layout = BoardLayout::calculate(window);
            }

            switch(uiState){
                case UIState::Start: handleStartInput(input, event, uiState, game, controller);
                                     break;

                case UIState::Chess: if(!controller.handleChessInput(input, *event, layout)){
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
            case UIState::Chess: renderer.drawBoard(window,game.getBoard(),controller.getSelectedSquare(),controller.getLegalMoves(),layout);
                                 break;

            case UIState::PromotionChoice:  renderer.drawBoard(window,game.getBoard(),controller.getSelectedSquare(),controller.getLegalMoves(),layout);
                                          break;                     
            
            case UIState::End: renderer.drawEndScreen(window);
                                 break;
            default: break;

        }

        window.display();
    }
}

