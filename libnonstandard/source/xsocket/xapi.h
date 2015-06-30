/**
 * @file xapi.h
 * @note API���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XAPI
#define _XAPI
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
struct S_XOverlapped;
//-----------------------------------------------------------------------------
//#define XSOCKET_DEBUG ///< xsocket�����Ҧ��w�q @ingroup xapi
#define XSOCKET_WSAVERSION MAKEWORD(2, 2) ///< �ϥΪ�Winsock�������X @ingroup xapi
#define XSOCKET_ADDRLENGTH sizeof(sockaddr) + 16 ///< ��}���� @ingroup xapi
#define XSOCKET_PACKETSIZE USHRT_MAX ///< �ǰe�ʥ]�̤j���� @ingroup xapi
#define XSOCKET_BUFFERSIZE 8192 ///< �ǿ�w�İϪ���, �V�p�ǿ�t�׶V�C, �V�j�V��, ���O���A���ϥΪ��O����]�|�ܦh @ingroup xapi
#define XSOCKET_NOTICESIZE 100 ///< �B�z�q������ @ingroup xapi
#define XSOCKET_CONNINTERVAL 100 ///< �s�u���j�ɶ� @ingroup xapi
#define XSOCKET_TPARAM_SERVER __T("server") ///< ������Ѽ� - ���A������ @ingroup xapi
#define XSOCKET_TPARAM_CLIENT __T("client") ///< ������Ѽ� - �Ȥ�ݫ��� @ingroup xapi
#define XSOCKET_TPARAM_THREAD __T("thread") ///< ������Ѽ� - ������Ҧ� @ingroup xapi
//-----------------------------------------------------------------------------
typedef unsigned short x_head; ///< ���Y���A @ingroup xapi
//-----------------------------------------------------------------------------
/**
 * @brief ������Ҧ��C�|
 * @ingroup xapi
 */
enum ENUM_XThread
{
	ENUM_XThread_NULL = 0, ///< �L��
	ENUM_XThread_Normal, ///< ���`�Ҧ�
	ENUM_XThread_Sleep, ///< ��v�Ҧ�

	ENUM_XThread_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief ��}���c
 * @ingroup xapi
 */
struct S_XAddr
{
	int iFamily; ///< ��}�a��
	int iSockType; ///< Socket���A
	int iProtocol; ///< ��w���A
	nstring szCanonName; ///< ��}�W��
	sockaddr sAddr; ///< ��}���c
	unsigned long ulAddrLen; ///< ��}���c����

	S_XAddr();
};
//-----------------------------------------------------------------------------
/**
 * @brief ���о����O
 * @ingroup xapi
 */
