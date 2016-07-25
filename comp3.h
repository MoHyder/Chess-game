#ifndef __COMP3_H__
#define __COMP3_H__
#include "player.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

class Comp3: public Player{
 const vector<Piece *> *myPieces;
 Piece *oppKing = nullptr;
 const vector<Piece *> *oppPieces;	
public:
 Comp3(Board *b, char colour): Player{b,colour}{};
 ~Comp3(){};
 bool move(){
  int curX, curY, desX, desY;
  if(colour == 'w') {
   myPieces = &(b->whitePieces);
   oppPieces = &(b->blackPieces);
   oppKing = b->blackKing;
  } else {
   myPieces = &(b->blackPieces);
   oppPieces = &(b->whitePieces);
   oppKing = b->whiteKing;
  }
// checking if any oppentents piece can be killed
  for(const auto &oppPiece : *oppPieces){
   for(const auto &myPiece : *myPieces){
    vector<string> validMoves = myPiece->validMoves;
    curX = myPiece->getX();
    curY = myPiece->getY();
    for(const auto &move : validMoves){					
     desX = move[0] - '0';
     desY = move[1] - '0';
     if(desX == oppPiece->getX() && desY == oppPiece->getY() && b->move(curX, curY, desX, desY, colour) != 204) return true;
    }
   }
  }
// checking if any opponents pieces can take any of our pieces
  for (const auto &oppPiece : *oppPieces) {
   vector<string> validMoves = oppPiece->validMoves;
   for (const auto &move : validMoves) {
    desX = move[0] - '0';
    desY = move[1] - '0';
    for (const auto &myPiece : *myPieces) {
     if (desX == myPiece->getX() && desY == myPiece->getY()) {
      // This piece is under attack, it should be moved
      vector<string> myMoves = myPiece->validMoves;
      int moveX = desX;
      int moveY = desY;
      for (const auto &myMove : myMoves) {
       desX = myMove[0] - '0';
       desY = myMove[1] - '0';
       // make sure it's not placing itself under attack from the same piece
       bool makemove = true;
       for (const auto &attackermove : validMoves) {
	if (desX == attackermove[0] - '0' && desY == attackermove[1] - '0') makemove = true; 
       }
       if (makemove && b->move(moveX, moveY, desX, desY, colour) != 204) return true; 
      }
     }
    }
   }
  }
// checking if any piece can cause a check
  for (const auto &piece : *myPieces){
   vector<string> validMoves = piece->validMoves;
   curX = piece->getX();
   curY = piece->getY();
   for (const auto &move : validMoves){				
    desX = move[0] - '0';
    desY = move[1] - '0';
    if(desX == oppKing->getX() && desY == oppKing->getY() && b->move(curX, curY, desX, desY, colour) != 204) return true;			
   }
  }
// if all fails, do first legal move
  for(const auto &piece : *myPieces){
   vector<string> validMoves = piece->validMoves;
   curX = piece->getX();
   curY = piece->getY();
   for(const auto &move : validMoves){				
    desX = move[0] - '0';
    desY = move[1] - '0';			
    if (b->move(curX, curY, desX, desY, colour) <= 102) return true;
   }
  }
  return false;
 }	
};

#endif
