//-----------------------------------------------------------------------------
#include "consoletool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 設定視窗標題
void SetConsoleWindowTile(IN const nstring &szTitle, IN const nstring &szVer, IN const nstring &szFile)
{
	nstring szWindowTile;

	if(szTitle.empty() == false)
		szWindowTile += nsoutf(__T("{} ")) << szTitle;

	if(szVer.empty() == false)
		szWindowTile += nsoutf(__T("[Ver:{}]")) << szVer;

	if(szFile.empty() == false)
	{
		struct _stat sStat;
		struct tm sTMTime;
		TCHAR szTime[32];

		_tstat(szFile.c_str(), &sStat);
		localtime_s(&sTMTime, &sStat.st_mtime);
		_tasctime_s(szTime, _countof(szTime), &sTMTime);

		szWindowTile += nsoutf(__T("[FileTime:{}]")) << szTime;
	}//if

	szWindowTile += nsoutf(__T("[PID:{}]")) << _getpid();

	SetConsoleTitle(szWindowTile.c_str());
}
//-----------------------------------------------------------------------------
// 輸出字串到視窗
void printfex(IN const nstring &szData)
{
	DWORD dwWrittenCount = 0;

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szData.c_str(), szData.size(), &dwWrittenCount, nullptr);
}
//-----------------------------------------------------------------------------
// 輸出字串到視窗
void printfex(IN unsigned short wColor, IN const nstring &szData)
{
	DWORD dwWrittenCount = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;

	GetConsoleScreenBufferInfo(hConsole, &ScreenInfo); // 取得當前控制台參數
	SetConsoleTextAttribute(hConsole, wColor); // 設定控制台文字顏色
	WriteConsole(hConsole, szData.c_str(), szData.size(), &dwWrittenCount, nullptr); // 輸出文字
	SetConsoleTextAttribute(hConsole, ScreenInfo.wAttributes); // 把控制台文字設回原始值
}
//-----------------------------------------------------------------------------
// 按鍵, 然後結束程式
void PressAnyKey2Exit(IN const nstring &szInput)
{
	printfex(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, nsoutf(__T("{}\n")) << szInput);
	_getch();
	exit(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
// 設定游標位置
bool SetConsoleMousePos(IN short X, short Y)
{
	COORD c;

	c.X = X;
	c.Y = Y;

	return (SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c)) ? true : false;
}
//-----------------------------------------------------------------------------
// 取得游標位置
bool GetConsoleMousePos(OUT short &X, OUT short &Y)
{
	CONSOLE_SCREEN_BUFFER_INFO s;

	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &s) == false)
		return false;

	X = s.dwCursorPosition.X;
	Y = s.dwCursorPosition.Y;

	return true;
}
//-----------------------------------------------------------------------------
// 清除目前行
void ClearConsoleLine(IN short wPos)
{
	short wX, wY;

	if(GetConsoleMousePos(wX, wY) == false)
		return;

	SetConsoleMousePos(0, wY);
	printfex(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, nstring(79, __T(' ')));
	SetConsoleMousePos(wPos, wY);
}
//-----------------------------------------------------------------------------
// 代替目前行, 並且重設位置
void ReplaceConsoleLine(IN const nstring &szInput, IN short wPos)
{
	short wX, wY;

	if(GetConsoleMousePos(wX, wY) == false)
		return;

	SetConsoleMousePos(0, wY);
	printfex(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, nstring(79, __T(' ')));
	SetConsoleMousePos(0, wY);
	printfex(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, szInput);
	SetConsoleMousePos(wPos, wY);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------