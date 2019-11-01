#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <Windows.h>
#include<iostream>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include <list>

//consts and global functions declartion:
enum { HUMAN_VS_HUMAN,HUMAN_VS_PC, PC_VS_PC };// game mode chosen by the user
enum { REGULAR, BECOMING_A_BOMB, BOMB };//ball modes
enum { MAX_X = 79, MIN_X = 1, MIN_Y = 4, MAX_Y = 24 };//game's board limits
enum{UP=-1,DOWN=1,RIGHT=1,LEFT=-1};//direction
enum { NOVICE = 10, GOOD = 40, BEST = 0 };//Game Mode chosen by the user
enum{ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE}; 
BOOL gotoxy(const WORD x, const WORD y);
void ShowConsoleCursor(bool showFlag);
void gameOverMelody();
