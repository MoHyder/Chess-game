#ifndef __COMP1_H__
#define __COMP1_H__
#include "player.h"
#include "piece.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Comp1: public Player{
	const vector<Piece *> *myPieces;	
public:
	Comp1(Board *b, char colour): Player{b,colour}{};
	~Comp1(){};
	
	bool move(){
		int curX, curY, desX, desY, randomInt;

		if(colour == 'w') myPieces = &(b->whitePieces);
		else myPieces = &(b->blackPieces);

		//truely random moves
		int tries = 3;
		while(tries >= 0){
			tries--;			
			srand(time(0));
			// generate random number
			randomInt = rand() % myPieces->size();
			for(const auto piece : *myPieces){
				if(randomInt != 0){
					randomInt--;
					continue;
				}
				vector<string> validMoves =  piece->validMoves;
				curX = piece->getX();
				curY = piece->getY();						
				for(const auto move : validMoves){				
					desX = move[0] - '0';
					desY = move[1] - '0';
					if (b->move(curX, curY, desX, desY, colour, 'Q') <= 102) return true;					
				}			
			}			
		}
		
		// if all three random moves do not work, make first legal move
		for(const auto &piece : *myPieces){
			vector<string> validMoves =  piece->validMoves;
			curX = piece->getX();
			curY = piece->getY();			
			for(const auto &move : validMoves){				
				desX = move[0] - '0';
				desY = move[1] - '0';				
				if (b->move(curX, curY, desX, desY, colour, 'Q') <= 102) return true;				
			}			
		}

		return false;

	}	
};

#endif
