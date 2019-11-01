#include "Game.h"

void Game::initialize(PongBoard* left, PongBoard* right, KeyboardManager& KbManager, Ball& b)const
{//positioning the pong boards and the ball to their starting points
	system("cls"); // clearing the screen.
	//[1] initializing positions for left and right boards and drawing it
	left->set({ LEFT_PLAYER_DEFAULT_X,LEFT_PLAYER_DEFAULT_Y,DEFAULT_SYMBOL }, { LEFT_PLAYER_DEFAULT_X,LEFT_PLAYER_DEFAULT_Y-2,DEFAULT_SYMBOL }, LEFT);
	right->set({ RIGHT_PLAYER_DEFAULT_X,RIGHT_PLAYER_DEFAULT_Y,DEFAULT_SYMBOL }, { RIGHT_PLAYER_DEFAULT_X,RIGHT_PLAYER_DEFAULT_Y-2,DEFAULT_SYMBOL }, RIGHT);
	left->draw();
	right->draw();
	//[2] initializing the ball position
	b.initialize();
	PcBoardMovementManager(left, right, b);
}

bool Game::hitUserBoard(const PongBoard* pb, Ball & ball) const
{//this function is checking if the ball is hitting the board corner or regular hit and return true if it hits one of them, false otherwise
	bool cornerHit = false;
	bool regularHit = false;
	Point ball_bottom, ball_upper, ball_rightest;
	ball.getCornersPoints(ball_upper, ball_rightest, ball_bottom, ball.getDirX());
	if (ball.getDirX() == RIGHT)
	{
		cornerHit = corHit(pb, ball_rightest, ball);
		if (!cornerHit)
			regularHit = ((regHit(pb, ball_bottom, ball)) || (regHit(pb, ball_upper, ball)) || (regHit(pb, ball_rightest, ball)));
	}
	else
	{
		cornerHit = corHit(pb, ball.getLeftest(), ball);
		if (!cornerHit)
			regularHit = ((regHit(pb, ball_bottom, ball)) || (regHit(pb, ball_upper, ball)) || (regHit(pb, ball.getLeftest(), ball)));
	}
	if (cornerHit || regularHit)
	{
		ball.changeDir(cornerHit);
		return true;
	}
	return false;
}

bool Game::regHit(const PongBoard* pb, const Point & p, const Ball& b)const
{//the function gets a point and return true if its gonna hit the pb
	Point temp = p;
	temp.move(b.getDirX(), b.getDirY());

	if ((temp.getY() <= pb->getLower().getY()) && (temp.getY() >= pb->getUpper().getY()))
	{
		if (temp.getX() == pb->getLower().getX())
			return true;
		return false;
	}
	return false;
}

bool Game::corHit(const PongBoard* pb, const Point & p, const Ball & b)const
{//this function is returning true if the ball is hitting the board on its corner, false otherwise
	Point temp = p;
	temp.move(b.getDirX(), b.getDirY());
	if (b.getDirY() == DOWN)
	{
		if (temp == pb->getUpper())
			return true;
		return false;
	}
	else //dir y is UP
	{
		if (temp == pb->getLower())
			return true;
		return false;
	}
}

bool Game::outOfBoard(const PongBoard* pb, Ball & b)const
{//this function returns true if ball passed the X line of the board, false otherwise
	Point bottom, upper, rightest;
	b.getCornersPoints(upper, rightest, bottom, b.getDirX());
	bottom.move(-b.getDirX(), b.getDirY());
	upper.move(-b.getDirX(), b.getDirY());
	if (pb->getLower().getX() < MAX_X / 2) // checking left board case.
		return (bottom.getX() <= pb->getLower().getX()); //passed the X line of board
	else // checking right board case.
		return (bottom.getX() >= pb->getLower().getX()); //passed the X line of board

}

void Game::setBoardInPlace(PongBoard* pb, int dirx)const
{//this function set the left and right boards back in place
	Point low = pb->getLower();
	Point up = pb->getUpper();
	int tempX = low.getX();
	pb->erase();
	if (pb->getBoardSide() == LEFT)
	{
		if (tempX >= MIN_X){
		low.set(tempX - dirx, 12, '#');
		up.set(tempX - dirx, 10, '#');
		pb->set(low, up, LEFT);
		}
	}
	else
	{
		if (tempX <= MAX_X) {
			low.set(tempX - dirx, 13, '#');
			up.set(tempX - dirx, 11, '#');
			pb->set(low, up, RIGHT);
		}
	}
}

