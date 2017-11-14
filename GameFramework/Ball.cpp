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
	//�� �ʱ�ȭ
	SetIsReady(true);
	SetPosition(player.GetPosition().x , player.GetPosition().y - 1);
	SetMoveTime(50);
	SetCount(0);
}
void Ball::Draw()
{
	screen.Print(GetPosition().x , GetPosition().y,"��");

	char str[100] = { 0, };

	sprintf(str, "���� �� : %d", GetCount());
	screen.Print(0, 0, str);
}
void Ball::Reset()
{
	SetIsReady(true);
	SetPosition(player.GetPosition().x, player.GetPosition().y - 1);
}
void Ball::Update(clock_t CurTime)
{
	//���� �̵� ó��

	int nLen = goalPost.GetLength() * 2 + 1;
	//���� �߻� ������ ���
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

	//��� ������ ��� 
	if (GetIsReady() == true)
	{
		SetPosition(player.GetPosition().x , player.GetPosition().y - 1);
	}

	//���� �浹 ó��

	//��� ���� �浹
	if (GetPosition().x >= goalPost.GetLineX(0) &&
		GetPosition().x + 1 <= goalPost.GetLineX(nLen - 1))
	{
		//��� ������ �Ѿ�� 
		if (GetPosition().y <= goalPost.GetPosition().y)
		{ 
			Reset();
			SetCount(GetCount() + 1);
		}
	}

	//��� �椷��
	if (//���� ���
		(GetPosition().x >= goalPost.GetLineX(0) - 2  && GetPosition().x <= goalPost.GetLineX(0) - 1 ) ||
		(GetPosition().x + 1 >= goalPost.GetLineX(0) - 2 && GetPosition().x + 1 <= goalPost.GetLineX(0) - 1 ) ||
		//������ ���
		(GetPosition().x  >= goalPost.GetLineX(nLen - 1) + 2 &&	GetPosition().x <= goalPost.GetLineX(nLen - 1) + 3) ||
		GetPosition().x + 1 >= goalPost.GetLineX(nLen - 1) + 2 && GetPosition().x + 1 <= goalPost.GetLineX(nLen - 1) + 3)
		
	{
		if (GetPosition().y <= goalPost.GetPosition().y)
		{
			Reset();
			//���� ó��
			
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