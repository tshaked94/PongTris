#include "PcPongBoard.h"

void PcPongBoard::moveBoardTowardsTarget()
{
	if (dirToMove != 0)
	{
		if (dirToMove > getLower().getY() && boardLimit(DOWN))
		{
			getUpper().erase();
			move(0, DOWN);
			getLower().draw();
		}
		else if (dirToMove < getLower().getY() && boardLimit(UP))
		{
			getLower().erase();
			move(0, UP);
			getUpper().draw();
		}
	}
}

int PcPongBoard::findBallHitLocation(PongBoard* leftPlayer, PongBoard* rightPlayer)const
{//this function calculates where the ball is going to hit and return the y of the hit location
	Point edge;
	int diry=ball->getDirY();
	edge = ball->getLeftest();

	if (ball->getDirX() == LEFT) 
	{
		while (leftPlayer->getLower().getX() != edge.getX())
		{
			if (edge.getY()+UP== MIN_Y || edge.getY()+DOWN == MAX_Y)
				diry *= -1;
			edge.move(LEFT, diry);
		}
		leftPlayer->setDirToMove(edge.getY()+DOWN);
	}
	else
	{
		edge.move(RIGHT * 3, 0);
		while (rightPlayer->getLower().getX() != edge.getX())
		{
			if (edge.getY() + UP == MIN_Y || edge.getY() + DOWN == MAX_Y)
				diry *= -1;
			edge.move(RIGHT, diry);
		}
		rightPlayer->setDirToMove(edge.getY()+DOWN);

	}
	return edge.getY();
}

void PcPongBoard::updateDirToMove(int gameMode,int ballHitLocation)
{
	int miss;
	switch (gameMode)
	{
	case NOVICE:
		miss = 10;
		break;
	case GOOD:
		miss = 40;
		break;
	case BEST:
		miss = 0;
		break;
	}
	if (miss != 0)
	{
		srand(time(NULL));//random func helper
		miss = rand() % miss;
	}
	if (miss == 1)//should miss the ball - put wrong hit location
	{
		dirToMove = ballHitLocation + UP * 5;
	}
}
