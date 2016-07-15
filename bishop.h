#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <piece.h>
#include <string>
#include <vector>

class Bishop: public Piece{
	int curX;
	int curY;
	const bool isWhite;	
public:
	std::vector<string> validMoves;	
	Bishop(int curX,int curY, bool isWhite);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);	
};

#endif