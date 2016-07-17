#include "board.h"
#include "pieces.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
Board::~Board() {
  for (int x = 0, x < 16, x++) {
    delete blackpieces[x];
    delete whitepieces[x];
  }
  for (int x = 0, x < 8, x++) {
    for (int b = 0, b < 8, b++) {
      layout[x][b] = nullptr;
    }
  }
  whiteKing = nullptr; blackKing = nullptr; 
  delete previous
}
Board::Board() {
  for (int x = 0, x < 8, x++) {
    for (int b = 0, b < 8, b++) {
      layout[x][b] = nullptr;
    }
  }
  for (int x = 0, x < 16, x++) {
    blackpieces[x] = nullptr;
    whitepieces[x] = nullptr;
  }
  whiteKing = nullptr; blackKing = nullptr;
  turn = true;
  incheck = false;
}
void Board::def() {
  for (int x = 0, x < 8, x++) {
    blackpieces[x] = new Pawn(1, x, false);
    whitepieces[x] = new Pawn(6, x, true);
    layout[1][x] = blackpieces[x];
    layour[6][x] = whitepieces[x];
  }
  blackpieces[8] = new Rook(0,0, false);
  blackpieces[9] = new Knight(1,0, false);
  blackpieces[10] = new Bishop(2,0,false);
  blackpieces[11] = new Queen(3,0,false);
  blackpieces[12] = new King(4,0,false);
  blackpieces[13] = new Bishop(5,0,false);
  blackpieces[14] = new Knight(6,0,false);
  blackpieces[15] = new Rook(7,0,false);
  whitepieces[8] = new Rook(0,7,true);
  whitepieces[9] = new Knight(1,7,true);
  whitepieces[10] = new Bishop(2,7,true);
  whitepieces[11] = new Queen(3,7,true);
  whitepieces[12] = new King(4,7,true);
  whitepieces[13] = new Bishop(5,7,true);
  whitepieces[14] = new Knight(6,7,true);
  whitepieces[15] = new Rook(7,7,true);
  whiteKing = whitepieces[12];
  blackKing = blackpieces[12];
  for (int x = 0, x < 8, x++) {
    layout[0][x] = blackpieces[x + 8];
    layour[7][x] = blackpieces[x + 8];
  }
  previous = nullptr;
}
bool Board::set(piece * x, int xpos, int ypos) {
  layout[ypos][xpos] = x;
  if (typeid(
}
 void def();
 bool set(piece * x, int xpos, int ypos);
}

