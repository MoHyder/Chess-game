#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <piece.h>
#include <string>
#include <vector>

class Knight: public Piece{
	int curX;
	int curY;	
	const bool isWhite;	
	// all possible moves a knight can make
	int allKnightMoves[8][2]= {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
public:
	std::vector<string> validMoves;
	Knight(int curX,int curY, bool isWhite);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);		
};

#endif