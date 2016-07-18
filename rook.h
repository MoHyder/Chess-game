#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include <string>
#include <vector>

class Rook: public Piece{
public:
	Rook(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8]);
	bool move(int destX, int destY, Piece* const layout[8][8]);
	// ~Rook();		
};

#endif