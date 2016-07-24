#include "board.h"
#include <iostream>
#include <string>
#include <sstream>
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
    pieceInCheck = nullptr;
    inBlackCheck = false;
    inWhiteCheck = false;
    inStaleMate = false;
    inCheckMate = false;

    // make array nullptr
    for(int x = 0; x < 8; ++x)
        for(int y = 0; y < 8; ++y)
            layout[x][y] = nullptr;

}

void Board::getBoardView(){
    // getting all pieces and kings
    whitePieces.clear();
    blackPieces.clear(); 
    string colours = "wb";
    for(unsigned int c = 0; c < 2; c++){ 
        char colour = colours[c];
        for(int x = 0; x < 8; ++x){
            for(int y = 0; y < 8; ++y){                
                if(layout[x][y] && layout[x][y]->getColour() == colour){ 
                    if(colour == 'w') whitePieces.push_back(layout[x][y]);
                    else blackPieces.push_back(layout[x][y]);      
                    layout[x][y]->getAllValidMoves(layout);                    
                }
                if(layout[x][y] && layout[x][y]->getName() == 'K' && layout[x][y]->getColour() == colour) {
                    if(colour == 'w') whiteKing = layout[x][y];
                    else blackKing = layout[x][y];
                }
            }
        } 
    }    
    return; 
}

// checking if board setup is done
bool Board::isDone(){
    //checking if there is only one of each king
    string colours = "wb" ;
    for(unsigned int c = 0; c < 2; c++){
        char colour = colours[c]; 
        int count = 0;
        for(int x = 0; x < 8; ++x)
            for(int y = 0; y < 8; ++y)
                if(layout[x][y] && layout[x][y]->getName() == 'K' && layout[x][y]->getColour() == colour)
                    count++;
            
        if(count != 1) return false;
    }    
    //checking if no pawns in the last rows of the board
    for(int x = 0; x < 8; ++x)
        if(layout[x][7] && layout[x][7]->getName() == 'P') return false;
    for(int x = 0; x < 8; ++x)
        if(layout[x][0] && layout[x][0]->getName() == 'P') return false;

    getBoardView();
    if(isCheck()) return false;
    return true;          
}

// adds and removes piece from Board
bool Board::editBoard(char piece, int posX, int posY){
    if(piece == 'd'){
        return isDone();
    }else if((piece == '-' && layout[posX][posY]) || layout[posX][posY]) {        
        delete layout[posX][posY];
        layout[posX][posY] = nullptr;        
    }

    // adding new peices
    if(piece == 'K'){
        bool moved = true;
        if(posX == 4 && posY == 0) moved = false;
        layout[posX][posY] = new King(posX,posY,'w',moved);          
    }else if(piece == 'Q'){
        layout[posX][posY] = new Queen(posX,posY,'w');
    }else if(piece == 'B'){
        layout[posX][posY] = new Bishop(posX,posY,'w');
    }else if(piece == 'N'){
        layout[posX][posY] = new Knight(posX,posY,'w');
    }else if (piece == 'R'){
        bool moved = true;
        if((posX == 0 && posY == 0) || (posX == 7 && posY == 0)) moved = false;
        layout[posX][posY] = new Rook(posX,posY,'w',moved);
    }else if(piece == 'P'){
        bool moved = false;
        if(posY != 1 ) moved = true;
        layout[posX][posY] = new Pawn(posX,posY,'w',moved);
    }else if(piece == 'k'){
        bool moved = true;
        if(posX == 4 && posY == 7) moved = false;
        layout[posX][posY] = new King(posX,posY,'b',moved);        
    }else if(piece == 'q'){
        layout[posX][posY] = new Queen(posX,posY,'b');
    }else if(piece == 'b'){
        layout[posX][posY] = new Bishop(posX,posY,'b');
    }else if(piece == 'n'){
        layout[posX][posY] = new Knight(posX,posY,'b');
    }else if(piece == 'r'){
        bool moved = true;
        if((posX == 0 && posY == 7) || (posX == 7 && posY == 7)) moved = false;
        layout[posX][posY] = new Rook(posX,posY,'b',moved);
    }else if(piece == 'p'){
        bool moved = false;
        if(posY != 6) moved = true;
        layout[posX][posY] = new Pawn(posX,posY,'b',moved);
    }
    return true;
}

// check if either kings are in check
bool Board::isCheck(){
    inBlackCheck = inWhiteCheck = false;
    // piece that is causing the check
    pieceInCheck = nullptr;
    string colours = "wb" ;
    for(unsigned int c = 0; c < colours.length(); c++){
        bool inCheck = false;
        Piece *king; vector<Piece *> *pieces;
        char colour = colours[c];
        if(colour == 'w'){ king = whiteKing; pieces = &blackPieces;}
        else{king = blackKing; pieces = &whitePieces;}

        for(const auto &piece : *pieces){                   
            for(const auto &pieceMove : piece->validMoves){
                string kingXY = to_string(king->getX()) + to_string(king->getY());
                if(kingXY == pieceMove){
                    inCheck = true;
                    pieceInCheck = piece;
                    break;
                }

            } 
            if(inCheck) break;           
        }
        if(inCheck && colour == 'w') inWhiteCheck = true;
        if(inCheck && colour == 'b') inBlackCheck = true;
        getBoardView();         
    }    
    return (inBlackCheck || inWhiteCheck);
}

