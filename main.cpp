#include "Game.h"
#include "Board.h"

int main()
{
	int mode;
	Board board1;
	Game pongTris;
	mode = board1.startMenu();
	if (mode)
	{
		pongTris.setGameMode(mode-1);
		pongTris.run(board1);
	}
	return 0;
}
