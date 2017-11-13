#pragma once
#include<Windows.h>

class Screen
{
public:
	Screen();
	~Screen();
public:
	void Init();
	void Flipping();
	void Clear();
	void Release();
	void Print(int x, int y, char *str);
	void SetColor(unsigned short color);
	
};

