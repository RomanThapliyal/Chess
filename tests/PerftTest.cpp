#include "ChessGame.hpp"
#include "MoveGenerator.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

struct TestCaseData {
    std::string fen;
    std::vector<unsigned long long> expected;
};

unsigned long long perft(const ChessGame& game, int depth, MoveGenerator& generator) {
    if (depth == 0) return 1;

    std::vector<Move> moves =
        generator.getAllLegalMoves(game.getBoard(), game.getTurn());

    if (depth == 1) return moves.size();

    unsigned long long total = 0;

    for (const Move& move : moves) {
        ChessGame copy = game;
        copy.makeMove(move);
        total += perft(copy, depth - 1, generator);
    }

    return total;
}

int main() {
    MoveGenerator generator;

    std::string fen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ChessGame game(fen);

    double cumulativeSeconds = 0.0;

    for (int depth = 1; depth <= 7; depth++) {
        auto start = std::chrono::high_resolution_clock::now();

        unsigned long long nodes = perft(game, depth, generator);

        auto end = std::chrono::high_resolution_clock::now();
        double seconds =
            std::chrono::duration<double>(end - start).count();

        cumulativeSeconds += seconds;

        std::cout << "At depth " << depth
                  << " no. of moves: " << nodes
                  << " | seconds: " << seconds
                  << " | cumulative: " << cumulativeSeconds
                  << '\n';
    }
}