#ifndef __COMP2_H__
#define __COMP2_H__
#include "player.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

class Comp2: public Player{
	const vector<Piece *> *myPieces;
	Piece *oppKing = nullptr;
	const vector<Piece *> *oppPieces;	
public:
	Comp2(Board *b, char colour): Player{b,colour}{};
	~Comp2(){};
	
	bool move(){
		int curX, curY, desX, desY;

		if(colour == 'w') {
			myPieces = &(b->whitePieces);
			oppPieces = &(b->blackPieces);
			oppKing = b->blackKing;
		}else {
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
					if(desX == oppPiece->getX() && desY == oppPiece->getY() && b->move(curX, curY, desX, desY, colour) != 204)						
						return true;
				}
			}
		}

		// checking if any piece can cause a check
		for(const auto &piece : *myPieces){
			vector<string> validMoves = piece->validMoves;
			curX = piece->getX();
			curY = piece->getY();
			for(const auto &move : validMoves){				
				desX = move[0] - '0';
				desY = move[1] - '0';
				if(desX == oppKing->getX() && desY == oppKing->getY() && b->move(curX, curY, desX, desY, colour) != 204)						
						return true;			
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
