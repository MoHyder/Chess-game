#ifndef __TEXT_H__
#define __TEXT_H__
#include "view.h"

class Text : public View{
public:
	Text(Board *b):View{b}{}
	void draw();
	~Text(){};
};

#endif