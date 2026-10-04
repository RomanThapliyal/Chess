#include "ChessGame.hpp"
#include "MoveGenerator.hpp"

#include <iostream>
#include <string>

struct TestCaseData{
    std::string fen;
    std::vector<unsigned long long>expected;
};
unsigned long long perft(const ChessGame& game, int depth, MoveGenerator& generator){
    if(depth==0) return 1;

    std::vector<Move> moves = generator.getAllLegalMoves(game.getBoard(),game.getTurn());

    if(depth==1) return moves.size();

    unsigned long long total=0;
    for(const Move& move:moves){
        ChessGame copy = game;
        copy.makeMove(move);
        total+=perft(copy,depth-1,generator);
    }
    return total;
}
int main(){
    MoveGenerator generator;
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessGame game(fen);
    for(int i=1;i<=7;i++){
        std::cout<<"At depth "<<i<<" no. of moves: "<<perft(game,i,generator)<<'\n';
    }
}