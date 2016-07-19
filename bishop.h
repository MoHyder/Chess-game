#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include <string>
#include <vector>

class Bishop: public Piece{
public:
	Bishop(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8], bool backedUp = false);
	bool move(int destX, int destY, Piece* const layout[8][8]);		
	~Bishop(){}
};

#endif