#pragma once
#include<ctime>
#include"Screen.h"
#include"FPS.h"
#include<conio.h>
#include"Player.h"

class Game
{
public:
	Game(Player &player,Screen &screen, FPS &fps);
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
};

