#include "Effect.h"



Effect::Effect(Screen &screen) : screen(screen)
{
}


Effect::~Effect()
{
}


void Effect::Init()
{
	SetIsGoal(false);
	//effData.StartTime = 3000;
	SetStayTime(3000); //3초
}
void Effect::Update(clock_t CurTime)
{
	if (GetIsGoal() == true)
	{
		//효과 지속 시간 체크
		if (CurTime - GetStartTime() > GetStayTime())
		{
			SetIsGoal(false);
		}
	}
}
void Effect::Draw()
{
	if (GetIsGoal() == true)
	{
		Message(8, 13);
	}
}
void Effect::Release()
{

}
void Effect::Message(int x, int y)
{
	screen.Print(x, y + 0, "☆ )) 골인 (( ★\n");
	screen.Print(x, y + 1, "＼(^^)／＼(^^)／\n");
	screen.Print(x, y + 2, "   ■      ■\n");
	screen.Print(x, y + 3, "   ┘┐   ┌└\n");
}

void Effect::FailScreen()
{
	//screen.Print();
}

void Effect::SetStartTime(clock_t time)
{
	effData.StartTime = time;
}
void Effect::SetStayTime(clock_t time)
{
	effData.StayTime = time;
}
void Effect::SetIsGoal(bool goal)
{
	effData.isGoal = goal;
}
clock_t Effect::GetStartTime()
{
	return effData.StartTime;
}
clock_t Effect::GetStayTime()
{
	return effData.StayTime;
}
bool Effect::GetIsGoal()
{
	return effData.isGoal;
}