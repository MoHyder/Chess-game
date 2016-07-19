#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>
#include <string>
#include <iostream>

class Piece{
public:
	int curX;
	int curY;
	std::string curXY;
	const std::string name;
	const char colour;
	bool moved;	
	// vector for all valid moves a piece can make
	std::vector<std::string> validMoves;
	
	Piece(int curX, int curY, std::string curXY, std::string name, char colour, bool moved = false)
	:curX{curX},curY{curY},curXY{curXY},name{name},colour{colour},moved{moved}{}
	// checks to see if cell is empty or can be attacked, if it is then it is a valid move
	// backedUp includes "killing own" as a move
	int pushValidMove(int x, int y,char colour, Piece* const layout[8][8], std::vector<std::string> &validMoves, bool backedUp = false){
		if(layout[x][y] == nullptr){
			// cell is empty
			std::string result = std::to_string(x) + std::to_string(y);
			if(result != curXY)	validMoves.push_back(result);
			return 0;
		}else if(backedUp || layout[x][y]->colour != colour){
			// piece is not same colour and can be killed 
			std::string result = std::to_string(x) + std::to_string(y);
			if(result != curXY)	validMoves.push_back(result);
		}
		return 1;
	}
	virtual void getAllValidMoves(Piece* const layout[8][8], bool backedUp = false) = 0;
	virtual bool move(int destX, int destY, Piece* const layout[8][8]) = 0;	
	virtual ~Piece(){};
};

#endif