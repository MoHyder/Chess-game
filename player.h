#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "board.h"
using namespace std;
class player {
  Board &b;
  bool move() = 0;
};
#endif
