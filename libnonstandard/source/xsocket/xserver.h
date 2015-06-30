/**
 * @file xserver.h
 * @note ���A�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XSERVER
#define _XSERVER
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ���A��IOCP�����
 * @param pParam ������Ѽ�
 * @return �Ǧ^��
 * @ingroup xserver
 */
unsigned int __stdcall XThreadServerIOCP(IN void *pParam);
/**
 * @brief ���A���B�z�����
 * @param pParam ������Ѽ�
 * @return �Ǧ^��
 * @ingroup xserver
 */
unsigned int __stdcall XThreadServerProc(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief ���A����T���c
 * @ingroup xserver
 */
struct S_XServer
{
	unsigned long ulSocketNormal; ///< �@��SocketID�ƶq
	unsigned long ulSocketExtra; ///< �B�~SocketID�ƶq
	unsigned long ulThreads; ///< ������ƶq
	unsigned long ulConnects; ///< �s�u�ƶq
	unsigned long ulNotices; ///< �q���ƶq
	unsigned long ulOverlappeds; ///< ���|����ƶq
	unsigned long ulOverlappedAccept; ///< �����s�u���|����ƶq
	unsigned long ulOverlappedRecv; ///< �������|����ƶq
	unsigned long ulOverlappedSend; ///< �ǰe���|����ƶq
	unsigned long ulUnits; ///< �ǿ�椸�ƶq
	unsigned long ulUnitRunnings; ///< ���椤�ǿ�椸�ƶq
	unsigned long ulUnitSuspends; ///< �Ȱ����ǿ�椸�ƶq
	unsigned long ulRecvBytesPerSecond; ///< �C�����줸�ռ�
	unsigned long ulSendBytesPerSecond; ///< �C��ǰe�줸�ռ�
	unsigned long ulBenchmarkIOCPFPS; ///< IOCP�C����榸��
	unsigned long ulBenchmarkIOCPLongest; ///< IOCP�̪�����ɶ�
	unsigned long ulBenchmarkIOCPAverage; ///< IOCP��������ɶ�
	unsigned long ulBenchmarkProcFPS; ///< �B�z�C����榸��
	unsigned long ulBenchmarkProcLongest; ///< �B�z�̪�����ɶ�
	unsigned long ulBenchmarkProcAverage; ///< �B�z��������ɶ�

	S_XServer();
};
//-----------------------------------------------------------------------------
/**
 * @brief ���A���֤����O
 * @ingroup xserver
 */
class C_XServerKernal
{
private:
	//-------------------------------------
	HANDLE m_hIOCP; ///< IOCompletionPort
	SOCKET m_Socket; ///< SocketID
	S_XAddr m_sAddr; ///< ��}��T
	unsigned long m_ulSocketNormal; ///< �@��SocketID�ƶq
	unsigned long m_ulSocketExtra; ///< �B�~SocketID�ƶq
	C_FlowRecord m_ccFlowRecordRecv; ///< �����y�q��������
	C_FlowRecord m_ccFlowRecordSend; ///< �ǰe�y�q��������
	C_Benchmark m_ccBenchmarkIOCP; ///< ���A��IOCP����įફ��
	C_Benchmark m_ccBenchmarkProc; ///< ���A���B�z����įફ��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XServerKernal();
	virtual ~C_XServerKernal();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �]�wIOCompletionPort
	 * @param hIOCP IOCompletionPort
	 */
	void IOCP(IN HANDLE hIOCP);
	/**
	 * @brief ���oIOCompletionPort
	 * @return IOCompletionPort
	 */
	HANDLE IOCP() const;
	/**
	 * @brief �]�wSocketID
	 * @param Socket SocketID
	 */
	void Socket(IN SOCKET Socket);
	/**
	 * @brief ���oSocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief �]�w��}��T
	 * @param sAddr ��}��T
	 */
	void Addr(IN const S_XAddr &sAddr);
	/**
	 * @brief ���o��}��T
	 * @return ��}��T
	 */
	S_XAddr Addr() const;
	/**
	 * @brief �W�[�@��SocketID�ƶq
	 * @param ulCount �ƶq
	 */
	void SocketNormal(IN unsigned long ulCount);
	/**
	 * @brief ���o�@��SocketID�ƶq
	 * @return �@��SocketID�ƶq
	 */
	unsigned long SocketNormal() const;
	/**
	 * @brief �W�[�B�~SocketID�ƶq
	 * @param ulCount �ƶq
	 */
	void SocketExtra(IN unsigned long ulCount);
	/**
	 * @brief ���o�B�~SocketID�ƶq
	 * @return �B�~SocketID�ƶq
	 */
	unsigned long SocketExtra() const;
	/**
	 * @brief ���o�`SocketID�ƶq
	 * @return �`SocketID�ƶq
	 */
	unsigned long SocketTotal() const;
	/**
	 * @brief ���������y�q
	 * @param lValue �y�q��
	 */
	void RecordRecv(IN long lValue);
	/**
	 * @brief ���o�����y�q
	 * @return �����y�q
	 */
	unsigned long RecordRecv() const;
	/**
	 * @brief �����ǰe�y�q
	 * @param lValue �y�q��
	 */
	void RecordSend(IN long lValue);
	/**
	 * @brief ���o�ǰe�y�q
	 * @return �ǰe�y�q
	 */
	unsigned long RecordSend() const;
	/**
	 * @brief �}�l�O�����A��IOCP����į�
	 */
	void BenchmarkIOCPStart();
	/**
	 * @brief �����O�����A��IOCP����į�
	 */
	void BenchmarkIOCPEnd();
	/**
	 * @brief �}�l�O�����A���B�z����įફ��
	 */
	void BenchmarkProcStart();
	/**
	 * @brief �����O�����A���B�z����įફ��
	 */
	void BenchmarkProcEnd();
	/**
	 * @brief ���o���A��IOCP�C����榸��
	 * @return �C����榸��
	 */
	unsigned long BenchmarkIOCPFPS() const;
	/**
	 * @brief ���o���A��IOCP�̪�����ɶ�
	 * @return �̪�����ɶ�
	 */
	unsigned long BenchmarkIOCPLongest() const;
	/**
	 * @brief ���o���A��IOCP��������ɶ�
	 * @return ��������ɶ�
	 */
	unsigned long BenchmarkIOCPAverage() const;
	/**
	 * @brief ���o���A���B�z�C����榸��
	 * @return �C����榸��
	 */
	unsigned long BenchmarkProcFPS() const;
	/**
	 * @brief ���o���A���B�z�̪�����ɶ�
	 * @return �̪�����ɶ�
	 */
	unsigned long BenchmarkProcLongest() const;
	/**
	 * @brief ���o���A���B�z��������ɶ�
	 * @return ��������ɶ�
	 */
	unsigned long BenchmarkProcAverage() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���A�����O
 * @ingroup xserver
 */
class C_XServer
{
	//-------------------------------------
	friend unsigned int __stdcall XThreadServerIOCP(IN void *pParam);
	friend unsigned int __stdcall XThreadServerProc(IN void *pParam);
	//-------------------------------------

private:
	//-------------------------------------
	C_XAPI m_ccAPI; ///< API����
	C_XServerKernal m_ccKernal; ///< �֤ߪ���
	C_XListNotice m_ccListNotice; ///< �q���C��
	C_XListOverlapped m_ccListOverlapped; ///< ���|�C��
	C_XListUnit m_ccListUnit; ///< �ǿ�椸�C��
	C_ThreadMgr m_ccThreadMgr; ///< ������޲z��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ���A��IOCP����
	 * @param pOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void ServerIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief ���A���B�z����
	 */
	void ServerProc();
	/**
	 * @brief �}�laccept
	 * @note �o�Ө禡�|�إߤ@�ӷs��SocketID
	 */
	void AcceptStart();
	/**
	 * @brief ����accept
	 * @param sOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void AcceptFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief �}�lrecv
	 * @param Socket SocketID
	 */
	void RecvStart(IN SOCKET Socket);
	/**
	 * @brief ����recv
	 * @param sOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void RecvFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief �}�lsend
	 * @param Socket SocketID
	 */
	void SendStart(IN SOCKET Socket);
	/**
	 * @brief ����send
	 * @param sOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void SendFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief �}�l�q��
	 * @param Socket SocketID
	 */
	void NoticeStart(IN SOCKET Socket);
	//-------------------------------------

public:
	//-------------------------------------
	C_XServer();
	virtual ~C_XServer();
	//-------------------------------------
	/**
	 * @brief �Ұʦ��A��
	 * @note �`�N!�Ұʦ��A���ä��|��l��Winsock�귽, �ϥΪ̻ݭn�ۤv�I�s XSocketInitialize() �禡\n
	 *       ��J����}�p�G�u�t�Ʀr�P�r��'.'����, �N�|�Q���Ѭ���Ʀr��}, ���M���ܴN�|�Q���Ѭ������W�٦�}, �ϥήɭn�S�O�`�N
	 * @param ccIPData ��}����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Start(IN const C_IPData &ccIPData);
	/**
	 * @brief ������A��
	 * @note �`�N!������A���ä��|����Winsock�귽, �ϥΪ̻ݭn�ۤv�I�s XSocketRelease() �禡
	 */
	void Stop();
	/**
	 * @brief �W�[�@��SocketID�ƶq
	 * @note �@��SocketID�ƶq�����O���ѫȤ�ݳs�u��SocketID�ƶq, �p�G�W�L�o�Ӽƶq���᪺�Ȥ�ݳ��|�Q���_�s�u
	 * @param ulCount �ƶq
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddSocketNormal(IN unsigned long ulCount);
	/**
	 * @brief �W�[�B�~SocketID�ƶq
	 * @note �B�~SocketID�ƶq�����O��s�u�ƶq�W�L�@��SocketID�ƶq��, �Ψӱ����ä��_�o�ǫȤ�ݪ�SocketID���ƶq
	 * @param ulCount �ƶq
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddSocketExtra(IN unsigned long ulCount);
	/**
	 * @brief �����Ȥ��
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool Disconnect(IN SOCKET Socket);
	/**
	 * @brief �ǰe��ƨ�Ȥ��
	 * @param Socket SocketID
	 * @param pData �ǰe��ƫ���
	 * @param ulSize �ǰe��ƪ���
	 */
	void Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief �ǰe��ƨ�����Ȥ��
	 * @param pData �ǰe��ƫ���
	 * @param ulSize �ǰe��ƪ���
	 */
	void Send(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ���o�q������C��
	 * @param ulMax �q������̤j�ƶq
	 * @return �q������C��
	 */
	std::vector<C_XNotice> Notice(IN unsigned long ulMax);
	/**
	 * @brief ���oSocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief ���oSocketID�s�u��}
	 * @param Socket SocketID
	 * @param ccIPDate ��}����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Address(IN SOCKET Socket, OUT C_IPData &ccIPDate) const;
	/**
	 * @brief �ˬdSocketID�O�_�s�u��
	 * @param Socket SocketID
	 * @return true��ܳs�u��, false�h�_
	 */
	bool IsConnect(IN SOCKET Socket) const;
	/**
	 * @brief ���o���A����T
	 * @return ���A����T
	 */
	S_XServer Infomation() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------