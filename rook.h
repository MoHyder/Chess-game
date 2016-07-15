#ifndef __ROOK_H__
#define __ROOK_H__
#include <piece.h>
#include <string>
#include <vector>

class Rook: public Piece{
	int curX;
	int curY;
	bool moved;
	const bool isWhite;	
public:
	std::vector<string> validMoves;		
	Rook(int curX,int curY, bool isWhite);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);		
};

#endif