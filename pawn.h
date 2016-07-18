#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
#include <string>
#include <vector>

class Pawn: public Piece{
public:
	Pawn(int curX,int curY, char colour, bool moved = false);
	void getAllValidMoves(Piece* const layout[8][8]);
	bool move(int destX, int destY, Piece* const layout[8][8]);	
	// ~Pawn();
};

#endif