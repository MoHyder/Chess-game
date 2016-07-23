#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
#include <string>
#include <vector>

class Knight: public Piece{
public:
	// all possible moves a knight can make
	int allKnightMoves[8][2]= {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
	Knight(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8], bool backedUp = false);
	bool move(int destX, int destY, Piece* const layout[8][8]);
	~Knight(){}
};

#endif