class C_XPoint
{
private:
	//-------------------------------------
	const void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	unsigned long m_ulPoint; ///< ���Ц�m
	//-------------------------------------

public:
	//-------------------------------------
	C_XPoint(IN const void *data, IN unsigned long size);
	virtual ~C_XPoint();
	//-------------------------------------
	/**
	 * @brief ���o��ƫ��Ы�, ���ʫ��Ц�m
	 * @param ulOfs �첾��
	 * @return ��ƫ���
	 */
	const void *Offset(IN unsigned long ulOfs);
	/**
	 * @brief ���o��ƪ���
	 * @return ��ƪ���
	 */
	unsigned long Size() const;
	/**
	 * @brief ���o�Ѿl����
	 * @return �Ѿl����
	 */
	unsigned long Less() const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܵ���, false�h�_
	 */
	bool IsOver() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief API���O
 * @ingroup xapi
 */
class C_XAPI
{
private:
	//-------------------------------------
	LPFN_GETACCEPTEXSOCKADDRS m_pfGetAcceptExSockAddrs; ///< GetAcceptExSockAddrs�禡����
	LPFN_ACCEPTEX m_pfAcceptEx; ///< AcceptEx�禡����
	LPFN_CONNECTEX m_pfConnectEx; ///< ConnectEx�禡����
	LPFN_DISCONNECTEX m_pfDisconnectEx; ///< DisconnectEx�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_XAPI();
	virtual ~C_XAPI();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @note ���~���i�禡���Ц��i��|�H�h������Ҧ��I�s
	 * @return true��ܦ��\, false�h�_
	 */
	bool Initialize();
	/**
	 * @brief ���J�X�RWinsock�禡
	 * @param Socket SocketID
	 * @param nFunction �禡�N�X
	 * @param pFunction �禡���аѷ�
	 * @return true��ܦ��\, false�h�_
	 */
	bool LoadWSAExtensionFunction(IN SOCKET Socket, IN GUID nFunction, OUT void *&pFunction);
	/**
	 * @brief ���o�u�@������ƶq
	 * @return ������ƶq
	 */
	unsigned long WorkThreads();
	/**
	 * @brief �����}�r��O��Ʀr��}�٬O�����W�٦�}
	 * @param szIP ��}
	 * @return AI_NUMERICHOST��ܬO��Ʀr��}, AI_CANONNAME��ܬO�����W�٦�}
	 */
	unsigned long ParseAddr(IN const nstring &szIP);
	/**
	 * @brief �إ�IOCompletionPort
	 * @param ulThreads ������ƶq
	 * @param hIOCP IOCompletionPort
	 * @return true��ܦ��\, false�h�_
	 */
	bool CreateIOCompletionPort(IN unsigned long ulThreads, OUT HANDLE &hIOCP);
	/**
	 * @brief �NSocketID�PIOCompletionPort���p�_��
	 * @param hIOCP IOCompletionPort
	 * @param Socket SocketID
	 * @param ulValue �ۭq��
	 * @return true��ܦ��\, false�h�_
	 */
	bool AssociateIOCompletionPort(IN HANDLE hIOCP, IN SOCKET Socket, IN unsigned long ulValue);
	/**
	 * @brief ����IOCompletionPort
	 * @param hIOCP IOCompletionPort
	 * @return true��ܦ��\, false�h�_
	 */
	bool ReleaseIOCompletionPort(IN HANDLE hIOCP);
	/**
	 * @brief ���o�D����}���c
	 * @param ccIPData ��}����
	 * @param sAddr ��}���c
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetHostAddrInfo(IN const C_IPData &ccIPData, OUT S_XAddr &sAddr);
	/**
	 * @brief ���o�j�w��}���c
	 * @param sAddr ��}���c
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetBindAddrInfo(OUT S_XAddr &sAddr);
	/**
	 * @brief �إ�SocketID
	 * @param sAddr �إ߸�T
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool CreateSocket(IN const S_XAddr &sAddr, OUT SOCKET &Socket);
	/**
	 * @brief ����SocketID
	 * @param Socket ����SocketID
	 */
	void ReleaseSocket(IN SOCKET Socket);
	/**
	 * @brief �j�wSocketID
	 * @param Socket �j�w��SocketID
	 * @param sAddr ��}���c
	 * @return true��ܦ��\, false�h�_
	 */
	bool BindSocket(IN SOCKET Socket, IN const S_XAddr &sAddr);
	/**
	 * @brief ��ťSocketID
	 * @param Socket ��ť��SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool ListenSocket(IN SOCKET Socket);
	/**
	 * @brief ���oSocketID���s�u�ɶ�
	 * @param Socket SocketID
	 * @param ulTime �s�u�ɶ�, �p�G�|���s�u�h�Ǧ^0xffffffff
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetConnectTime(IN SOCKET Socket, OUT unsigned long &ulTime);
	/**
	 * @brief Accept
	 * @param SocketServer ���A��SocketID
	 * @param Socket ������SocketID
	 * @param pBuffer �w�İϫ���
	 * @param sOverlapped ���|����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Accept(IN SOCKET SocketServer, IN SOCKET Socket, IN void *pBuffer, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Connect
	 * @param Socket �s�u��SocketID
	 * @param pAddr �s�u��}����
	 * @param iAddrSize �s�u��}����
	 * @param sOverlapped ���|����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Connect(IN SOCKET Socket, IN const sockaddr *pAddr, IN int iAddrSize, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief �]�wAccept�����᪺SocketID
	 * @param SocketServer ���A��SocketID
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool AcceptContext(IN SOCKET SocketServer, IN SOCKET Socket);
	/**
	 * @brief �]�wConnect�����᪺SocketID
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool ConnectContext(IN SOCKET Socket);
	/**
	 * @brief Disconnect
	 * @param Socket �_�u��SocketID
	 * @param sOverlapped ���|����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Disconnect(IN SOCKET Socket, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Recv
	 * @param Socket ������SocketID
	 * @param sWSABuf �����w�İϪ���
	 * @param sOverlapped ���|����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Recv(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Send
	 * @param Socket �ǰe��SocketID
	 * @param sWSABuf �ǰe�w�İϪ���
	 * @param sOverlapped ���|����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Send(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief GetAcceptSockAddr
	 * @param pBuffer �����s�u�ɪ��w�İϫ���
	 * @param sAddrServer ���A����}���c
	 * @param sAddrClient �Ȥ�ݦ�}���c
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetAcceptSockAddr(IN void *pBuffer, IN sockaddr &sAddrServer, IN sockaddr &sAddrClient);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ��l��Winsock
 * @param pWSAData Winsock��l�Ƹ�T����
 * @return true��ܦ��\, false�h�_
 * @ingroup xapi
 */
bool XSocketInitialize(IN WSADATA *pWSAData = nullptr);
/**
 * @brief ����Winsock
 * @ingroup xapi
 */
void XSocketRelease();
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------