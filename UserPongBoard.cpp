#include "UserPongBoard.h"
#include<conio.h>

// PongBoard::handleKey handle the user clicks to move the pongBoards
void UserPongBoard::handleKey(char c)
{
	if (c == kbChars[MOVE_UP])
	{
		if (boardLimit(UP))
		{
			getLower().erase();
			move(0, UP);
			getUpper().draw();
		}
	}
	else if (c == kbChars[MOVE_DOWN])
	{
		if (boardLimit(DOWN))
		{
			getUpper().erase();
			move(0, DOWN);
			getLower().draw();
		}
	}
}