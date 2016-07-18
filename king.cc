#include "king.h"
#include <string>
#include <vector>
using namespace std;

King::King(int curX,int curY, char colour, bool moved):Piece{curX,curY,to_string(curX)+to_string(curY),"King",colour,moved}{}

void King::getAllValidMoves(Piece* const layout[8][8]){
	// swip clean original validMoves
	validMoves.clear();	
	for (int i = 0; i < 8; ++i){
		int x = curX - allKingMoves[i][0];
		int y = curY - allKingMoves[i][1];
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
			Piece::pushValidMove(x, y, colour, layout, validMoves);
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