#pragma once
#include<ctime>
#include"Screen.h"
#include"FPS.h"
#include"Ball.h"
#include"GoalPost.h"
#include"Player.h"
#include"Effect.h"
#include<conio.h>
#include<iostream>

#define MSG_MAX 100
#define STAY_TIME 3000
#define LIMIT_TIME 10000 //10초
#define MAX_STAGE 10

enum GAME_STATE
{
	INIT,
	READY,
	RUNNING,
	STOP,
	SUCCESS,
	FAILED,
	RESULT,
	CLEAR
};
struct StageInfo
{
	int nGoalBall;		//골인해야 할 볼의 개수
	clock_t limitTime;	//제한 시간
	int nGoalPostLen;	//골대 길이
	int nGoalPostX;		//골대 이동 x좌표
	int nGoalPostY;		//골대 이동 y좌표
	clock_t moveTime;	//골대 이동 시간 간격
	int nDist;			//골대 이동 거리
};

struct GameData
{
	bool isGoal;
	int nStage;
	clock_t startTime;
	clock_t oldTime;
	GAME_STATE gameState;
	char strMessage[MSG_MAX];
	clock_t limitTime;
	int goalBall;
	char strTime[MSG_MAX];
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
	void SetStage(int stageNum);
private:
	Screen &screen;
	FPS &fps;
	Player &player;
	Ball &ball;
	GoalPost &goalPost;
	Effect &effect;
	GameData gameData;
	StageInfo *info;

	bool isClearCheck;
	char *remainCount;
	int nRemainCount;	
};