void Game::setBallControl(Ball & b, int gameMode)const
{
	if (gameMode == HUMAN_VS_HUMAN)
		b.setKbChars('s','k');
	else if (gameMode == HUMAN_VS_PC)
		b.setKbChars('s','\0');
	else if (gameMode == PC_VS_PC)
		b.setKbChars('\0','\0');
}

int Game::followBallMovement(PongBoard* leftBoard, PongBoard* rightBoard,Graveyard& graveLeft,Graveyard& graveRight, Ball & b)const
{//followBallMovement return LEFT if left pong board is dead because he missed the ball.
 //followBallMovement return RIGHT if right pong board is dead because he missed the ball.
 //followBallMovement return LEFT_EXPLODED if right pong board is dead because he is hitted by a bomb.
 //followBallMovement return RIGHT_EXPLODED if right pong board is dead because he is hitted by a bomb.
 //followBallMovement return 0 if nobody os dead.
	//LEFT_REGULAR_MISS -
	//	1. left miss the ball when it was a regular ball.

	//	LEFT_BECOMING_A_BOMB_MISS
	//	1. left miss the ball when it was in becoming a bomb state.

	//	LEFT_BOMB_BIG_MISS
	//	1. left got hitted by the bomb, it a big miss.

	//	LEFT_GRAVES_OR_EDGE_WAS_HITTED_BY_BOM

	bool isItOut = false;
	int reasonOfLosing=0;
	if (b.getDirX() == LEFT)
	{
		if (!hitUserBoard(leftBoard, b))// the condition gets true if the ball didn't hit the pong board.
		{
			isItOut = outOfBoard(leftBoard, b); // return true if the ball passed the pong board column.
			if (isItOut && b.getBallState() == REGULAR)
				return LEFT;
			else if (isItOut && b.getBallState() != REGULAR)
			{
				reasonOfLosing=ballIsInGraveyard(graveLeft, b); 
				if (reasonOfLosing == TETRIS_AWARD)
					return LEFT_TETRIS_AWARD;
				else if (reasonOfLosing == REGULAR_LOSS)
					return LEFT;
			}
		}
		else //hitted the board, check if bomb
		{
			if (b.getBallState() == BOMB)
				return LEFT_EXPLODED;
			PcBoardMovementManager(leftBoard, rightBoard, b);//calculate where to move
			leftBoard->goBackToCenter();
		}
	}
	else
	{
		if (!hitUserBoard(rightBoard, b)) // the condition gets true if the ball didn't hitted the right pong board.
		{
			isItOut = outOfBoard(rightBoard, b);
			if (isItOut && b.getBallState() == REGULAR)
				return RIGHT;
			else if (isItOut && b.getBallState() != REGULAR)
			{
				reasonOfLosing = ballIsInGraveyard(graveRight, b);
				if (reasonOfLosing == TETRIS_AWARD)
					return RIGHT_TETRIS_AWARD;
				else if (reasonOfLosing == REGULAR_LOSS)
					return RIGHT;
			}
		}
		else //hitted the board, check if bomb
		{
			if (b.getBallState() == BOMB)
				return RIGHT_EXPLODED;
			PcBoardMovementManager(leftBoard, rightBoard, b);//calculate where to move
			rightBoard->goBackToCenter();
		}
	}
	return 0;//no one is dead
}


