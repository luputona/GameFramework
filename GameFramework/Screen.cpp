#include "Screen.h"

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

Screen::Screen()
{
}


Screen::~Screen()
{
}

void Screen::Init()
{
	CONSOLE_CURSOR_INFO cci;

	//화면 버퍼 2개 생성
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서를 숨김
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}
void Screen::Flipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}
void Screen::Clear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 2 * 25, Coor, &dw);
}
void Screen::Release()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);

}
void Screen::Print(int x, int y, char *str)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], str, strlen(str), &dw, NULL);

}
void Screen::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}