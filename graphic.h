#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
#include "view.h"
#include "board.h"
#include "window.h"
#include <iostream>
using namespace std;

class Graphic: public View{
	Xwindow w;
	char colourLayout[8][8];	
public:
	Graphic(Board *b):View{b}{
		// printing board squares
		int squareColour = Xwindow::Red;
	    bool squareBlack = false;
		for(int y = 7; y >=0; y--){
	        for(int x = 0; x < 8; x++){
	        	if(squareBlack) squareColour = Xwindow::Black;
	            else squareColour = Xwindow::Red;            
	            w.fillRectangle(50 *(x + 1), 25 + 50 *(7 - y), 50, 50, squareColour);

	            // initializing colour layout
	            if(b->layout[x][y]) colourLayout[x][y] = b->layout[x][y]->getColour();
                else colourLayout[x][y] = 'n';
	           	squareBlack = !squareBlack;
	        }
	        squareBlack = !squareBlack;
	    }
	}	

	// redraw board
	void draw(){		
		int squareColour = Xwindow::Red;
	    bool squareBlack = false;
	    for(int y = 7; y >=0; y--){
	        for(int x = 0; x < 8; x++){
	        	// deciding colour
	            if(squareBlack) squareColour = Xwindow::Black;
	            else squareColour = Xwindow::Red;

	            // printing board
	            if(b->layout[x][y] != nullptr && b->layout[x][y]->getColour() != colourLayout[x][y]){
	            	string pieceName;
	            	stringstream ss;
	            	char name = b->layout[x][y]->getName();
                    if(b->layout[x][y]->getColour() == 'b') name += 32;
                    ss << name;
                    ss >> pieceName;
                    w.fillRectangle(50 *(x + 1), 25 + 50 *(7 - y), 50, 50, squareColour);
                    w.drawString( 25 + 50 *(x + 1) , 50 + 50 *(7 - y), pieceName , Xwindow::White);
                }else if(b->layout[x][y] == nullptr && colourLayout[x][y] != 'n' ){
                	w.fillRectangle(50 *(x + 1), 25 + 50 *(7 - y), 50, 50, squareColour);
                }

                // updating colour layout
                if(b->layout[x][y]) colourLayout[x][y] = b->layout[x][y]->getColour();
                else colourLayout[x][y] = 'n';

	            squareBlack = !squareBlack;
	        }
	        squareBlack = !squareBlack;        
	    }	        
	}

	~Graphic(){b = nullptr;}
	
};

#endif