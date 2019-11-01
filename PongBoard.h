#pragma once
#include "Point.h"
#include "utils.h"
//This is the base class
class PongBoard
{
	int boardSide;
	Point lower, upper;	
public:
	virtual ~PongBoard() { ; }
	PongBoard(int boardSide1, const Point & lower1 = {}, const Point& upper1 = {}) :lower(lower1), upper(upper1), boardSide(boardSide1) {}
	void draw() const;
	void set(const Point& lower1, const Point& upper1, int boardSide1) { lower = lower1; upper = upper1; boardSide = boardSide1; }
	bool boardLimit(int diry)const;
	void move(int dirx, int diry);
	void erase()const;
	PongBoard() = default;
	Point getLower() const { return lower; }
	Point getUpper() const { return upper; }
	int getBoardSide() const { return boardSide; }
	virtual int getDirToMove() const = 0;
	virtual int findBallHitLocation(PongBoard* leftPlayer, PongBoard* rightPlayer)const = 0;
	virtual void updateDirToMove(int gameMode, int ballHitLocation) = 0;
	virtual void moveBoardTowardsTarget() = 0;
	virtual void setDirToMove(int newDir) = 0;
	virtual int getGameLevel()const = 0;
	virtual void goBackToCenter() = 0;
};

