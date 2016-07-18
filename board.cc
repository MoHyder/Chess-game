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

// 
void Board::getBoardView(){    
    // getting white pieces and king
    whitePieces.clear();
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){            
            if(layout[x][y] && layout[x][y]->colour == 'w'){  
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
        if(layout[x][7] && layout[x][0]->name == "Pawn") return false;
    for(int x = 0; x < 8; ++x)
        if(layout[x][0] && layout[x][0]->name == "Pawn") return false;

    getBoardView();
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
                for(const auto &whitePieceMove : whitePiece->validMoves){
                    if(blackKingMove == whitePieceMove){
                        inBlackCheckMate = true;
                        break;
                    }
                }
                if(inBlackCheckMate) break;            
            }
        }
    }

    // checking if white check mate
    if(!inWhiteCheck) inWhiteCheckMate = false;
    // checking if white king can make any move
    else{
        for(const auto &whiteKingMove : whiteKing->validMoves){
            inWhiteCheckMate = false;
            for(const auto &blackPiece : blackPieces){
                for(const auto &blackPieceMove : blackPiece->validMoves){
                    if(whiteKingMove == blackPieceMove){
                        inWhiteCheckMate = true;
                        break;
                    }
                }
                if(inWhiteCheckMate) break;            
            }
        }
    }

    return (inWhiteCheckMate || inBlackCheckMate);
}

bool Board::isStaleMate(){
    inWhiteStaleMate = inBlackStaleMate = false;

    if(inBlackCheck) inBlackStaleMate = false;
    // checking if black in is stale mate
    else{
        for(const auto &blackKingMove : blackKing->validMoves){
            inBlackStaleMate = false;
            if(blackKingMove == blackKing->curXY) continue;
            for(const auto &whitePiece : whitePieces){
                for(const auto &whitePieceMove : whitePiece->validMoves){
                    if(blackKingMove == whitePieceMove){
                        inBlackStaleMate = true;
                        break;
                    }
                }
                if(inBlackStaleMate) break;            
            }
        }
    }

    if(inWhiteCheck) inWhiteStaleMate = false;
    // checking if white in is stale mate
    else {
        for(const auto &whiteKingMove : whiteKing->validMoves){
            inWhiteStaleMate = false;
            if(whiteKingMove == whiteKing->curXY) continue;
            for(const auto &blackPiece : blackPieces){
                for(const auto &blackPieceMove : blackPiece->validMoves){
                    if(whiteKingMove == blackPieceMove){
                        inWhiteStaleMate = true;
                        break;
                    }
                }
                if(inWhiteStaleMate) break;            
            }
        }
    }
    return (inWhiteStaleMate || inBlackStaleMate);

}

// The move function returns an int depending if move was a success or a failure
int Board::move(int posX, int posY, int destX, int destY, char turn, string promoted){
    // gameover Stale Mate
    if(inBlackStaleMate || inWhiteStaleMate) return 201;
    // gameover checkMate
    if(inBlackCheckMate || inBlackCheckMate) return 202;
    // return 203 if no piece exists
    if(layout[posX][posY] == nullptr) return 203;
    // return 204 trying to move opponents piece
    if(!((layout[posX][posY]->colour == 'w' && turn == 'w') || (layout[posX][posY]->colour == 'b' && turn == 'b')))  return 204;

    // return 0 valid move
    if(layout[posX][posY]->move(destX,destY,layout)){
        // temp variables
        Piece *kill = nullptr;
        bool tempMoved = layout[posX][posY]->moved;
        // killing oppents piece
        if(layout[destX][destY] != nullptr && (layout[posX][posY]->colour != layout[destX][destY]->colour))
            kill = layout[destX][destY];
        // "physically moving the piece"
        layout[destX][destY] = layout[posX][posY];
        layout[posX][posY] = nullptr;        
        // updating piece's information            
        layout[destX][destY]->curX = destX;
        layout[destX][destY]->curY = destY;
        layout[destX][destY]->moved = true;
        layout[destX][destY]->curXY = to_string(destX) + to_string(destY);              
        getBoardView();
        isCheck();
        // if check undo move 
        if((inBlackCheck && turn == 'b') || (inWhiteCheck && turn == 'w')){
            // reseting piece's info to original
            layout[destX][destY]->curX = posX;
            layout[destX][destY]->curY = posY;
            layout[destX][destY]->moved = tempMoved;
            layout[destX][destY]->curXY = to_string(posX) + to_string(posY);
            layout[posX][posY] = layout[destX][destY];
            layout[destX][destY] = kill;              
            return 205;
        }else{         
            cout << "Moving " << layout[destX][destY]->colour + layout[destX][destY]->name << endl;   
            // killing peice;
            if(kill) delete kill;
            getBoardView();
            if (isStaleMate()) return 201;
            if(isCheckMate()) return 202;            
            return 0;
        }        
    }
    return 200;
}

Board::~Board(){
    for(int x = 0; x < 8; ++x)
        for(int y = 0; y < 8; ++y)
            if(layout[x][y]) delete layout[x][y];

}