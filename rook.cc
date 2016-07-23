#include "rook.h"
#include <string>
#include <vector>
using namespace std;

Rook::Rook(int curX,int curY, char colour, bool moved):Piece{curX,curY,'R',colour,moved}{}

void Rook::getAllValidMoves(Piece* const layout[8][8], bool backedUp){
	// swip clean original validMoves
	validMoves.clear();
	// left
	int x = curX - 1;
	int y = curY;
	while(x >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){
			x--;
			continue;		
		}    
		break;
	}
	// right
	x = curX + 1;
	y = curY;
	while(x <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){
			x++;		
			continue;
		}    
		break;
	}
	// up
	x = curX;
	y = curY + 1;
	while(y <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){
			y++;
			continue;
		}    
		break;
	}
	// down
	x = curX;
	y = curY - 1;
	while(y >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){
			y--;
			continue;
		}
		break;    
	}
}
bool Rook::move(int destX, int destY, Piece* const layout[8][8]){
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
