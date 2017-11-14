#pragma once
#define GAME_MAX_WIDTH 40
#include<Windows.h>

class Screen
{
public:
	Screen();
	~Screen();
public:
	void Init();		//�ʱ�ȭ
	void Flipping();	//ȭ�� ���� ��ȯ
	void Clear();		//ȭ�� ���� �����
	void Release();		//ȭ�� ���� ����
	void Print(int x, int y, char *str);	//ȭ�� ���
	void SetColor(unsigned short color);	//���� ����
	
};

