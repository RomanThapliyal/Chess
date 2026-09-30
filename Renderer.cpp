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
}


void Renderer::drawStartScreen(sf::RenderWindow& window){

    //bg
    sf::RectangleShape bg({640,640});
    bg.setFillColor(sf::Color::Red);
    bg.setPosition({0,0});
    window.draw(bg);

}

void Renderer::drawBoard(sf::RenderWindow& window, const Board& board, const std::optional<Square>& selectedSquare, const std::vector<Move>&legalMoves){
    drawTiles(window);
    drawOverlays(window,selectedSquare,legalMoves);
    drawPieces(window,board);
}

void Renderer::drawEndScreen(sf::RenderWindow& window){

    //bg
    sf::RectangleShape bg({640,640});
    bg.setFillColor(sf::Color::Blue);
    bg.setPosition({0,0});
    window.draw(bg);

}

void Renderer::drawTiles(sf::RenderWindow& window){

    sf::RectangleShape tile({tileSize,tileSize});

    for(int row=0;row<Board::SIZE;row++){
        for(int col=0;col<Board::SIZE;col++){
            tile.setPosition({col*tileSize,row*tileSize});

            if((row+col)%2==0) tile.setFillColor(sf::Color(200,165,130));   //white square
            else  tile.setFillColor(sf::Color::Black);                      //black square

            window.draw(tile);
        }
    }
}

 void Renderer::drawOverlays(sf::RenderWindow& window, const std::optional<Square>& selectedSquare, const std::vector<Move>& legalMoves){
    if(selectedSquare){   //adds overlay on selected squares
        sf::RectangleShape overlay({tileSize,tileSize});
        overlay.setPosition({selectedSquare->col*tileSize,selectedSquare->row*tileSize});
        overlay.setFillColor(sf::Color(255,255,0,150));
        window.draw(overlay);
    }
    for(const Move& move:legalMoves){      //adds overlay on squares with legal moves
        sf::RectangleShape overlay({tileSize,tileSize});
        overlay.setPosition({move.to.col*tileSize,move.to.row*tileSize});
        overlay.setFillColor(sf::Color(255,0,0,100));
        window.draw(overlay);
    }
 }

 void Renderer::drawPieces(sf::RenderWindow& window,const Board& board){

    const float pieceScale=0.31f;

    for(int row=0;row<Board::SIZE;row++){
        for(int col=0;col<Board::SIZE;col++){
            
            const Piece& piece=board.getPiece({row,col});

            if(piece.type==PieceType::None) continue;

            sf::Vector2f squareCenter={col*tileSize+tileSize/2,row*tileSize+tileSize/2};

            sf::Texture& texture = getTexture(piece);
            sf::Sprite sprite(texture);

            sprite.setScale({pieceScale,pieceScale});
            sprite.setOrigin(sprite.getLocalBounds().getCenter());
            sprite.setPosition(squareCenter);

            window.draw(sprite);           
        }
    }
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