#include "bishop.h"
#include <string>
#include <vector>
using namespace std;

Bishop::Bishop(int curX,int curY, char colour, bool moved):Piece{curX,curY,'B',colour,moved}{}

// pushes all valid moves to vector validMoves
void Bishop::getAllValidMoves(Piece* const layout[8][8],bool backedUp){
	// swip clean original validMoves
	validMoves.clear();
	// left down diagonal
	int x = curX - 1;
	int y = curY - 1;	
	while(x >= 0 && y >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){	    	
			x--;
			y--;
			continue;
		}
		break;
	}
	// left up diagonal
	x = curX + 1;
	y = curY + 1;
	while(x <= 7 && y <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){	    	
			x++;
			y++;
			continue;
		}
		break;		
	}
	// right down diagonal
	x = curX + 1;
	y = curY - 1;  
	while(x <= 7 && y >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){	    	
			x++;
			y--;
			continue;
		}
		break;
	}
	// right up diagonal
	x = curX - 1;
	y = curY + 1;  
	while(x >= 0 && y <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves,backedUp) == 0){	    	
			x--;
			y++;
			continue;
		}
		break;
	}
}
bool Bishop::move(int destX, int destY, Piece* const layout[8][8]){
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
