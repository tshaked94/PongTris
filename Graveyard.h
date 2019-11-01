#pragma once
#include "utils.h"
#include "UserPongBoard.h"
#include "PcPongBoard.h"

typedef struct BurriedBoard:public PongBoard 
{//struct for handling the list of the dead boards
	int getDirToMove() const override { return 0; }
	void updateDirToMove(int gameMode,int ballHitLocation) override { return; }
	int getGameLevel()const override { return 0; }
	int findBallHitLocation(PongBoard* leftPlayer, PongBoard* rightPlayer)const override {return -1;};
	void moveBoardTowardsTarget()override { return; }
	void setDirToMove(int newDir)override { return; }
	void goBackToCenter()override { return; }
	BurriedBoard() = default;
}BurriedBoard;

class Graveyard
{
public:
	enum { MAX_LOSES = 16 };
private:
	std::list<BurriedBoard> graveZone[MAX_LOSES];
public:
	int buryBoard(PongBoard* pb);
	bool isItTetrisLine(int index) const; // the function return true tetris line is exists. 
	bool pushCheck(const BurriedBoard bb, int i);// return 1 if you can push, 0 if not
	bool pushCheckHelper(Point& lower, std::list<BurriedBoard>* list)const;//this function gets list and the lower point and return 1 if there is dead board in the range of y.
    bool overBoards(Point* lower1,Point &lower2)const; //the function return true if the boards crossing.
	void gravesCleaner();
	void draw() ;
	friend class Game;
};

