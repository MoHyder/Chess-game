#ifndef __TEXT_H__
#define __TEXT_H__
#include "view.h"
#include <iostream>
using namespace std;

class Text : public View{
public:
    Text(Board *b):View{b}{}    
    ~Text(){b = nullptr;}

    void draw(){
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
};

#endif