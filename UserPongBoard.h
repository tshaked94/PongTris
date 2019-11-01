#pragma once
#include "Point.h"
#include "utils.h"
#include "PongBoard.h"
#include "KeyboardEventListener.h"

class UserPongBoard :public PongBoard, public KeyboardEventListener
{
private:
	enum { MOVE_UP, MOVE_DOWN };
	char kbChars[3]; //UserPongBoard moving keys
public:
	UserPongBoard(int boardSide1) :PongBoard(boardSide1)
	{
		if (PongBoard::getBoardSide() == LEFT) // setting UserPongBoard moving keys by his defined side.
		{ 
			kbChars[0] = 'q';
			kbChars[1] = 'a';
			kbChars[2] = '\0';
		}
		else
		{
			kbChars[0] = 'p';
			kbChars[1] = 'l';
			kbChars[2] = '\0';
		}
	}
	void handleKey(char c);
	const char* getKbChars()const override { return kbChars; }
	void setKbChars(const char c1, const char c2) {
		kbChars[0] = c1;
		kbChars[1] = c2;
	}
	int getGameLevel()const override { return 0; }
	int findBallHitLocation(PongBoard* leftPlayer, PongBoard* rightPlayer)const override { return -1; }
	void moveBoardTowardsTarget()override { return; }
	void setDirToMove(int newDir)override { return; }
	void goBackToCenter()override { return; }
	int getDirToMove() const override { return 0; }//userPongBoard is not interested in this function
	void updateDirToMove(int gameMode, int ballHitLocation) override { return; }//userPongBoard is not interested in this function
};

