#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <iostream>
#include <string>
#include "board.h"
using namespace std;
class human : public player {
  bool move() {
    string command, cell1, cell2;
    cin >> command;
    if (command == "resign") {return false;}
    cin >> cell1 >> cell2;
    int x1, x2, y1, y2;
    x1 = cell1[0] - 'a';
    x2 = cell2[0] - 'a';
    y1 = cell1[1] - '1';
    y2 = cell2[1] - '1';
    while (b.move(x1, y1, x2, y2) > 101 ) {
      cin >> cell1 >> cell2;
      x1 = cell1[0] - 'a';
      x2 = cell2[0] - 'a';
      y1 = cell1[1] - '1';
      y2 = cell2[1] - '1';
    }
    return true
  }
  player(Board &b) : b(b) {}
  ~player(Board &b) {b = nullptr;}
};

#endif
