#pragma once
#include "Player.h"
#include"Screen.h"

#include <ctime>

#define LINE_X_MAX 7

struct GPData
{
	Position pos;			//골대의 기준 좌표
	int nLength;			//골대의 길이
	int nLineX[LINE_X_MAX];	//골인 라인의 좌표
	int nDist;				//골대의 이동거리
	clock_t moveTime;		//골대의 이동 시간을 정의하기 위한 시간 
	clock_t oldTime;		//골대의 이동 시간을 정의하기 위한 시간 
};

struct StageInfo;

class GoalPost
{
public:
	GoalPost(Screen &screen);
	~GoalPost();
public:
	void Init(StageInfo &info);
	void Draw();
	void Update(clock_t CurTime);
	void SetPosition(int x ,int y);
	void SetMoveTime(clock_t time);
	void SetOldTime(clock_t time);
	void SetLength(int len);
	void SetDistance(int dist);
	
	void SetLineX(int idx, int val);
	Position &GetPosition();
	clock_t GetMoveTime();
	clock_t GetOldTime();
	int GetLength();
	int GetDistance();
	int GetLineX(int idx);

private:
	GPData gpData;
	Screen &screen;

};

