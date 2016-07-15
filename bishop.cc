#include <Bishop.h>
#include <string>
#include <vector>

Bishop::Bishop(int curX,int curY, bool isWhite):isWhite{isWhite}{
	curX = curX;
	curY = curY;
}

// pushes all valid moves to vector validMoves
void Bishop::getAllValidMoves(const Piece** layout){
	// swip clean original validMoves
	validMoves.clear();
	// left down diagonal
	int x = curX - 1;
	int y = curY - 1;
	while(x - 1 >= 0 && y - 1 >= 0){
	    if(Piece::pushValidMove(x, y, layout, validMoves) == 0){
			x--;
			y--;
			continue;
		}
		break;
	}
	// left up diagonal
	x = curX + 1;
	y = curY + 1;
	while(x - 1 <= 7 && y - 1 <= 7){
	    if(Piece::pushValidMove(x, y, layout, validMoves) == 0){	        
			x++;
			y++;
			continue;
		}
		break;
	}
	// right down diagonal
	x = curX + 1;
	y = curY - 1;  
	while(x - 1 <= 7 && y - 1 >= 0){
	    if(Piece::pushValidMove(x, y, layout, validMoves) == 0){			
			x++;
			y--;
			continue;
		}
		break;
	}
	// right up diagonal
	x = curX - 1;
	y = curY + 1;  
	while(x - 1 >= 0 && y - 1 <= 7){
	    if(Piece::pushValidMove(x, y, layout, validMoves) == 0){			
			x--;
			y++;
			continue;
		}
		break;
	}
}
bool Bishop::move(int destX, int destY, const Piece** layout){
	// get all valid moves and store it in vector validMoves 
	getAllValidMoves(layout);
	// iterate validMoves and check if position is equal to any one of them
	for(const auto &validPosition : validMoves){
		if (validPosition[0] == to_string(destX) && validPosition[1] == to_string(destY)) 
			return true;
	}
	return false;		
}