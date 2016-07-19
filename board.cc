#include "board.h"
#include <iostream>
#include <string>
#include <fstream>
#include "board.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
using namespace std;

// need for clerification
Board::Board(){
    blackKing = nullptr;
    whiteKing = nullptr;
    inBlackCheck = false;
    inWhiteCheck = false;   
    inBlackStaleMate = false;
    inWhiteStaleMate = false;
    inBlackCheckMate = false;
    inWhiteCheckMate = false;
}

void Board::getBoardView(){    
    // getting white pieces and king
    whitePieces.clear();
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){            
            if(layout[x][y] && layout[x][y]->colour == 'w'){ 
                // cout <<  layout[x][y]->name << " w " << layout[x][y]->curXY << endl;
                whitePieces.push_back(layout[x][y]);                
                layout[x][y]->getAllValidMoves(layout);
            }
            if(layout[x][y] && layout[x][y]->name == "King" && layout[x][y]->colour == 'w') whiteKing = layout[x][y];
        }
    }
    // getting black pieces and king
    blackPieces.clear();    
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){            
            if(layout[x][y] && layout[x][y]->colour == 'b') {
                // cout <<  layout[x][y]->name << " b " << layout[x][y]->curXY << endl;
                blackPieces.push_back(layout[x][y]);
                layout[x][y]->getAllValidMoves(layout);
            }
            if(layout[x][y] && layout[x][y]->name == "King" && layout[x][y]->colour == 'b') blackKing = layout[x][y];
        }
    }
    
}

// checking if board setup is done
bool Board::isDone(){

    if(isCheck()) return false;
    //checking if there is only one white king
    int count = 0;
    for(int x = 0; x < 8; ++x)
        for(int y = 0; y < 8; ++y)
            if(layout[x][y] && layout[x][y]->name == "King" && layout[x][y]->colour == 'w')
                count++;
        
    if(count != 1) return false;
    
    //checking if there is only one black king
    count = 0;
    for(int x = 0; x < 8; ++x)
        for(int y = 0; y < 8; ++y)
            if(layout[x][y] && layout[x][y]->name == "King" && layout[x][y]->colour == 'b')
                count++;
        
    if(count != 1) return false;
    
    //checking if no pawns in the last rows of the board
    for(int x = 0; x < 8; ++x)
        if(layout[x][7] && layout[x][7]->name == "Pawn") return false;
    for(int x = 0; x < 8; ++x)
        if(layout[x][0] && layout[x][0]->name == "Pawn") return false;

    getBoardView();

    if(isCheck()) return false;

    return true;

           
}
// adds and removes piece from Board
bool Board::editBoard(string piece, int posX, int posY){
    if(piece == "d"){
        return isDone();
    }else if(layout[posX][posY]) {
        // remove piece
        delete layout[posX][posY];
        layout[posX][posY] = nullptr;        
    }
    // adding peices
    if(piece == "K"){
        bool moved = false;
        if(posX != 4 && posY != 0) moved = true;
        layout[posX][posY] = new King(posX,posY,'w',moved); 
    }else if(piece == "Q"){
        layout[posX][posY] = new Queen(posX,posY,'w');
    }else if(piece == "B"){
        layout[posX][posY] = new Bishop(posX,posY,'w');
    }else if(piece == "KN"){
        layout[posX][posY] = new Knight(posX,posY,'w');
    }else if (piece == "R"){
        bool moved = false;
        if((posX != 0 && posY != 0) || (posX != 7 && posY != 0)) moved = true;
        layout[posX][posY] = new Rook(posX,posY,'w',moved);
    }else if(piece == "P"){
        bool moved = false;
        if(posY != 1 ) moved = true;
        layout[posX][posY] = new Pawn(posX,posY,'w',moved);
    }else if(piece == "k"){
        bool moved = false;
        if(posX != 4 && posY != 7) moved = true;
        layout[posX][posY] = new King(posX,posY,'b',moved);        
    }else if(piece == "q"){
        layout[posX][posY] = new Queen(posX,posY,'b');
    }else if(piece == "b"){
        layout[posX][posY] = new Bishop(posX,posY,'b');
    }else if(piece == "kn"){
        layout[posX][posY] = new Knight(posX,posY,'b');
    }else if(piece == "r"){
        bool moved = false;
        if((posX != 0 && posY != 7) || (posX != 7 && posY != 7)) moved = true;
        layout[posX][posY] = new Rook(posX,posY,'b',moved);
    }else if(piece == "p"){
        bool moved = false;
        if(posY != 6) moved = true;
        layout[posX][posY] = new Pawn(posX,posY,'b',moved);
    }
    return true;
}

