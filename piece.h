#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>
#include <string>
#include <iostream>

class Piece{
protected:
	int curX;
	int curY;
	const char name;
	const char colour;
	bool moved;

	// checks to see if cell is empty or can be attacked, if it is then it is a valid move
	// backedUp includes "killing own" as a move
	int pushValidMove(int x, int y, Piece* const layout[8][8], std::vector<std::string> &validMoves, bool backedUp){
		std::string curXY = std::to_string(curX) + std::to_string(curY);
		if(layout[x][y] == nullptr){
			// cell is empty
			std::string result = std::to_string(x) + std::to_string(y);
			if(result != curXY)	validMoves.push_back(result);
			return 0;
		}else if(backedUp || layout[x][y]->colour != colour){
			// piece is not same colour and can be killed 
			std::string result = std::to_string(x) + std::to_string(y);
			if(result != curXY)	validMoves.push_back(result);
			if(backedUp && layout[x][y]->getName() == 'K') return 0;
		}
		return 1;
	}

public:	
	// vector for all valid moves a piece can make
	std::vector<std::string> validMoves;
	Piece(int curX, int curY, char name, char colour, bool moved = false)
	:curX{curX},curY{curY},name{name},colour{colour},moved{moved}{}	

	int getX(){return curX;}
	int getY(){return curY;}
	bool getMoved(){return moved;}
	char getColour(){return colour;}
	char getName(){return name;}
	void setX(int x){curX = x;}
	void setY(int y){curY = y;}
	void setMoved(bool move){moved = move;};

	virtual void getAllValidMoves(Piece* const layout[8][8], bool backedUp = false) = 0;
	virtual bool move(int destX, int destY, Piece* const layout[8][8]) = 0;	
	virtual ~Piece(){};
};

#endif
