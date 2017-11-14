#pragma once
#include"Screen.h"
#include<cstdio>
#include<cstring>
#include<conio.h>

struct Position
{
	int x, y;
};
struct PlayerData
{
	Position pos;
	Position center;
	char *strPlayer;
	int nLength;
};
class Player
{
public:
	Player(Screen &screen);
	~Player();

public:
	void Init();
	void Draw();
	void SetPosition(int x, int y);
	void SetCenterPosition(int x, int y);
	void SetPlayerString(char *str);
	Position &GetPosition();
	Position &GetCenterPos();
	char *SetPlayerString();
	int GetStrLen();
	char *GetPlayerString();

private:
	PlayerData playerData;
	Screen &screen;
};