void Game::run(Board &board)
{
	bool escPressed = false, gameOver = false;
	int isItDead = 0, restartGame = 0;
	Ball b;
	KeyboardManager KbManager;
	UserPongBoard leftUserBoard(LEFT), rightUserBoard(RIGHT);
	PcPongBoard leftPcBoard(LEFT, &b), rightPcBoard(RIGHT, &b);
	PongBoard* leftPlayer = nullptr, *rightPlayer = nullptr;
	Graveyard graveLeft, graveRight;
	registerListeners(leftUserBoard, rightUserBoard, KbManager,b);

	setPlayers(&leftPlayer, &rightPlayer, &leftUserBoard, &rightUserBoard, &leftPcBoard, &rightPcBoard);
	//get game Level from user if there is a PC Player
	setGameLevels(&leftPcBoard, &rightPcBoard, board);
	setBallControl(b,gameMode);
	//drawing game frame and initializing
	board.drawFrame();
	initialize(leftPlayer, rightPlayer, KbManager, b);
	while (true)
	{
		checkBallState(b, leftPlayer, rightPlayer);
		escPressed = KbManager.handleKeyboard();//checking if escape is pressed
		if (escPressed)
		{
			restartGame = board.pausedMenu(); //restartGame = true if the user choosed to start a new game, else it will get false.
			if (restartGame == -1)
				return;
			system("cls"); // clearing the screen after returning from menu.
		}
		if (restartGame)
		{	
			gameMode = restartGame - 1;
			setBallControl(b, gameMode);
			setPlayers(&leftPlayer, &rightPlayer, &leftUserBoard, &rightUserBoard, &leftPcBoard, &rightPcBoard);
			setGameLevels(&leftPcBoard, &rightPcBoard, board);

			//[2] restart the pongBoards and Ball positions
			initialize(leftPlayer, rightPlayer, KbManager, b);
			// [3] clear grave lists
			graveLeft.gravesCleaner();
			graveRight.gravesCleaner();
		}
		else //resuming the current game.
		{
			draw(leftPlayer, rightPlayer, graveLeft, graveRight, b); //re-drawing all game objects.
		}
		board.drawFrame();

		isItDead = followBallMovement(leftPlayer, rightPlayer,graveLeft,graveRight, b);//checking if one of the boards is 'dead'
		gameOver = underTaker(rightPlayer, leftPlayer, graveLeft, graveRight, b,isItDead);
		escPressed = false;
		restartGame = 0;
		if (gameOver)
		{
			if (board.startMenu())
			{
				restartGame = true;
				gameOver = false;
			}
			else
			{
				graveLeft.gravesCleaner();
				graveRight.gravesCleaner();
				return;
			}
		}
		b.move();
		leftPlayer->moveBoardTowardsTarget();
		rightPlayer->moveBoardTowardsTarget();
		b.setCountToChangeState(b.getCountToChangeState() - 1);//update ball count
		Sleep(50);
		isItDead = 0;
	}
}

void Game::draw(const PongBoard*leftBoard, const PongBoard*rightBoard, Graveyard &leftGrave, Graveyard &rightGrave, const Ball &b) const
{
	leftBoard->draw();
	rightBoard->draw();
	leftGrave.draw();
	rightGrave.draw();
	b.draw();
}

bool Game::graveManager(Graveyard& graves, PongBoard* pb)const
{
	int loser, index;
	//[1]send the losing board to the graveyard(all the way to the wall or next to other dead board)
	index = graves.buryBoard(pb);
	//[2]check if tetris line is recieved
	if (graves.isItTetrisLine(index)) //entering the condition if we got a tetris line.
	{
		Tetris(graves, index);
		repositionTetris(pb);
	}
	//[3] check if GAME OVER(passed the X line and lose the game)
	if (isItGameOver(graves, pb))
	{
		//release all the list and memory!
		system("cls");
		loser = pb->getBoardSide();
		if (loser == RIGHT)
			cout << "The winner is: **LEFT PLAYER**" << endl;
		else
			cout << "The winner is: **RIGHT PLAYER**" << endl;
		cout << endl << "You will soon return to the main menu, meanwhile enjoy the melody :)" << endl;
		gameOverMelody();
		return true;
	}
	else// if not GAME OVER sleep and countdown
		Sleep(350);
	return false;
}

int Game::ballIsInGraveyard(Graveyard & graves, Ball & b)const
{
	//getting ball corners and setting them to the temp point(according to dir of movement)
	Point upper, bottom, edge;
	BurriedBoard bb;
	int index;
	b.getCornersPoints(upper, edge, bottom, b.getDirX());
	upper.move(b.getDirX(), b.getDirY());
	bottom.move(b.getDirX(), b.getDirY());
	if (b.getDirX() == LEFT)
	{
		edge = b.getLeftest();
		edge.move(b.getDirX(), b.getDirY());
		//run on the list and check if the ball is hitting a dead board - if it is act according to ball state
		index = hitADeadBoard(graves, upper, edge, bottom, b.getDirX());
	}
	else//dir x is RIGHT
	{
		edge.move(b.getDirX(), b.getDirY());
		index = hitADeadBoard(graves, upper, edge, bottom, b.getDirX());
	}
	if (index != DIDNT_HIT_ANYTHING) // the ball hitted the screen limits or a dead board.
	{
		if (b.getBallState() == BOMB)
		{
			if (index == HIT_SCREEN_LIMITS)
				index = 0;
			Tetris(graves, index);
			return TETRIS_AWARD; // the defender got tetris award and go 1 step back.
		}
		else 
			return REGULAR_LOSS;
	}
	return 0; // nothing happened
}

