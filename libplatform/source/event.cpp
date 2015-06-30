//-----------------------------------------------------------------------------
#include "_include.h"
#include "event.h"
//-----------------------------------------------------------------------------
C_Event::C_Event()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Event::~C_Event()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Event::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<C_EventKey, C_EventList>::value_type &Itor) { Itor.second.Clear(); });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 執行事件處理
void C_Event::Execute(IN const C_EventKey &ccKey, IN SOCKET Socket)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_EventKey, C_EventList>::iterator Itor = m_Data.find(ccKey);

	if(Itor != m_Data.end())
		Itor->second.Execute(Socket);
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, int> C_Event::Record(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, int> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer, &Result] (const std::map<C_EventKey, C_EventList>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = Itor.second.Size(); });

	return Result;
}
//-----------------------------------------------------------------------------