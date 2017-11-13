#include "Player.h"
#pragma warning(disable : 4996)


Player::Player()
{
}


Player::~Player()
{
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
char *Player::SetPlayerString()
{
	return playerData.strPlayer;
}
int Player::GetStrLen()
{
	return playerData.nLength;
}
char *Player::GetPlayerString()
{
	return playerData.strPlayer;
}

