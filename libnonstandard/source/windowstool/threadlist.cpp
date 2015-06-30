//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "threadlist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
S_Thread::S_Thread(IN THREADENTRY32 &r) : ulThreadID(r.th32ThreadID), ulProcessID(r.th32OwnerProcessID), lPriority(r.tpBasePri) {}
//-----------------------------------------------------------------------------
C_ThreadList::C_ThreadList() {}
//-----------------------------------------------------------------------------
C_ThreadList::~C_ThreadList() {}
//-----------------------------------------------------------------------------
// 初始化
bool C_ThreadList::Initialize(IN unsigned long ulProcessID)
{
	m_Thread.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // 取得處理程序中執行緒的快照

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	THREADENTRY32 sThread;

	ZeroMemory(&sThread, sizeof(sThread));
	sThread.dwSize = sizeof(sThread);

	// 取得第一個執行緒列表資訊
	if(Thread32First(static_cast<HANDLE>(ccSnap), &sThread) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Thread32First failed"));

	// 依序取得執行緒列表資訊
	do
	{
		// 檢查此執行緒資訊是否屬於輸入的處理程序
		if(sThread.th32OwnerProcessID == ulProcessID)
			m_Thread.push_back(S_Thread(sThread));
	} while(Thread32Next(static_cast<HANDLE>(ccSnap), &sThread) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// 取得列表開頭迭代器
C_ThreadList::const_iterator C_ThreadList::Begin() const
{
	return m_Thread.begin();
}
//-----------------------------------------------------------------------------
// 取得列表結尾迭代器
C_ThreadList::const_iterator C_ThreadList::End() const
{
	return m_Thread.end();
}
//-----------------------------------------------------------------------------
// 取得數量
unsigned long C_ThreadList::Size() const
{
	return m_Thread.size();
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_ThreadList::Empty() const
{
	return m_Thread.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------