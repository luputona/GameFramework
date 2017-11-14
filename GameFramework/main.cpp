#include<iostream>
#include"Screen.h"
#include"FPS.h"
#include"Game.h"
#include"Ball.h"
#include"Effect.h"

#include"Player.h"
void main()
{	
	Screen screen;
	Player player(screen);
	FPS fps(screen);
	GoalPost goalPost(screen);
	Ball ball(player ,goalPost ,screen);
	Effect effect(screen);
	Game game(player, ball,goalPost, effect, screen, fps);

	//초기화
	screen.Init();
	game.Init();

	while(true)
	{
		int nKey = game.GetKeyEvent();

		if (nKey == 'q')
		{
			break;
		}

		game.KeyProcess(nKey);

		//데이터 갱신
		game.Update();
		//화면 출력
		game.Render();
		//대기
		game.WaitRender(clock());

	}

	game.Release();
	screen.Release();

}