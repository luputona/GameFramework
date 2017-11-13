#pragma once
#include<cstring>
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
	Player();
	~Player();

public:
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
};

