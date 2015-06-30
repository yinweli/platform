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
// �Ұʦ��A��
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

	// �إߦ�}���c
	if(m_ccAPI.GetHostAddrInfo(ccIPData, sAddr) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create address failed"));

	// �إ�SocketID
	if(m_ccAPI.CreateSocket(sAddr, Socket) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create socket failed"));

	// �j�wSocketID
	if(m_ccAPI.BindSocket(Socket, sAddr) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("bind failed"));
	}//if

	// ��ťSocketID
	if(m_ccAPI.ListenSocket(Socket) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("listen failed"));
	}//if

	unsigned long ulThreads = m_ccAPI.WorkThreads(); // ���o�u�@������ƶq

	// �إ�IOCompletionPort
	if(m_ccAPI.CreateIOCompletionPort(ulThreads, hIOCP) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create iocp failed"));
	}//if

	// �]�w������Ѽ�
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_SERVER, reinterpret_cast<long>(this));
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Sleep)); // �o�̬G�N��������i�J��v, ����̫�A��_���`�Ҧ�

	// �إߦ��A��IOCP�����
	for(unsigned long ulCount = 0; ulCount < ulThreads; ++ulCount)
	{
		if(m_ccThreadMgr.Create(XThreadServerIOCP) == false)
		{
			m_ccAPI.ReleaseSocket(Socket);
			m_ccAPI.ReleaseIOCompletionPort(hIOCP);

			return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
		}//if
	}//for

	// �إߦ��A���B�z�����
	if(m_ccThreadMgr.Create(XThreadServerProc) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccAPI.ReleaseIOCompletionPort(hIOCP);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
	}//if

	// �NSocketID�PIOCP���p�_��
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
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Normal)); // �������_���`�Ҧ�

	return true;
}
//-----------------------------------------------------------------------------
// ������A��
void C_XServer::Stop()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_ccThreadMgr.Shutdown(); // ���������

	// �����������o�X�H��, �ϥ��̵�������
	for(unsigned long ulCount = 0, ulMax = m_ccThreadMgr.Size(); ulCount < ulMax; ++ulCount)
		PostQueuedCompletionStatus(m_ccKernal.IOCP(), 0, 0, nullptr);

	// ���������
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
// �W�[�@��SocketID�ƶq
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
// �W�[�B�~SocketID�ƶq
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
// �����Ȥ��
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
// �ǰe��ƨ�Ȥ��
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
// �ǰe��ƨ�����Ȥ��
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
// ���o�q������C��
std::vector<C_XNotice> C_XServer::Notice(IN unsigned long ulMax)
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListNotice.List(ulMax);
}
//-----------------------------------------------------------------------------
// ���oSocketID
SOCKET C_XServer::Socket() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccKernal.Socket();
}
//-----------------------------------------------------------------------------
// ���oSocketID�s�u��}
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
// �ˬdSocketID�O�_�s�u��
bool C_XServer::IsConnect(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	return ccUnit && ccUnit->Running();
}
//-----------------------------------------------------------------------------
// ���o���A����T
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