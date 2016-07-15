#include <King.h>
#include <string>
#include <vector>

King::King(int curX,int curY, bool isWhite):isWhite{isWhite}{
	curX = curX;
	curY = curY;
	moved = false;	
}

void King::getAllValidMoves(const Piece** layout){
	// swip clean original validMoves
	validMoves.clear();	
	for (int i = 0; i < 8; ++i){
		int x = curX - allKingMoves[i][0];
		int y = curY - allKingMoves[i][1];
		if(x >= 1 && x <= 8 && y >= 1 && y <= 8)
			Piece::pushValidMove(x, y, layout, validMoves);
	}
}
bool King::move(int destX, int destY, const Piece** layout){
	// get all valid moves and store it in vector validMoves 
	getAllValidMoves(layout);
	// iterate validMoves and check if position is equal to any one of them
	for(const auto &validPosition : validMoves){
		if (validPosition[0] == to_string(destX) && validPosition[1] == to_string(destY)){ 
			moved = True;
			return true;
		}
	}
	return false;		
}