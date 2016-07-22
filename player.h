#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "board.h"
using namespace std;

class Player {
protected:
	Board *b;
	const char colour;
public:	
	Player(Board * b, char colour): b{b}, colour{colour}{}
	virtual ~Player(){}
	virtual bool move() = 0;	
};

#endif
