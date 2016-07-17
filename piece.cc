#include "piece.h"
#include <vector>
#include <string>
int Piece::pushValidMove(int x, int y,const Piece** layout, vector<string> &validMoves){
  if(layout[x - 1][y - 1] == nullptr){
  // cell is empty
  string result = to_string(x) + to_string(y);
  validMoves.push_back(result);
  return 0;
  } else if(layout[x - 1][y - 1]->colour != colour){
    // piece is not same colour and can be killed 
    string result = to_string(x) + to_string(y);
    validMoves.push_back(result);
    return 1;
  }else return 2;
}
virtual void getAllValidMove(const Piece** layout) = 0;
virtual bool move(int destX, int destY, const Piece** layout) = 0;
Piece::Piece(int x, int y, bool white) {
}
Piece::~Piece(int x, int y) {
