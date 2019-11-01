#include "PongBoard.h"

//GeneralBoard::erase GeneralBoard object.
void PongBoard::erase()const
{
	Point mid = lower;
	mid.move(0, UP);
	lower.erase();
	mid.erase();
	upper.erase();
}

//GeneralBoard::move responsible on the PongBoard moving.
void PongBoard::move(int dirx, int diry)
{
	Point mid = lower;
	mid.move(0, UP);
	mid.move(dirx, diry);
	lower.move(dirx, diry);
	upper.move(dirx, diry);
}

//GeneralBoard::draw drawing an GeneralBoard object on the screen.
void PongBoard::draw() const
{
	Point temp = lower;
	while (temp != upper)
	{
		temp.draw();
		temp.move(0, UP);
	}
	temp.draw();
}

//This function is checking if the movement is legal(not over the board limits) if it is it return true, otherwise it return false.
bool PongBoard::boardLimit(int diry)const
{
	int pyLower, pyUpper;
	pyLower = lower.getY() + diry;
	pyUpper = upper.getY() + diry;
	return((pyUpper >= MIN_Y) && (pyLower <= MAX_Y));
}
