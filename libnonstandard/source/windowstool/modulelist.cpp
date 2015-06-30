//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "modulelist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
S_Module::S_Module(IN MODULEENTRY32 &r) : ulHandle(reinterpret_cast<unsigned long>(r.hModule)), ulProcessID(r.th32ProcessID), ulAddress(reinterpret_cast<unsigned long>(r.modBaseAddr)), ulSize(r.modBaseSize), szModuleName(r.szModule), szModulePath(r.szExePath) {}
//-----------------------------------------------------------------------------
C_ModuleList::C_ModuleList() {}
//-----------------------------------------------------------------------------
C_ModuleList::~C_ModuleList() {}
//-----------------------------------------------------------------------------
// ��l��
bool C_ModuleList::Initialize(IN unsigned long ulProcessID)
{
	m_Module.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ulProcessID); // ���o�B�z�{�Ǥ��Ҳժ��ַ�

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	MODULEENTRY32 sModule;

	ZeroMemory(&sModule, sizeof(sModule));
	sModule.dwSize = sizeof(sModule);

	// ���o�Ĥ@�ӼҲզC���T
	if(Module32First(static_cast<HANDLE>(ccSnap), &sModule) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Module32First failed"));

	// �̧Ǩ��o�ҲզC���T
	do
	{
		m_Module.push_back(S_Module(sModule));
	} while(Module32Next(static_cast<HANDLE>(ccSnap), &sModule) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// ���o�C��}�Y���N��
C_ModuleList::const_iterator C_ModuleList::Begin() const
{
	return m_Module.begin();
}
//-----------------------------------------------------------------------------
// ���o�C�������N��
C_ModuleList::const_iterator C_ModuleList::End() const
{
	return m_Module.end();
}
//-----------------------------------------------------------------------------
// ���o�ƶq
unsigned long C_ModuleList::Size() const
{
	return m_Module.size();
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_ModuleList::Empty() const
{
	return m_Module.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------