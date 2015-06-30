//-----------------------------------------------------------------------------
#include "threadobj.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
C_ThreadObj::C_ThreadObj(IN void *param) : m_pThreadMgr(reinterpret_cast<C_ThreadMgr *>(param)), m_ulThreadID(GetCurrentThreadId())
{
	if(m_pThreadMgr)
		m_pThreadMgr->AddThreadID(m_ulThreadID);
}
//-----------------------------------------------------------------------------
C_ThreadObj::~C_ThreadObj()
{
	if(m_pThreadMgr)
		m_pThreadMgr->DelThreadID(m_ulThreadID);
}
//-----------------------------------------------------------------------------
C_ThreadObj::operator bool () const
{
	return m_pThreadMgr != nullptr;
}
//-----------------------------------------------------------------------------
// 清除參數
void C_ThreadObj::ClrParam()
{
	if(m_pThreadMgr)
		m_pThreadMgr->ClrParam();
}
//-----------------------------------------------------------------------------
// 設定參數
void C_ThreadObj::SetParam(IN const nstring &szName, IN const C_Argu &ccParam)
{
	if(m_pThreadMgr)
		m_pThreadMgr->SetParam(szName, ccParam);
}
//-----------------------------------------------------------------------------
// 刪除參數
void C_ThreadObj::DelParam(IN const nstring &szName)
{
	if(m_pThreadMgr)
		m_pThreadMgr->DelParam(szName);
}
//-----------------------------------------------------------------------------
// 取得參數
bool C_ThreadObj::GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const
{
	return m_pThreadMgr ? m_pThreadMgr->GetParam(szName, ccParam) : false;
}
//-----------------------------------------------------------------------------
// 是否要關閉執行緒
bool C_ThreadObj::IsShutdown() const
{
	return m_pThreadMgr ? m_pThreadMgr->IsShutdown(m_ulThreadID) : false;
}
//-----------------------------------------------------------------------------
// 取得執行緒編號
unsigned long C_ThreadObj::ThreadID() const
{
	return m_ulThreadID;
}
//-----------------------------------------------------------------------------
// 新增執行緒編號
void C_ThreadMgr::AddThreadID(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Thread[ulThreadID] = false;
}
//-----------------------------------------------------------------------------
// 刪除執行緒編號
void C_ThreadMgr::DelThreadID(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Thread.erase(ulThreadID);
}
//-----------------------------------------------------------------------------
// 取得執行旗標
bool C_ThreadMgr::IsShutdown(IN unsigned long ulThreadID) const
{
	C_ThreadLock ccLock(&m_csCommon);
	std::map<unsigned long, bool>::const_iterator Itor = m_Thread.find(ulThreadID);

	return Itor != m_Thread.end() ? Itor->second : false;
}
//-----------------------------------------------------------------------------
C_ThreadMgr::C_ThreadMgr()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_ThreadMgr::~C_ThreadMgr()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 建立執行緒
bool C_ThreadMgr::Create(IN LPFN_Thread pfThread)
{
	if(pfThread == nullptr)
		return false;

	unsigned long ulThreadID = 0;

	CloseHandle(reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, pfThread, reinterpret_cast<void *>(this), 0, reinterpret_cast<unsigned int *>(&ulThreadID)))); // 建立執行緒
	Sleep(250); // 等待一下

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Thread.find(ulThreadID) == m_Thread.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 關閉執行緒
void C_ThreadMgr::Shutdown()
{
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Thread.begin(), m_Thread.end(), [] (std::map<unsigned long, bool>::value_type &Itor) { Itor.second = true; });
}
//-----------------------------------------------------------------------------
// 關閉執行緒
void C_ThreadMgr::Shutdown(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);
	std::map<unsigned long, bool>::iterator Itor = m_Thread.find(ulThreadID);

	if(Itor == m_Thread.end())
		return;

	Itor->second = true;
}
//-----------------------------------------------------------------------------
// 清除參數
void C_ThreadMgr::ClrParam()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param.clear();
}
//-----------------------------------------------------------------------------
// 設定參數
void C_ThreadMgr::SetParam(IN const nstring &szName, IN const C_Argu &ccParam)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param[szName] = ccParam;
}
//-----------------------------------------------------------------------------
// 刪除參數
void C_ThreadMgr::DelParam(IN const nstring &szName)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param.erase(szName);
}
//-----------------------------------------------------------------------------
// 取得參數
bool C_ThreadMgr::GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const
{
	C_ThreadLock ccLock(&m_csCommon);
	std::map<nstring, C_Argu>::const_iterator Itor = m_Param.find(szName);

	if(Itor == m_Param.end())
		return false;

	ccParam = Itor->second;

	return true;
}
//-----------------------------------------------------------------------------
// 取得執行緒列表
std::set<unsigned long> C_ThreadMgr::List() const
{
	std::set<unsigned long> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Thread.begin(), m_Thread.end(), [&Result] (const std::map<unsigned long, bool>::value_type &Itor) { Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// 取得執行緒數量
unsigned long C_ThreadMgr::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Thread.size();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------