// check if either kings are in check
bool Board::isCheck(){
    inBlackCheck = inWhiteCheck = false;

    // checking if black king is in check
    for(const auto &whitePiece : whitePieces){
        whitePiece->getAllValidMoves(layout,true);        
       for(const auto &whitePieceMove : whitePiece->validMoves){
            if(blackKing->curXY == whitePieceMove){
                inBlackCheck = true;
                break;
            }
        }
        if(inWhiteCheck) break;
    }

    // checking if white king is in check
    for(const auto &blackPiece : blackPieces){
        blackPiece->getAllValidMoves(layout,true);        
        for(const auto &blackPieceMove : blackPiece->validMoves){
            if(whiteKing->curXY == blackPieceMove){
                inWhiteCheck = true;
                break;
            }
        }
        if(inWhiteCheck) break;
    }    
    return (inBlackCheck || inWhiteCheck);    
      
}

bool Board::isCheckMate(){
    inWhiteCheckMate = inBlackCheckMate = false;
    
    // checking if black check mate
    if(!inBlackCheck) inBlackCheckMate = false;
    // checking if black king can make any move    
    else{
        for(const auto &blackKingMove : blackKing->validMoves){            
            inBlackCheckMate = false;
            for(const auto &whitePiece : whitePieces){ 
                whitePiece->getAllValidMoves(layout,true);    
                for(const auto &whitePieceMove : whitePiece->validMoves){                    
                    if(blackKingMove == whitePieceMove){
                        cout << blackKingMove << " == " << whitePieceMove << " " << whitePiece->name << endl;
                        inBlackCheckMate = true;
                        break;
                    }
                } 
                if(inBlackCheckMate) break;               
            }
            if(!inBlackCheckMate) break;
        }
    }

    // checking if white check mate
    if(!inWhiteCheck) inWhiteCheckMate = false;
    // checking if white king can make any move
    else{
        for(const auto &whiteKingMove : whiteKing->validMoves){
            inWhiteCheckMate = false;
            for(const auto &blackPiece : blackPieces){
                blackPiece->getAllValidMoves(layout,true);                    
                for(const auto &blackPieceMove : blackPiece->validMoves){
                    if(whiteKingMove == blackPieceMove){
                        cout << whiteKingMove << " == " << blackPieceMove << " " << blackPiece->name << endl;
                        inWhiteCheckMate = true;
                        break;
                    }
                }
                if(inWhiteCheckMate) break;                 
            }
            if(!inWhiteCheckMate) break;
        }
    }

    return (inWhiteCheckMate || inBlackCheckMate);
}

bool Board::isStaleMate(){
    inWhiteStaleMate = inBlackStaleMate = false;

    if(inBlackCheck) inBlackStaleMate = false;
    // checking if black in is stale mate
    else{
        // checking if any black peice can move
        for(const auto &blackPiece : blackPieces){
            inBlackStaleMate = true;
            if(blackPiece->name == "King") continue;
            blackPiece->getAllValidMoves(layout);
            if(blackPiece->validMoves.size() > 0){
                inBlackStaleMate = false;
                break;
            }
        }
        // checking if black king can make any moves
        if (inBlackStaleMate){
            for(const auto &blackKingMove : blackKing->validMoves){
                inBlackStaleMate = false;
                for(const auto &whitePiece : whitePieces){
                    whitePiece->getAllValidMoves(layout,true);
                    for(const auto &whitePieceMove : whitePiece->validMoves){
                        if(blackKingMove == whitePieceMove){
                            inBlackStaleMate = true;
                            break;
                        }
                    }
                    if(inBlackStaleMate) break;            
                }
                if(!inBlackStaleMate) break;
            }
        }
     }

    if(inWhiteCheck) inWhiteStaleMate = false;
    // checking if white in is stale mate
    else{
        // checking if any white peice can move
        for(const auto &whitePiece : whitePieces){
            inWhiteStaleMate = true;
            if(whitePiece->name == "King") continue;
            whitePiece->getAllValidMoves(layout);
            if(whitePiece->validMoves.size() > 0){
                inWhiteStaleMate = false;
                break;
            }
        }
        // checking if white king can make any moves
        if (inWhiteStaleMate){
            for(const auto &whiteKingMove : whiteKing->validMoves){
                inWhiteStaleMate = false;
                for(const auto &blackPiece : blackPieces){
                    blackPiece->getAllValidMoves(layout,true);
                    for(const auto &blackPieceMove : blackPiece->validMoves){
                        if(whiteKingMove == blackPieceMove){
                            inWhiteStaleMate = true;
                            break;
                        }
                    }
                    if(inWhiteStaleMate) break;            
                }
                if(!inWhiteStaleMate) break;
            }
        }
    }
    return (inWhiteStaleMate || inBlackStaleMate);

}

void Board::updatePieceInfo(int curX, int curY, bool moved){
    layout[curX][curY]->curX = curX;
    layout[curX][curY]->curY= curY;
    layout[curX][curY]->curXY= to_string(curX) + to_string(curY);
    layout[curX][curY]->moved = moved;
    return;
}

