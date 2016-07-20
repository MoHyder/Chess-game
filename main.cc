#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "pieces.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "player.h"
#include "human.h"
#include "view.h"
#include "text.h"

using namespace std;

int main() {
  string c;
  stringstream x;
  player *white;
  player *black;
  player *current;
  int whitescore = 0;
  int blackscore = 0;
  Board * board = new Board();
  Text view = new Text(board);
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
	  int xpos, ypos;
	  xpos = x[0] - 'a';
	  ypos = x[1] - '1';
          board->editBoard(x, xpos, ypos);
        } else if (c == "-") {
          cin >> c;
          board->remove(c);
        }
      }
    }
    View view(board);
    view.print();
    while (! board->isCheckMate() || ! board->isStaleMate()) {
      if (! current->move) {
        break;
      }
      view.print();
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
