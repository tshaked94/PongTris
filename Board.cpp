#include "utils.h"
#include "Board.h"


int Board::startMenu()const
{
	system("cls"); //clearning the screen
	ShowConsoleCursor(false);
	//cout << "(1) Start a new game\n(8) Present instructions and keys\n(9) EXIT";

	cout << "(1) Start a new game - Human vs Human\n(2) Start a new game - Human vs Computer\n(3) Start a new game - Computer vs Computer\n(8) Present instructions and keys\n(9) EXIT";
	char k = (_getch());
	while (k != '1' && k != '2'&&k != '3')
	{
		if (k == '9')
		{
			cout << "\nThank you !!!" ;
			Sleep(100);
			return 0;
		}
		else if (k =='8')
		{
			showInsturctions();
			system("cls");
			cout << "(1) Start a new game - Human vs Human\n(2) Start a new game - Human vs Computer\n(3) Start a new game - Computer vs Computer\n(8) Present instructions and keys\n(9) EXIT";
		}
		 k = (_getch());
	}
	system("cls");
	return k-'0';
}


int Board::pausedMenu() const// the function will return 1 if the user choosed to start a new game.
{					    // the function will return 0 if the user choosed to resume the current game.
						// the function will return -1 if the user choosed to exit.
	system("cls");
	//cout << "(1) Start a new game\n(2) Continue a paused game\n(8) Present instructions and keys\n(9) EXIT";
	cout << "(1) Start a new game - Human vs Human\n(2) Start a new game - Human vs Computer\n(3) Start a new game - Computer vs Computer\n(4) Continue a paused game\n(8) Present instructions and keys\n(9) EXIT";

	char k = (_getch());
	while (k != '1' && k != '2'&&k != '3' && k != '4')
	{
		if (k == '9')
		{
			cout << "\nThank you !!!" ;
			Sleep(100);
			return -1;
		}
		else if (k =='8')
		{
			showInsturctions();
			system("cls");
			cout << "(1) Start a new game - Human vs Human\n(2) Start a new game - Human vs Computer\n(3) Start a new game - Computer vs Computer\n(4) Continue a paused game\n(8) Present instructions and keys\n(9) EXIT";			
		}
		 k = (_getch());
	}
	if (k == '1' || k == '2' || k == '3') // the user choosed to start a new game.
		return k-'0'; // return the wanted game mode.
	else //the user choosed to resume the current game.
		return 0;
}

int Board::gameLevelMenu(int side)const
{
	char k;
	system("cls");
	if (side == LEFT)
		cout << "Choose game level for left pc player\n";
	else
		cout << "Choose game level for right pc player\n";
	cout << "(1) Novice\n(2) Good\n(3) Best\n";
	do {
		k = (_getch());
	}
		while (k != '1' && k != '2'&&k != '3');
	system("cls");
	if (k == '1')
		return NOVICE;
	else if (k == '2')
		return GOOD;
	else if (k == '3')
		return BEST;
	return 0;
}

void Board::showInsturctions() const
{
	system("cls");
	cout << "Instructions:\n Welcome to PongTris game!\n This game is a PvP. The left user is controlling his board by using the letters 'q' and 'a'.";
	cout << "\n q will move the left user board UP and a will move it DOWN.\nThe right user is controlling his board by using the letters 'p' and 'l'.";
	cout << "\n p will move the right user board UP and l will move it DOWN.\n";
	cout << "The ball will move in diagonal movement, dont let the ball pass by your board towards the wall!\n";
	cout << "If the ball will pass by it, This will make your board move one step closer to GAME OVER\n";
	cout << "After 16 steps as described , you will lose and the game will stop!\n";
	cout << "When the ball is passing by a user board, the board will 'die' and will be moved to the farest point towards the board limits\n";
	cout << "You can try to make a 'Tetris line' by completing a full row of 'dead boards'!";
	cout << "If you will do it, your user board will go 5 steps 'back' and give you 5 more chances to lose before GAME OVER\n";
	cout << "The game developers hope you will enjoy your gaming experience!\n";
	system("PAUSE");
}

void Board::drawFrame()const
{//drawing board limits
	for (size_t i = 0; i < SCREEN_MAX_X; i++)
	{
		gotoxy(i, 3);
		cout << '-';
		gotoxy(i, 25);
		cout << '-';
	}
	for (size_t i = 4; i < SCREEN_MAX_Y; i++)
	{
		gotoxy(0,i);
		cout << '|';
	}
}
