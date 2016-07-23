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
    cout << "resign : to resign game" << endl;
    cout << "move : to move piece" << endl;
    cout << "undo : to undo last move" << endl;
    string command, cell1, cell2;
    cin >> command;
    if (command == "resign") {return false;}
    else if (command == "move") {
        int result = 300;
        while (result > 102) {
            if(result != 300) cout << "TRY AGAIN" << endl;
            cin >> cell1 >> cell2;
            int x1 = cell1[0] - 'a';
            int x2 = cell1[1] - '1';
            int y1 = cell2[0] - 'a';
            int y2 = cell2[1] - '1';
            result = b->move(x1, x2, y1, y2, colour);
            cout << "HUMAN result: " << result << endl;           
        }
        return true;
    }else if(command == "undo") {
        b->undoMove();
        return true;
    }
    return false;
  }
  Human(Board *b, char colour): Player(b, colour) {}
  ~Human(){}
};

#endif
