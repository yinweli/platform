//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "winlist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �����C�|�^�I�禡
BOOL CALLBACK _EnumWindows(HWND hWnd, LPARAM lParam)
{
	std::vector<S_Windows> *pList = reinterpret_cast<std::vector<S_Windows> *>(lParam);

	if(pList == nullptr)
		return FALSE;

	TCHAR szTemp[1024];

	GetWindowText(hWnd, szTemp, sizeof(szTemp)); // ���o�������D�r��
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
// ��l��
bool C_WinList::Initialize()
{
	m_Windows.clear();

	return EnumWindows(_EnumWindows, (LPARAM)&m_Windows) ? true : C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("EnumWindows failed"));
}
//-----------------------------------------------------------------------------
// ���o�C��}�Y���N��
C_WinList::const_iterator C_WinList::Begin() const
{
	return m_Windows.begin();
}
//-----------------------------------------------------------------------------
// ���o�C�������N��
C_WinList::const_iterator C_WinList::End() const
{
	return m_Windows.end();
}
//-----------------------------------------------------------------------------
// ���o�ƶq
unsigned long C_WinList::Size() const
{
	return m_Windows.size();
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_WinList::Empty() const
{
	return m_Windows.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------