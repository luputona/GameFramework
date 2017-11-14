#pragma once
#define GAME_MAX_WIDTH 40
#include<Windows.h>

class Screen
{
public:
	Screen();
	~Screen();
public:
	void Init();		//초기화
	void Flipping();	//화면 버퍼 전환
	void Clear();		//화면 버퍼 지우기
	void Release();		//화면 버퍼 해제
	void Print(int x, int y, char *str);	//화면 출력
	void SetColor(unsigned short color);	//색상 설정
	
};

