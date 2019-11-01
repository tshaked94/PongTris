#pragma once

#include"PongBoard.h"
#include"Board.h"
#include "KeyboardEventListener.h"


 class Ball:public KeyboardEventListener
{
private:
	int ballState = REGULAR;
	int countToChangeState = -1;
	char kbChars[3]="sk";
	int bombActivatorLeft = 0; 
	int bombActivatorRight = 0; 
	int dir_x;
	int dir_y;
	Point leftest;  //         OO
	               //leftest->OOOO
			      //		   OO

	//get the ball corners and set it to Point varibales by ref
public:
	void getCornersPoints(Point& upper, Point& rightest, Point &bottom,int dirx) const;
	Ball() :KeyboardEventListener() {}
	void move();
	void draw() const;
	void erase()const;
	void initialize(int center = 35, int dirX = 0);
	void handleKey(char k)override;
	void setBallState(int state) { ballState = state; }
	void setBombActivatorLeft(int ba) {bombActivatorLeft = ba;}
	void setBombActivatorRight(int ba) {bombActivatorRight = ba;}
	void setKbChars(const char c1, const char c2) { 
		kbChars[0] = c1;
		kbChars[1] = c2;
	}
	void setCountToChangeState(int count) { countToChangeState = count; }
	const char* getKbChars()const override {return kbChars;} 
	Point getLeftest()const { return leftest; }
	int getBallState()const { return ballState; }
	int getBombActivatorLeft() const {return bombActivatorLeft;}
	int getBombActivatorRight() const {return bombActivatorRight;}	
	int getCountToChangeState()const{ return countToChangeState; }
	int getDirX()const { return dir_x; }
	int getDirY()const { return dir_y; }
	bool isInitialized() const
	{ //if ball is in center - return true, else otherwise
		Point center = { 35,14,'O' }; //center pos of ball
		return (leftest == center);
	}
	void changeDir(bool corner) //change ball dir according to the hit type
	{
		if (corner)
		{
			dir_x *= -1;
			dir_y *= -1;
		}
		else
			dir_x *= -1;
	}
	int hitBoard()const;
};

