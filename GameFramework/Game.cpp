#pragma warning(disable : 4996)
#include "Game.h"



Game::Game(Player &player , Ball &ball, GoalPost &goalPost, Effect &effect ,Screen &screen, FPS &fps) : screen(screen),ball(ball) , goalPost(goalPost) ,effect(effect),fps(fps) , player(player)
{
}

Game::~Game()
{
	
}
void Game::Init()	//초기화 
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


void Game::Update()	//데이터 갱신
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
			sprintf(gameData.strMessage, "%s", "게임 및 사운드 초기화");

			if (CurTime - gameData.oldTime > STAY_TIME)
			{
				gameData.oldTime = CurTime;
				gameData.nStage = 1;
			}
		}
		else
		{
			sprintf(gameData.strMessage, "[INIT] 게임 %d 스테이지 초기화", gameData.nStage);

			if (CurTime - gameData.oldTime > STAY_TIME)
			{
				gameData.oldTime = CurTime;
				gameData.gameState = READY;
			}
		}
		break;
	case READY:
		sprintf(gameData.strMessage, "[READY]%d 스테이지", gameData.nStage);
		
		if (CurTime - gameData.oldTime > STAY_TIME)
		{
			gameData.oldTime = CurTime;
			gameData.gameState = RUNNING;
			gameData.startTime = CurTime;
		}
		break;
	case RUNNING: //게임 진행
		if (CurTime - gameData.startTime > LIMIT_TIME) //제한 시간
		{
			gameData.gameState = STOP;
		}
		else
		{
			sprintf(gameData.strMessage, "[RUNNING] 제한 시간 : 10초, 현재 시간 : %d", (CurTime - gameData.startTime) / 1000);
		}
		break;
	case STOP: // 게임 미션 판정		
		gameData.gameState = (gameData.isGoal) ? SUCCESS : FAILED;
		break;
	case SUCCESS: //미션 성공
		
		break;
	case FAILED: // 미션 실패
		break;
	case RESULT: // 게임 결과
		break;
	}
}
void Game::Render()	//화면 출력
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

	
	}

}