#ifndef __PAWN_H__
#define __PAWN_H__
#include <piece.h>
#include <string>
#include <vector>

class Pawn: public Piece{
	int curX;
	int curY;
	bool moved;	
	const bool colour;	
public:
	std::vector<string> validMoves;		
	Pawn(int curX,int curY, bool isWhite);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);		
};

#endif