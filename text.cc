#include "board.h"
#include "view.h"
#include "text.h"
#include <iostream>
using namespace std;

void Text::draw(){
	bool squareBlack = false;

	for(int y = 7; y >= 0 ; y--){		
		for(int x = 0; x < 8; x++){		
			if(b->layout[x][y] != nullptr){
				if(b->layout[x][y]->getColour() == 'w') cout << b->layout[x][y]->getName();
				else{
					char colour = b->layout[x][y]->getName() + 32;
					cout << colour;
				} 
			}else if(squareBlack) cout << "_";
			else cout << " ";	
			
			squareBlack = !squareBlack; 
		}
		squareBlack = !squareBlack; 
		cout << endl;
	}
}