bool Board::isCheckMate(){   
    if(!(inBlackCheck || inWhiteCheck))  return false;    
    
    inCheckMate = true;
    vector<Piece *> *opponentPieces;
    if(turn == 'w') opponentPieces = &blackPieces ;
    else opponentPieces = &whitePieces;

    // check if any move can be made by any piece
    for(auto &piece : *opponentPieces){
        vector<string> validMoves = piece->validMoves;
        int curX = piece->getX();
        int curY = piece->getY();   
        for(auto &validMove : validMoves){
            int desX = validMove[0] - '0';
            int desY = validMove[1] - '0';
            int result = move(curX, curY, desX, desY, piece->getColour(),'q');
            if(result <= 102){
                undoMove();
                inCheckMate = false;
                break;
            }
        }
        if(!inCheckMate) break;            
    }
       
    return inCheckMate;
}


bool Board::isStaleMate(){
    if(inBlackCheck || inWhiteCheck) return false;
    
    inStaleMate = true;
    vector<Piece *> *opponentPieces;
    if(turn == 'w') opponentPieces = &blackPieces;
    else opponentPieces = &whitePieces;

    // check if any move can be made by any piece
    for(auto &piece : *opponentPieces){
        vector<string> validMoves = piece->validMoves;
        int curX = piece->getX();
        int curY = piece->getY();   
        for(auto &validMove : validMoves){
            int desX = validMove[0] - '0';
            int desY = validMove[1] - '0';
            int result = move(curX, curY, desX, desY, piece->getColour(),'q');
            if(result <= 102){                    
                undoMove();
                inStaleMate = false;
                break;
            }
        }
        if(!inStaleMate) break;            
    }   

    return inStaleMate;

}

void Board::updatePieceInfo(int curX, int curY, bool moved){
    layout[curX][curY]->setX(curX);
    layout[curX][curY]->setY(curY);
    layout[curX][curY]->setMoved(moved);
    return;
}

bool Board::moveCastling(int posX, int posY, int destX, int destY){
    if(layout[posX][posY] && layout[posX][posY]->getName() == 'K' && !layout[posX][posY]->getMoved()){        
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
    }

    return false;
}

void Board::pushToUndoStack(){
    // get a snapshot of all the pieces on the board
    string snapshot = "";
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){
            if(layout[x][y]){
                if (layout[x][y]->getColour() == 'w'){
                    snapshot += layout[x][y]->getName() + to_string(layout[x][y]->getX())
                                + to_string(layout[x][y]->getY()) + " "; 
                }else{
                    char name = layout[x][y]->getName() + 32;
                    snapshot += name + to_string(layout[x][y]->getX())
                                + to_string(layout[x][y]->getY()) + " "; 
                }
            } 
        }
    }

    if(snapshot != "") undoStack.push_back(snapshot);
    return;
}

bool Board::undoMove(){    
    if(undoStack.size() == 0) return false;
    //clar board
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){
            if(layout[x][y]) {
                delete layout[x][y];
                layout[x][y] = nullptr;
            }
        }
    }
    
    // set board to previous state
    string undoMove = undoStack.back();
    stringstream ss{undoMove};
    char i;    
    while(ss >> i){
        if(i == ' ') continue;
        char piece = i;
        ss >> i;
        int x = i - '0';
        ss >> i;
        int y = i - '0';        
        editBoard(piece, x , y);        
    }
    undoStack.pop_back();
    getBoardView();    
    return false;
}

// The move function returns an int depending if move was a success or a failure
int Board::move(int posX, int posY, int destX, int destY, char turn, char promote){
    if(posX == destX && posY == destY) return 201; // false
    // if no piece exists
    if(layout[posX][posY] == nullptr) return 202; // false
    // trying to move opponents piece
    if(layout[posX][posY]->getColour() != turn)  return 203;
    // valid move
    if(layout[posX][posY]->move(destX,destY,layout)){
        pushToUndoStack();
        bool killed = false;
        bool promotion = false;

        // pawn promotion
        if((destY == 0 || destY == 7) && layout[posX][posY]->getName() == 'P') promotion = true;
        
        // killing oppents piece
        if(layout[destX][destY] != nullptr && (layout[posX][posY]->getColour() != layout[destX][destY]->getColour())) {
           killed = true;
           delete layout[destX][destY];
           layout[destX][destY] = nullptr;
        // castling & any other move        
        }

        if(!moveCastling(posX,posY, destX, destY)){        

           // "physically moving the piece"
            layout[destX][destY] = layout[posX][posY];            
            // updating piece's information
            updatePieceInfo(destX,destY,true);
            layout[posX][posY] = nullptr; 
        } 

        getBoardView();
        isCheck();       

        // if check undo move 
        if((inBlackCheck && turn == 'b') || (inWhiteCheck && turn == 'w')){
            undoMove();
            return 204;
        }else{ 
            if (promotion){            
                if(promote == 0) {
                    cout << "PAWN PROMOTION" << endl;
                    cin >> promote;
                }else {
                    promote = 'Q';
                    if(turn == 'b') promote += 'a';
                }                
                editBoard(promote, destX, destY);
            }    

            // cleaning up;
            this->turn = turn;                        
            getBoardView();
            if(inBlackCheck || inWhiteCheck) return 102; 
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
