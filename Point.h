#pragma once
using namespace std;
#include "utils.h"

BOOL gotoxy(const WORD x, const WORD y);//check

//TODO: delete ctor if not needed
class Point {
private:
	int x,y;
	char ch;
	void draw(char c)const {//drawing a char on the current x and y
		gotoxy(x, y);
		std::cout << c;
	}
public:
	Point(const int& x1, const int& y1, const char &ch1) :x(x1), y(y1), ch(ch1){};
	Point() = default;
	bool operator!=(const Point& other)const //mean points are different by their coords and not by their char
	{
		return ((x != other.x) || (y != other.y));
	}
	bool operator==(const Point& other)const //mean points are equal by their coords and not by their char
	{
		return ((x == other.x) && (y == other.y));
	}
	int getX() const{ return x; }
	int getY() const { return y; }
	void erase()const { draw(' '); }
	void move(int dirx, int diry) { x += dirx; y += diry; }
	void set(const int& x1,const int& y1,const char& ch1)
	{
		x = x1;
		y = y1;
		ch = ch1;
	}
	void draw()const {
		draw(ch);
	}
};