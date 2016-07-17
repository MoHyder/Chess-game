#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>
#include <string>

class Piece{
	int curX;
	int curY;
	const bool isWhite;
public:
	// vector for all valid moves a piece can make
	std::vector<string> validMoves;	
	// checks to see if cell is empty or can be attacked, if it is then it is a valid move
	int pushValidMove(int x, int y,const Piece** layout, vector<string> &validMoves){
		if(layout[x - 1][y - 1] == nullptr){
			// cell is empty
			string result = to_string(x) + to_string(y);
			validMoves.push_back(result);
			return 0;
		}else if(layout[x - 1][y - 1]->colour != colour){
			// piece is not same colour and can be killed 
			string result = to_string(x) + to_string(y);
			validMoves.push_back(result);
			return 1;
		}else return 2;
	}
	virtual void getAllValidMove(const Piece** layout) = 0;
	virtual bool move(int destX, int destY, const Piece** layout) = 0;
	virtual Piece(int x, int y) = 0;
        ~Piece(int x, int y);
};
