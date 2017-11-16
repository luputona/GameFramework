#pragma warning(disable : 4996)
#include "Game.h"
#include<string>
using namespace std;

Game::Game(Player &player , Ball &ball, GoalPost &goalPost, Effect &effect ,Screen &screen, FPS &fps ) : screen(screen),ball(ball) , goalPost(goalPost) ,effect(effect),fps(fps) , player(player)
{
	
	
}


Game::~Game()
{
	
}
void Game::Init()	//�ʱ�ȭ 
{
	//�������� ���� �ʱ�ȭ
	StageInfo stageInfo[] = {
		{ 1, 1000 * 10, 3, 20, 7 , 100, 1 },			//�����ؾ� �� ���� ����
		{ 3, 1000 * 10, 3, 20, 7 , 90, 1 },			//���� �ð�
		{ 5, 1000 * 15 , 2, 20, 6 , 80, 1 },			//��� ����
		{ 7, 1000 * 15, 2, 20, 6 , 70, 1 },			//��� �̵� x��ǥ
		{ 9, 1000 * 20, 2, 20, 5 , 60, 1 },			//��� �̵� y��ǥ
		{ 10, 1000 * 20, 2, 20, 5 , 50, 1 },			//��� �̵� �ð� ����
		{ 13, 1000 * 30, 2, 20, 4 , 50, 1 },			//��� �̵� �Ÿ�
		{ 16, 1000 * 30, 2, 20, 4 , 50,1 },
		{ 18, 1000 * 30, 2, 20, 4 , 50,1 },
		{ 20, 1000 * 30, 3, 20, 5 , 50,1 }
	};
	gameData.nStage = 0;
	info = new StageInfo[MAX_STAGE];
	
	for (int i = 0; i < MAX_STAGE; i++)
	{
		info[i] = stageInfo[i];
	}
	
	//���� ������ �ʱ�ȭ
	gameData.oldTime = clock();
	gameData.gameState = INIT;	
	gameData.limitTime = info->limitTime;
	gameData.goalBall = info->nGoalBall;
	
	ball.SetMinusCount(gameData.goalBall);
	isClearCheck = false;
	
	remainCount = new char;
	//remainCount = "a ";

	nRemainCount = 0;

	fps.Init();
	player.Init();
	ball.Init(info[0]);
	goalPost.Init(info[0]);
	effect.Init();
}
void Game::SetStage(int stageNum)
{
	goalPost.Init(info[stageNum]);
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
		isClearCheck = false;
		if (gameData.nStage == 0)
		{
			sprintf(gameData.strMessage, "%s", "���� �� ���� �ʱ�ȭ");
			
			if (CurTime - gameData.oldTime > STAY_TIME)
			{
				ball.SetMinusCount(info[gameData.nStage - 1].nGoalBall);
				gameData.oldTime = CurTime;
				gameData.nStage = 1;
			}
		}
		else
		{	
			if (gameData.nStage >= MAX_STAGE)
			{
				gameData.nStage = 0;
				gameData.gameState = RESULT;				
			}

			sprintf(gameData.strMessage, "[INIT] ���� %d �������� �ʱ�ȭ", gameData.nStage);
			
			if (CurTime - gameData.oldTime > STAY_TIME)
			{			
				gameData.goalBall = info[gameData.nStage - 1].nGoalBall;
				nRemainCount = (gameData.goalBall) - ball.GetCount();
				ball.SetMinusCount(nRemainCount);

				SetStage(gameData.nStage - 1);
								
				gameData.oldTime = CurTime;
				gameData.gameState = READY;
			}			
		}		
		break;
	case READY:		
		sprintf(gameData.strMessage, "[READY]%d ��������", gameData.nStage);
		
		if (CurTime - gameData.oldTime > STAY_TIME)
		{			
			sprintf(remainCount, "�־�� �� �� ���� : %d", ball.GetMinusCount());
			gameData.oldTime = CurTime;
			gameData.gameState = RUNNING;
			gameData.startTime = CurTime;
		}
		break;
	case RUNNING: //���� ����
		isClearCheck = true;				
		if (CurTime - gameData.startTime > info[gameData.nStage - 1].limitTime) //���� �ð�
		{
			gameData.gameState = FAILED;
		}
		else
		{			
			sprintf(gameData.strTime, "[RUNNING] ���� �ð� : %d��", info[gameData.nStage - 1].limitTime / 1000);
			
			sprintf(gameData.strMessage,  "���� �ð� : %d",  (CurTime - gameData.startTime) / 1000);			
			//�̼� ���� üũ
			if (ball.GetCount() >= gameData.goalBall)
			{
				gameData.gameState = SUCCESS;
			}			
		}		
		break;
	case STOP: // ���� �̼� ����
		gameData.gameState = (gameData.isGoal) ? SUCCESS : FAILED;
		break;
	case SUCCESS: //�̼� ����
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "�̼� ����");
		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			gameData.gameState = INIT;
			++gameData.nStage;
		}		
		break;
	case FAILED: // �̼� ����
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "�̼� ����! ��� �Ͻðڽ��ϱ�? <y/n>");
		ball.SetCount(0);
		break;
	case RESULT: // ���� ���
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "��� �������� Ŭ����! ��� �Ͻðڽ��ϱ�? <y/n>");

		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			//gameData.gameState = CLEAR;
		}
		ball.SetCount(0);
		break;
	/*case CLEAR:
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "��� �������� Ŭ����! ��� �Ͻðڽ��ϱ�? <y/n>");
		ball.SetCount(0);
		break;*/
	}	
}
void Game::Render()	//ȭ�� ���
{
	screen.Clear();
	screen.Print(1, 1, remainCount);
	/*char* str = new char;
	sprintf(str, "%d", gameData.goalBall);
	screen.Print(20, 20, str);*/
		
	screen.Print(20, 9, gameData.strTime);
	screen.Print(20, 10, gameData.strMessage);

	fps.Draw();
	
	if (isClearCheck == true)
	{
		player.Draw();
		ball.Draw();
		goalPost.Draw();
	}
	
	effect.Draw();
	screen.Flipping();
}
void Game::Release()	//����	
{
	fps.Destroy();
	delete[] info;
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

		if ((player.GetPosition().x - player.GetCenterPos().x) < 0 || player.GetPosition().x + ((player.GetCenterPos().x * 2 ) + 1) > GAME_MAX_WIDTH)
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
	case 'n':
		gameData.gameState = RESULT;

		break;
	case 'y':
		gameData.gameState = INIT;
		isClearCheck = false;
		break;	
	}

}