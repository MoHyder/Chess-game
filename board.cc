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
    inStaleMate = false;
    inCheckMate = false;
}

void Board::getBoardView(){    
    // getting white pieces and king
    whitePieces.clear();
    blackPieces.clear(); 
    string colours = "wb";
    for(unsigned int c = 0; c < colours.length(); c++){ 
        char colour = colours[c];
        for(int x = 0; x < 8; ++x){
            for(int y = 0; y < 8; ++y){            
                if(layout[x][y] && layout[x][y]->getColour() == colour){ 
                    if(colour == 'w') whitePieces.push_back(layout[x][y]);
                    else blackPieces.push_back(layout[x][y]);      
                    layout[x][y]->getAllValidMoves(layout);
                }
                if(layout[x][y] && layout[x][y]->getName() == "King" && layout[x][y]->getColour() == colour) {
                    if(colour == 'w') whiteKing = layout[x][y];
                    else blackKing = layout[x][y];
                }
            }
        } 
    }  
}

// checking if board setup is done
bool Board::isDone(){
    if(isCheck()) return false;
    //checking if there is only one of each king
    string colours = "wb" ;
    for(unsigned int c = 0; c < colours.length(); c++){
        char colour = colours[c]; 
        int count = 0;
        for(int x = 0; x < 8; ++x)
            for(int y = 0; y < 8; ++y)
                if(layout[x][y] && layout[x][y]->getName() == "King" && layout[x][y]->getColour() == colour)
                    count++;
            
        if(count != 1) return false;
    }
    //checking if no pawns in the last rows of the board
    for(int x = 0; x < 8; ++x)
        if(layout[x][7] && layout[x][7]->getName() == "Pawn") return false;
    for(int x = 0; x < 8; ++x)
        if(layout[x][0] && layout[x][0]->getName() == "Pawn") return false;

    getBoardView();
    return true;          
}

// adds and removes piece from Board
bool Board::editBoard(string piece, int posX, int posY){
    if(piece == "d"){
        return isDone();
    }else if(piece == "-" || layout[posX][posY]) {
        // remove piece
        delete layout[posX][posY];
        layout[posX][posY] = nullptr;        
    }

    // adding new peices
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

    string colours = "wb" ;
    for(unsigned int c = 0; c < colours.length(); c++){
        bool inCheck = false;
        Piece *king; vector<Piece *> *pieces;
        char colour = colours[c];
        if(colour == 'w'){ king = whiteKing; pieces = &blackPieces;}
        else{king = blackKing; pieces = &whitePieces;}

        for(const auto &piece : *pieces){
            piece->getAllValidMoves(layout,true);        
            for(const auto &pieceMove : piece->validMoves){
                string kingXY = to_string(king->getX()) + to_string(king->getY());
                if(kingXY == pieceMove){
                    inCheck = true;
                    break;
                }
            }
            if(inCheck) break;
        }
        if(inCheck && colour == 'w'){ inWhiteCheck = true; return true;}
        if(inCheck && colour == 'b'){ inBlackCheck = true; return true;}
        getBoardView();         
    }

    return false;  
}

bool Board::isCheckMate(){   
    if(!(inBlackCheck || inWhiteCheck))  return false;
    
    string colours = "wb" ;
    for(unsigned int c = 0; c < colours.length(); c++){
        inCheckMate = false;
        Piece *king; vector<Piece *> *pieces;
        char colour = colours[c];
        if(colour == 'w'){ king = whiteKing; pieces = &blackPieces;}
        else{king = blackKing; pieces = &whitePieces;}

        for(const auto &kingMove : king->validMoves){
            inCheckMate = false;
            for(const auto &piece : *pieces){ 
                piece->getAllValidMoves(layout,true);    
                for(const auto &pieceMove : piece->validMoves){                    
                    if(kingMove == pieceMove){
                        cout << kingMove << " == " << pieceMove << " " << piece->getName() << endl;
                        inCheckMate = true;
                        break;
                    }
                } 
                if(inCheckMate) break;               
            }
            if(!inCheckMate) break;
        }
        if(inCheckMate) return true;
        getBoardView(); 
    }    
    return false;
}


bool Board::isStaleMate(){
    if(inBlackCheck || inWhiteCheck) return false;

    string colours = "wb" ;
    for(unsigned int c = 0; c < colours.length(); c++){
        inStaleMate = true;
        Piece *king; vector<Piece *> *playerPieces; vector<Piece *> *opponentPieces;
        char colour = colours[c];
        if(colour == 'w'){ king = whiteKing; playerPieces = &whitePieces;  opponentPieces = &blackPieces;}
        else{ king = blackKing; playerPieces = &blackPieces;  opponentPieces = &whitePieces;}

        for(const auto &piece : *playerPieces){
            if(piece->getName() == "King") continue;
            piece->getAllValidMoves(layout);
            if(piece->validMoves.size() > 0){
                inStaleMate = false;
                break;
            }
        }

        if (inStaleMate){
            for(const auto &kingMove : king->validMoves){
                inStaleMate = false;
                for(const auto &piece : *opponentPieces){
                    piece->getAllValidMoves(layout,true);
                    for(const auto &pieceMove : piece->validMoves){
                        if(kingMove == pieceMove){
                            inStaleMate = true;
                            break;
                        }
                    }
                    
                    if(inStaleMate) break;            
                }
                if(!inStaleMate) break;

            }
        }
        if(inStaleMate) return true;
        getBoardView();
    } 

    return false;

}

void Board::updatePieceInfo(int curX, int curY, bool moved){
    layout[curX][curY]->setX(curX);
    layout[curX][curY]->setY(curY);
    layout[curX][curY]->setMoved(moved);
    return;
}

bool Board::moveCastling(int posX, int posY, int destX, int destY, bool undo){
    if(layout[posX][posY] && layout[posX][posY]->getName() == "King" && !undo){
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
    }else if(layout[posX][posY] && layout[posX][posY]->getName() == "King" && undo){
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
    if(inCheckMate) return 90;
    // gameover Stale Mate
    if(inStaleMate) return 91;
    if(posX == destX && posY == destY) return 201;    
    // if no piece exists
    if(layout[posX][posY] == nullptr) return 202;
    // trying to move opponents piece
    if(!((layout[posX][posY]->getColour() == turn) || (layout[posX][posY]->getColour() == turn)))  return 203;

    // valid move
    if(layout[posX][posY]->move(destX,destY,layout)){
        // temp variables
        Piece *kill = nullptr;
        bool tempMoved = layout[posX][posY]->getMoved();
        bool castling = false;
        Piece *tempPawn = nullptr;
        bool pawnPromotion= false;
        // pawn promotion
        if(promote != "" && layout[posX][posY]->getName() == "Pawn"){
            cout << "promote" << endl;
           if((layout[posX][posY]->getY() == 6 && destY == 7) || (layout[posX][posY]->getY() == 1 && destY == 0)){
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
            if(layout[destX][destY] != nullptr && (layout[posX][posY]->getColour() != layout[destX][destY]->getColour())) 
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
            cout << "Moving " << layout[destX][destY]->getColour() + layout[destX][destY]->getName() << endl;   
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