void Game::repositionTetris(PongBoard * pb)const
{
	if (pb->getBoardSide() == LEFT)
		pb->move(LEFT * 5, 0);
	else
		pb->move(RIGHT * 5, 0);
}

int Game::hitADeadBoard(Graveyard & graves, Point & upper, Point & edge, Point & bottom,int dirx)const
{
	std::list<BurriedBoard>::iterator itr;
	for (int i = Graveyard::MAX_LOSES - 1; i >= 0; i--)
	{
		for (itr = graves.graveZone[i].begin(); itr != graves.graveZone[i].end(); ++itr)
		{
			if ((itr->getLower().getY())>=edge.getY()  && itr->getUpper().getY()<=edge.getY() && itr->getUpper().getX() ==edge.getX())
			{//return true if some board is disturbing.
				if (dirx == LEFT)
					return edge.getX() - 1;
				else
					return 79 - edge.getX();
			}
			else if ((graves.overBoards(&(itr->getLower()), bottom)))
			{
				if (dirx == LEFT)
					return bottom.getX()-1;
				else
					return 79 - bottom.getX();
			}

		}
	}
	if (edge.getX() == MAX_X + ONE || edge.getX() == MAX_X + TWO || edge.getX() == MIN_X - ONE || bottom.getX() == MIN_X - ONE)
		return HIT_SCREEN_LIMITS;
	return DIDNT_HIT_ANYTHING;//DIDNT HIT ANYTHING- KEEP GOING
}

void Game::Tetris(Graveyard & graves, int index)const
{
	std::list<BurriedBoard>::iterator itr;
	for (int i = index; i < Graveyard::MAX_LOSES - 1; i++)
	{
		for (itr = graves.graveZone[i].begin(); itr != graves.graveZone[i].end(); ++itr)
			itr->erase();
		if (!graves.graveZone[i].size())
			return;
		graves.graveZone[i].clear();
		graves.graveZone[i] = graves.graveZone[i + 1];
		for (itr = graves.graveZone[i].begin(); itr != graves.graveZone[i].end(); ++itr) {
			if (itr->getLower().getX() < (MAX_X / 2))//you are left graveyard
				itr->move(LEFT, 0);
			else // you are right graveyard
				itr->move(RIGHT, 0);
			itr->draw();
		}
	}
}

void Game::PcBoardMovementManager(PongBoard * left, PongBoard * right,Ball& b)const
{
	int hitLoc = right->findBallHitLocation(left, right);
	if (b.getDirX() == LEFT)
		left->updateDirToMove(left->getGameLevel(), hitLoc);
	else
		right->updateDirToMove(right->getGameLevel(), hitLoc);

	if (b.getDirX() == LEFT)
	{//move left player
		left->moveBoardTowardsTarget();
	}
	else
	{//move right player
		right->moveBoardTowardsTarget();
	}
}

bool Game::isItGameOver(Graveyard & graves, PongBoard* pb)const
{
	if (pb->getBoardSide() == LEFT)
		return(pb->getLower().getX() >= GAME_OVER_LEFT);
	else
		return(pb->getLower().getX() <= GAME_OVER_RIGHT);
}

void Game::setGameLevels(PcPongBoard * leftPcBoard, PcPongBoard * rightPcBoard, Board & board)const
{
	int level;
	if (gameMode == HUMAN_VS_HUMAN)
		return;
	else if (gameMode == HUMAN_VS_PC)
	{
		level = board.gameLevelMenu(RIGHT);
		leftPcBoard->setGameLevel(level);
	}
	else if (gameMode == PC_VS_PC)
	{
		level = board.gameLevelMenu(LEFT);
		leftPcBoard->setGameLevel(level);
		level = board.gameLevelMenu(RIGHT);
		rightPcBoard->setGameLevel(level);
	}
}

