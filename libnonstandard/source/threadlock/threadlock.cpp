//-----------------------------------------------------------------------------
#include "threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_ThreadLock::C_ThreadLock(IN CRITICAL_SECTION *pLock) : m_pLock(pLock)
{
	if(m_pLock)
		EnterCriticalSection(m_pLock);
}
//-----------------------------------------------------------------------------
C_ThreadLock::C_ThreadLock(IN const CRITICAL_SECTION *pLock) : m_pLock(const_cast<CRITICAL_SECTION *>(pLock))
{
	if(m_pLock)
		EnterCriticalSection(m_pLock);
}
//-----------------------------------------------------------------------------
C_ThreadLock::~C_ThreadLock()
{
	Unlock();
}
//-----------------------------------------------------------------------------
// 解開同步鎖
void C_ThreadLock::Unlock()
{
	if(m_pLock)
	{
		LeaveCriticalSection(m_pLock);
		m_pLock = nullptr;
	}//if
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------