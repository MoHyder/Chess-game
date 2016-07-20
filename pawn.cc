#include "pawn.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Pawn::Pawn(int curX,int curY, char colour, bool moved):Piece{curX,curY,'P',colour,moved}{}
	

void Pawn::getAllValidMoves(Piece* const layout[8][8], bool backedUp){
	int multiplier = 1;
	if (colour == 'b') multiplier = -1;
	// swip clean original validMoves
	validMoves.clear();
	int x = curX;
	int y = curY + (multiplier  * 1);
	// two steps	
	if(!moved && y < 7 && y > 1 && layout[x][y + (multiplier*1)] == nullptr)			
		Piece::pushValidMove(x, y + (multiplier  * 1), layout,validMoves,backedUp);
	// one step
	if(layout[x][y] == nullptr) Piece::pushValidMove(x, y, layout,validMoves,backedUp);
	// kill
	if(x < 7 && layout[x + 1][y] != nullptr && layout[x + 1][y]->getColour() != colour)
		Piece::pushValidMove(x + 1, y, layout,validMoves,backedUp);	
	if(x > 1  && layout[x - 1][y] != nullptr && layout[x - 1][y]->getColour() != colour)
		Piece::pushValidMove(x - 1, y, layout,validMoves,backedUp);	
}
bool Pawn::move(int destX, int destY, Piece* const layout[8][8]){
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