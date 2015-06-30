//-----------------------------------------------------------------------------
#include "_include.h"
#include "control.h"
//-----------------------------------------------------------------------------
C_Control::C_Control()
{
	m_ccData.SetToken(__T(">"));
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Control::~C_Control()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 定時處理
void C_Control::Process()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_ccData.Process();
}
//-----------------------------------------------------------------------------
// 設定標題字串
void C_Control::Set(IN const cstring &szTitle)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_ccData.SetTitle(szTitle);
	m_Target.insert(szTitle);
}
//-----------------------------------------------------------------------------
// 取得指令字串
cstring C_Control::Get()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_ccData.GetCommand();
}
//-----------------------------------------------------------------------------
// 檢查是否為目前標題字串
bool C_Control::Chk(IN const cstring &szTitle) const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return szTitle == m_ccData.GetTitle();
}
//-----------------------------------------------------------------------------
// 取得目標列表
std::set<cstring> C_Control::Target() const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Target;
}
//-----------------------------------------------------------------------------