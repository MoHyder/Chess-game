#include <iostream>
#include <string>
#include <sstream>
#include "board.h"

#include "piece.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"

#include "player.h"
#include "human.h"
#include "comp1.h"

#include "view.h"
#include "text.h"

using namespace std;

int main() {
  string c;
  Player *white;
  Player *black;
  Player *current;
//  int whitescore = 0;
//  int blackscore = 0;
  Board * board = new Board();
  Text view = Text(board);
  bool whiteturn = true;
  while (cin >> c) {
    if ("game" == c) {
      for (int i = 0; i < 8; i++) {
	board->editBoard('p',1,i);
	board->editBoard('P',6,i);
      }
        board->editBoard('r',0,0);
        board->editBoard('n',0,1);
        board->editBoard('b',0,2);
	board->editBoard('q',0,3);
        board->editBoard('k',0,4);
        board->editBoard('b',0,5);
        board->editBoard('n',0,6);
        board->editBoard('r',0,7);
        board->editBoard('R',0,0);
        board->editBoard('N',0,1);
        board->editBoard('B',0,2);
        board->editBoard('Q',0,3);
        board->editBoard('K',0,4);
        board->editBoard('B',0,5);
        board->editBoard('N',0,6);
        board->editBoard('R',0,7);
      cin >> c;
      if (c == "human") {
        white = new Human(board, 'w');
      } else if (c == "computer[1]") {
	white = new Comp1(board, 'w');
      } //else if (c == "computer[2]") {
	//white = new AI2(board);
     // }
      cin >> c;
      if (c == "human") {
	black = new Human(board, 'b');
      } else if (c == "computer[1]") {
	black = new Comp1(board, 'b');
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
          board->editBoard(c[0], xpos, ypos);
        } else if (c == "-") {
          cin >> c;
	  int xpos, ypos;
	  xpos = c[0] - 'a';
	  ypos = c[1] - '1';
          delete board->layout[xpos][ypos];
	  board->layout[xpos][ypos] = nullptr;
        }
      }
    }
    view.draw();
    while (! board->isCheckMate() || ! board->isStaleMate()) {
      if (! current->move()) {
        break;
      }
      view.draw();
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
