#pragma once
#pragma warning(disable : 4996)
#include "Ball.h"



Ball::Ball(Player &player, GoalPost &goalPost , Screen &screen) : player(player) ,goalPost(goalPost) ,screen(screen)
{
}


Ball::~Ball()
{

}
void Ball::Init()
{
	//볼 초기화
	SetIsReady(true);
	SetPosition(player.GetPosition().x , player.GetPosition().y - 1);
	SetMoveTime(50);
	SetCount(0);
}
void Ball::Draw()
{
	screen.Print(GetPosition().x , GetPosition().y,"◎");

	char str[100] = { 0, };

	sprintf(str, "골인 수 : %d", GetCount());
	screen.Print(0, 0, str);
}
void Ball::Reset()
{
	SetIsReady(true);
	SetPosition(player.GetPosition().x, player.GetPosition().y - 1);
}
void Ball::Update(clock_t CurTime)
{
	//공의 이동 처리

	int nLen = goalPost.GetLength() * 2 + 1;
	//볼이 발사 상태일 경우
	if (GetIsReady() == false)
	{
		if ((CurTime - GetOldTime()) > GetMoveTime())
		{
			if (GetPosition().y > 0)
			{
				SetPosition(GetPosition().x, --GetPosition().y);
				SetOldTime(CurTime);				
			}
			else
			{
				Reset();
			}
		}
	}

	//대기 상태일 경우 
	if (GetIsReady() == true)
	{
		SetPosition(player.GetPosition().x , player.GetPosition().y - 1);
	}

	//볼의 충돌 처리

	//골대 라인 충돌
	if (GetPosition().x >= goalPost.GetLineX(0) &&
		GetPosition().x + 1 <= goalPost.GetLineX(nLen - 1))
	{
		//골대 라인을 넘어가면 
		if (GetPosition().y <= goalPost.GetPosition().y)
		{ 
			Reset();
			SetCount(GetCount() + 1);
		}
	}

	//골대 충ㅇ돌
	if (//왼쪽 골대
		(GetPosition().x >= goalPost.GetLineX(0) - 2  && GetPosition().x <= goalPost.GetLineX(0) - 1 ) ||
		(GetPosition().x + 1 >= goalPost.GetLineX(0) - 2 && GetPosition().x + 1 <= goalPost.GetLineX(0) - 1 ) ||
		//오른쪽 골대
		(GetPosition().x  >= goalPost.GetLineX(nLen - 1) + 2 &&	GetPosition().x <= goalPost.GetLineX(nLen - 1) + 3) ||
		GetPosition().x + 1 >= goalPost.GetLineX(nLen - 1) + 2 && GetPosition().x + 1 <= goalPost.GetLineX(nLen - 1) + 3)
		
	{
		if (GetPosition().y <= goalPost.GetPosition().y)
		{
			Reset();
			//득점 처리
			
		}
	}
}
void Ball::SetIsReady(bool ready)
{
	ballData.isReady = ready;
}
void Ball::SetPosition(int x, int y)
{
	ballData.pos.x = x;
	ballData.pos.y = y;
}
void Ball::SetMoveTime(clock_t time)
{
	ballData.moveTime = time;
}
void Ball::SetOldTime(clock_t time)
{
	ballData.oldTime = time;
}

void Ball::SetCount(int count)
{
	ballData.count = count;
}

int Ball::GetCount()
{
	return ballData.count;
}

bool Ball::GetIsReady()
{
	return  ballData.isReady;
}
clock_t Ball::GetMoveTime()
{
	return ballData.moveTime;
}
clock_t Ball::GetOldTime()
{
	return ballData.oldTime;
}
Position &Ball::GetPosition()
{
	return ballData.pos;
}