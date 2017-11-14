#pragma once
#include"Screen.h"
#include<ctime>
struct EffData
{
	clock_t StartTime;
	clock_t StayTime;
	bool isGoal;
};

class Effect
{
public:
	Effect(Screen &screen);
	~Effect();

public:
	void Init();
	void Update(clock_t CurTime);
	void Draw();
	void Release();
	void Message(int x, int y);
	void SetStartTime(clock_t time);
	void SetStayTime(clock_t time);
	void SetIsGoal(bool goal);
	clock_t GetStartTime();
	clock_t GetStayTime();
	bool GetIsGoal();

private:
	EffData effData;
	Screen &screen;

};

