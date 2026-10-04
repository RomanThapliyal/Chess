#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::getMoves(const Board& board,const Square& from){

    std::vector<Move>moves;
    const Piece& piece=board.getPiece(from);

    if(piece.type==PieceType::None) return moves;

    if(piece.type==PieceType::Pawn){

        int direction=(piece.color==Color::White)?-1:1;       //prevents pawns from going back

        Square nextSquare{from.row+direction, from.col};

        bool isPromotion=(piece.color==Color::White&&nextSquare.row==0) ||         //if nextSqaure is back rank
                         (piece.color==Color::Black&&nextSquare.row==7);                   

        if(isInside(board,nextSquare)&&board.getPiece(nextSquare).type==PieceType::None){
            if(isPromotion){
                moves.push_back({from,nextSquare,MoveFlag::PromotionQueen});
                moves.push_back({from,nextSquare,MoveFlag::PromotionRook});
                moves.push_back({from,nextSquare,MoveFlag::PromotionKnight});
                moves.push_back({from,nextSquare,MoveFlag::PromotionBishop});
            }
            else{
                moves.push_back({from,nextSquare,MoveFlag::Normal});   //single push
            }

            bool isOnStartRank=(piece.color==Color::White&&from.row==6)||(piece.color==Color::Black&&from.row==1);

            if(isOnStartRank){             //double push 
                Square doubleStep{nextSquare.row+direction,nextSquare.col};
                if(isInside(board,doubleStep)&&board.getPiece(doubleStep).type==PieceType::None)
                    moves.push_back({from,doubleStep, MoveFlag::EnPassantTarget});   //only a double pushhed pawn can be captured in enpassant
            }
        }
          
        //diagonal capture

        Square captureLeftDiag{from.row+direction,from.col-1};
        Square captureRightDiag{from.row+direction,from.col+1};

        if(isInside(board,captureLeftDiag)){
            const Piece& captured=board.getPiece(captureLeftDiag);
            if(captured.type!=PieceType::None && captured.color!=piece.color){
                if(isPromotion){
                    moves.push_back({from,captureLeftDiag,MoveFlag::PromotionQueen});
                    moves.push_back({from,captureLeftDiag,MoveFlag::PromotionRook});
                    moves.push_back({from,captureLeftDiag,MoveFlag::PromotionKnight});
                    moves.push_back({from,captureLeftDiag,MoveFlag::PromotionBishop});
                }
                else moves.push_back({from,captureLeftDiag,MoveFlag::Normal});
            }
        }

        if(isInside(board,captureRightDiag)){
            const Piece& captured = board.getPiece(captureRightDiag);
            if(captured.type!=PieceType::None && captured.color!=piece.color){
                if(isPromotion){
                    moves.push_back({from,captureRightDiag,MoveFlag::PromotionQueen});
                    moves.push_back({from,captureRightDiag,MoveFlag::PromotionRook});
                    moves.push_back({from,captureRightDiag,MoveFlag::PromotionKnight});
                    moves.push_back({from,captureRightDiag,MoveFlag::PromotionBishop});
                }
                else moves.push_back({from,captureRightDiag,MoveFlag::Normal});
            }
        }

           //enpassant capture
        auto epTarget=board.getEnPassantTarget();       //the sqaure where the pawn is which can be captured by enpassant
        if(epTarget.has_value()){
            Square captureLeft{from.row,from.col-1};    //left of the same rank
            Square captureRight{from.row,from.col+1};   //right of the same rank

            if(isInside(board,captureLeft)){
                const Piece& captured=board.getPiece(captureLeft);
                if(captured.type!=PieceType::None && captured.color!=piece.color){
                    Square afterEnPassantLeft{from.row+direction,from.col-1};        //backside of pawn which can be captured by enpassant
                    if(epTarget.value()==captureLeft)    
                        moves.push_back({from,afterEnPassantLeft,MoveFlag::EnPassantCapture});
                }
            }

            if(isInside(board,captureRight)){
                const Piece& captured = board.getPiece(captureRight);
                if(captured.type!=PieceType::None && captured.color!=piece.color){
                    Square afterEnPassantRight{from.row+direction,from.col+1};        //backside of pawn which can be captured by enpassant
                    if(epTarget.value()==captureRight)
                    moves.push_back({from,afterEnPassantRight,MoveFlag::EnPassantCapture});
                }
            }
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

        //castel moves

        if(board.canCastle(piece.color)){
            if(board.canCastleOnSide(piece.color, CastlingSide::KingSide)){
                if(piece.color==Color::White){
                    //(7,5) (7,6) should be empty
                    if(board.getPiece({7,5}).type==PieceType::None && board.getPiece({7,6}).type==PieceType::None){
                        //add the castel move
                        moves.push_back({from,{7,6},MoveFlag::CastleKingSide});
                    }
                }
                else if(piece.color==Color::Black){
                    //(0,5) (0,6) should be empty
                    if(board.getPiece({0,5}).type==PieceType::None && board.getPiece({0,6}).type==PieceType::None){
                        //add the castel move
                        moves.push_back({from,{0,6},MoveFlag::CastleKingSide});
                    }
                }
            }
            if(board.canCastleOnSide(piece.color, CastlingSide::QueenSide)){
                if(piece.color==Color::White){
                    //(7,1) (7,2) (7,3) should be empty
                    if(board.getPiece({7,1}).type==PieceType::None && board.getPiece({7,2}).type==PieceType::None && board.getPiece({7,3}).type==PieceType::None){
                        //add the castel move
                        moves.push_back({from,{7,2},MoveFlag::CastleQueenSide});
                    }
                }
                else if(piece.color==Color::Black){
                    //(0,1) (0,2) (0,3) should be empty
                    if(board.getPiece({0,1}).type==PieceType::None && board.getPiece({0,2}).type==PieceType::None && board.getPiece({0,3}).type==PieceType::None){
                        //add the castel move
                        moves.push_back({from,{0,2},MoveFlag::CastleQueenSide});
                    }
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

        if(move.flag==MoveFlag::CastleKingSide||move.flag==MoveFlag::CastleQueenSide){    // Casteling moves
            //1.current King safe?
            //2.destination sqaure of King safe?
            //3.middle sqaures attack free?

            const Piece& king=board.getPiece(move.from);
            if(isInCheck(board,king.color)) continue;   //1.
            Color attackingColor= (king.color==Color::White)?(Color::Black):(Color::White);
            if(isSquareAttacked(board,move.to,attackingColor)) continue;     //2.

            if(move.flag==MoveFlag::CastleKingSide){        //3.
                if(king.color==Color::White){
                    //(7,5) should not be attacked  -- (7,6) was already accounted for as its the destination sq of king after castel
                    if(isSquareAttacked(board,{7,5},attackingColor)) continue;
                }
                else if(king.color==Color::Black){
                    //(0,5) should not be attacked  -- (0,6) was already accounted for as its the destination sq of king after castel
                    if(isSquareAttacked(board,{0,5},attackingColor)) continue;
                }
            }
            else if(move.flag==MoveFlag::CastleQueenSide){
                if(king.color==Color::White){
                    //(7,3) should not be attacked  -- (7,2) was already accounted for as its the destination sq of king after castel
                    if(isSquareAttacked(board,{7,3},attackingColor)) continue;
                }
                else if(king.color==Color::Black){
                    //(0,3) should not be attacked  -- (0,2) was already accounted for as its the destination sq of king after castel
                    if(isSquareAttacked(board,{0,3},attackingColor)) continue;
                }
            }
            legalMoves.push_back(move);
        }
        
        else{    //normal moves
            Board testBoard=board;

            testBoard.setPiece(move.to, testBoard.getPiece(move.from));
            testBoard.setPiece(move.from,{PieceType::None, Color::None});

            if(move.flag==MoveFlag::EnPassantCapture)
                testBoard.setPiece({move.from.row,move.to.col},{PieceType::None, Color::None});

            if(!isInCheck(testBoard,color)){
                legalMoves.push_back(move);
            }
        }
    }
    return legalMoves;
}

std::vector<Move> MoveGenerator::getAllLegalMoves(const Board& board, Color color){
    std::vector<Move> allLegalMoves;
    for(int row=0;row<board.SIZE;row++){
        for(int col=0;col<board.SIZE;col++){
            Square square{row,col};
            const Piece& piece=board.getPiece(square);

            if(piece.type==PieceType::None||piece.color!=color) continue;

            std::vector<Move> legalMoves=getLegalMoves(board,square);

            allLegalMoves.insert(allLegalMoves.end(),legalMoves.begin(),legalMoves.end());
        }
    }
    return allLegalMoves;
}

std::vector<Square> MoveGenerator::getAttackSquares(const Board& board,const Square& from){

    std::vector<Square> attackSquares;
    const Piece& piece = board.getPiece(from);

    if (piece.type == PieceType::None) return attackSquares;

    if(piece.type==PieceType::Pawn){

        int direction=(piece.color==Color::White)?-1:1;

        Square captureLeftDiag{from.row+direction,from.col-1};
        Square captureRightDiag{from.row+direction,from.col+1};

        if(isInside(board,captureLeftDiag))
            attackSquares.push_back(captureLeftDiag);

        if(isInside(board,captureRightDiag))
            attackSquares.push_back(captureRightDiag);
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

bool MoveGenerator::isSquareAttacked(const Board& board,const Square& target, Color attackingColor){
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

bool MoveGenerator::isInCheck(const Board& board, Color color){

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

bool MoveGenerator::isCheckMate(const Board& board, Color color){
    return isInCheck(board, color) && getAllLegalMoves(board, color).empty();
}

bool MoveGenerator::isStaleMate(const Board& board, Color color){
    return !isInCheck(board, color) && getAllLegalMoves(board, color).empty();
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
