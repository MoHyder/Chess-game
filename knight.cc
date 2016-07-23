#include "knight.h"
#include <string>
#include <vector>
using namespace std;

Knight::Knight(int curX,int curY, char colour, bool moved):Piece{curX,curY,'N',colour,moved}{}

void Knight::getAllValidMoves(Piece* const layout[8][8], bool backedUp){
	// swip clean original validMoves
	validMoves.clear();	
	for (int i = 0; i < 8; ++i){
		int x = curX - allKnightMoves[i][0];
		int y = curY - allKnightMoves[i][1];		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
			Piece::pushValidMove(x, y, layout, validMoves,backedUp);
	}	
}
bool Knight::move(int destX, int destY, Piece* const layout[8][8]){
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
