//-----------------------------------------------------------------------------
#include "_include.h"
#include "output.h"
//-----------------------------------------------------------------------------
C_Output::C_Output()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Output::~C_Output()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Output::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 新增輸出
void C_Output::Add(IN const cstring &szOutput)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	if(szOutput.empty() == false)
		m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + szOutput);
}
//-----------------------------------------------------------------------------
// 取得輸出
cstring C_Output::Get()
{
	_G_();

	cstring szResult;
	C_ThreadLock ccLock(&m_csCommon);

	if(m_Data.empty() == false)
	{
		szResult = m_Data.front();
		m_Data.pop_front();
	}//if

	return szResult;
}
//-----------------------------------------------------------------------------