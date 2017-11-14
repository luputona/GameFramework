#pragma once
#include"Player.h"
#include"Screen.h"
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

class Ball
{

public:
	Ball(Player &player, GoalPost &goalPost, Screen &screen);
	~Ball();

public:
	void Init();
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

private:
	BallData ballData;
	Player &player;
	Screen &screen;
	GoalPost &goalPost;
};

