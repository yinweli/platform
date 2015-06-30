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
// 初始化
bool C_ModuleList::Initialize(IN unsigned long ulProcessID)
{
	m_Module.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ulProcessID); // 取得處理程序中模組的快照

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	MODULEENTRY32 sModule;

	ZeroMemory(&sModule, sizeof(sModule));
	sModule.dwSize = sizeof(sModule);

	// 取得第一個模組列表資訊
	if(Module32First(static_cast<HANDLE>(ccSnap), &sModule) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Module32First failed"));

	// 依序取得模組列表資訊
	do
	{
		m_Module.push_back(S_Module(sModule));
	} while(Module32Next(static_cast<HANDLE>(ccSnap), &sModule) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// 取得列表開頭迭代器
C_ModuleList::const_iterator C_ModuleList::Begin() const
{
	return m_Module.begin();
}
//-----------------------------------------------------------------------------
// 取得列表結尾迭代器
C_ModuleList::const_iterator C_ModuleList::End() const
{
	return m_Module.end();
}
//-----------------------------------------------------------------------------
// 取得數量
unsigned long C_ModuleList::Size() const
{
	return m_Module.size();
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_ModuleList::Empty() const
{
	return m_Module.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------