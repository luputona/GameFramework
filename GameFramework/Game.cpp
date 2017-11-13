#pragma warning(disable : 4996)
#include "Game.h"



Game::Game(Player &player ,Screen &screen, FPS &fps) : screen(screen), fps(fps) , player(player)
{
}

Game::~Game()
{
	
}
void Game::Init()	//초기화 
{
	fps.Init();
	player.SetPosition(0, 22);
	player.SetCenterPosition(4, 0);
	player.SetPlayerString("└─●─┘");
	
	
}
void Game::Update()	//데이터 갱신
{

}
void Game::Render()	//화면 출력
{
	screen.Clear();
	fps.Draw();
	
	char str[100] = { 0, };

	int printX = player.GetPosition().x - player.GetCenterPos().x;

	if (printX < 0)
	{
		screen.Print(0, player.GetPosition().y, &(player.GetPlayerString()[printX * -1]));
	}
	else if (player.GetPosition().x + player.GetCenterPos().x > 40)
	{
		strncat(str, player.GetPlayerString(), player.GetStrLen() - ((player.GetPosition().x + player.GetCenterPos().x + 1) - 40));
		screen.Print(printX, player.GetPosition().y , str);
	}
	else
	{
		//플레이어 
		screen.Print(player.GetPosition().x, player.GetPosition().y, player.GetPlayerString());
	}

	//좌표 출력
	sprintf(str, "주인공 이동 좌표 : %d, %d", player.GetPosition().x, player.GetPosition().y);
	screen.Print(0, 3, str);

	screen.Flipping();
}
void Game::Release()	//해제	
{
	fps.Destroy();
}
void Game::WaitRender(clock_t oldTime)	//화면 출력 지연
{
	clock_t CurTime;
	while (true)
	{
		CurTime = clock();

		if (CurTime - oldTime > 33) // 1/30 초, 30FPS
		{
			break;
		}
	}
}
int Game::GetKeyEvent()					// 키 이벤트
{
	if (_kbhit())
	{
		return _getch();
	}

	return 0;
}
void Game::KeyProcess(int key)			//키 프로그레스 
{
	switch (key)
	{
	case 'j': //좌
		player.SetPosition(--player.GetPosition().x, player.GetPosition().y);
		break;
	case 'l':
		player.SetPosition(++player.GetPosition().x, player.GetPosition().y);
		break; //우
	
	}

}