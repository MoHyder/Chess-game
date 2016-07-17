#include "cell.h"
#include "pieces.h"
#include <iostream>
#include <string>
using namespace std;

class Board {
 piece*[8][8] layout;
 piece *whiteKing;
 piece *blackKing;
 bool turn;
 bool incheck;
 piece*[16] blackpieces;
 piece*[16] whitepieces;
 
 Board();
 ~Board();
 void def();
 bool set(piece * x, int xpos, int ypos);
}

