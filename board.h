#include "cell.h"
#include "pieces.h"
#include <iostream>
#include <string>
using namespace std;
class Stack {
  piece * taken;
  int movedtox, movedtoy, movedfromx, movedfromy;
  Stack * next;
  Stack(int movedtox, int movedtoy, int movedfromx, int movedfromy, piece *taken = nullptr, Stack * next) : movedtox(movedtox), movedtoy(movedtoy), movedfromx(movedfromx), movedfromy(movedfromy), next(next) {}
  ~Stack() {taken = nullptr; delete next;}
}

class Board {
 piece*[8][8] layout;
 piece *whiteKing;
 piece *blackKing;
 bool turn;
 bool incheck;
 Stack previous;
 piece*[16] blackpieces;
 piece*[16] whitepieces;
 
 Board();
 ~Board();
 void def();
 bool set(piece * x, int xpos, int ypos);
}

