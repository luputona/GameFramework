#pragma once
#include<ctime>
#include"Screen.h"
#include"FPS.h"
#include"Ball.h"
#include"GoalPost.h"
#include"Player.h"
#include"Effect.h"
#include<conio.h>

#define MSG_MAX 100
#define STAY_TIME 3000
#define LIMIT_TIME 10000 //10초

enum GAME_STATE
{
	INIT,
	READY,
	RUNNING,
	STOP,
	SUCCESS,
	FAILED,
	RESULT
};

struct GameData
{
	bool isGoal;
	int nStage;
	clock_t startTime;
	clock_t oldTime;
	GAME_STATE gameState;
	char strMessage[MSG_MAX];
};

class Game
{
public:
	Game(Player &player,Ball &ball, GoalPost &goalPost ,Effect &effect,  Screen &screen, FPS &fps);
	~Game();
public:
	void Init();	//초기화 
	void Update();	//데이터 갱신
	void Render();	//화면 출력
	void Release();	//해제	
	void WaitRender(clock_t oldTime);	//화면 출력 지연
	int GetKeyEvent();					// 키 이벤트
	void KeyProcess(int key);			//키 프로그레스 
private:
	Screen &screen;
	FPS &fps;
	Player &player;
	Ball &ball;
	GoalPost &goalPost;
	Effect &effect;
	GameData gameData;
};

