#pragma once
#include"Player.h"
#include"Screen.h"
#include"Effect.h"
#include"GoalPost.h"

#include<ctime>
struct BallData
{
	bool isReady;
	Position pos;
	clock_t moveTime;
	clock_t oldTime;
	int count;
};
struct StageInfo;
class Ball
{

public:
	Ball(Player &player, GoalPost &goalPost,Effect &effect, Screen &screen);
	~Ball();

public:
	void Init(StageInfo &info);
	void Draw();
	void Reset();
	void Update(clock_t CurTime);
	void SetIsReady(bool ready);
	void SetPosition(int x, int y);
	void SetMoveTime(clock_t time);
	void SetOldTime(clock_t time);
	void SetCount(int count);
	bool GetIsReady();
	clock_t GetMoveTime();
	clock_t GetOldTime();
	Position &GetPosition();
	int GetCount();

	void SetMinusCount(int count);
	int GetMinusCount();

private:
	BallData ballData;
	Player &player;
	Screen &screen;
	GoalPost &goalPost;
	Effect &effect;
	int m_count;
	
};

