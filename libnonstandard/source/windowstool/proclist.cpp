//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "proclist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
S_Process::S_Process(IN PROCESSENTRY32 &r) : ulProcessID(r.th32ProcessID), ulParentProcessID(r.th32ParentProcessID), ulThreads(r.cntThreads), szExeFile(r.szExeFile) {}
//-----------------------------------------------------------------------------
C_ProcList::C_ProcList() {}
//-----------------------------------------------------------------------------
C_ProcList::~C_ProcList() {}
//-----------------------------------------------------------------------------
// 初始化
bool C_ProcList::Initialize()
{
	m_Process.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 取得所有處理程序的快照

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	PROCESSENTRY32 sProcess;

	ZeroMemory(&sProcess, sizeof(sProcess));
	sProcess.dwSize = sizeof(sProcess);

	// 取得第一個處理程序資訊
	if(Process32First(static_cast<HANDLE>(ccSnap), &sProcess) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Process32First failed"));

	// 依序取得處理程序資訊
	do
	{
		m_Process.push_back(S_Process(sProcess));
	} while(Process32Next(static_cast<HANDLE>(ccSnap), &sProcess) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// 取得列表開頭迭代器
C_ProcList::const_iterator C_ProcList::Begin() const
{
	return m_Process.begin();
}
//-----------------------------------------------------------------------------
// 取得列表結尾迭代器
C_ProcList::const_iterator C_ProcList::End() const
{
	return m_Process.end();
}
//-----------------------------------------------------------------------------
// 取得數量
unsigned long C_ProcList::Size() const
{
	return m_Process.size();
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_ProcList::Empty() const
{
	return m_Process.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------