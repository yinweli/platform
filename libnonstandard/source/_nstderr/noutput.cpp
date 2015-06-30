//-----------------------------------------------------------------------------
#include "_nstderr.h"
#include "noutput.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_NOutput::C_NOutput()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_NOutput::~C_NOutput()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 取得錯誤輸出物件
C_NOutput &C_NOutput::Instance()
{
	static C_NOutput ccNOutput;

	return ccNOutput;
}
//-----------------------------------------------------------------------------
// 清除全部
void C_NOutput::Clear()
{
	EnterCriticalSection(&m_csCommon);

	m_Data.clear();

	LeaveCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 錯誤輸出
bool C_NOutput::Error(IN const estring &szError)
{
	EnterCriticalSection(&m_csCommon);

	m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + szError);

	if(m_Data.size() > NOUTPUT_MAX)
		m_Data.pop_front();

	LeaveCriticalSection(&m_csCommon);

	return false;
}
//-----------------------------------------------------------------------------
// 錯誤輸出
bool C_NOutput::Error(IN const C_ErrorNSTD &ccError, IN const estring &szError)
{
	EnterCriticalSection(&m_csCommon);

	m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + static_cast<estring>(ccError) + __T("\n") + szError);

	if(m_Data.size() > NOUTPUT_MAX)
		m_Data.pop_front();

	LeaveCriticalSection(&m_csCommon);

	return false;
}
//-----------------------------------------------------------------------------
// 錯誤輸出
bool C_NOutput::Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt)
{
	EnterCriticalSection(&m_csCommon);

	m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + static_cast<estring>(ccError) + __T("\n") + static_cast<estring>(ccErrorExt));

	if(m_Data.size() > NOUTPUT_MAX)
		m_Data.pop_front();

	LeaveCriticalSection(&m_csCommon);

	return false;
}
//-----------------------------------------------------------------------------
// 錯誤輸出
bool C_NOutput::Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt, IN const estring &szError)
{
	EnterCriticalSection(&m_csCommon);

	m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + static_cast<estring>(ccError) + __T("\n") + static_cast<estring>(ccErrorExt) + __T("\n") + szError);

	if(m_Data.size() > NOUTPUT_MAX)
		m_Data.pop_front();

	LeaveCriticalSection(&m_csCommon);

	return false;
}
//-----------------------------------------------------------------------------
// 取得錯誤訊息
estring C_NOutput::Get()
{
	EnterCriticalSection(&m_csCommon);

	estring szError;

	if(m_Data.empty() == false)
	{
		szError = m_Data.front();
		m_Data.pop_front();
	}//if

	LeaveCriticalSection(&m_csCommon);

	return szError;
}
//-----------------------------------------------------------------------------
// 取得是否為空
bool C_NOutput::Empty() const
{
	EnterCriticalSection(const_cast<CRITICAL_SECTION *>(&m_csCommon));

	bool bEmpty = m_Data.empty();

	LeaveCriticalSection(const_cast<CRITICAL_SECTION *>(&m_csCommon));

	return bEmpty;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------