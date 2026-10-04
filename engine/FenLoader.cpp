#include "FenLoader.hpp"

#include<iostream>
#include <cctype>
#include <sstream>

Position FenLoader::load(const std::string& fen)const{
    Position pos{};

    std::istringstream iss(fen);  //creates a input stream

    std::string boardPart,turnPart,castlePart,enPassantPart;

    if(!(iss>>boardPart)){
        std::cout<<"\nFen string is invalid - missing board\n";
        return Position{};
    }

    if(!(iss>>turnPart)){
        std::cout<<"\nFen string is invalid - missing turn\n";
        return Position{};
    }
    
    if(!(iss>>castlePart)){
        std::cout<<"\nFen string is invalid - missing castle\n";
        return Position{};
    }

    if(!(iss>>enPassantPart)){
        std::cout<<"\nFen string is invalid - missing enPassant\n";
        return Position{};
    }

    if(!decodeBoard(boardPart,pos)){
        std::cout<<"\nFen string is invalid - board part malformed\n";
        return Position{};
    }

    if(!decodeTurn(turnPart,pos)){
        std::cout<<"\nFen string is invalid - turn part malformed\n";
        return Position{};
    }

    if(!decodeCastle(castlePart,pos)){
        std::cout<<"\nFen string is invalid - castle part malformed\n";
        return Position{};
    }

    if(!decodeenPassant(enPassantPart,pos)){
        std::cout<<"\nFen string is invalid - enPassant part malformed\n";
        return Position{};
    }
    return pos;
}

bool FenLoader::decodeBoard(const std::string& boardStr, Position& pos)const{
    int rank=0;
    int file=0;

    for(char ch:boardStr){
        if(std::isalpha(ch)){
            if(file>=8){
                return false;  //too many pieces on this file
            }
            pos.squares[rank][file]=getPiece(ch);
            file++;
        }
        else if(std::isdigit(ch)){
            int n=ch-'0';

            if(n<=0||n>8)
                return false; //invalid digit

            file+=n;
            if(file>8)
                return false; //too many pieces on this file
        }
        else if(ch=='/'){ //end of rank
            if(file!=8) 
                return false; //all ranks must have 8 squares
            rank++;
            file=0;
            if(rank>7)
                return false; //too many ranks
        }
        else {       //invalid character
            return false;  
        }
    }
    return (rank==7) && (file==8);
}

bool FenLoader::decodeTurn(const std::string& turnStr, Position& pos)const{
    if(turnStr.size()!=1)  
        return false;
    if(turnStr=="w"){
        pos.turn=Color::White;
        return true;
    }
    else if(turnStr=="b"){
        pos.turn=Color::Black;
        return true;
    }
    return false;
}

bool FenLoader::decodeCastle(const std::string& castleStr, Position& pos)const{
    if(castleStr.empty()||castleStr.size()>4)
        return false;

    pos.castlingRights.wkCastle = false;   
    pos.castlingRights.wqCastle = false;
    pos.castlingRights.bkCastle = false;
    pos.castlingRights.bqCastle = false;

    if(castleStr=="-"){
        return true;
    }

    for(char x:castleStr){
        switch (x) {
            case 'K':
                if(pos.squares[7][4]!=getPiece('K') || pos.squares[7][7]!=getPiece('R')) return false;
                pos.castlingRights.wkCastle = true;
                break;
            case 'Q':
                if(pos.squares[7][4]!=getPiece('K') || pos.squares[7][0]!=getPiece('R')) return false;
                pos.castlingRights.wqCastle = true;
                break;
            case 'k':
                if(pos.squares[0][4]!=getPiece('k') || pos.squares[0][7]!=getPiece('r')) return false;
                pos.castlingRights.bkCastle = true;
                break;
            case 'q':
                if(pos.squares[0][4]!=getPiece('k') || pos.squares[0][0]!=getPiece('r')) return false;
                pos.castlingRights.bqCastle = true;
                break;
            default:
                return false; // invalid character
        }
    }
    return true;
}

bool FenLoader::decodeenPassant(const std::string& enPassantStr, Position& pos)const{
    if(enPassantStr.empty()) 
        return false;

    if(enPassantStr=="-"){
        pos.enPassantTarget=std::nullopt;
        return true;
    }

    if(enPassantStr.size()!=2)
        return false;
    
    char fileChar=enPassantStr[0];
    int rankNum=enPassantStr[1]-'0';

    if(fileChar<'a'||fileChar>'h') 
        return false;

    if(rankNum<1||rankNum>8) 
        return false;

    int row;     //converting fen coords to our board coords
    int col=fileChar - 'a';

    if(pos.turn==Color::White){    //cause fen and our engine's internal representaion is diff
        if(rankNum!=6)
            return false;
        row=3;
    }
    else {
        if(rankNum!=3) return false;
        row=4;

    }


    if(row<0 || row>7)   //just for saftey
        return false;

    pos.enPassantTarget=Square{row,col};

    return true;
}

Piece FenLoader::getPiece(char pieceName)const{
    switch (pieceName) {
        case 'k': return {PieceType::King,   Color::Black};
        case 'q': return {PieceType::Queen,  Color::Black};
        case 'r': return {PieceType::Rook,   Color::Black};
        case 'b': return {PieceType::Bishop, Color::Black};
        case 'n': return {PieceType::Knight, Color::Black};
        case 'p': return {PieceType::Pawn,   Color::Black};

        case 'K': return {PieceType::King,   Color::White};
        case 'Q': return {PieceType::Queen,  Color::White};
        case 'R': return {PieceType::Rook,   Color::White};
        case 'B': return {PieceType::Bishop, Color::White};
        case 'N': return {PieceType::Knight, Color::White};
        case 'P': return {PieceType::Pawn,   Color::White};

        default:  return {PieceType::None,   Color::None};
    }
}