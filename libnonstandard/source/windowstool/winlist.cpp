//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "winlist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 視窗列舉回呼函式
BOOL CALLBACK _EnumWindows(HWND hWnd, LPARAM lParam)
{
	std::vector<S_Windows> *pList = reinterpret_cast<std::vector<S_Windows> *>(lParam);

	if(pList == nullptr)
		return FALSE;

	TCHAR szTemp[1024];

	GetWindowText(hWnd, szTemp, sizeof(szTemp)); // 取得視窗標題字串
	pList->push_back(S_Windows(hWnd, szTemp));

	return TRUE;
}
//-----------------------------------------------------------------------------
S_Windows::S_Windows(IN HWND h, IN const nstring &name) : hWnd(h), szName(name) {}
//-----------------------------------------------------------------------------
C_WinList::C_WinList() {}
//-----------------------------------------------------------------------------
C_WinList::~C_WinList() {}
//-----------------------------------------------------------------------------
// 初始化
bool C_WinList::Initialize()
{
	m_Windows.clear();

	return EnumWindows(_EnumWindows, (LPARAM)&m_Windows) ? true : C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("EnumWindows failed"));
}
//-----------------------------------------------------------------------------
// 取得列表開頭迭代器
C_WinList::const_iterator C_WinList::Begin() const
{
	return m_Windows.begin();
}
//-----------------------------------------------------------------------------
// 取得列表結尾迭代器
C_WinList::const_iterator C_WinList::End() const
{
	return m_Windows.end();
}
//-----------------------------------------------------------------------------
// 取得數量
unsigned long C_WinList::Size() const
{
	return m_Windows.size();
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_WinList::Empty() const
{
	return m_Windows.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------