void Game::checkBallState(Ball & b,PongBoard *leftPlayer, PongBoard *rightPlayer)const
{
	int bLeftestX = b.getLeftest().getX(), bombAcLeft, bombAcRight;
	if ((b.getBallState() == BECOMING_A_BOMB) && (b.getCountToChangeState() == 0))
	{
		b.setBallState(BOMB);
		b.setCountToChangeState(4);
	}
	else if (b.getBallState() == BOMB && b.getCountToChangeState() == 0)
	{
		if (leftPlayer->getLower().getX() <= bLeftestX && rightPlayer->getLower().getX() >= bLeftestX) // the ball appear between the pong boards.
			b.setBallState(REGULAR);
	}
	if (bLeftestX == (MAX_X+1)/2)
	{
		bombAcLeft =b.getBombActivatorLeft();
		bombAcRight =b.getBombActivatorRight(); 
		if (bombAcLeft > 0) {
			b.setBombActivatorLeft(bombAcLeft - 1);
		}
		if (bombAcRight > 0) {
			b.setBombActivatorRight(bombAcRight - 1);
		}
	}
}

bool Game::underTaker(PongBoard * rightPlayer, PongBoard * leftPlayer, Graveyard & graveLeft, Graveyard & graveRight, Ball & b, int isItDead)const
{
	bool gameOver = false;
	b.erase();
	switch (isItDead)
	{
	case LEFT:
		gameOver = graveManager(graveLeft, leftPlayer);
		setBoardInPlace(leftPlayer, LEFT);
		setBoardInPlace(rightPlayer, 0);
		b.initialize();
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	case LEFT_EXPLODED:
		gameOver = graveManager(graveLeft, leftPlayer);
		setBoardInPlace(leftPlayer, LEFT * 3);
		setBoardInPlace(rightPlayer, 0);
		b.initialize();
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	case LEFT_TETRIS_AWARD:
		if (leftPlayer->getLower().getX() > MIN_X + 1)
			setBoardInPlace(leftPlayer, RIGHT);
		setBoardInPlace(rightPlayer, 0);
		b.initialize(40, RIGHT);
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	case RIGHT:
		gameOver = graveManager(graveRight, rightPlayer);
		setBoardInPlace(rightPlayer, RIGHT);
		setBoardInPlace(leftPlayer, 0);
		b.initialize();
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	case RIGHT_EXPLODED:
		gameOver = graveManager(graveRight, rightPlayer);
		setBoardInPlace(leftPlayer, 0);
		setBoardInPlace(rightPlayer, RIGHT * 3);
		b.initialize();
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	case RIGHT_TETRIS_AWARD:
		setBoardInPlace(leftPlayer, 0);
		if (rightPlayer->getLower().getX() < MAX_X - 2)
			setBoardInPlace(rightPlayer, LEFT);
		b.initialize(40,LEFT);
		PcBoardMovementManager(leftPlayer, rightPlayer, b);
		break;
	}
	rightPlayer->draw();
	leftPlayer->draw();
	return gameOver;
}

void Game::setPlayers(PongBoard ** leftPlayer, PongBoard ** rightPlayer, UserPongBoard * leftUserBoard, UserPongBoard * rightUserBoard, PcPongBoard * leftPcBoard, PcPongBoard * rightPcBoard)const
{
	if (gameMode == HUMAN_VS_HUMAN)
	{
		*leftPlayer = leftUserBoard;
		*rightPlayer = rightUserBoard;
		leftUserBoard->setKbChars('q', 'a');
		rightUserBoard->setKbChars('p', 'l');
	
	}
	else if (gameMode == HUMAN_VS_PC)
	{
		*leftPlayer = leftUserBoard;
		*rightPlayer = rightPcBoard;
		leftUserBoard->setKbChars('q', 'a');
		rightUserBoard->setKbChars('\0', '\0');
	}
	else if (gameMode == PC_VS_PC)
	{
		*leftPlayer = leftPcBoard;
		*rightPlayer = rightPcBoard;
		leftUserBoard->setKbChars('\0', '\0');
		rightUserBoard->setKbChars('\0', '\0');
	}
}
