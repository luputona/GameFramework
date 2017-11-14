#include "GoalPost.h"



GoalPost::GoalPost(Screen &screen): screen(screen)
{

}


GoalPost::~GoalPost()
{
}

void GoalPost::Init()
{
	SetPosition(20, 5);	//초기 위치값
	SetLength(1);		//골대의 기본 길이 , 1
	SetMoveTime(100);	//100ms단ㅇ위로 움직이도록 설정
	SetOldTime(clock());//
	SetDistance(1);		//골대가 100ms 마다 움직이는 거리, 1 

	int nLen = GetLength() * 2 + 1;

	//bitstream
	for (int i = 0; i < nLen; i++)
	{
		//nLineX[i]에 계산한 골 라인의 길이(3)만큼 순서대로 라인의 좌표를 넣어준다.
		SetLineX(i, GetPosition().x + 2 * (i + 1));
	}
}
void GoalPost::Draw()
{
	//왼쪽 골 포스트 출력
	screen.Print(GetPosition().x, GetPosition().y, "□");


	//골대 길이만큼 골 라인 출력
	int nLen = GetLength() * 2 + 1;

	for (int i = 0; i < nLen; i++)
	{
		screen.Print(GetLineX(i), GetPosition().y, "─");
	}

	//골 라인 다음의 칼럼(+2)에 오른쪽 골 포스트 출력
	screen.Print(GetLineX(nLen - 1) + 2, GetPosition().y, "□");
}
void GoalPost::Update(clock_t CurTime)
{
	//골대의 움직임
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
