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
};

