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
void Game::Init()	//초기화 
{
	//스테이지 정보 초기화
	StageInfo stageInfo[] = {
		{ 1, 1000 * 10, 3, 20, 7 , 100, 1 },			//골인해야 할 볼의 개수
		{ 3, 1000 * 10, 3, 20, 7 , 90, 1 },			//제한 시간
		{ 5, 1000 * 15 , 2, 20, 6 , 80, 1 },			//골대 길이
		{ 7, 1000 * 15, 2, 20, 6 , 70, 1 },			//골대 이동 x좌표
		{ 9, 1000 * 20, 2, 20, 5 , 60, 1 },			//골대 이동 y좌표
		{ 10, 1000 * 20, 2, 20, 5 , 50, 1 },			//골대 이동 시간 간격
		{ 13, 1000 * 30, 2, 20, 4 , 50, 1 },			//골대 이동 거리
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
	
	//게임 데이터 초기화
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

void Game::Update()	//데이터 갱신
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
			sprintf(gameData.strMessage, "%s", "게임 및 사운드 초기화");
			
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

			sprintf(gameData.strMessage, "[INIT] 게임 %d 스테이지 초기화", gameData.nStage);
			
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
		sprintf(gameData.strMessage, "[READY]%d 스테이지", gameData.nStage);
		
		if (CurTime - gameData.oldTime > STAY_TIME)
		{			
			sprintf(remainCount, "넣어야 할 총 갯수 : %d", ball.GetMinusCount());
			gameData.oldTime = CurTime;
			gameData.gameState = RUNNING;
			gameData.startTime = CurTime;
		}
		break;
	case RUNNING: //게임 진행
		isClearCheck = true;				
		if (CurTime - gameData.startTime > info[gameData.nStage - 1].limitTime) //제한 시간
		{
			gameData.gameState = FAILED;
		}
		else
		{			
			sprintf(gameData.strTime, "[RUNNING] 제한 시간 : %d초", info[gameData.nStage - 1].limitTime / 1000);
			
			sprintf(gameData.strMessage,  "현재 시간 : %d",  (CurTime - gameData.startTime) / 1000);			
			//미션 성공 체크
			if (ball.GetCount() >= gameData.goalBall)
			{
				gameData.gameState = SUCCESS;
			}			
		}		
		break;
	case STOP: // 게임 미션 판정
		gameData.gameState = (gameData.isGoal) ? SUCCESS : FAILED;
		break;
	case SUCCESS: //미션 성공
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "미션 성공");
		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			gameData.gameState = INIT;
			++gameData.nStage;
		}		
		break;
	case FAILED: // 미션 실패
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "미션 실패! 계속 하시겠습니까? <y/n>");
		ball.SetCount(0);
		break;
	case RESULT: // 게임 결과
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "모든 스테이지 클리어! 계속 하시겠습니까? <y/n>");

		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			//gameData.gameState = CLEAR;
		}
		ball.SetCount(0);
		break;
	/*case CLEAR:
		isClearCheck = false;
		sprintf(gameData.strMessage, "%s", "모든 스테이지 클리어! 계속 하시겠습니까? <y/n>");
		ball.SetCount(0);
		break;*/
	}	
}
void Game::Render()	//화면 출력
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
void Game::Release()	//해제	
{
	fps.Destroy();
	delete[] info;
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
	case 'l'://우
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
	case 'k'://발사
		if (ball.GetIsReady() == true)
		{
			ball.SetPosition(player.GetPosition().x, player.GetPosition().y - 1);
			ball.SetOldTime(clock());
			ball.SetIsReady(false);
		}
		break;
	case 't': //테스트
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