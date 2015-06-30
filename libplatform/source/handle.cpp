//-----------------------------------------------------------------------------
#include "_include.h"
#include "handle.h"
//-----------------------------------------------------------------------------
C_Handle::C_Handle()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Handle::~C_Handle()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Handle::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<C_HandleKey, C_HandleInterface *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 執行定時處理
void C_Handle::Execute(IN const cstring &szServer)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer] (std::map<C_HandleKey, C_HandleInterface *>::value_type &Itor) { if(Itor.first.Server() == szServer && Itor.second && Itor.second->Check()) Itor.second->Execute(); });
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, unsigned long> C_Handle::Record(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, unsigned long> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer, &Result] (const std::map<C_HandleKey, C_HandleInterface *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = Itor.second ? Itor.second->Get() : 0; });

	return Result;
}
//-----------------------------------------------------------------------------