#include "king.h"
#include <string>
#include <vector>
using namespace std;

King::King(int curX,int curY, char colour, bool moved):Piece{curX,curY,'K',colour,moved}{}

void King::getAllValidMoves(Piece* const layout[8][8],bool backedUp){
	// swip clean original validMoves
	validMoves.clear();	
	for (int i = 0; i < 8; ++i){
		int x = curX - allKingMoves[i][0];
		int y = curY - allKingMoves[i][1];
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
			Piece::pushValidMove(x, y, layout, validMoves,backedUp);
	}
	// Castling white king
	if(!moved && colour == 'w'){
		// right side
		bool castleRight = true;
		for(int x = curX + 1; x < 7; ++x)			
			if(layout[x][0] != nullptr){								
				castleRight = false;
			 	break;
			}		
		
		if(castleRight && layout[7][0] && layout[7][0]->getName() == 'R' && layout[7][0]->getColour() == 'w')
			validMoves.push_back("60");			

		// left side
		bool castleLeft = true;
		for(int x = curX - 1 ; x > 0; --x)			
			if(layout[x][0] != nullptr){
				castleLeft = false;
			 	break;
			}				
					
		if(castleLeft && layout[0][0] && layout[0][0]->getName() == 'R' && layout[0][0]->getColour() == 'w')
			validMoves.push_back("20");		
	}

	// Castling black king
	if(!moved && colour == 'b'){		
		// right side
		bool castleRight = true;
		for(int x = curX + 1; x < 7; ++x)
			if(layout[x][7] != nullptr){
				castleRight = false;
			 	break;
			}		
		
		if(castleRight && layout[7][7] && layout[7][7]->getName() == 'R' && layout[7][7]->getColour() == 'b')
			validMoves.push_back("67");
		
		// left side
		bool castleLeft = true;
		for(int x = curX - 1; x > 0; --x)
			if(layout[x][7] != nullptr){
				castleLeft = false;
			 	break;
			}		
		
		if(castleLeft && layout[0][7] && layout[0][7]->getName() == 'R' && layout[0][7]->getColour() == 'b')
			validMoves.push_back("27");
		
		
	}

}
bool King::move(int destX, int destY, Piece* const layout[8][8]){
	// get all valid moves and store it in vector validMoves 
	getAllValidMoves(layout);
	// iterate validMoves and check if position is equal to any one of them
	for(const auto &validPosition : validMoves){		
		if (validPosition == (to_string(destX) + to_string(destY))){ 			
			return true;
		}
	}
	return false;		
}
