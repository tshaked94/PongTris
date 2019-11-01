#include "Graveyard.h"

int Graveyard::buryBoard(PongBoard* pb)
{//this function is moving the board to the right place and return the index of the list that marks the position of the dead board
	BurriedBoard bb, temp;
	bb.set(pb->getLower(), pb->getUpper(), pb->getBoardSide());
	temp = bb;
    int index;
	int xMoving = 0;
	while (!pushCheck(bb,xMoving))//true if someone is disturbing , false otherwise
    {
		if (bb.getBoardSide() == LEFT)
		{
			temp.erase();
			temp.move(LEFT, 0);
			temp.draw();
		}
		else
		{
			temp.erase();
			temp.move(RIGHT, 0);
			temp.draw();
		}
		xMoving++;
		Sleep(50);
    }
	if (bb.getBoardSide() == LEFT)
	{
		index = temp.getLower().getX()-1;
		if (index<MAX_LOSES)
			(graveZone)[index].push_back(temp);
	}
	else
	{
		index = 79 - temp.getLower().getX();
		if (index < MAX_LOSES)
			(graveZone[index]).push_back(temp);
	}
	return index;
}

bool Graveyard::isItTetrisLine(int index) const
{
	return (graveZone[index].size() == 7); //return true if we got a tetris line !
}


bool Graveyard::pushCheck(const BurriedBoard bb,int i)
{
	Point tempLow = bb.getLower();
	if (bb.getBoardSide() == LEFT)
	{
		tempLow.move(LEFT-i, 0);
		//[1] check if there is dead board on the place we want to go to
		//run on all the list nodes at the relevant list(index of arr) and check if there is someone disturbing  
		return ((tempLow.getX()==0) || pushCheckHelper(tempLow, graveZone));
	}
	else
	{
		tempLow.move(RIGHT+i, 0);
		return ( (tempLow.getX()==80) || pushCheckHelper(tempLow, graveZone));
	}
}

bool Graveyard::pushCheckHelper(Point & lower, std::list<BurriedBoard>* list)const
{//false if no one is disturbing
	Point tempLow = lower;
	std::list<BurriedBoard>::iterator itr;
	for (int i = MAX_LOSES-1; i >= 0; i--)
	{
		for (itr = list[i].begin(); itr != list[i].end(); ++itr)
		{
			if (overBoards(&(itr->getLower()), tempLow)) //return true if some board is disturbing.
				return true;
		}
	}
 	return false;
}

bool Graveyard::overBoards(Point* lower1, Point & lower2)const
{// false if no one is disturbing
	return (abs(lower1->getY() - lower2.getY()) <= 2) && (lower1->getX() == lower2.getX());
}

void Graveyard::gravesCleaner()
{
	for (size_t i = 0; i < MAX_LOSES; i++)
		graveZone[i].clear();
}

void Graveyard::draw()
{
	std::list<BurriedBoard>::iterator itr;
	for (int i = 0; i < MAX_LOSES; i++)
		for (itr = graveZone[i].begin(); itr != graveZone[i].end(); ++itr)
			itr->draw();
}
