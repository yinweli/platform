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
// �M������
void C_Output::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_Data.clear();
}
//-----------------------------------------------------------------------------
// �s�W��X
void C_Output::Add(IN const cstring &szOutput)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	if(szOutput.empty() == false)
		m_Data.push_back(__T("[") + TimeStringLocal() + __T("] ") + szOutput);
}
//-----------------------------------------------------------------------------
// ���o��X
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