#include <Pawn.h>
#include <string>
#include <vector>

Pawn::Pawn(int curX,int curY, bool isWhite):isWhite{isWhite}{
	curX = curX;
	curY = curY;
	moved = false;	
}

void Pawn::getAllValidMoves(const Piece** layout){
	// swip clean original validMoves
	validMoves.clear();
	int x = curX;
	int y = curY + 1;
	// two steps	
	if(!moved) Piece::pushValidMove(x, y + 1, layout,validMoves);
	// one step
	Piece::pushValidMove(x, y, layout,validMoves);
	// kill 
	Piece::pushValidMove(x + 1, y, layout,validMoves);
}
bool Pawn::move(int destX, int destY, const Piece** layout){
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