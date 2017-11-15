#pragma once
#include "Player.h"
#include"Screen.h"

#include <ctime>

#define LINE_X_MAX 7

struct GPData
{
	Position pos;			//����� ���� ��ǥ
	int nLength;			//����� ����
	int nLineX[LINE_X_MAX];	//���� ������ ��ǥ
	int nDist;				//����� �̵��Ÿ�
	clock_t moveTime;		//����� �̵� �ð��� �����ϱ� ���� �ð� 
	clock_t oldTime;		//����� �̵� �ð��� �����ϱ� ���� �ð� 
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

