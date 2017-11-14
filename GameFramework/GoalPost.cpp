#include "GoalPost.h"



GoalPost::GoalPost(Screen &screen): screen(screen)
{

}


GoalPost::~GoalPost()
{
}

void GoalPost::Init()
{
	SetPosition(20, 5);	//�ʱ� ��ġ��
	SetLength(1);		//����� �⺻ ���� , 1
	SetMoveTime(100);	//100ms�ܤ����� �����̵��� ����
	SetOldTime(clock());//
	SetDistance(1);		//��밡 100ms ���� �����̴� �Ÿ�, 1 

	int nLen = GetLength() * 2 + 1;

	//bitstream
	for (int i = 0; i < nLen; i++)
	{
		//nLineX[i]�� ����� �� ������ ����(3)��ŭ ������� ������ ��ǥ�� �־��ش�.
		SetLineX(i, GetPosition().x + 2 * (i + 1));
	}
}
void GoalPost::Draw()
{
	//���� �� ����Ʈ ���
	screen.Print(GetPosition().x, GetPosition().y, "��");


	//��� ���̸�ŭ �� ���� ���
	int nLen = GetLength() * 2 + 1;

	for (int i = 0; i < nLen; i++)
	{
		screen.Print(GetLineX(i), GetPosition().y, "��");
	}

	//�� ���� ������ Į��(+2)�� ������ �� ����Ʈ ���
	screen.Print(GetLineX(nLen - 1) + 2, GetPosition().y, "��");
}
void GoalPost::Update(clock_t CurTime)
{
	//����� ������
	if (CurTime - GetOldTime() > GetMoveTime())
	{
		int nLen = GetLength() * 2 + 1;

		SetOldTime(CurTime);
		if (GetPosition().x + GetDistance() >= 0 &&
			((GetLineX(nLen - 1) + 3) + GetDistance()) <= GAME_MAX_WIDTH )
		{
			SetPosition(GetPosition().x + GetDistance(), GetPosition().y);

			for (int i =0; i < nLen; i++)
			{
				SetLineX(i, GetPosition().x + (2 * (i + 1)));
			}
		}
		else
		{
			SetDistance(GetDistance() * -1);
		}
	}
}
void GoalPost::SetPosition(int x, int y)
{
	gpData.pos.x = x;
	gpData.pos.y = y;
}
void GoalPost::SetMoveTime(clock_t time)
{
	gpData.moveTime = time;
}
void GoalPost::SetOldTime(clock_t time)
{
	gpData.oldTime = time;
}
void GoalPost::SetLength(int len)
{
	gpData.nLength = len;
}
void GoalPost::SetDistance(int dist)
{
	gpData.nDist = dist;
}
void GoalPost::SetLineX(int idx, int val)
{
	gpData.nLineX[idx] = val;
}
Position &GoalPost::GetPosition()
{
	return gpData.pos;
}
clock_t GoalPost::GetMoveTime()
{
	return gpData.moveTime;
}
clock_t GoalPost::GetOldTime()
{
	return gpData.oldTime;
}
int GoalPost::GetLength()
{
	return gpData.nLength;
}
int GoalPost::GetDistance()
{
	return gpData.nDist;
}
int GoalPost::GetLineX(int idx)
{
	return gpData.nLineX[idx];
}
