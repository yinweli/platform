//-----------------------------------------------------------------------------
#include "_include.h"
#include "server.h"
//-----------------------------------------------------------------------------
// 伺服器處理執行緒
unsigned int __stdcall ThreadServer(IN void *pParam)
{
	_G_();

	// 建立執行緒物件
	C_ThreadObj ccThread(pParam);

	if(ccThread == false)
		return 0;

	C_Argu ccServerObj;

	if(ccThread.GetParam(THREAD_SERVER, ccServerObj) == false)
		return 0;

	C_ServerObj *pServerObj = reinterpret_cast<C_ServerObj *>(static_cast<int>(ccServerObj));

	if(pServerObj == nullptr)
		return 0;

	while(ccThread.IsShutdown() == false)
	{
		pServerObj->Process();
		Sleep(10); // 這裡的睡眠是為了把控制權交還給作業系統, 避免造成作業系統停止回應
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
// 顯示效能資訊
cstring C_ServerObj::Cmd_Benchmark(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, S_RecordBMData> Record = C_Platform::Instance().GetBMData().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("count") << __T("fps") << __T("total") << __T("longest") << __T("average"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, S_RecordBMData>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second.iCount << Itor.second.iFPS << Itor.second.iTotal << Itor.second.iLongest << Itor.second.iAverage); });

	return __T("benchmark infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 變更命令目標
cstring C_ServerObj::Cmd_Change(IN const C_Argv &ccArgv)
{
	_G_();

	if(ccArgv.empty())
		return __T("server not exist");

	std::set<cstring> Target = C_Platform::Instance().GetControl().Target();
	cstring szName = ccArgv.get(0);

	if(Target.find(szName) == Target.end())
		return __T("server not exist");

	C_Platform::Instance().GetControl().Set(szName);

	return __T("change to ") + szName;
}
//-----------------------------------------------------------------------------
// 顯示元件資訊
cstring C_ServerObj::Cmd_Component(IN const C_Argv &ccArgv)
{
	_G_();

	std::set<cstring> Record = C_Platform::Instance().GetComponent().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::set<cstring>::value_type &Itor) { ccTable.Add(C_Argv() << Itor); });

	return __T("component infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示資料庫資訊
cstring C_ServerObj::Cmd_Database(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, S_RecordDatabase> Record = C_Platform::Instance().GetDatabase().Record();
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("type") << __T("dbaddr") << __T("dbname"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, S_RecordDatabase>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second.szType << Itor.second.szDBAddr << Itor.second.szDBName); });

	return __T("database infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示dbf資訊
cstring C_ServerObj::Cmd_DBF(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, S_RecordDBF> Record = C_Platform::Instance().GetDBF().Record();
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("filepath") << __T("size"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, S_RecordDBF>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second.szFilePath << Itor.second.iSize); });

	return __T("dbf infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示事件資訊
cstring C_ServerObj::Cmd_Event(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, int> Record = C_Platform::Instance().GetEvent().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("count"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, int>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second); });

	return __T("event infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示定時處理資訊
cstring C_ServerObj::Cmd_Handle(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, unsigned long> Record = C_Platform::Instance().GetHandle().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("interval"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, unsigned long>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second); });

	return __T("handle infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示命令說明
cstring C_ServerObj::Cmd_Help(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, cstring> Record = C_Platform::Instance().GetCommand().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("help"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, cstring>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second); });

	return __T("command infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示命令目標
cstring C_ServerObj::Cmd_List(IN const C_Argv &ccArgv)
{
	_G_();

	std::set<cstring> Record = C_Platform::Instance().GetControl().Target();
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::set<cstring>::value_type &Itor) { ccTable.Add(C_Argv() << Itor); });

	return __T("target infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示客戶端網路資訊
cstring C_ServerObj::Cmd_NetClient(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, S_XClient> Record = C_Platform::Instance().GetNetwork().RecordClient(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("thread") << __T("connect") << __T("recv bps") << __T("send bps") << __T("iocp fps") << __T("proc fps"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, S_XClient>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second.ulThreads << Itor.second.ulConnects << Itor.second.ulRecvBytesPerSecond << Itor.second.ulSendBytesPerSecond << Itor.second.ulBenchmarkIOCPFPS << Itor.second.ulBenchmarkProcFPS); });

	return __T("network client infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示伺服器網路資訊
cstring C_ServerObj::Cmd_NetServer(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<cstring, S_XServer> Record = C_Platform::Instance().GetNetwork().RecordServer(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("name") << __T("thread") << __T("connect") << __T("recv bps") << __T("send bps") << __T("iocp fps") << __T("proc fps"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<cstring, S_XServer>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first << Itor.second.ulThreads << Itor.second.ulConnects << Itor.second.ulRecvBytesPerSecond << Itor.second.ulSendBytesPerSecond << Itor.second.ulBenchmarkIOCPFPS << Itor.second.ulBenchmarkProcFPS); });

	return __T("network server infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示封包處理資訊
cstring C_ServerObj::Cmd_Packet(IN const C_Argv &ccArgv)
{
	_G_();

	std::set<C_PacketKey> Record = C_Platform::Instance().GetPacket().Record(m_szServer);
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("server") << __T("network") << __T("packet index"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::set<C_PacketKey>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.Server() << Itor.Name() << Itor.PacketID()); });

	return __T("packet infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
// 顯示封包紀錄資訊
cstring C_ServerObj::Cmd_Record(IN const C_Argv &ccArgv)
{
	_G_();

	std::map<C_RecordKey, C_RecordData> Record = C_Platform::Instance().GetRecord().Record();
	C_FormTable ccTable;

	// 建立標頭
	ccTable.Add(C_Argv() << __T("packet") << __T("source") << __T("target") << __T("bytes") << __T("count"));
	// 建立內容
	std::for_each(Record.begin(), Record.end(), [&ccTable] (const std::map<C_RecordKey, C_RecordData>::value_type &Itor) { ccTable.Add(C_Argv() << Itor.first.Packet() << Itor.first.Source() << Itor.first.Target() << ByteString(Itor.second.Size()) << Itor.second.Count()); });

	return __T("record infomation:\n") + ccTable.ExportString();
}
//-----------------------------------------------------------------------------
C_ServerObj::C_ServerObj(IN const cstring &server) : m_szServer(server) {}
//-----------------------------------------------------------------------------
C_ServerObj::~C_ServerObj()
{
	Release();
}
//-----------------------------------------------------------------------------
// 初始化
bool C_ServerObj::Initialize(IN Setup::SServer ^Setup)
{
	_G_();

	if(Setup == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("setup null"));

	// 建立預設命令
	{
		bool bResult = true;

		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("benchmark")), __T("show benchmark"), &C_ServerObj::Cmd_Benchmark, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("ch")), __T("change command server [server name]"), &C_ServerObj::Cmd_Change, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("component")), __T("show component"), &C_ServerObj::Cmd_Component, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("database")), __T("show database"), &C_ServerObj::Cmd_Database, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("dbf")), __T("show dbf"), &C_ServerObj::Cmd_DBF, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("event")), __T("show event"), &C_ServerObj::Cmd_Event, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("handle")), __T("show handle"), &C_ServerObj::Cmd_Handle, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("help")), __T("show help"), &C_ServerObj::Cmd_Help, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("list")), __T("show server list"), &C_ServerObj::Cmd_List, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("netclient")), __T("show netclient"), &C_ServerObj::Cmd_NetClient, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("netserver")), __T("show netserver"), &C_ServerObj::Cmd_NetServer, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("packet")), __T("show packet"), &C_ServerObj::Cmd_Packet, *this);
		bResult &= C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, __T("record")), __T("show record"), &C_ServerObj::Cmd_Record, *this);

		if(bResult == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("add command failed"));
	}

	// 建立主要元件
	{
		cstring szMain = Setup->Main;

		if(C_Platform::Instance().GetComponent().Get(C_ComponentKey(m_szServer, COMPONENT_FIX + szMain)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create component failed(") + szMain + __T(")"));
	}

	// 建立伺服器網路
	{
		for(int iPos = 0, iMax = Setup->NetServer->Length; iPos < iMax; ++iPos)
		{
			cstring szName = Setup->NetServer[iPos]->Name;
			cstring szAddr = Setup->NetServer[iPos]->Addr;

			if(C_Platform::Instance().GetNetwork().AddServer(C_NetworkKey(m_szServer, szName), C_IPData(szAddr), Setup->NetServer[iPos]->Connect) == false)
				return C_NOutput::Instance().Error(ERRORNSTD, __T("add network server failed(") + szName + __T(":") + szAddr + __T(")"));
		}//for
	}

	// 建立客戶端網路
	{
		for(int iPos = 0, iMax = Setup->NetClient->Length; iPos < iMax; ++iPos)
		{
			cstring szName = Setup->NetClient[iPos]->Name;
			cstring szAddr = Setup->NetClient[iPos]->Addr;

			if(C_Platform::Instance().GetNetwork().AddClient(C_NetworkKey(m_szServer, szName), C_IPData(szAddr)) == false)
				return C_NOutput::Instance().Error(ERRORNSTD, __T("add network client failed(") + szName + __T(":") + szAddr + __T(")"));
		}//for
	}

	// 建立伺服器執行緒
	{
		// 設定執行緒參數
		m_ccThread.SetParam(THREAD_SERVER, reinterpret_cast<int>(this));

		// 建立伺服器執行緒
		if(m_ccThread.Create(ThreadServer) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create server thread failed(") + m_szServer + __T(")"));
	}

	return true;
}
//-----------------------------------------------------------------------------
// 釋放
void C_ServerObj::Release()
{
	_G_();

	m_ccThread.Shutdown();

	while(m_ccThread.Size() > 0)
		Sleep(100);
}
//-----------------------------------------------------------------------------
// 定時處理
bool C_ServerObj::Process()
{
	_G_();

	C_BMObj ccBMObj(C_Platform::Instance().GetBMData(), C_BMDataKey(m_szServer, BMDATA_SERVER));

	C_Platform::Instance().GetCommand().Execute(m_szServer, C_Platform::Instance().GetControl(), C_Platform::Instance().GetOutput());
	C_Platform::Instance().GetHandle().Execute(m_szServer);
	C_Platform::Instance().GetNetwork().Execute(m_szServer, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetPacket(), C_Platform::Instance().GetRecord());

	return true;
}
//-----------------------------------------------------------------------------
C_Server::C_Server()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Server::~C_Server()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Server::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<cstring, C_ServerObj *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 新增伺服器
bool C_Server::Add(IN Setup::SServer ^Setup)
{
	_G_();

	if(Setup == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("setup null"));

	cstring szName = Setup->Name;

	if(szName.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Data.find(szName) != m_Data.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

	C_ServerObj *pServer = nstdnew C_ServerObj(szName);

	if(pServer == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create server failed(") + szName + __T(")"));

	if(pServer->Initialize(Setup) == false)
	{
		delete pServer;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("initialize server failed(") + szName + __T(")"));
	}//if

	m_Data[szName] = pServer;

	return true;
}
//-----------------------------------------------------------------------------