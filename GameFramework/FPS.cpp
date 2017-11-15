#pragma warning(disable : 4996)
#include "FPS.h"

FPS::FPS(Screen &screen) : screen(screen)
{
}


FPS::~FPS()
{
}
void FPS::Init()
{
	fpsData.frameCnt = 0;
	fpsData.fpsTextBuffer = new char[BUF_MAX];
	fpsData.fpsOldTime = clock();
	sprintf(fpsData.fpsTextBuffer, "FPS : %d", fpsData.frameCnt);
}
void FPS::Draw()
{
	fpsData.frameCnt++;
	fpsData.fpsCurTime = clock();

	if (fpsData.fpsCurTime - fpsData.fpsOldTime > 1000)
	{
		sprintf(fpsData.fpsTextBuffer, "FPS : %d", fpsData.frameCnt);
		fpsData.fpsOldTime = clock();
		fpsData.frameCnt = 0;
	}

	screen.Print(0, 0, fpsData.fpsTextBuffer);
}
void FPS::Destroy()
{
	delete fpsData.fpsTextBuffer;
}