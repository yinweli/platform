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
// ��l��
bool C_ThreadList::Initialize(IN unsigned long ulProcessID)
{
	m_Thread.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // ���o�B�z�{�Ǥ���������ַ�

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	THREADENTRY32 sThread;

	ZeroMemory(&sThread, sizeof(sThread));
	sThread.dwSize = sizeof(sThread);

	// ���o�Ĥ@�Ӱ�����C���T
	if(Thread32First(static_cast<HANDLE>(ccSnap), &sThread) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Thread32First failed"));

	// �̧Ǩ��o������C���T
	do
	{
		// �ˬd���������T�O�_�ݩ��J���B�z�{��
		if(sThread.th32OwnerProcessID == ulProcessID)
			m_Thread.push_back(S_Thread(sThread));
	} while(Thread32Next(static_cast<HANDLE>(ccSnap), &sThread) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// ���o�C��}�Y���N��
C_ThreadList::const_iterator C_ThreadList::Begin() const
{
	return m_Thread.begin();
}
//-----------------------------------------------------------------------------
// ���o�C�������N��
C_ThreadList::const_iterator C_ThreadList::End() const
{
	return m_Thread.end();
}
//-----------------------------------------------------------------------------
// ���o�ƶq
unsigned long C_ThreadList::Size() const
{
	return m_Thread.size();
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_ThreadList::Empty() const
{
	return m_Thread.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------