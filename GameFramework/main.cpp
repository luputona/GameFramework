#include<iostream>
#include"Screen.h"
#include"FPS.h"
#include"Game.h"

#include"Player.h"
void main()
{
	Player player;
	Screen screen;
	FPS fps(screen);
	Game game(player, screen, fps);

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