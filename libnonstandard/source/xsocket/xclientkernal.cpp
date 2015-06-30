//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XClientKernal::C_XClientKernal() : m_hIOCP(INVALID_HANDLE_VALUE), m_bAuto(false), m_ulInterval(XSOCKET_CONNINTERVAL), m_ulConnect(0)
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XClientKernal::~C_XClientKernal()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XClientKernal::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = INVALID_HANDLE_VALUE;
	m_bAuto = false;
	m_ulInterval = XSOCKET_CONNINTERVAL;
	m_ulConnect = 0;
	m_ccRecvFlowRecord.Clear();
	m_ccSendFlowRecord.Clear();
	m_ccBenchmarkIOCP.Clear();
	m_ccBenchmarkProc.Clear();
}
//-----------------------------------------------------------------------------
// 定時處理
void C_XClientKernal::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccRecvFlowRecord.Process();
	m_ccSendFlowRecord.Process();
	m_ccBenchmarkIOCP.Process();
	m_ccBenchmarkProc.Process();
}
//-----------------------------------------------------------------------------
// 設定IOCompletionPort
void C_XClientKernal::IOCP(IN HANDLE hIOCP)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = hIOCP;
}
//-----------------------------------------------------------------------------
// 取得IOCompletionPort
HANDLE C_XClientKernal::IOCP() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_hIOCP;
}
//-----------------------------------------------------------------------------
// 設定自動連線旗標
void C_XClientKernal::Auto(IN bool bEnable)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_bAuto = bEnable;
}
//-----------------------------------------------------------------------------
// 取得自動連線旗標
bool C_XClientKernal::Auto() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_bAuto;
}
//-----------------------------------------------------------------------------
// 設定連線間隔時間
void C_XClientKernal::Interval(IN unsigned long ulInterval)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulInterval = ulInterval;
}
//-----------------------------------------------------------------------------
// 取得連線間隔時間
unsigned long C_XClientKernal::Interval() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulInterval;
}
//-----------------------------------------------------------------------------
// 檢查是否可以連線
bool C_XClientKernal::ConnectCheck()
{
	C_ThreadLock ccLock(&m_csCommon);
	unsigned long ulTime = timeGetTime();

	if(ulTime < m_ulConnect)
		return false;

	m_ulConnect = ulTime + m_ulInterval;

	return true;
}
//-----------------------------------------------------------------------------
// 紀錄接收流量
void C_XClientKernal::RecordRecv(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccRecvFlowRecord.Record(lValue);
}
//-----------------------------------------------------------------------------
// 取得接收流量
unsigned long C_XClientKernal::RecordRecv() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccRecvFlowRecord.ValueRecord();
}
//-----------------------------------------------------------------------------
// 紀錄傳送流量
void C_XClientKernal::RecordSend(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccSendFlowRecord.Record(lValue);
}
//-----------------------------------------------------------------------------
// 取得傳送流量
unsigned long C_XClientKernal::RecordSend() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccSendFlowRecord.ValueRecord();
}
//-----------------------------------------------------------------------------
// 開始記錄伺服器IOCP執行效能
void C_XClientKernal::BenchmarkIOCPStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.Start();
}
//-----------------------------------------------------------------------------
// 結束記錄伺服器IOCP執行效能
void C_XClientKernal::BenchmarkIOCPEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.End();
}
//-----------------------------------------------------------------------------
// 開始記錄伺服器處理執行效能物件
void C_XClientKernal::BenchmarkProcStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.Start();
}
//-----------------------------------------------------------------------------
// 結束記錄伺服器處理執行效能物件
void C_XClientKernal::BenchmarkProcEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.End();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP每秒執行次數
unsigned long C_XClientKernal::BenchmarkIOCPFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.FPS();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP最長執行時間
unsigned long C_XClientKernal::BenchmarkIOCPLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Longest();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP平均執行時間
unsigned long C_XClientKernal::BenchmarkIOCPAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Average();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理每秒執行次數
unsigned long C_XClientKernal::BenchmarkProcFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.FPS();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理最長執行時間
unsigned long C_XClientKernal::BenchmarkProcLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Longest();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理平均執行時間
unsigned long C_XClientKernal::BenchmarkProcAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Average();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------