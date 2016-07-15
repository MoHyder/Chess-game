#include <queen.h>
#include <string>
#include <vector>

Queen::Queen(int curX,int curY, bool isWhite):isWhite{isWhite}{	
	curX = curX;
	curY = curY;
}

void Queen::getAllValidMoves(){
	// swip clean original validMoves
	validMoves.clear();
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
	// left
	x = curX;
	y = curY;
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

bool Queen::move(int destX, int destY, const Piece* layout){
	// get all valid moves and store it in vector validMoves 
	getAllValidMoves();
	// iterate validMoves and check if destination is equal to any one of them
	for(const auto &validPosition : validMoves){
		if (validPosition[0] == to_string(destX) && validPosition[1] == to_string(destY)) return true;
	}
	return false;		
}