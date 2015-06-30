//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_XClient::S_XClient() : Socket(INVALID_SOCKET), ulThreads(0), ulConnects(0), ulNotices(0), ulOverlappeds(0), ulOverlappedConnect(0), ulOverlappedRecv(0), ulOverlappedSend(0), ulUnits(0), ulUnitRunnings(0), ulUnitSuspends(0), ulRecvBytesPerSecond(0), ulSendBytesPerSecond(0), ulBenchmarkIOCPFPS(0), ulBenchmarkIOCPLongest(0), ulBenchmarkIOCPAverage(0), ulBenchmarkProcFPS(0), ulBenchmarkProcLongest(0), ulBenchmarkProcAverage(0) {}
//-----------------------------------------------------------------------------
C_XClient::C_XClient()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XClient::~C_XClient()
{
	Stop();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 啟動客戶端
bool C_XClient::Start(IN bool bAuto, IN unsigned long ulInterval)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccAPI.Initialize() == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("initialize api failed"));

	if(m_ccKernal.IOCP() != INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already start"));

	if(m_ccThreadMgr.Size() > 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already start"));

	HANDLE hIOCP;

	unsigned long ulThreads = m_ccAPI.WorkThreads(); // 取得工作執行緒數量

	// 建立IOCompletionPort
	if(m_ccAPI.CreateIOCompletionPort(ulThreads, hIOCP) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create iocp failed"));

	// 設定執行緒參數
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_CLIENT, reinterpret_cast<long>(this));
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Sleep)); // 這裡故意讓執行緒進入休眠, 等到最後再恢復正常模式

	// 建立客戶端IOCP執行緒
	for(unsigned long ulCount = 0; ulCount < ulThreads; ++ulCount)
	{
		if(m_ccThreadMgr.Create(XThreadClientIOCP) == false)
		{
			m_ccAPI.ReleaseIOCompletionPort(hIOCP);

			return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
		}//if
	}//for

	// 建立客戶端處理執行緒
	if(m_ccThreadMgr.Create(XThreadClientProc) == false)
	{
		m_ccAPI.ReleaseIOCompletionPort(hIOCP);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
	}//if

	m_ccKernal.IOCP(hIOCP);
	m_ccKernal.Interval(ulInterval);
	m_ccKernal.Auto(bAuto);
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Normal)); // 執行緒恢復正常模式

	return true;
}
//-----------------------------------------------------------------------------
// 停止客戶端
void C_XClient::Stop()
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

	// 關閉全部客戶端
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketList())
		m_ccAPI.ReleaseSocket(Itor);

	m_ccKernal.Clear();
	m_ccListConnect.Clear();
	m_ccListNotice.Clear();
	m_ccListOverlapped.Clear();
	m_ccListUnit.Clear();
}
//-----------------------------------------------------------------------------
// 連線到伺服器
bool C_XClient::Connect(IN const C_IPData &ccIPData)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("client stop"));

	if(m_ccThreadMgr.Size() <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("client stop"));

	m_ccListConnect.Add(ccIPData);

	return true;
}
//-----------------------------------------------------------------------------
// 關閉連線
bool C_XClient::Disconnect(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("client stop"));

	if(m_ccThreadMgr.Size() <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("client stop"));

	m_ccListConnect.Del(Socket);
	m_ccAPI.ReleaseSocket(Socket);

	return true;
}
//-----------------------------------------------------------------------------
// 傳送資料到伺服器
void C_XClient::Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit)
		ccUnit->AddSend(pData, ulSize);
}
//-----------------------------------------------------------------------------
// 傳送資料到伺服器
void C_XClient::Send(IN const void *pData, IN unsigned long ulSize)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
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
std::vector<C_XNotice> C_XClient::Notice(IN unsigned long ulMax)
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListNotice.List(ulMax);
}
//-----------------------------------------------------------------------------
// 取得位址物件
C_IPData C_XClient::IPData(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListConnect.IPData(Socket);
}
//-----------------------------------------------------------------------------
// 檢查是否與伺服器連線中
bool C_XClient::IsConnect(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	return ccUnit && ccUnit->Running();
}
//-----------------------------------------------------------------------------
// 取得客戶端資訊
S_XClient C_XClient::Infomation() const
{
	S_XClient sInfomation;
	C_ThreadLock ccLock(&m_csCommon);

	sInfomation.ulConnects = m_ccListConnect.Size();
	sInfomation.ulThreads = m_ccThreadMgr.Size();
	sInfomation.ulNotices = m_ccListNotice.Size();
	sInfomation.ulOverlappeds = m_ccListOverlapped.Size();
	sInfomation.ulOverlappedConnect = m_ccListOverlapped.Size(ENUM_XOverlapped_Connect);
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