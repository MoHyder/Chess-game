#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "board.h"
using namespace std;
class Player{
  public: 
  Board * b;
  virtual bool move() = 0;
  Player(Board * b): b(b) {}
};
#endif
