#pragma warning(disable : 4996)
#include "Game.h"



Game::Game(Player &player ,Screen &screen, FPS &fps) : screen(screen), fps(fps) , player(player)
{
}

Game::~Game()
{
	
}
void Game::Init()	//�ʱ�ȭ 
{
	fps.Init();
	player.SetPosition(0, 22);
	player.SetCenterPosition(4, 0);
	player.SetPlayerString("�����ܦ���");
	
	
}
void Game::Update()	//������ ����
{

}
void Game::Render()	//ȭ�� ���
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
		//�÷��̾� 
		screen.Print(player.GetPosition().x, player.GetPosition().y, player.GetPlayerString());
	}

	//��ǥ ���
	sprintf(str, "���ΰ� �̵� ��ǥ : %d, %d", player.GetPosition().x, player.GetPosition().y);
	screen.Print(0, 3, str);

	screen.Flipping();
}
void Game::Release()	//����	
{
	fps.Destroy();
}
void Game::WaitRender(clock_t oldTime)	//ȭ�� ��� ����
{
	clock_t CurTime;
	while (true)
	{
		CurTime = clock();

		if (CurTime - oldTime > 33) // 1/30 ��, 30FPS
		{
			break;
		}
	}
}
int Game::GetKeyEvent()					// Ű �̺�Ʈ
{
	if (_kbhit())
	{
		return _getch();
	}

	return 0;
}
void Game::KeyProcess(int key)			//Ű ���α׷��� 
{
	switch (key)
	{
	case 'j': //��
		player.SetPosition(--player.GetPosition().x, player.GetPosition().y);
		break;
	case 'l':
		player.SetPosition(++player.GetPosition().x, player.GetPosition().y);
		break; //��
	
	}

}