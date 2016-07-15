#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <piece.h>
#include <string>
#include <vector>

class Queen: public Piece{
	int curX;
	int curY;
	const bool isWhite;	
public:
	std::vector<string> validMoves;	
	Queen(int curX,int curY, bool colour);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);		
};

#endif