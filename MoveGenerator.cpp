#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::getMoves(const Board& board,const Square& from){

    std::vector<Move>moves;
    const Piece& piece=board.getPiece(from);

    if(piece.type==PieceType::None) return moves;

    if(piece.type==PieceType::Pawn){

        int direction=(piece.color==Color::White)?-1:1;

        Square nextSquare{from.row+direction, from.col};

        if(isInside(board,nextSquare)&&board.getPiece(nextSquare).type==PieceType::None){

            moves.push_back({from,nextSquare});

            bool isOnStartRank=(piece.color==Color::White&&from.row==6)||(piece.color==Color::Black&&from.row==1);

            if(isOnStartRank){
                Square doubleStep{nextSquare.row+direction,nextSquare.col};
                if(isInside(board,doubleStep)&&board.getPiece(doubleStep).type==PieceType::None)
                    moves.push_back({from,doubleStep});
            }
        }

        Square captureLeft{from.row+direction,from.col-1};
        Square captureRight{from.row+direction,from.col+1};

        if(isInside(board,captureLeft)){
            const Piece& captured=board.getPiece(captureLeft);
            if(captured.type!=PieceType::None && captured.color!=piece.color)
                moves.push_back({from,captureLeft});
        }

        if(isInside(board,captureRight)){
            const Piece& captured = board.getPiece(captureRight);
            if(captured.type!=PieceType::None && captured.color!=piece.color)
                moves.push_back({from,captureRight});
        }
    }

    else if(piece.type==PieceType::Rook){

        int rookDirs[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
        addSlidingMoves(board, from, piece, rookDirs, moves);
    }

    else if(piece.type==PieceType::Bishop){

        int bishopDirs[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
        addSlidingMoves(board, from, piece, bishopDirs, moves);
    }

    else if(piece.type==PieceType::Queen){
        int dir1[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
        addSlidingMoves(board, from, piece, dir1, moves);

        int dir2[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
        addSlidingMoves(board, from, piece, dir2, moves);
    }

    else if(piece.type==PieceType::Knight){

        int KnightDir[8][2]={{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};

        for(int i=0;i<8;i++){

            int dr=KnightDir[i][0];
            int dc=KnightDir[i][1];

            Square nextSquare{from.row+dr, from.col+dc};

            if(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None||p.color!=piece.color){
                    moves.push_back({from,nextSquare});
                }
            }
        }
    }
    else if(piece.type==PieceType::King){

        int KingDir[8][2]={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

        for(int i=0;i<8;i++){

            int dr=KingDir[i][0];
            int dc=KingDir[i][1];

            Square nextSquare{from.row+dr, from.col+dc};

            if(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None||p.color!=piece.color){
                    moves.push_back({from,nextSquare});
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::getLegalMoves(const Board& board,const Square& from){
    std::vector<Move> legalMoves;
    std::vector<Move> moves=getMoves(board,from);

    Color color=board.getPiece(from).color;

    for(const auto& move:moves){
        Board testBoard=board;

        testBoard.setPiece(move.to, testBoard.getPiece(move.from));
        testBoard.setPiece(move.from,{PieceType::None, Color::None});

        if(!isInCheck(testBoard,color)){
            legalMoves.push_back(move);
        }
    }
    return legalMoves;
}

std::vector<Square> MoveGenerator::getAttackSquares(const Board& board,const Square& from){

    std::vector<Square> attackSquares;
    const Piece& piece = board.getPiece(from);

    if (piece.type == PieceType::None) return attackSquares;

    if(piece.type==PieceType::Pawn){

        int direction=(piece.color==Color::White)?-1:1;

        Square captureLeft{from.row+direction,from.col-1};
        Square captureRight{from.row+direction,from.col+1};

        if(isInside(board,captureLeft))
            attackSquares.push_back(captureLeft);

        if(isInside(board,captureRight))
            attackSquares.push_back(captureRight);
    }

    else if(piece.type==PieceType::Rook){

        int rookDirs[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
        addSlidingSquares(board, from, piece, rookDirs, attackSquares);
    }

    else if(piece.type==PieceType::Bishop){

        int bishopDirs[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
        addSlidingSquares(board, from, piece, bishopDirs, attackSquares);
    }

    else if(piece.type==PieceType::Queen){
        int dir1[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
        addSlidingSquares(board, from, piece, dir1, attackSquares);

        int dir2[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
        addSlidingSquares(board, from, piece, dir2, attackSquares);
    }

    else if(piece.type==PieceType::Knight){

        int KnightDir[8][2]={{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};

        for(int i=0;i<8;i++){

            int dr=KnightDir[i][0];
            int dc=KnightDir[i][1];

            Square nextSquare{from.row+dr, from.col+dc};

            if(isInside(board,nextSquare)){
                attackSquares.push_back(nextSquare);
            }
        }
    }
    else if(piece.type==PieceType::King){

        int KingDir[8][2]={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

        for(int i=0;i<8;i++){

            int dr=KingDir[i][0];
            int dc=KingDir[i][1];

            Square nextSquare{from.row+dr, from.col+dc};

            if(isInside(board,nextSquare)){
                attackSquares.push_back(nextSquare);
            }
        }
    }
    return attackSquares;
}

bool MoveGenerator::isSquareAttacked(const Board& board,const Square& target, Color& attackingColor){
    std::vector<Square>attackSquares;
    for(int row=0;row<board.SIZE;row++){
        for(int col=0;col<board.SIZE;col++){

            Square square{row,col};
            const Piece& piece=board.getPiece(square);

            if(piece.type==PieceType::None||piece.color!=attackingColor) continue;

            attackSquares=getAttackSquares(board,square);

            for(const auto& sq:attackSquares){
                if(sq==target){
                    return true;
                }
            }
        }
    }
    return false;
}

bool MoveGenerator::isInCheck(const Board& board, Color& color){

    Color attackingColor=(color==Color::White)?Color::Black : Color::White;
    Square kingSquare{-1,-1};

    for(int row=0;row<board.SIZE;row++){
        for(int col=0;col<board.SIZE;col++){
            Square square{row,col};
            const Piece& piece=board.getPiece(square);
            if(piece.type==PieceType::King&&piece.color!=attackingColor){
                kingSquare=square;
                row=board.SIZE;  //breaks outer loop
                break;           //breakes inner loop
            }
        }
    }
    return isSquareAttacked(board,kingSquare,attackingColor);
}

bool MoveGenerator::isInside(const Board& board, const Square& square){
    return square.row>=0 && square.row<board.SIZE && 
           square.col>=0 && square.col<board.SIZE ;
}

void MoveGenerator::addSlidingMoves(const Board& board, const Square& from, const Piece& piece, const int (&directions)[4][2],std::vector<Move>& moves){
    for(int i=0;i<4;i++){
            int dr=directions[i][0];
            int dc=directions[i][1];
            Square nextSquare{from.row+dr, from.col+dc};
            while(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None){
                    moves.push_back({from,nextSquare});
                    nextSquare.row+=dr;
                    nextSquare.col+=dc;
                }
                else if(p.color!=piece.color){
                    moves.push_back({from,nextSquare});
                    break;
                }
                else break;
            }
        }
}

void MoveGenerator::addSlidingSquares(const Board& board, const Square& from, const Piece& piece, const int (&directions)[4][2],std::vector<Square>& square){
    for(int i=0;i<4;i++){
            int dr=directions[i][0];
            int dc=directions[i][1];
            Square nextSquare{from.row+dr, from.col+dc};
            while(isInside(board,nextSquare)){
                const Piece& p=board.getPiece(nextSquare);
                if(p.type==PieceType::None){
                    square.push_back(nextSquare);
                    nextSquare.row+=dr;
                    nextSquare.col+=dc;
                }
                else if(p.color!=piece.color){
                    square.push_back(nextSquare);
                    break;
                }
                else break;
            }
        }
}