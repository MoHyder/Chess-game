#ifndef __BOARD_H
#define __BOARD_H
#include "piece.h"
#include <vector>

class Board {    
    Piece *blackKing;
    Piece *whiteKing;
    // piece that are causing the check
    Piece *pieceInCheck; 
    bool inWhiteCheck;
    bool inBlackCheck;   
    bool inStaleMate;
    bool inCheckMate;
    std::vector<std::string> undoStack;    

public:
    Piece *layout [8][8];       
    std::vector <Piece *> blackPieces;
    std::vector <Piece *> whitePieces;
    // functions 
    Board();
    void getBoardView();
    bool isDone();
    bool editBoard(std::string piece, int posX, int posY);
    void updatePieceInfo(int curX, int curY, bool moved);
    bool moveCastling(int posX, int posY, int destX, int destY, bool undo = false);
    void pushToUndoStack();
    bool undoMove();
    int move(int posX, int posY, int destX, int destY, char turn);
    bool isCheck();
    bool isCheckMate();
    bool isStaleMate();
    ~Board();
};
#endif

