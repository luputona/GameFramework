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
#define LIMIT_TIME 10000 //10��

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
	void Init();	//�ʱ�ȭ 
	void Update();	//������ ����
	void Render();	//ȭ�� ���
	void Release();	//����	
	void WaitRender(clock_t oldTime);	//ȭ�� ��� ����
	int GetKeyEvent();					// Ű �̺�Ʈ
	void KeyProcess(int key);			//Ű ���α׷��� 
private:
	Screen &screen;
	FPS &fps;
	Player &player;
	Ball &ball;
	GoalPost &goalPost;
	Effect &effect;
	GameData gameData;
};

