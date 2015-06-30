//-----------------------------------------------------------------------------
#include "_include.h"
#include "packet.h"
//-----------------------------------------------------------------------------
C_Packet::C_Packet()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Packet::~C_Packet()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Packet::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<C_PacketKey, C_PacketInterface *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 執行封包處理
bool C_Packet::Execute(IN const cstring &szServer, IN const cstring &szName, IN SOCKET Socket, IN const cstring &szJson, OUT LibCSNStandard::Packet ^Packet)
{
	_G_();

	Packet = LibCSNStandard::Json::ToObject<LibCSNStandard::Packet ^>(szJson.tostring());

	if(Packet == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("json failed"));

	C_PacketKey ccKey(szServer, szName, Packet);
	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_PacketKey, C_PacketInterface *>::iterator Itor = m_Data.find(ccKey);

	if(Itor == m_Data.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("not found(") + ccKey.Key() + __T(")"));

	if(Itor->second == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("packet null(") + ccKey.Key() + __T(")"));

	if(Itor->second->Execute(Socket, szJson) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("packet failed(") + ccKey.Key() + __T(")"));

	return true;
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::set<C_PacketKey> C_Packet::Record(IN const cstring &szServer) const
{
	_G_();

	std::set<C_PacketKey> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer, &Result] (const std::map<C_PacketKey, C_PacketInterface *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------