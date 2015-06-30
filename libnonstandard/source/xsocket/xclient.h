/**
 * @file xclient.h
 * @note �Ȥ�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XCLIENT
#define _XCLIENT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �Ȥ��IOCP�����
 * @param pParam ������Ѽ�
 * @ingroup xclient
 */
unsigned int __stdcall XThreadClientIOCP(IN void *pParam);
/**
 * @brief �Ȥ�ݳB�z�����
 * @param pParam ������Ѽ�
 * @ingroup xserver
 */
unsigned int __stdcall XThreadClientProc(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief �Ȥ�ݸ�T���c
 * @ingroup xclient
 */
struct S_XClient
{
	SOCKET Socket; ///< SocketID
	unsigned long ulThreads; ///< ������ƶq
	unsigned long ulConnects; ///< �s�u�ƶq
	unsigned long ulNotices; ///< �q���ƶq
	unsigned long ulOverlappeds; ///< ���|����ƶq
	unsigned long ulOverlappedConnect; ///< ���ݳs�u���|����ƶq
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

	S_XClient();
};
//-----------------------------------------------------------------------------
/**
 * @brief �Ȥ�ݮ֤����O
 * @ingroup xclient
 */
class C_XClientKernal
{
private:
	//-------------------------------------
	HANDLE m_hIOCP; ///< IOCompletionPort
	bool m_bAuto; ///< �۰ʳs�u�X��
	unsigned long m_ulInterval; ///< �s�u���j�ɶ�
	unsigned long m_ulConnect; ///< �s�u�ˬd�ɶ�
	C_FlowRecord m_ccRecvFlowRecord; ///< �����y�q��������
	C_FlowRecord m_ccSendFlowRecord; ///< �ǰe�y�q��������
	C_Benchmark m_ccBenchmarkIOCP; ///< ���A��IOCP����įફ��
	C_Benchmark m_ccBenchmarkProc; ///< ���A���B�z����įફ��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XClientKernal();
	virtual ~C_XClientKernal();
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
	 * @brief �]�w�۰ʳs�u�X��
	 * @param bEnable �X��
	 */
	void Auto(IN bool bEnable);
	/**
	 * @brief ���o�۰ʳs�u�X��
	 * @return �۰ʳs�u�X��
	 */
	bool Auto() const;
	/**
	 * @brief �]�w�s�u���j�ɶ�
	 * @param ulInterval �s�u���j�ɶ�
	 */
	void Interval(IN unsigned long ulInterval);
	/**
	 * @brief ���o�s�u���j�ɶ�
	 * @return �s�u���j�ɶ�
	 */
	unsigned long Interval() const;
	/**
	 * @brief �ˬd�O�_�i�H�s�u
	 * @return true��ܥi�s�u, false�h�_
	 */
	bool ConnectCheck();
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
 * @brief �Ȥ�����O
 * @ingroup xclient
 */
class C_XClient
{
	//-------------------------------------
	friend unsigned int __stdcall XThreadClientIOCP(IN void *pParam);
	friend unsigned int __stdcall XThreadClientProc(IN void *pParam);
	//-------------------------------------

private:
	//-------------------------------------
	C_XAPI m_ccAPI; ///< API����
	C_XClientKernal m_ccKernal; ///< �֤ߪ���
	C_XListConnect m_ccListConnect; ///< �s�u�C��
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
	 * @brief �Ȥ��IOCP����
	 * @param pOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void ClientIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief �Ȥ�ݳB�z����
	 */
	void ClientProc();
	/**
	 * @brief �}�lconnect
	 * @param ccIPData ��}����
	 */
	void ConnectStart(IN const C_IPData &ccIPData);
	/**
	 * @brief ����connect
	 * @param sOverlapped ���|����
	 * @param ulBytes �ǿ����
	 * @param bResult ���浲�G
	 */
	void ConnectFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
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
	C_XClient();
	virtual ~C_XClient();
	//-------------------------------------
	/**
	 * @brief �ҰʫȤ��
	 * @note �`�N!�ҰʫȤ�ݨä��|��l��Winsock�귽, �ϥΪ̻ݭn�ۤv�I�s XSocketInitialize() �禡
	 * @param bAuto �۰ʳs�u�X��
	 * @param ulInterval �s�u���j�ɶ�
	 * @return true��ܦ��\, false�h�_
	 */
	bool Start(IN bool bAuto, IN unsigned long ulInterval);
	/**
	 * @brief ����Ȥ��
	 * @note �`�N!����Ȥ�ݨä��|����Winsock�귽, �ϥΪ̻ݭn�ۤv�I�s XSocketRelease() �禡
	 */
	void Stop();
	/**
	 * @brief �s�u����A��
	 * @note �`�N!�����n���I�s�ҰʫȤ�ݨ禡, ���M�N�L�ĤF\n
	 *       ���禡�i�H���ƩI�s, �ӳs�u�줣�P�����A��\n
	 *       ��J����}�p�G�u�t�Ʀr�P�r��'.'����, �N�|�Q���Ѭ���Ʀr��}, ���M���ܴN�|�Q���Ѭ������W�٦�}, �ϥήɭn�S�O�`�N
	 * @param ccIPData ��}����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Connect(IN const C_IPData &ccIPData);
	/**
	 * @brief �����s�u
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool Disconnect(IN SOCKET Socket);
	/**
	 * @brief �ǰe��ƨ���A��
	 * @param Socket SocketID
	 * @param pData �ǰe��ƫ���
	 * @param ulSize �ǰe��ƪ���
	 */
	void Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief �ǰe��ƨ�������A��
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
	 * @brief ���o��}����
	 * @param Socket SocketID
	 * @return ��}����
	 */
	C_IPData IPData(IN SOCKET Socket) const;
	/**
	 * @brief �ˬd�O�_�P���A���s�u��
	 * @param Socket SocketID
	 * @return true��ܳs�u��, false�h�_
	 */
	bool IsConnect(IN SOCKET Socket) const;
	/**
	 * @brief ���o�Ȥ�ݸ�T
	 * @return �Ȥ�ݸ�T
	 */
	S_XClient Infomation() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------