#pragma once
#include"Screen.h"
#include<ctime>
#include<cstdio>

#define BUF_MAX 10

struct FPSData
{
	clock_t fpsCurTime;
	clock_t fpsOldTime;
	int frameCnt;
	char *fpsTextBuffer;
};

class FPS
{
public:
	FPS(Screen &screen);
	~FPS();
public:
	void Init();
	void Draw();
	void Destroy();

private:
	Screen &screen;
	FPSData fpsData;
};

