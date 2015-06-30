//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_XServer::S_XServer() : ulSocketNormal(0), ulSocketExtra(0), ulThreads(0), ulConnects(0), ulNotices(0), ulOverlappeds(0), ulOverlappedAccept(0), ulOverlappedRecv(0), ulOverlappedSend(0), ulUnits(0), ulUnitRunnings(0), ulUnitSuspends(0), ulRecvBytesPerSecond(0), ulSendBytesPerSecond(0), ulBenchmarkIOCPFPS(0), ulBenchmarkIOCPLongest(0), ulBenchmarkIOCPAverage(0), ulBenchmarkProcFPS(0), ulBenchmarkProcLongest(0), ulBenchmarkProcAverage(0) {}
//-----------------------------------------------------------------------------
C_XServer::C_XServer()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XServer::~C_XServer()
{
	Stop();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 啟動伺服器
bool C_XServer::Start(IN const C_IPData &ccIPData)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccAPI.Initialize() == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("initialize api failed"));

	if(m_ccKernal.IOCP() != INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already start"));

	if(m_ccKernal.Socket() != INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already start"));

	if(m_ccThreadMgr.Size() > 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("thread running"));

	HANDLE hIOCP;
	SOCKET Socket;
	S_XAddr sAddr;

	// 建立位址結構
	if(m_ccAPI.GetHostAddrInfo(ccIPData, sAddr) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create address failed"));

	// 建立SocketID
	if(m_ccAPI.CreateSocket(sAddr, Socket) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create socket failed"));

	// 綁定SocketID
	if(m_ccAPI.BindSocket(Socket, sAddr) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("bind failed"));
	}//if

	// 監聽SocketID
	if(m_ccAPI.ListenSocket(Socket) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("listen failed"));
	}//if

	unsigned long ulThreads = m_ccAPI.WorkThreads(); // 取得工作執行緒數量

	// 建立IOCompletionPort
	if(m_ccAPI.CreateIOCompletionPort(ulThreads, hIOCP) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create iocp failed"));
	}//if

	// 設定執行緒參數
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_SERVER, reinterpret_cast<long>(this));
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Sleep)); // 這裡故意讓執行緒進入休眠, 等到最後再恢復正常模式

	// 建立伺服器IOCP執行緒
	for(unsigned long ulCount = 0; ulCount < ulThreads; ++ulCount)
	{
		if(m_ccThreadMgr.Create(XThreadServerIOCP) == false)
		{
			m_ccAPI.ReleaseSocket(Socket);
			m_ccAPI.ReleaseIOCompletionPort(hIOCP);

			return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
		}//if
	}//for

	// 建立伺服器處理執行緒
	if(m_ccThreadMgr.Create(XThreadServerProc) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccAPI.ReleaseIOCompletionPort(hIOCP);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
	}//if

	// 將SocketID與IOCP關聯起來
	if(m_ccAPI.AssociateIOCompletionPort(hIOCP, Socket, 0) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccAPI.ReleaseIOCompletionPort(hIOCP);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("associate iocp failed"));
	}//if

	m_ccKernal.Clear();
	m_ccKernal.IOCP(hIOCP);
	m_ccKernal.Socket(Socket);
	m_ccKernal.Addr(sAddr);
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Normal)); // 執行緒恢復正常模式

	return true;
}
//-----------------------------------------------------------------------------
// 停止伺服器
void C_XServer::Stop()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccThreadMgr.Shutdown(); // 關閉執行緒

	// 對全部執行緒發出信號, 使它們結束執行
	for(unsigned long ulCount = 0, ulMax = m_ccThreadMgr.Size(); ulCount < ulMax; ++ulCount)
		PostQueuedCompletionStatus(m_ccKernal.IOCP(), 0, 0, nullptr);

	// 關閉執行緒
	while(m_ccThreadMgr.Size() > 0)
		Sleep(100);

	m_ccAPI.ReleaseIOCompletionPort(m_ccKernal.IOCP());
	m_ccAPI.ReleaseSocket(m_ccKernal.Socket());
	m_ccKernal.Clear();
	m_ccListNotice.Clear();
	m_ccListOverlapped.Clear();
	m_ccListUnit.Clear();
}
//-----------------------------------------------------------------------------
// 增加一般SocketID數量
bool C_XServer::AddSocketNormal(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccThreadMgr.Size() <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	m_ccKernal.SocketNormal(ulCount);

	return true;
}
//-----------------------------------------------------------------------------
// 增加額外SocketID數量
bool C_XServer::AddSocketExtra(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccThreadMgr.Size() <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	m_ccKernal.SocketExtra(ulCount);

	return true;
}
//-----------------------------------------------------------------------------
// 關閉客戶端
bool C_XServer::Disconnect(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	if(m_ccThreadMgr.Size() <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("server stop"));

	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit)
		ccUnit->Disconnect(true);

	return true;
}
//-----------------------------------------------------------------------------
// 傳送資料到客戶端
void C_XServer::Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit)
		ccUnit->AddSend(pData, ulSize);
}
//-----------------------------------------------------------------------------
// 傳送資料到全部客戶端
void C_XServer::Send(IN const void *pData, IN unsigned long ulSize)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketProcess())
	{
		C_XUnitLock ccUnit = m_ccListUnit.Lock(Itor);

		if(ccUnit)
			ccUnit->AddSend(pData, ulSize);
	}//for
}
//-----------------------------------------------------------------------------
// 取得通知物件列表
std::vector<C_XNotice> C_XServer::Notice(IN unsigned long ulMax)
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListNotice.List(ulMax);
}
//-----------------------------------------------------------------------------
// 取得SocketID
SOCKET C_XServer::Socket() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccKernal.Socket();
}
//-----------------------------------------------------------------------------
// 取得SocketID連線位址
bool C_XServer::Address(IN SOCKET Socket, OUT C_IPData &ccIPDate) const
{
	nstring szIP;
	unsigned long ulPort;
	C_ThreadLock ccLock(&m_csCommon);
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
		return false;

	ccUnit->Address(szIP, ulPort);
	ccIPDate.Import(szIP, ulPort);

	return true;
}
//-----------------------------------------------------------------------------
// 檢查SocketID是否連線中
bool C_XServer::IsConnect(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	return ccUnit && ccUnit->Running();
}
//-----------------------------------------------------------------------------
// 取得伺服器資訊
S_XServer C_XServer::Infomation() const
{
	S_XServer sInfomation;
	C_ThreadLock ccLock(&m_csCommon);

	sInfomation.ulSocketNormal = m_ccKernal.SocketNormal();
	sInfomation.ulSocketExtra = m_ccKernal.SocketExtra();
	sInfomation.ulThreads = m_ccThreadMgr.Size();
	sInfomation.ulConnects = m_ccListUnit.Size(true);
	sInfomation.ulNotices = m_ccListNotice.Size();
	sInfomation.ulOverlappeds = m_ccListOverlapped.Size();
	sInfomation.ulOverlappedAccept = m_ccListOverlapped.Size(ENUM_XOverlapped_Accept);
	sInfomation.ulOverlappedRecv = m_ccListOverlapped.Size(ENUM_XOverlapped_Recv);
	sInfomation.ulOverlappedSend = m_ccListOverlapped.Size(ENUM_XOverlapped_Send);
	sInfomation.ulUnits = m_ccListUnit.Size();
	sInfomation.ulUnitRunnings = m_ccListUnit.Size(true);
	sInfomation.ulUnitSuspends = m_ccListUnit.Size(false);
	sInfomation.ulRecvBytesPerSecond = m_ccKernal.RecordRecv();
	sInfomation.ulSendBytesPerSecond = m_ccKernal.RecordSend();
	sInfomation.ulBenchmarkIOCPFPS = m_ccKernal.BenchmarkIOCPFPS();
	sInfomation.ulBenchmarkIOCPLongest = m_ccKernal.BenchmarkIOCPLongest();
	sInfomation.ulBenchmarkIOCPAverage = m_ccKernal.BenchmarkIOCPAverage();
	sInfomation.ulBenchmarkProcFPS = m_ccKernal.BenchmarkProcFPS();
	sInfomation.ulBenchmarkProcLongest = m_ccKernal.BenchmarkProcLongest();
	sInfomation.ulBenchmarkProcAverage = m_ccKernal.BenchmarkProcAverage();

	return sInfomation;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------