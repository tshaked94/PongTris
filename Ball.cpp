#include "Ball.h"

void Ball::draw() const
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (getBallState() + ONE)*SEVEN); // arbitrary way to color the ball state.

	Point temp = leftest;
	for (int i = 0; i < 4; i++)//drawing middle row of the ball
	{
		temp.draw();
		temp.move(RIGHT, 0);
	}
	temp = leftest;
	temp.move(RIGHT, UP);
	for (int i = 0; i < 2; i++) //drawing upper row of the ball
	{
		temp.draw();
		temp.move(RIGHT, 0);
	}
	temp = leftest;
	temp.move(RIGHT, DOWN);
	for (int i = 0; i < 2; i++) //drawing bottom row of the ball
	{
		temp.draw();
		temp.move(RIGHT, 0);
	}
	SetConsoleTextAttribute(h, 10);
}

void Ball::erase()const
{
	Point temp = leftest;
	for (int i = 0; i < 4; i++)
	{
		temp.erase();
		temp.move(RIGHT, 0);
	}
	temp = leftest;
	temp.move(RIGHT, UP);
	for (int i = 0; i < 2; i++)
	{
		temp.erase();
		temp.move(RIGHT, 0);
	}
	temp = leftest;
	temp.move(RIGHT, DOWN);
	for (int i = 0; i < 2; i++)
	{
		temp.erase();
		temp.move(RIGHT, 0);
	}
}

//Ball::getCorenerPoints return the edges of the ball by parameter
void Ball::getCornersPoints(Point & upper, Point & rightest, Point & bottom, int dirx) const
{
	if (dirx == LEFT)
		dirx = 0;
	upper.set(leftest.getX() + RIGHT + dirx, leftest.getY() + UP, 'O');
	rightest.set(leftest.getX() + 3 * RIGHT, leftest.getY(), 'O');
	bottom.set(leftest.getX() + RIGHT + dirx, leftest.getY() + DOWN, 'O');
}


void Ball::move()
{
	int didItHit = hitBoard();
	if (didItHit == 0) //hitting the board limits( 1 = hitted the Y limits, -1 = didnt hit)
	{
		dir_x *= -1;//change dir
	}
	else if (didItHit == 1)
	{
		dir_y *= -1;
	}
	erase();
	leftest.move(dir_x, dir_y);
	draw();
}

///Ball::initialize function set the ball in the center, draw it and give it a random direction.
void Ball::initialize(int center, int dirX)
{
	bombActivatorLeft = bombActivatorRight = 0;
	if (!isInitialized())
	{
		leftest.set(center, 14, 'O');
	}
	draw();

	// initializing the ball dir x and dir_y.
	srand(time(NULL));//random func helper
	ballState = REGULAR;
	if (dirX == 0) {
		dir_x = rand() % 2;
		if (dir_x == 0)
			dir_x = -1;
	}
	else {
		dir_x = dirX;
	}

	dir_y = rand() % 2;
	if (dir_y == 0)
		dir_y = -1;

	//dir_x = 1;
	//dir_y = 1;
}

void Ball::handleKey(char k)
{
	if (k == kbChars[0]) // 's' key has been pressed
	{//BECOME A BOMB AND UPDATE THE COUNTER AND THE PLAYER WHO PRESSED THE KEY
		if (ballState == REGULAR && bombActivatorLeft == 0)
		{
		ballState = BECOMING_A_BOMB;
		countToChangeState = 8;
		bombActivatorLeft = LEFT * (-4);
		}
	}
	else if (k == kbChars[1])
	{
		if (ballState == REGULAR && bombActivatorRight == 0)
		{
		ballState = BECOMING_A_BOMB;
		countToChangeState = 8;
		bombActivatorRight = RIGHT*4;
		}
	}
}

int Ball::hitBoard()const
{//checking if the ball is about to cross the board limit - if it is return 1 else return -1.

	//define the ball by his borders Points
	Point rightest, upper, bottom;
	getCornersPoints(upper, rightest, bottom, dir_x);

	if ((upper.getY() + dir_y < MIN_Y) || (bottom.getY() + dir_y > MAX_Y))
		return 1;
	return -1;
}


