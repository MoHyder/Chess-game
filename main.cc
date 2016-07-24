#include <iostream>
 #include <string>
 #include <sstream>
 #include <fstream>
 #include "board.h"
 
 #include "piece.h"
 #include "player.h"
 #include "human.h"
 #include "comp1.h"
 #include "comp2.h"
 
 #include "view.h"
 #include "text.h"
 #include "graphic.h"
 
 using namespace std;
 
 
 Board b{};
 bool whiteTurn = true;
 
 bool setup(string c){	
 	istream *in = &cin;
 	ifstream fin;
 
 	// read from file			
 	if("lff" == c){
 		cout << "ENTER FILE NAME:" << endl;
 		cin >> c;		
 		fin = ifstream{c};
 		// change input method to file
 		in = &fin; 
 	}else if("game" == c){
 		fin = ifstream{"defaultBoard.in"};
 		in = &fin; 
 	} 
 	while (*in >> c) {
 		if(c == "setup") continue;
 		if (c == "done" && b.isDone()) {return true;}
 		else if (c == "+") {
 		  	*in >> c;
 		  	string x;
 		  	*in >> x;
 				int xpos, ypos;
 				xpos = x[0] - 'a';
 				ypos = x[1] - '1';
 		  	b.editBoard(c[0], xpos, ypos);
 		} else if (c == "-") {
 		  	*in >> c;
 			int xpos, ypos;
 				xpos = c[0] - 'a';
 				ypos = c[1] - '1';
 				b.editBoard(c[0], xpos, ypos);
 		}else if(c == "="){
 			*in >> c;
 			if(c == "black") whiteTurn = !whiteTurn;
 		}else cout << "TRY AGAIN" << endl;
 	}
 
 	return false;	
 }
 
int main() {
	string c;
 	Player *white;
 	Player *black;
 	Player *current;
 	float whitescore = 0;
 	float blackscore = 0;
 	Text view {&b}; 	
 	bool lff = false;	
 	while (true) {
 		cout << "PLEASE ENTER" << endl;
 		cout << "1) lff :To load from file" << endl;
 		cout << "2) setup :To setup board" << endl;  	
 		cout << "3) game :To start game" << endl;
 		cin >> c;
 		if(cin.fail()) break;		
 		if ("setup" == c || "lff" == c) {
 			if("lff" == c) lff = true;
 			setup(c);
 			view.draw();
 		}		
 		if("game" == c){
 			cout << "WHITE PLAYER, PLEASE ENTER:" << endl;
 	  		cout << "1) human" << endl;
 	  		cout << "2) computer[1]" << endl;
 	  		cout << "3) computer[2]" << endl;
 	  		cin >> c;
 			if (c == "human") white = new Human(&b, 'w');
 			else if (c == "computer[1]") white = new Comp1(&b, 'w');
 			else if (c == "computer[2]") white = new Comp2(&b,'w');
 			cout << "BLACK PLAYER" << endl;	  		
 	  		cin >> c;
 			if (c == "human") black = new Human(&b, 'b');
 			else if (c == "computer[1]") black = new Comp1(&b, 'b');
 			else if (c == "computer[2]") black = new Comp2(&b,'b');			
 		  	current = white;
 
 			cout << "STARTING GAME" << endl;
 			if(!lff) {setup("game"); view.draw();}
 			
 			bool resigned = false;
 			bool inCheckMate = false;
 			bool inStaleMate = false;

 			while (!inCheckMate && !inStaleMate && !resigned) {
 				if(whiteTurn) cout << "ENTER WHITE'S MOVE:" << endl;
 				else cout << "ENTER BLACK'S MOVE:" << endl;

 				if (whiteTurn) current = white;
 				else current = black;
 
 				current->move();
 				if(b.isCheckMate()) inCheckMate = true;
 				if(b.isStaleMate()) inStaleMate = true;				
 				view.draw();
 
 				whiteTurn = !whiteTurn;
 			}			
 
 			// updating score
			if(inStaleMate){
				cout << "Stalemate!" << endl;
				whitescore += 0.5; blackscore += 0.5;
			}else if(inCheckMate || resigned){
				if (!resigned) cout << "Checkmate!" << endl;
				if(!whiteTurn){
					whitescore++;
					cout << "White wins!" << endl;
				}
				else {
					blackscore++;
					cout << "Black wins!" << endl;	
				}					
			}			 	
 		}
 	} 
 	cout << "Final Score" << endl;
 	cout << "White: " << whitescore << endl;
 	cout << "Black: " << blackscore << endl;	
 
 	return 0;
}