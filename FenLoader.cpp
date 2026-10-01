#include "FenLoader.hpp"

#include<iostream>
#include <cctype>

Position FenLoader::load(const std::string& fen)const{
    std::cout<<"Fenloader reaced";
    Position pos{};
    int k1=0,k2=0;
    int section=0;
    for(char ch:fen){
        switch(section){
            case 0: if(!handlePiece(ch,pos,section,k1,k2)){std::cout<<"\nFen string is invalid - missing piece\n";}
                    break;
            case 1: if(!handelTurn(ch,pos,section)){std::cout<<"\nFen string is invalid - missing turn\n";}
                    break;
            //case 2:  //castel
            //case 3:  //enpassant
            //case 4:  //half move clock
            //case 5:  //full move number
            default: break;
        }
    }
    return pos;
}




bool FenLoader::handlePiece(char ch,Position& pos,int& section,int& k1,int& k2)const{
    if(std::isalpha(ch)){           //ch == a-z A-Z  (piece)
        if(ch>='A'&&ch<='Z'){          //capital, white piece
            pos.squares[k1][k2++]=getPiece(ch,Color::White);
        }
        else if(ch>='a'&&ch<='z'){     //small, black piece
            pos.squares[k1][k2++]=getPiece(ch,Color::Black);
        }
        else {
            return false;
        }
    }
    else if(std::isdigit(ch)){   //ch== num (n empty squares in that rank)
        int n=ch-'0';
        k2+=n;
    }   
    else if(ch=='/'){  //ch== '/'  (rank ends)
        k1++;
        k2=0;
    }  

    if(ch==' ') section++;

    return true;
}

bool FenLoader::handelTurn(char ch,Position& pos,int& section)const{

    if(ch=='w') pos.turn=Color::White;
    else if(ch=='b') pos.turn=Color::Black;

    if(pos.turn==Color::None) return false;

    section++;
    return true;
}


Piece FenLoader::getPiece(char pieceName, Color pieceColor)const {
    switch (pieceName) {
        case 'k': return {PieceType::King,   pieceColor};
        case 'q': return {PieceType::Queen,  pieceColor};
        case 'r': return {PieceType::Rook,   pieceColor};
        case 'b': return {PieceType::Bishop, pieceColor};
        case 'n': return {PieceType::Knight, pieceColor};
        case 'p': return {PieceType::Pawn,   pieceColor};

        case 'K': return {PieceType::King,   pieceColor};
        case 'Q': return {PieceType::Queen,  pieceColor};
        case 'R': return {PieceType::Rook,   pieceColor};
        case 'B': return {PieceType::Bishop, pieceColor};
        case 'N': return {PieceType::Knight, pieceColor};
        case 'P': return {PieceType::Pawn,   pieceColor};
        default:  return {PieceType::None,   Color::None};
    }
}