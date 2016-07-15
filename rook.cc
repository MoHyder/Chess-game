#include <Rook.h>
#include <string>
#include <vector>

Rook::Rook(int curX,int curY, bool isWhite):isWhite{isWhite}{
	curX = curX;
	curY = curY;
	moved = false;
}

void Rook::getAllValidMoves(const Piece** layout){
	// swip clean original validMoves
	validMoves.clear();
	// left
	int x = curX;
	int y = curY;
	while(x - 1 >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves) == 0){			
			x--;
			continue;		
		}    
		break;
	}
	// right
	x = curX;
	y = curY;
	while(x - 1 <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves) == 0){			
			x++;		
			continue;
		}    
		break;
	}
	// up
	x = curX;
	y = curY;
	while(y - 1 <= 7){
		if(Piece::pushValidMove(x, y, layout, validMoves) == 0){
			y++;
			continue;
		}    
		break;
	}
	// down
	x = curX;
	y = curY;
	while(y - 1 >= 0){
		if(Piece::pushValidMove(x, y, layout, validMoves) == 0){
			y--;
			continue;
		}
		break;    
	}
}
bool Rook::move(char destX, int destY, const Piece** layout){
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