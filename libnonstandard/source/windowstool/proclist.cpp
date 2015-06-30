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
// ��l��
bool C_ProcList::Initialize()
{
	m_Process.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ���o�Ҧ��B�z�{�Ǫ��ַ�

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	PROCESSENTRY32 sProcess;

	ZeroMemory(&sProcess, sizeof(sProcess));
	sProcess.dwSize = sizeof(sProcess);

	// ���o�Ĥ@�ӳB�z�{�Ǹ�T
	if(Process32First(static_cast<HANDLE>(ccSnap), &sProcess) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Process32First failed"));

	// �̧Ǩ��o�B�z�{�Ǹ�T
	do
	{
		m_Process.push_back(S_Process(sProcess));
	} while(Process32Next(static_cast<HANDLE>(ccSnap), &sProcess) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// ���o�C��}�Y���N��
C_ProcList::const_iterator C_ProcList::Begin() const
{
	return m_Process.begin();
}
//-----------------------------------------------------------------------------
// ���o�C�������N��
C_ProcList::const_iterator C_ProcList::End() const
{
	return m_Process.end();
}
//-----------------------------------------------------------------------------
// ���o�ƶq
unsigned long C_ProcList::Size() const
{
	return m_Process.size();
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_ProcList::Empty() const
{
	return m_Process.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------