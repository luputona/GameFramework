#pragma warning(disable : 4996)
#include "Game.h"



Game::Game(Player &player , Ball &ball, GoalPost &goalPost, Effect &effect ,Screen &screen, FPS &fps) : screen(screen),ball(ball) , goalPost(goalPost) ,effect(effect),fps(fps) , player(player)
{
}

Game::~Game()
{
	
}
void Game::Init()	//�ʱ�ȭ 
{
	gameData.oldTime = clock();
	gameData.gameState = INIT;
	gameData.nStage = 0;

	fps.Init();
	player.Init();
	ball.Init();
	goalPost.Init();
	effect.Init();
}


void Game::Update()	//������ ����
{
	clock_t CurTime = clock();
	ball.Update(CurTime);
	goalPost.Update(CurTime);
	
	effect.Update(CurTime);

	switch (gameData.gameState)
	{
	case INIT:
		if (gameData.nStage == 0)
		{
			sprintf(gameData.strMessage, "%s", "���� �� ���� �ʱ�ȭ");

			if (CurTime - gameData.oldTime > STAY_TIME)
			{
				gameData.oldTime = CurTime;
				gameData.nStage = 1;
			}
		}
		else
		{
			sprintf(gameData.strMessage, "[INIT] ���� %d �������� �ʱ�ȭ", gameData.nStage);

			if (CurTime - gameData.oldTime > STAY_TIME)
			{
				gameData.oldTime = CurTime;
				gameData.gameState = READY;
			}
		}
		break;
	case READY:
		sprintf(gameData.strMessage, "[READY]%d ��������", gameData.nStage);
		
		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			gameData.gameState = RUNNING;
			gameData.startTime = CurTime;
		}
		break;
	case RUNNING: //���� ����
		if (CurTime - gameData.startTime > LIMIT_TIME) //���� �ð�
		{
			gameData.gameState = STOP;
		}
		else
		{
			sprintf(gameData.strMessage, "[RUNNING] ���� �ð� : 10��, ���� �ð� : %d", (CurTime - gameData.startTime) / 1000);
		}
		break;
	case STOP: // ���� �̼� ����		
		gameData.gameState = (gameData.isGoal) ? SUCCESS : FAILED;
		break;
	case SUCCESS: //�̼� ����
		
		break;
	case FAILED: // �̼� ����
		break;
	case RESULT: // ���� ���
		break;
	}
}
void Game::Render()	//ȭ�� ���
{
	screen.Clear();

	screen.Print(20, 10, gameData.strMessage);

	fps.Draw();
	player.Draw();
	ball.Draw();
	goalPost.Draw();
	effect.Draw();
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
		if (player.GetPosition().x < 1)
		{
			break;
		}
		player.SetPosition(--player.GetPosition().x, player.GetPosition().y);

		if ((player.GetPosition().x - player.GetCenterPos().x) < 0 ||
			player.GetPosition().x + ((player.GetCenterPos().x * 2 ) + 1) > GAME_MAX_WIDTH)
		{
			player.SetPosition(--player.GetPosition().x, player.GetPosition().y);
		}		


		break;
	case 'l'://��
		if (player.GetPosition().x >= GAME_MAX_WIDTH -1)
		{
			break;
		}
		player.SetPosition(++player.GetPosition().x, player.GetPosition().y);

		if (player.GetPosition().x + ((player.GetCenterPos().x * 2) + 1) > GAME_MAX_WIDTH ||
			(player.GetPosition().x - player.GetPosition().x) < 0)
		{
			player.SetPosition(++player.GetPosition().x, player.GetPosition().y);
		}
		break; 
	case 'k'://�߻�
		if (ball.GetIsReady() == true)
		{
			ball.SetPosition(player.GetPosition().x, player.GetPosition().y - 1);
			ball.SetOldTime(clock());
			ball.SetIsReady(false);
		}
		break;
	case 't': //�׽�Ʈ
		if (effect.GetIsGoal() == false)
		{
			effect.SetIsGoal(true);
			effect.SetStartTime(clock());
		}
		break;

	
	}

}