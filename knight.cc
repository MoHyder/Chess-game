#include <Knight.h>
#include <string>
#include <vector>

Knight::Knight(int curX,int curY, bool isWhite):isWhite{isWhite}{
	curX = curX;
	curY = curY;	
}

void Knight::getAllValidMoves(const Piece** layout){
	// swip clean original validMoves
	validMoves.clear();	
	for (int i = 0; i < 8; ++i){
		int x = curX - allKnightMoves[i][0];
		int y = curY - allKnightMoves[i][1];
		if(x >= 1 && x <= 8 && y >= 1 && y <= 8)
			Piece::pushValidMove(x, y, layout, validMoves);
	}
}
bool Knight::move(int destX, int destY, const Piece** layout){
	// get all valid moves and store it in vector validMoves 
	getAllValidMoves(layout);
	// iterate validMoves and check if position is equal to any one of them
	for(const auto &validPosition : validMoves){
		if (validPosition[0] == to_string(destX) && validPosition[1] == to_string(destY)){ 
			return true;
		}
	}
	return false;		
}