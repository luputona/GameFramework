#include "Player.h"
#include"Game.h"
#pragma warning(disable : 4996)


Player::Player(Screen &screen) : screen (screen)
{
}


Player::~Player()
{
}


void Player::Init()
{	
	SetPosition(4, 22);
	SetCenterPosition(4, 0);
	SetPlayerString("└─●─┘");
}
void Player::Draw()
{
	char str[100] = { 0, };

	int printX = GetPosition().x - GetCenterPos().x;

	if (printX < 0)
	{
		screen.Print(0, GetPosition().y, &(GetPlayerString()[printX * -1]));
	}
	else if (GetPosition().x + GetCenterPos().x > GAME_MAX_WIDTH)
	{
		strncat(str, GetPlayerString(), GetStrLen() - ((GetPosition().x + GetCenterPos().x + 1) - GAME_MAX_WIDTH));
		screen.Print(printX, GetPosition().y, str);
	}
	else
	{
		//플레이어 
		screen.Print(printX, GetPosition().y, GetPlayerString());
	}

	//좌표 출력
	sprintf(str, "주인공 이동 좌표 : %d, %d", GetPosition().x, GetPosition().y);
	screen.Print(0, 2, str);
}

void Player::SetPosition(int x, int y)
{
	playerData.pos.x = x;
	playerData.pos.y = y;
}

void Player::SetCenterPosition(int x, int y)
{
	playerData.center.x = x;
	playerData.center.y = y;
}
Position &Player::GetCenterPos()
{
	return playerData.center;
}
void Player::SetPlayerString(char *str)
{
	playerData.nLength = strlen(str);
	playerData.strPlayer = new char[playerData.nLength + 1];
	strcpy(playerData.strPlayer, str);
}
Position &Player::GetPosition()
{
	return playerData.pos;
}
char *Player::GetPlayerString()
{
	return playerData.strPlayer;
}
int Player::GetStrLen()
{
	return playerData.nLength;
}

