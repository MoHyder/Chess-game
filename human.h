#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <iostream>
#include <string>
#include "player.h"
#include "board.h"
using namespace std;
class Human: public Player {
  public:
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
    char type;
    if (b->layout[x1][y1]) {
      type = b->layout[x1][y1]->getName();
      while (b->move(x1, y1, x2, y2, type) > 101 ) {
        cin >> cell1 >> cell2;
        x1 = cell1[0] - 'a';
        x2 = cell2[0] - 'a';
        y1 = cell1[1] - '1';
        y2 = cell2[1] - '1';
      }
    return true;
    } return false;
  }
  Human(Board * b, char colour): Player(b, colour) {}
};

#endif
