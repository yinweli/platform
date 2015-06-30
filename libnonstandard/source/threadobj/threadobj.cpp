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
// �M���Ѽ�
void C_ThreadObj::ClrParam()
{
	if(m_pThreadMgr)
		m_pThreadMgr->ClrParam();
}
//-----------------------------------------------------------------------------
// �]�w�Ѽ�
void C_ThreadObj::SetParam(IN const nstring &szName, IN const C_Argu &ccParam)
{
	if(m_pThreadMgr)
		m_pThreadMgr->SetParam(szName, ccParam);
}
//-----------------------------------------------------------------------------
// �R���Ѽ�
void C_ThreadObj::DelParam(IN const nstring &szName)
{
	if(m_pThreadMgr)
		m_pThreadMgr->DelParam(szName);
}
//-----------------------------------------------------------------------------
// ���o�Ѽ�
bool C_ThreadObj::GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const
{
	return m_pThreadMgr ? m_pThreadMgr->GetParam(szName, ccParam) : false;
}
//-----------------------------------------------------------------------------
// �O�_�n���������
bool C_ThreadObj::IsShutdown() const
{
	return m_pThreadMgr ? m_pThreadMgr->IsShutdown(m_ulThreadID) : false;
}
//-----------------------------------------------------------------------------
// ���o������s��
unsigned long C_ThreadObj::ThreadID() const
{
	return m_ulThreadID;
}
//-----------------------------------------------------------------------------
// �s�W������s��
void C_ThreadMgr::AddThreadID(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Thread[ulThreadID] = false;
}
//-----------------------------------------------------------------------------
// �R��������s��
void C_ThreadMgr::DelThreadID(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Thread.erase(ulThreadID);
}
//-----------------------------------------------------------------------------
// ���o����X��
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
// �إ߰����
bool C_ThreadMgr::Create(IN LPFN_Thread pfThread)
{
	if(pfThread == nullptr)
		return false;

	unsigned long ulThreadID = 0;

	CloseHandle(reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, pfThread, reinterpret_cast<void *>(this), 0, reinterpret_cast<unsigned int *>(&ulThreadID)))); // �إ߰����
	Sleep(250); // ���ݤ@�U

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Thread.find(ulThreadID) == m_Thread.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ���������
void C_ThreadMgr::Shutdown()
{
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Thread.begin(), m_Thread.end(), [] (std::map<unsigned long, bool>::value_type &Itor) { Itor.second = true; });
}
//-----------------------------------------------------------------------------
// ���������
void C_ThreadMgr::Shutdown(IN unsigned long ulThreadID)
{
	C_ThreadLock ccLock(&m_csCommon);
	std::map<unsigned long, bool>::iterator Itor = m_Thread.find(ulThreadID);

	if(Itor == m_Thread.end())
		return;

	Itor->second = true;
}
//-----------------------------------------------------------------------------
// �M���Ѽ�
void C_ThreadMgr::ClrParam()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param.clear();
}
//-----------------------------------------------------------------------------
// �]�w�Ѽ�
void C_ThreadMgr::SetParam(IN const nstring &szName, IN const C_Argu &ccParam)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param[szName] = ccParam;
}
//-----------------------------------------------------------------------------
// �R���Ѽ�
void C_ThreadMgr::DelParam(IN const nstring &szName)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Param.erase(szName);
}
//-----------------------------------------------------------------------------
// ���o�Ѽ�
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
// ���o������C��
std::set<unsigned long> C_ThreadMgr::List() const
{
	std::set<unsigned long> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Thread.begin(), m_Thread.end(), [&Result] (const std::map<unsigned long, bool>::value_type &Itor) { Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// ���o������ƶq
unsigned long C_ThreadMgr::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Thread.size();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------