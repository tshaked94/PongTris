#pragma once
#include<Windows.h>
#include<iostream>
#include "utils.h"
using namespace std;
class Board {
public:
	enum{SCREEN_MAX_X=80,SCREEN_MAX_Y=25};//BOARD LIMITS

	int startMenu()const;//this function will show the start menu to the user return 1 if user chose option 1,2 if user chose option 2, 3 if user chose option 3
	int pausedMenu()const; //this function will show the paused menu to the user
	int gameLevelMenu(int side)const;//this function will show the game level menu where the user have to choose level for pc player
	void showInsturctions()const;//this function will show the instructions to the user
	void drawFrame()const;//this function will draw the game frame
};