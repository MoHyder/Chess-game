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
    blackpieces[x] = new Pawn(1, x);
    whitepieces[x] = new Pawn(6, x);
    layout[1][x] = blackpieces[x];
    layour[6][x] = whitepieces[x];
  }
  blackpieces[8] = new Rook(0,0); blackpieces[9] = new Knight(0,1); blackpieces[10] = new Bishop(0,2); blackpieces[11] = new Queen(0,3); blackpieces[12] = new King(0,4); blackpieces[13] = new Bishop(0,5); blackpieces[14] = new Knight(0,6); blackpieces[15] = new Rook(0,7);
  whitepieces[8] = new Rook(7,0); whitepieces[9] = new Knight(7,1); whitepieces[10] = new Bishop(7,2); whitepieces[11] = new Queen(7,3); whitepieces[12] = new King(7,4); whitepieces[13] = new Bishop(7,5); whitepieces[14] = new Knight(7,6); whitepieces[15] = new Rook(7,7);
  whiteKing = whitepieces[12];
  blackKing = blackpieces[12];
  for (int x = 0, x < 8, x++) {
    layout[0][x] = blackpieces[x + 8];
    layour[7][x] = blackpieces[x + 8];
  }
  previous = nullptr;
}
bool Board::set(piece * x, int xpos, int ypos) {
  if (x->
}
 void def();
 bool set(piece * x, int xpos, int ypos);
}

