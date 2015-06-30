//-----------------------------------------------------------------------------
#include "_include.h"
#include "network.h"
//-----------------------------------------------------------------------------
C_Network::C_Network()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Network::~C_Network()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Network::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Client.begin(), m_Client.end(), [] (std::map<C_NetworkKey, C_XClient *>::value_type &Itor) { if(Itor.second) { Itor.second->Stop(); delete Itor.second; } });
	std::for_each(m_Server.begin(), m_Server.end(), [] (std::map<C_NetworkKey, C_XServer *>::value_type &Itor) { if(Itor.second) { Itor.second->Stop(); delete Itor.second; } });
	m_Client.clear();
	m_Server.clear();
}
//-----------------------------------------------------------------------------
// 新增客戶端網路物件
bool C_Network::AddClient(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData)
{
	_G_();

	if(ccKey == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Client.find(ccKey) != m_Client.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist in client(") + ccKey.Key() + __T(")"));

	if(m_Server.find(ccKey) != m_Server.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist in server(") + ccKey.Key() + __T(")"));

	C_XClient *pObject = nstdnew C_XClient();

	if(pObject == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create client failed(") + ccKey.Key() + __T(")"));

	if(pObject->Start(true, CONNECT_INTERVAL) == false)
	{
		delete pObject;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("start client failed(") + ccKey.Key() + __T(")"));
	}//if

	if(pObject->Connect(ccIPData) == false)
	{
		delete pObject;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("connect failed(") + ccKey.Key() + __T(")"));
	}//if

	m_Client[ccKey] = pObject;

	return true;
}
//-----------------------------------------------------------------------------
// 新增伺服器網路物件
bool C_Network::AddServer(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData, IN int iConnect)
{
	_G_();

	if(ccKey == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Client.find(ccKey) != m_Client.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist in client(") + ccKey.Key() + __T(")"));

	if(m_Server.find(ccKey) != m_Server.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist in server(") + ccKey.Key() + __T(")"));

	C_XServer *pObject = nstdnew C_XServer();

	if(pObject == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create server failed(") + ccKey.Key() + __T(")"));

	if(pObject->Start(ccIPData) == false)
	{
		delete pObject;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("start server failed(") + ccKey.Key() + __T(")"));
	}//if

	if(pObject->AddSocketNormal(iConnect) == false)
	{
		delete pObject;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("add connects normal failed(") + ccKey.Key() + __T(")"));
	}//if

	if(pObject->AddSocketExtra(CONNECT_EXTRA) == false)
	{
		delete pObject;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("add connects extra failed(") + ccKey.Key() + __T(")"));
	}//if

	m_Server[ccKey] = pObject;

	return true;
}
//-----------------------------------------------------------------------------
// 傳送封包到伺服器
void C_Network::SendToServer(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_NetworkKey, C_XClient *>::iterator Itor = m_Client.find(ccKey);

	if(Itor == m_Client.end())
		return;

	if(Itor->second == nullptr)
		return;

	S_Network sNetwork(Packet);

	Itor->second->Send(sNetwork, sNetwork);
	ccEvent.Execute(C_EventKey(ccKey.Server(), ccKey.Name(), ENUM_Event::PacketSend), INVALID_SOCKET);
	ccRecord.Record(Packet, ccKey.Key(), __T("server"), sNetwork);
}
//-----------------------------------------------------------------------------
// 傳送封包到客戶端
void C_Network::SendToClient(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_NetworkKey, C_XServer *>::iterator Itor = m_Server.find(ccKey);

	if(Itor == m_Server.end())
		return;

	if(Itor->second == nullptr)
		return;

	S_Network sNetwork(Packet);

	Itor->second->Send(sNetwork, sNetwork);
	ccEvent.Execute(C_EventKey(ccKey.Server(), ccKey.Name(), ENUM_Event::PacketSend), INVALID_SOCKET);
	ccRecord.Record(Packet, ccKey.Key(), __T("client"), sNetwork);
}
//-----------------------------------------------------------------------------
// 傳送封包到客戶端
void C_Network::SendToClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_NetworkKey, C_XServer *>::iterator Itor = m_Server.find(ccKey);

	if(Itor == m_Server.end())
		return;

	if(Itor->second == nullptr)
		return;

	S_Network sNetwork(Packet);

	Itor->second->Send(Socket, sNetwork, sNetwork);
	ccEvent.Execute(C_EventKey(ccKey.Server(), ccKey.Name(), ENUM_Event::PacketSend), Socket);
	ccRecord.Record(Packet, ccKey.Key(), __T("client"), sNetwork);
}
//-----------------------------------------------------------------------------
// 中斷客戶端連線
void C_Network::CloseClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_NetworkKey, C_XServer *>::iterator Itor = m_Server.find(ccKey);

	if(Itor == m_Server.end())
		return;

	if(Itor->second == nullptr)
		return;

	Itor->second->Disconnect(Socket);
}
//-----------------------------------------------------------------------------
// 執行定時處理
void C_Network::Execute(IN const cstring &szServer, IN C_Event &ccEvent, IN C_Packet &ccPacket, IN C_Record &ccRecord)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	// 客戶端網路處理
	for(std::map<C_NetworkKey, C_XClient *>::value_type &Itor : m_Client)
	{
		if(Itor.second == nullptr)
			continue;

		if(Itor.first.Server() != szServer)
			continue;

		for(const std::vector<C_XNotice>::value_type &ItorNotice : Itor.second->Notice(PROCESS_NOTICE))
		{
			switch(ItorNotice.Type())
			{
			case ENUM_XNotice_Connect:
				ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::Connect), ItorNotice.Socket());
				break;

			case ENUM_XNotice_Disconnect:
				ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::Disconnect), ItorNotice.Socket());
				break;

			case ENUM_XNotice_Receive:
				{
					C_XComplete ccComplete = ItorNotice.Complete(); // 取得封包內容

					if(ccComplete.Empty())
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet empty"));
						break;
					}//if

					if(ccComplete.Data() == nullptr)
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet null"));
						break;
					}//if

					ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::PacketRecv), ItorNotice.Socket());

					LibCSNStandard::Packet ^Packet = nullptr;

					if(ccPacket.Execute(Itor.first.Server(), Itor.first.Name(), ItorNotice.Socket(), ccComplete.Data(), Packet) == false)
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet failed"));
						break;
					}//if

					ccRecord.Record(Packet, __T("server"), Itor.first.Key(), ccComplete.Size());
				}
				break;

			default:
				break;
			}//switch
		}//for
	}//for

	// 伺服器網路處理
	for(std::map<C_NetworkKey, C_XServer *>::value_type &Itor : m_Server)
	{
		if(Itor.second == nullptr)
			continue;

		for(const std::vector<C_XNotice>::value_type &ItorNotice : Itor.second->Notice(PROCESS_NOTICE))
		{
			switch(ItorNotice.Type())
			{
			case ENUM_XNotice_Connect:
				ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::Connect), ItorNotice.Socket());
				break;

			case ENUM_XNotice_Disconnect:
				ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::Disconnect), ItorNotice.Socket());
				break;

			case ENUM_XNotice_Receive:
				{
					C_XComplete ccComplete = ItorNotice.Complete(); // 取得封包內容

					if(ccComplete.Empty())
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet empty"));
						break;
					}//if

					if(ccComplete.Data() == nullptr)
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet null"));
						break;
					}//if

					ccEvent.Execute(C_EventKey(Itor.first.Server(), Itor.first.Name(), ENUM_Event::PacketRecv), ItorNotice.Socket());

					LibCSNStandard::Packet ^Packet = nullptr;

					if(ccPacket.Execute(Itor.first.Server(), Itor.first.Name(), ItorNotice.Socket(), ccComplete.Data(), Packet) == false)
					{
						C_NOutput::Instance().Error(ERRORNSTD, __T("packet failed"));
						break;
					}//if

					ccRecord.Record(Packet, __T("client"), Itor.first.Key(), ccComplete.Size());
				}
				break;

			default:
				break;
			}//switch
		}//for
	}//for
}
//-----------------------------------------------------------------------------
// 檢查網路是否存在
bool C_Network::IsExist(IN const C_NetworkKey &ccKey) const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Client.find(ccKey) != m_Client.end() || m_Server.find(ccKey) != m_Server.end();
}
//-----------------------------------------------------------------------------
// 取得客戶端紀錄紀錄列表
std::map<cstring, S_XClient> C_Network::RecordClient(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, S_XClient> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Client.begin(), m_Client.end(), [&szServer, &Result] (const std::map<C_NetworkKey, C_XClient *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = Itor.second ? Itor.second->Infomation() : S_XClient(); });

	return Result;
}
//-----------------------------------------------------------------------------
// 取得伺服器紀錄紀錄列表
std::map<cstring, S_XServer> C_Network::RecordServer(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, S_XServer> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Server.begin(), m_Server.end(), [&szServer, &Result] (const std::map<C_NetworkKey, C_XServer *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = Itor.second ? Itor.second->Infomation() : S_XServer(); });

	return Result;
}
//-----------------------------------------------------------------------------