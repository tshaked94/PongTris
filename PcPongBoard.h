#pragma once
#include "Point.h"
#include "PongBoard.h"
#include "utils.h"
#include "Ball.h"
class PcPongBoard:public PongBoard
{
	int gameLevel;
	int dirToMove = 0;
	Ball* ball;
public:
	PcPongBoard(int boardSide1, Ball* b, int gameLevel1=NOVICE) :PongBoard(boardSide1),gameLevel(gameLevel1), ball(b) {}//c'tor
	int getDirToMove() const override { return dirToMove; }
	void updateDirToMove(int gameMode, int ballHitLocation) override ;
	int getGameLevel()const override { return gameLevel; }
	void setGameLevel(int level) { gameLevel = level; }
	void moveBoardTowardsTarget()override;
	void setDirToMove(int newDir)override { dirToMove = newDir; }
	void goBackToCenter()override { dirToMove = 14; }
	int findBallHitLocation(PongBoard* leftPlayer, PongBoard* rightPlayer)const override;
};

