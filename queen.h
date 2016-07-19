#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
#include <string>
#include <vector>

class Queen: public Piece{
public:
	Queen(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8], bool backedUp = false);
	bool move(int destX, int destY, Piece* const layout[8][8]);	
	~Queen(){}	
};

#endif