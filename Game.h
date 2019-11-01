#pragma once
#include "PongBoard.h"
#include "Board.h"
#include "Ball.h"
#include "KeyboardManager.h"
#include "Graveyard.h"
#include "UserPongBoard.h"
#include"PcPongBoard.h"
#include"utils.h"
class Game
{
	int gameMode;
private:
	enum{LEFT_PLAYER_DEFAULT_X=4,LEFT_PLAYER_DEFAULT_Y=12,DEFAULT_SYMBOL='#',RIGHT_PLAYER_DEFAULT_X=76,RIGHT_PLAYER_DEFAULT_Y=13 };
	enum { HIT_SCREEN_LIMITS = 200, DIDNT_HIT_ANYTHING = 100 };
	enum{REGULAR_LOSS=5, LEFT_EXPLODED,RIGHT_EXPLODED};
	enum {TETRIS_AWARD=10, LEFT_TETRIS_AWARD,RIGHT_TETRIS_AWARD};
	
	enum {GAME_OVER_LEFT=20,GAME_OVER_RIGHT=60};//if the left user reaches GAME_OVER_LEFT or right user reaches GAME_OVER_RIGHT its GAME OVER
	void initialize(PongBoard* left, PongBoard* right,KeyboardManager& KbManager,Ball& b)const;
	bool hitUserBoard(const PongBoard*  pb, Ball & ball)const;
	bool regHit(const PongBoard* pb, const Point& p, const Ball& b)const;
	bool corHit(const PongBoard* pb, const Point& p, const Ball& b)const;
	bool outOfBoard(const PongBoard*  pb, Ball& b)const;
	void setBoardInPlace(PongBoard* pb, int dirx)const;
	void setBallControl(Ball &b, int gameMode)const;
	int followBallMovement(PongBoard* leftBoard,PongBoard* rightBoard, Graveyard& graveLeft, Graveyard& graveRight, Ball& b)const;
	void draw(const PongBoard* leftBoard, const PongBoard* rightBoard,Graveyard &garve1,Graveyard &grave2, const Ball &b) const;
	bool graveManager(Graveyard& graves, PongBoard* pb)const;
	int ballIsInGraveyard(Graveyard& graves, Ball& b)const;
	void repositionTetris(PongBoard* pb)const;
	int hitADeadBoard(Graveyard& graves,Point& upper,Point& edge,Point& bottom,int dirx)const;
	void Tetris(Graveyard& graves,int index)const;
	void PcBoardMovementManager(PongBoard* left, PongBoard* right,Ball& b)const;
	bool isItGameOver(Graveyard& graves, PongBoard*  pb)const;
	void setGameLevels(PcPongBoard* leftPcBoard, PcPongBoard* rightPcBoard,Board& board)const;
	void checkBallState(Ball & b, PongBoard *leftPlayer, PongBoard *rightPlayer)const;
	bool underTaker(PongBoard* rightPlayer, PongBoard* leftPlayer, Graveyard& graveLeft, Graveyard& graveRight, Ball& b,int isItDead)const;
	void setPlayers(PongBoard** leftPlayer, PongBoard** rightPlayer, UserPongBoard* leftUserBoard, UserPongBoard* rightUserBoard, PcPongBoard* leftPcBoard, PcPongBoard* rightPcBoard)const;
	void registerListeners(UserPongBoard& leftUserBoard, UserPongBoard& rightUserBoard, KeyboardManager& KbManager, Ball& b)const
	{
		KbManager.registerKbListener(&leftUserBoard);
		KbManager.registerKbListener(&rightUserBoard);
		KbManager.registerKbListener(&b);
	}
public:
	void setGameMode(int mode) { gameMode = mode; }
	void run(Board &board);
};

