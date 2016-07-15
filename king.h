#ifndef __KING_H__
#define __KING_H__
#include <piece.h>
#include <string>
#include <vector>

class King: public Piece{
	int curX;
	int curY;
	bool moved;	
	const bool isWhite;	
	// all possible moves a king can make
	int allKingMoves[8][2]= {{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
public:
	std::vector<string> validMoves;	
	King(int curX,int curY, bool isWhite);
	void getAllValidMove(const Piece** layout);
	bool move(int destX, int destY, const Piece** layout);		
};

#endif