bool Board::moveCastling(int posX, int posY, int destX, int destY, bool undo){
    if(layout[posX][posY] && layout[posX][posY]->name == "King" && !undo){
        if((destX == 6 && destY == 0) || (destX == 6 && destY == 7)){
            // change king
            layout[destX][destY] = layout[posX][posY];
            // update king info
            updatePieceInfo(destX ,destY, true);
            layout[posX][posY] = nullptr;
            // change castle
            layout[destX - 1][destY] = layout[7][posY];
            // update castle info
            updatePieceInfo(destX - 1,destY, true);
            layout[7][posY] = nullptr;
            return true;            
        }else if((destX == 2 && destY == 0) || (destX == 2 && destY == 7)){
            layout[destX][destY] = layout[posX][posY];
            updatePieceInfo(destX ,destY,true);
            layout[posX][posY] = nullptr;
            layout[destX + 1][destY] = layout[0][posY];
            updatePieceInfo(destX + 1,destY, true);
            layout[0][posY] = nullptr;
            return true;
        }        
    // undo move
    }else if(layout[posX][posY] && layout[posX][posY]->name == "King" && undo){
        if((destX == 6 && destY == 0) || (destX == 6 && destY == 7)){
            layout[posX][posY] = layout[destX][destY];
            updatePieceInfo(posX ,posY,true);
            layout[destX][destY] = nullptr;
            layout[7][posY] = layout[destX - 1][destY];
            updatePieceInfo(7,posY,true);
            layout[destX - 1][destY] = nullptr;
        }else if((destX == 2 && destY == 0) || (destX == 2 && destY == 7)){
            layout[posX][posY] = layout[destX][destY];
            updatePieceInfo(posX ,posY,true);
            layout[destX][destY] = nullptr;
            layout[0][posY] = layout[destX - 1][destY];
            updatePieceInfo(0,posY,true);
            layout[destX - 1][destY] = nullptr;
        }

    }

    return false;
}

// The move function returns an int depending if move was a success or a failure
int Board::move(int posX, int posY, int destX, int destY, char turn, string promote){
    // gameover checkMate
    if(inBlackCheckMate || inBlackCheckMate) return 90;
    // gameover Stale Mate
    if(inBlackStaleMate || inWhiteStaleMate) return 91;
    if(posX == destX && posY == destY) return 201;    
    // if no piece exists
    if(layout[posX][posY] == nullptr) return 202;
    // trying to move opponents piece
    if(!((layout[posX][posY]->colour == 'w' && turn == 'w') || (layout[posX][posY]->colour == 'b' && turn == 'b')))  return 203;

    // valid move
    if(layout[posX][posY]->move(destX,destY,layout)){
        // temp variables
        Piece *kill = nullptr;
        bool tempMoved = layout[posX][posY]->moved;
        bool castling = false;
        Piece *tempPawn = nullptr;
        bool pawnPromotion= false;
        // pawn promotion
        if(promote != "" && layout[posX][posY]->name == "Pawn"){
            cout << "promote" << endl;
           if((layout[posX][posY]->curY == 6 && destY == 7) || (layout[posX][posY]->curY == 1 && destY == 0)){
                if(posX - destX == 1 || posX - destX == -1) {kill = layout[destX][destY]; layout[destX][destY] = nullptr;}
                tempPawn = layout[posX][posY];
                layout[posX][posY] = nullptr;
                pawnPromotion = true;
                editBoard(promote, destX, destY);                
            }
        //castling
        }else if(!isCheck() && moveCastling(posX,posY, destX, destY)){
            cout << "castling" << endl;
            castling = true;  
        // all other moves              
        }else{        
            // killing oppents piece
            if(layout[destX][destY] != nullptr && (layout[posX][posY]->colour != layout[destX][destY]->colour)) 
                kill = layout[destX][destY];
            // "physically moving the piece"
            layout[destX][destY] = layout[posX][posY];            
            // updating piece's information
            updatePieceInfo(destX,destY,true);
            layout[posX][posY] = nullptr;
        }              
        getBoardView();
        cout << "isCheck: " << isCheck() << endl;
        // if check undo move 
        if((inBlackCheck && turn == 'b') || (inWhiteCheck && turn == 'w')){            
            if(pawnPromotion){
                layout[posX][posY] = tempPawn;
                delete layout[destX][destY];                
                if(kill) layout[destX][destY] = kill;
                else layout[destX][destY] = nullptr;
                kill = nullptr;
                getBoardView();                           
            }else if(castling) {
                moveCastling(posX, posY, destX, destY, true);
            }else{
                // reseting piece's info to original
                layout[posX][posY] = layout[destX][destY];
                updatePieceInfo(posX,posY,tempMoved);                        
                layout[destX][destY] = kill;
                kill = nullptr;
            }              
            return 204;
        }else{ 
            cout << "Moving " << layout[destX][destY]->colour + layout[destX][destY]->name << endl;   
            // cleaning up;
            int killed = 0;
            int promotion = 0;  
            if(kill){killed = 1; delete kill;}
            if(tempPawn){promotion = 1; delete tempPawn;}

            getBoardView();
            if(isCheckMate()) return 90;
            if(isStaleMate()) return 91; 
            if(killed) return 101;            
            return 100;
        }        
    }
    return 200;
}

Board::~Board(){
    for(int x = 0; x < 8; ++x)
        for(int y = 0; y < 8; ++y)
            if(layout[x][y]) delete layout[x][y];
}