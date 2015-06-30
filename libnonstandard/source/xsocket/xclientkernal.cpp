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
// �M������
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
// �w�ɳB�z
void C_XClientKernal::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccRecvFlowRecord.Process();
	m_ccSendFlowRecord.Process();
	m_ccBenchmarkIOCP.Process();
	m_ccBenchmarkProc.Process();
}
//-----------------------------------------------------------------------------
// �]�wIOCompletionPort
void C_XClientKernal::IOCP(IN HANDLE hIOCP)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = hIOCP;
}
//-----------------------------------------------------------------------------
// ���oIOCompletionPort
HANDLE C_XClientKernal::IOCP() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_hIOCP;
}
//-----------------------------------------------------------------------------
// �]�w�۰ʳs�u�X��
void C_XClientKernal::Auto(IN bool bEnable)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_bAuto = bEnable;
}
//-----------------------------------------------------------------------------
// ���o�۰ʳs�u�X��
bool C_XClientKernal::Auto() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_bAuto;
}
//-----------------------------------------------------------------------------
// �]�w�s�u���j�ɶ�
void C_XClientKernal::Interval(IN unsigned long ulInterval)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulInterval = ulInterval;
}
//-----------------------------------------------------------------------------
// ���o�s�u���j�ɶ�
unsigned long C_XClientKernal::Interval() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulInterval;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_�i�H�s�u
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
// ���������y�q
void C_XClientKernal::RecordRecv(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccRecvFlowRecord.Record(lValue);
}
//-----------------------------------------------------------------------------
// ���o�����y�q
unsigned long C_XClientKernal::RecordRecv() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccRecvFlowRecord.ValueRecord();
}
//-----------------------------------------------------------------------------
// �����ǰe�y�q
void C_XClientKernal::RecordSend(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccSendFlowRecord.Record(lValue);
}
//-----------------------------------------------------------------------------
// ���o�ǰe�y�q
unsigned long C_XClientKernal::RecordSend() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccSendFlowRecord.ValueRecord();
}
//-----------------------------------------------------------------------------
// �}�l�O�����A��IOCP����į�
void C_XClientKernal::BenchmarkIOCPStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.Start();
}
//-----------------------------------------------------------------------------
// �����O�����A��IOCP����į�
void C_XClientKernal::BenchmarkIOCPEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.End();
}
//-----------------------------------------------------------------------------
// �}�l�O�����A���B�z����įફ��
void C_XClientKernal::BenchmarkProcStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.Start();
}
//-----------------------------------------------------------------------------
// �����O�����A���B�z����įફ��
void C_XClientKernal::BenchmarkProcEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.End();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP�C����榸��
unsigned long C_XClientKernal::BenchmarkIOCPFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.FPS();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP�̪�����ɶ�
unsigned long C_XClientKernal::BenchmarkIOCPLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Longest();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP��������ɶ�
unsigned long C_XClientKernal::BenchmarkIOCPAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Average();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z�C����榸��
unsigned long C_XClientKernal::BenchmarkProcFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.FPS();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z�̪�����ɶ�
unsigned long C_XClientKernal::BenchmarkProcLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Longest();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z��������ɶ�
unsigned long C_XClientKernal::BenchmarkProcAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Average();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------