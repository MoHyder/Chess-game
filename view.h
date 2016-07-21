#ifndef __VIEW_H__
#define __VIEW_H__
#include "board.h"

class View {
protected:
	Board *b;
public:
	View(Board *b): b{b}{}
	virtual void draw() = 0;
	virtual ~View(){}
};

#endif