//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XServerKernal::C_XServerKernal() : m_hIOCP(INVALID_HANDLE_VALUE), m_Socket(INVALID_SOCKET), m_ulSocketNormal(0), m_ulSocketExtra(0)
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XServerKernal::~C_XServerKernal()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XServerKernal::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = INVALID_HANDLE_VALUE;
	m_Socket = INVALID_SOCKET;
	m_sAddr = S_XAddr();
	m_ulSocketNormal = 0;
	m_ulSocketExtra = 0;
	m_ccFlowRecordRecv.Clear();
	m_ccFlowRecordSend.Clear();
	m_ccBenchmarkIOCP.Clear();
	m_ccBenchmarkProc.Clear();
}
//-----------------------------------------------------------------------------
// 定時處理
void C_XServerKernal::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordRecv.Process();
	m_ccFlowRecordSend.Process();
	m_ccBenchmarkIOCP.Process();
	m_ccBenchmarkProc.Process();
}
//-----------------------------------------------------------------------------
// 設定IOCompletionPort
void C_XServerKernal::IOCP(IN HANDLE hIOCP)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = hIOCP;
}
//-----------------------------------------------------------------------------
// 取得IOCompletionPort
HANDLE C_XServerKernal::IOCP() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_hIOCP;
}
//-----------------------------------------------------------------------------
// 設定SocketID
void C_XServerKernal::Socket(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Socket = Socket;
}
//-----------------------------------------------------------------------------
// 取得SocketID
SOCKET C_XServerKernal::Socket() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Socket;
}
//-----------------------------------------------------------------------------
// 設定位址資訊
void C_XServerKernal::Addr(IN const S_XAddr &sAddr)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_sAddr = sAddr;
}
//-----------------------------------------------------------------------------
// 取得位址資訊
S_XAddr C_XServerKernal::Addr() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_sAddr;
}
//-----------------------------------------------------------------------------
// 增加一般SocketID數量
void C_XServerKernal::SocketNormal(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulSocketNormal += ulCount;
}
//-----------------------------------------------------------------------------
// 取得一般SocketID數量
unsigned long C_XServerKernal::SocketNormal() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketNormal;
}
//-----------------------------------------------------------------------------
// 增加額外SocketID數量
void C_XServerKernal::SocketExtra(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulSocketExtra += ulCount;
}
//-----------------------------------------------------------------------------
// 取得額外SocketID數量
unsigned long C_XServerKernal::SocketExtra() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketExtra;
}
//-----------------------------------------------------------------------------
// 取得總SocketID數量
unsigned long C_XServerKernal::SocketTotal() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketNormal + m_ulSocketExtra;
}
//-----------------------------------------------------------------------------
// 紀錄接收流量
void C_XServerKernal::RecordRecv(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordRecv.Record(lValue);
}
//-----------------------------------------------------------------------------
// 取得接收流量
unsigned long C_XServerKernal::RecordRecv() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccFlowRecordRecv.ValueRecord();
}
//-----------------------------------------------------------------------------
// 紀錄傳送流量
void C_XServerKernal::RecordSend(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordSend.Record(lValue);
}
//-----------------------------------------------------------------------------
// 取得傳送流量
unsigned long C_XServerKernal::RecordSend() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccFlowRecordSend.ValueRecord();
}
//-----------------------------------------------------------------------------
// 開始記錄伺服器IOCP執行效能
void C_XServerKernal::BenchmarkIOCPStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.Start();
}
//-----------------------------------------------------------------------------
// 結束記錄伺服器IOCP執行效能
void C_XServerKernal::BenchmarkIOCPEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.End();
}
//-----------------------------------------------------------------------------
// 開始記錄伺服器處理執行效能物件
void C_XServerKernal::BenchmarkProcStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.Start();
}
//-----------------------------------------------------------------------------
// 結束記錄伺服器處理執行效能物件
void C_XServerKernal::BenchmarkProcEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.End();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP每秒執行次數
unsigned long C_XServerKernal::BenchmarkIOCPFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.FPS();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP最長執行時間
unsigned long C_XServerKernal::BenchmarkIOCPLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Longest();
}
//-----------------------------------------------------------------------------
// 取得伺服器IOCP平均執行時間
unsigned long C_XServerKernal::BenchmarkIOCPAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Average();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理每秒執行次數
unsigned long C_XServerKernal::BenchmarkProcFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.FPS();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理最長執行時間
unsigned long C_XServerKernal::BenchmarkProcLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Longest();
}
//-----------------------------------------------------------------------------
// 取得伺服器處理平均執行時間
unsigned long C_XServerKernal::BenchmarkProcAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Average();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------