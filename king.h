#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
#include <string>
#include <vector>

class King: public Piece{
public:	
	// all possible moves a king can make
	int allKingMoves[8][2]= {{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	King(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8]);
	bool move(int destX, int destY, Piece* const layout[8][8]);
	// ~King();		
};

#endif