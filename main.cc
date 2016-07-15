#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "pieces.h"
#include "king.h"
#include "cell.h"
using namespace std;
class player {
  Board &b;
  bool move() = 0;
};
class human : public player {
  bool move() {
    string command, cell1, cell2;
    cin >> command;
    if (command == "resign") 
    return b.move(cell1, cell2);
  }
  player(Board &b) : b(b) {};
}

int main() {
  string c;
  stringstream x;
  player *white;
  player *black;
  player *current;
  int whitescore = 0;
  int blackscore = 0;
  Board * board = new Board();
  bool whiteturn = true;
  while (cin >> c) {
    if ("game" == c) {
      board->def();
      cin >> c;
      if (c == "human") {
        white = new human();
      }
      cin >> c;
      if (c == "human") {
	black = new human();
      }
      current = white;
    }
    if ("setup" == c) {
      while (cin >> c) {
        if (c == "done") {break;}
        else if (c == "+") {
          cin >> c;
          string x;
          cin >> x;
          piece newpiece;
          // check what piece c is, initialize it.
          board->set(newpiece, x);
        } else if (c == "-") {
          cin >> c;
          board->remove(c);
        }
      }
    }
    while (! board->done) {
      try {current->move;}
      catch { // catch resign and break
      }
      if (whiteturn) {
        whiteturn = false;
        current = black;
      } else {
	whiteturn = true;
	current = white;
      }
    }
  }
}
