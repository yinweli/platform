//-----------------------------------------------------------------------------
#include "consoletool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �]�w�������D
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
// ��X�r������
void printfex(IN const nstring &szData)
{
	DWORD dwWrittenCount = 0;

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szData.c_str(), szData.size(), &dwWrittenCount, nullptr);
}
//-----------------------------------------------------------------------------
// ��X�r������
void printfex(IN unsigned short wColor, IN const nstring &szData)
{
	DWORD dwWrittenCount = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;

	GetConsoleScreenBufferInfo(hConsole, &ScreenInfo); // ���o��e����x�Ѽ�
	SetConsoleTextAttribute(hConsole, wColor); // �]�w����x��r�C��
	WriteConsole(hConsole, szData.c_str(), szData.size(), &dwWrittenCount, nullptr); // ��X��r
	SetConsoleTextAttribute(hConsole, ScreenInfo.wAttributes); // �ⱱ��x��r�]�^��l��
}
//-----------------------------------------------------------------------------
// ����, �M�ᵲ���{��
void PressAnyKey2Exit(IN const nstring &szInput)
{
	printfex(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, nsoutf(__T("{}\n")) << szInput);
	_getch();
	exit(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
// �]�w��Ц�m
bool SetConsoleMousePos(IN short X, short Y)
{
	COORD c;

	c.X = X;
	c.Y = Y;

	return (SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c)) ? true : false;
}
//-----------------------------------------------------------------------------
// ���o��Ц�m
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
// �M���ثe��
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
// �N���ثe��, �åB���]��m
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