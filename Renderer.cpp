#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(){      //loads all piece's images
    
    if(!whitePawn.loadFromFile("Assets/Pieces/WhiteWood/Pawn.png")) std::cout<<"Cant load white pawn.png";
    if(!whiteKnight.loadFromFile("Assets/Pieces/WhiteWood/Knight.png")) std::cout<<"Cant load white knight.png";
    if(!whiteBishop.loadFromFile("Assets/Pieces/WhiteWood/Bishop.png")) std::cout<<"Cant load white bishop.png";
    if(!whiteRook.loadFromFile("Assets/Pieces/WhiteWood/Rook.png")) std::cout<<"Cant load white rook.png";
    if(!whiteQueen.loadFromFile("Assets/Pieces/WhiteWood/Queen.png")) std::cout<<"Cant load white queen.png";
    if(!whiteKing.loadFromFile("Assets/Pieces/WhiteWood/King.png")) std::cout<<"Cant load white king.png";

    if(!blackPawn.loadFromFile("Assets/Pieces/BlackWood/Pawn.png")) std::cout<<"Cant load black pawn.png";
    if(!blackKnight.loadFromFile("Assets/Pieces/BlackWood/Knight.png")) std::cout<<"Cant load black knight.png";
    if(!blackBishop.loadFromFile("Assets/Pieces/BlackWood/Bishop.png")) std::cout<<"Cant load black bishop.png";
    if(!blackRook.loadFromFile("Assets/Pieces/BlackWood/Rook.png")) std::cout<<"Cant load black rook.png";
    if(!blackQueen.loadFromFile("Assets/Pieces/BlackWood/Queen.png")) std::cout<<"Cant load black queen.png";
    if(!blackKing.loadFromFile("Assets/Pieces/BlackWood/King.png")) std::cout<<"Cant load black king.png";

    if (!gameFont.openFromFile("Assets/Fonts/PressStart2P-Regular.ttf")) std::cout << "cant load font\n";
}


void Renderer::drawStartScreen(sf::RenderWindow& window,const StartScreenLayout& layout){

    //bg
    sf::RectangleShape bg({layout.screenWidth,layout.screenHeight});
    bg.setFillColor(sf::Color::Black);
    bg.setPosition(layout.screenCenter);
    bg.setOrigin(bg.getLocalBounds().getCenter());
    window.draw(bg);
 
    //logo
    sf::Texture& texture = whiteQueen;
    sf::Sprite logo(texture);
    logo.setPosition(layout.logo);
    float scale=layout.logoSize/texture.getSize().x;
    logo.setScale({scale,scale});
    logo.setOrigin(logo.getLocalBounds().getCenter());
    window.draw(logo);
 
    //title
    drawCenteredText(window,"Chess",layout.title,layout.titleSize);

    //startbutton
    drawButton(window,layout.startButton,layout.startButtonSize,layout.buttonOutline,"Start",layout.buttonTextSize);
    //endbutton
    drawButton(window,layout.quitButton,layout.quitButtonSize,layout.buttonOutline,"Quit",layout.buttonTextSize);

}

void Renderer::drawBoard(sf::RenderWindow& window, const Board& board, const std::optional<Square>& selectedSquare, const std::vector<Move>&legalMoves, const BoardLayout& layout){

    drawTiles(window,layout.boardX,layout.boardY,layout.tileSize);
    drawOverlays(window,selectedSquare,legalMoves,layout.boardX,layout.boardY,layout.tileSize);
    drawPieces(window,board,layout.boardX,layout.boardY,layout.tileSize);

}

void Renderer::drawEndScreen(sf::RenderWindow& window){

    //bg
    sf::RectangleShape bg({640,640});
    bg.setFillColor(sf::Color::Blue);
    bg.setPosition({0,0});
    window.draw(bg);

}

void Renderer::drawTiles(sf::RenderWindow& window, float boardX, float boardY, float tileSize){

    sf::RectangleShape tile({tileSize,tileSize});

    for(int row=0;row<Board::SIZE;row++){
        for(int col=0;col<Board::SIZE;col++){
            tile.setPosition({boardX+col*tileSize,boardY+row*tileSize});

            if((row+col)%2==0) tile.setFillColor(sf::Color(200,165,130));   //white square
            else  tile.setFillColor(sf::Color::Black);                      //black square

            window.draw(tile);
        }
    }
}

 void Renderer::drawOverlays(sf::RenderWindow& window, const std::optional<Square>& selectedSquare, const std::vector<Move>& legalMoves, float boardX, float boardY, float tileSize){
    if(selectedSquare){   //adds overlay on selected squares
        sf::RectangleShape overlay({tileSize,tileSize});
        overlay.setPosition({boardX+selectedSquare->col*tileSize,boardY+selectedSquare->row*tileSize});
        overlay.setFillColor(sf::Color(255,255,0,150));
        window.draw(overlay);
    }
    for(const Move& move:legalMoves){      //adds overlay on squares with legal moves
        sf::RectangleShape overlay({tileSize,tileSize});
        overlay.setPosition({boardX+move.to.col*tileSize,boardY+move.to.row*tileSize});
        overlay.setFillColor(sf::Color(255,0,0,100));
        window.draw(overlay);
    }
 }

 void Renderer::drawPieces(sf::RenderWindow& window,const Board& board, float boardX, float boardY, float tileSize){

    const float pieceScale=0.31f*tileSize/TILE_SIZE;

    for(int row=0;row<Board::SIZE;row++){
        for(int col=0;col<Board::SIZE;col++){
            
            const Piece& piece=board.getPiece({row,col});

            if(piece.type==PieceType::None) continue;

            sf::Vector2f squareCenter={boardX+col*tileSize+tileSize/2,boardY+row*tileSize+tileSize/2};

            sf::Texture& texture = getTexture(piece);
            sf::Sprite sprite(texture);

            sprite.setScale({pieceScale,pieceScale});
            sprite.setOrigin(sprite.getLocalBounds().getCenter());
            sprite.setPosition(squareCenter);

            window.draw(sprite);           
        }
    }
 }

 void Renderer::drawCenteredText(sf::RenderWindow& window, const std::string& content, sf::Vector2f position, float size){

    sf::Text text(gameFont);
    text.setString(content);
    text.setCharacterSize(static_cast<unsigned>(size));
    text.setPosition(position);
    text.setOrigin(text.getLocalBounds().position+text.getLocalBounds().size/2.f);
    window.draw(text);
}

void Renderer::drawButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float outline, const std::string& label, float textSize){

    sf::RectangleShape button;
    button.setSize(size);
    button.setFillColor(sf::Color::Magenta);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(outline);
    button.setPosition(position);
    button.setOrigin(button.getLocalBounds().getCenter());
    window.draw(button);

    drawCenteredText(window,label,position,textSize);
}

sf::Texture& Renderer::getTexture(const Piece& piece){
    if(piece.color == Color::White)
    {
        switch(piece.type)
        {
            case PieceType::Pawn: return whitePawn;
            case PieceType::Knight: return whiteKnight;
            case PieceType::Bishop: return whiteBishop;
            case PieceType::Rook: return whiteRook;
            case PieceType::Queen: return whiteQueen;
            case PieceType::King: return whiteKing;
            default: break;
        }
    }
    else
    {
        switch(piece.type)
        {
            case PieceType::Pawn: return blackPawn;
            case PieceType::Knight: return blackKnight;
            case PieceType::Bishop: return blackBishop;
            case PieceType::Rook: return blackRook;
            case PieceType::Queen: return blackQueen;
            case PieceType::King: return blackKing;
            default: break;
        }
    }

    return whitePawn;

 }