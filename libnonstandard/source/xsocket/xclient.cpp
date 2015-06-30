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
// �ҰʫȤ��
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

	unsigned long ulThreads = m_ccAPI.WorkThreads(); // ���o�u�@������ƶq

	// �إ�IOCompletionPort
	if(m_ccAPI.CreateIOCompletionPort(ulThreads, hIOCP) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create iocp failed"));

	// �]�w������Ѽ�
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_CLIENT, reinterpret_cast<long>(this));
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Sleep)); // �o�̬G�N��������i�J��v, ����̫�A��_���`�Ҧ�

	// �إ߫Ȥ��IOCP�����
	for(unsigned long ulCount = 0; ulCount < ulThreads; ++ulCount)
	{
		if(m_ccThreadMgr.Create(XThreadClientIOCP) == false)
		{
			m_ccAPI.ReleaseIOCompletionPort(hIOCP);

			return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
		}//if
	}//for

	// �إ߫Ȥ�ݳB�z�����
	if(m_ccThreadMgr.Create(XThreadClientProc) == false)
	{
		m_ccAPI.ReleaseIOCompletionPort(hIOCP);

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create thread failed"));
	}//if

	m_ccKernal.IOCP(hIOCP);
	m_ccKernal.Interval(ulInterval);
	m_ccKernal.Auto(bAuto);
	m_ccThreadMgr.SetParam(XSOCKET_TPARAM_THREAD, static_cast<long>(ENUM_XThread_Normal)); // �������_���`�Ҧ�

	return true;
}
//-----------------------------------------------------------------------------
// ����Ȥ��
void C_XClient::Stop()
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

	// ���������Ȥ��
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketList())
		m_ccAPI.ReleaseSocket(Itor);

	m_ccKernal.Clear();
	m_ccListConnect.Clear();
	m_ccListNotice.Clear();
	m_ccListOverlapped.Clear();
	m_ccListUnit.Clear();
}
//-----------------------------------------------------------------------------
// �s�u����A��
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
// �����s�u
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
// �ǰe��ƨ���A��
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
// �ǰe��ƨ���A��
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
// ���o�q������C��
std::vector<C_XNotice> C_XClient::Notice(IN unsigned long ulMax)
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListNotice.List(ulMax);
}
//-----------------------------------------------------------------------------
// ���o��}����
C_IPData C_XClient::IPData(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_ccListConnect.IPData(Socket);
}
//-----------------------------------------------------------------------------
// �ˬd�O�_�P���A���s�u��
bool C_XClient::IsConnect(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	return ccUnit && ccUnit->Running();
}
//-----------------------------------------------------------------------------
// ���o�Ȥ�ݸ�T
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