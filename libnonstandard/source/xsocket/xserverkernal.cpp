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
// �M������
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
// �w�ɳB�z
void C_XServerKernal::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordRecv.Process();
	m_ccFlowRecordSend.Process();
	m_ccBenchmarkIOCP.Process();
	m_ccBenchmarkProc.Process();
}
//-----------------------------------------------------------------------------
// �]�wIOCompletionPort
void C_XServerKernal::IOCP(IN HANDLE hIOCP)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_hIOCP = hIOCP;
}
//-----------------------------------------------------------------------------
// ���oIOCompletionPort
HANDLE C_XServerKernal::IOCP() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_hIOCP;
}
//-----------------------------------------------------------------------------
// �]�wSocketID
void C_XServerKernal::Socket(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Socket = Socket;
}
//-----------------------------------------------------------------------------
// ���oSocketID
SOCKET C_XServerKernal::Socket() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Socket;
}
//-----------------------------------------------------------------------------
// �]�w��}��T
void C_XServerKernal::Addr(IN const S_XAddr &sAddr)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_sAddr = sAddr;
}
//-----------------------------------------------------------------------------
// ���o��}��T
S_XAddr C_XServerKernal::Addr() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_sAddr;
}
//-----------------------------------------------------------------------------
// �W�[�@��SocketID�ƶq
void C_XServerKernal::SocketNormal(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulSocketNormal += ulCount;
}
//-----------------------------------------------------------------------------
// ���o�@��SocketID�ƶq
unsigned long C_XServerKernal::SocketNormal() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketNormal;
}
//-----------------------------------------------------------------------------
// �W�[�B�~SocketID�ƶq
void C_XServerKernal::SocketExtra(IN unsigned long ulCount)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ulSocketExtra += ulCount;
}
//-----------------------------------------------------------------------------
// ���o�B�~SocketID�ƶq
unsigned long C_XServerKernal::SocketExtra() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketExtra;
}
//-----------------------------------------------------------------------------
// ���o�`SocketID�ƶq
unsigned long C_XServerKernal::SocketTotal() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ulSocketNormal + m_ulSocketExtra;
}
//-----------------------------------------------------------------------------
// ���������y�q
void C_XServerKernal::RecordRecv(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordRecv.Record(lValue);
}
//-----------------------------------------------------------------------------
// ���o�����y�q
unsigned long C_XServerKernal::RecordRecv() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccFlowRecordRecv.ValueRecord();
}
//-----------------------------------------------------------------------------
// �����ǰe�y�q
void C_XServerKernal::RecordSend(IN long lValue)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccFlowRecordSend.Record(lValue);
}
//-----------------------------------------------------------------------------
// ���o�ǰe�y�q
unsigned long C_XServerKernal::RecordSend() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccFlowRecordSend.ValueRecord();
}
//-----------------------------------------------------------------------------
// �}�l�O�����A��IOCP����į�
void C_XServerKernal::BenchmarkIOCPStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.Start();
}
//-----------------------------------------------------------------------------
// �����O�����A��IOCP����į�
void C_XServerKernal::BenchmarkIOCPEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkIOCP.End();
}
//-----------------------------------------------------------------------------
// �}�l�O�����A���B�z����įફ��
void C_XServerKernal::BenchmarkProcStart()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.Start();
}
//-----------------------------------------------------------------------------
// �����O�����A���B�z����įફ��
void C_XServerKernal::BenchmarkProcEnd()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccBenchmarkProc.End();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP�C����榸��
unsigned long C_XServerKernal::BenchmarkIOCPFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.FPS();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP�̪�����ɶ�
unsigned long C_XServerKernal::BenchmarkIOCPLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Longest();
}
//-----------------------------------------------------------------------------
// ���o���A��IOCP��������ɶ�
unsigned long C_XServerKernal::BenchmarkIOCPAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkIOCP.Average();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z�C����榸��
unsigned long C_XServerKernal::BenchmarkProcFPS() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.FPS();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z�̪�����ɶ�
unsigned long C_XServerKernal::BenchmarkProcLongest() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Longest();
}
//-----------------------------------------------------------------------------
// ���o���A���B�z��������ɶ�
unsigned long C_XServerKernal::BenchmarkProcAverage() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccBenchmarkProc.Average();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------