//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xapi.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_XAddr::S_XAddr() : iFamily(0), iSockType(0), iProtocol(0), ulAddrLen(sizeof(sAddr))
{
	memset(&sAddr, 0, ulAddrLen);
}
//-----------------------------------------------------------------------------
C_XPoint::C_XPoint(IN const void *data, IN unsigned long size) : m_pData(data), m_ulSize(size), m_ulPoint(0) {}
//-----------------------------------------------------------------------------
C_XPoint::~C_XPoint() {}
//-----------------------------------------------------------------------------
// ���o��ƫ��Ы�, ���ʫ��Ц�m
const void *C_XPoint::Offset(IN unsigned long ulOfs)
{
	const void *pData = reinterpret_cast<const void *>(reinterpret_cast<const char *>(m_pData) + m_ulPoint);

	m_ulPoint += ulOfs;
	m_ulPoint = std::min(m_ulSize, m_ulPoint);

	return pData;
}
//-----------------------------------------------------------------------------
// ���o��ƪ���
unsigned long C_XPoint::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
// ���o�Ѿl����
unsigned long C_XPoint::Less() const
{
	return m_ulSize > m_ulPoint ? m_ulSize - m_ulPoint : 0;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XPoint::IsOver() const
{
	return m_ulPoint >= m_ulSize;
}
//-----------------------------------------------------------------------------
C_XAPI::C_XAPI() : m_pfGetAcceptExSockAddrs(nullptr), m_pfAcceptEx(nullptr), m_pfConnectEx(nullptr), m_pfDisconnectEx(nullptr) {}
//-----------------------------------------------------------------------------
C_XAPI::~C_XAPI() {}
//-----------------------------------------------------------------------------
// ��l��
bool C_XAPI::Initialize()
{
	SOCKET Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED); // �إߤ@�ӵ����J�X�RWinsock�禡�ϥΪ�SocketID

	// �p�G�S�إߦ��\�N���ѤF
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("create socket failed"));

	// ���JAccept�禡
	{
		GUID Guid = WSAID_ACCEPTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfAcceptEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(AcceptEx)"));
	}

	// ���JConnect�禡
	{
		GUID Guid = WSAID_CONNECTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfConnectEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(ConnectEx)"));
	}

	// ���JDisconnect�禡
	{
		GUID Guid = WSAID_DISCONNECTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfDisconnectEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(DisconnectEx)"));
	}

	// ���JGetAcceptSockAddr�禡
	{
		GUID Guid = WSAID_GETACCEPTEXSOCKADDRS;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfGetAcceptExSockAddrs)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(GetAcceptExSockAddrs)"));
	}

	if(closesocket(Socket) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("close socket failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ���J�X�RWinsock�禡
bool C_XAPI::LoadWSAExtensionFunction(IN SOCKET Socket, IN GUID nFunction, OUT void *&pFunction)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	unsigned long ulBytes = 0;

	// ���J�X�RWinsock�禡
	if(WSAIoctl(Socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &nFunction, sizeof(nFunction), &pFunction, sizeof(pFunction), &ulBytes, nullptr, nullptr) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("WSAIoctl failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ���o�u�@������ƶq
unsigned long C_XAPI::WorkThreads()
{
#ifdef XSOCKET_DEBUG
	return 1; // �����Ҧ��U�u�Τ@�Ӱ����
#else
	SYSTEM_INFO sSysInfo;

	GetSystemInfo(&sSysInfo); // ���o�t�θ�T

	return sSysInfo.dwNumberOfProcessors * 2 + 2; // ���A���ݨ̷ӷL�n���ˬ��B�z���ƶq * 2 + 2
#endif
}
//-----------------------------------------------------------------------------
// �����}�r��O��Ʀr��}�٬O�����W�٦�}
unsigned long C_XAPI::ParseAddr(IN const nstring &szIP)
{
	for(const nstring::value_type &Itor : szIP)
	{
		if(Itor == __T('.'))
			continue;

		if(Itor >= __T('0') && Itor <= __T('9'))
			continue;

		return AI_CANONNAME;
	}//for

	return AI_NUMERICHOST;
}
//-----------------------------------------------------------------------------
// �إ�IOCompletionPort
bool C_XAPI::CreateIOCompletionPort(IN unsigned long ulThreads, OUT HANDLE &hIOCP)
{
	return (hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, ulThreads)) != INVALID_HANDLE_VALUE ? true : C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("create iocp failed"));
}
//-----------------------------------------------------------------------------
// �NSocketID�PIOCompletionPort���p�_��
bool C_XAPI::AssociateIOCompletionPort(IN HANDLE hIOCP, IN SOCKET Socket, IN unsigned long ulValue)
{
	return CreateIoCompletionPort(reinterpret_cast<HANDLE>(Socket), hIOCP, ulValue, 0) == hIOCP; // ���ݭn��ܿ��~�T��, �]���o�ɭԪ����~�i�H�Q����
}
//-----------------------------------------------------------------------------
// ����IOCompletionPort
bool C_XAPI::ReleaseIOCompletionPort(IN HANDLE hIOCP)
{
	return CloseHandle(hIOCP) != FALSE; // ���ݭn��ܿ��~�T��, �]���o�ɭԪ����~�i�H�Q����
}
//-----------------------------------------------------------------------------
// ���o��}���c
bool C_XAPI::GetHostAddrInfo(IN const C_IPData &ccIPData, OUT S_XAddr &sAddr)
{
	ADDRINFOT sHint, *pAddr = nullptr, *pTemp = nullptr;

	memset(&sHint, 0, sizeof(sHint));
	sHint.ai_flags = ParseAddr(ccIPData.IP());
	sHint.ai_family = AF_INET;
	sHint.ai_socktype = SOCK_STREAM;
	sHint.ai_protocol = IPPROTO_TCP;

	// ���o��}��T
	if(GetAddrInfo(ccIPData.IP().c_str(), ntox(ccIPData.Port(), 10).c_str(), &sHint, &pAddr) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("get addrinfo failed"));

	// �p�G���G��nullptr, �N�����F
	if(pAddr == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("addrinfo null"));

	// �`�����o��}���, �ѩ�@�ӹq���i�঳�h�i���d, �ҥH�i��|���o�h�Ӧ�}��T
	// ���b�o�̥u���βŦX���w��IP����, Socket����, �q�T��w��������}��T
	// ���p�G���n�X�Ӧ�}��T���ŦX����, �N�|���o�̫�@�ӲŦX����}��T
	pTemp = pAddr;

	while(pTemp)
	{
		if(pTemp->ai_family == AF_INET && pTemp->ai_socktype == SOCK_STREAM && pTemp->ai_protocol == IPPROTO_TCP)
		{
			sAddr.iFamily = pTemp->ai_family;
			sAddr.iSockType = pTemp->ai_socktype;
			sAddr.iProtocol = pTemp->ai_protocol;
			sAddr.szCanonName = pTemp->ai_canonname ? pTemp->ai_canonname : __T("");
			sAddr.sAddr = *pTemp->ai_addr;
		}//if

		pTemp = pTemp->ai_next;
	}//while

	FreeAddrInfo(pAddr); // �����}��T

	return true;
}
//-----------------------------------------------------------------------------
// ���o�j�w��}���c
bool C_XAPI::GetBindAddrInfo(OUT S_XAddr &sAddr)
{
	ADDRINFOT sHint, *pAddr = nullptr, *pTemp = nullptr;

	memset(&sHint, 0, sizeof(sHint));
	sHint.ai_flags = AI_PASSIVE;
	sHint.ai_family = AF_INET;
	sHint.ai_socktype = SOCK_STREAM;
	sHint.ai_protocol = IPPROTO_TCP;

	// ���o��}��T
	if(GetAddrInfo(nullptr, __T("0"), &sHint, &pAddr) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("get addrinfo failed"));

	// �p�G���G��nullptr, �N�����F
	if(pAddr == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("addrinfo null"));

	// �`�����o��}���, �ѩ�@�ӹq���i�঳�h�i���d, �ҥH�i��|���o�h�Ӧ�}��T
	// ���b�o�̥u���βŦX���w��IP����, Socket����, �q�T��w��������}��T
	// ���p�G���n�X�Ӧ�}��T���ŦX����, �N�|���o�̫�@�ӲŦX����}��T
	pTemp = pAddr;

	while(pTemp)
	{
		if(pTemp->ai_family == AF_INET && pTemp->ai_socktype == SOCK_STREAM && pTemp->ai_protocol == IPPROTO_TCP)
		{
			sAddr.iFamily = pTemp->ai_family;
			sAddr.iSockType = pTemp->ai_socktype;
			sAddr.iProtocol = pTemp->ai_protocol;
			sAddr.szCanonName = pTemp->ai_canonname ? pTemp->ai_canonname : __T("");
			sAddr.sAddr = *pTemp->ai_addr;
		}//if

		pTemp = pTemp->ai_next;
	}//while

	FreeAddrInfo(pAddr); // �����}��T

	return true;
}
//-----------------------------------------------------------------------------
// �إ�SocketID
bool C_XAPI::CreateSocket(IN const S_XAddr &sAddr, OUT SOCKET &Socket)
{
	// �إ߱a�����|�ݩʪ�SocketID
	if((Socket = WSASocket(sAddr.iFamily, sAddr.iSockType, sAddr.iProtocol, nullptr, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("create socket failed"));

	char cValue = 1;

	// ����Nagle�t��k
	if(setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, &cValue, sizeof(cValue)) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("set socket option failed(TCP_NODELAY)"));

	// �]�w�_�u���ݮɶ�
	LINGER sLinger;

	sLinger.l_onoff = 1;
	sLinger.l_linger = 0;

	if(setsockopt(Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char *>(&sLinger), sizeof(sLinger)) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("set socket option failed(SO_LINGER)"));

	return true;
}
//-----------------------------------------------------------------------------
// ����SocketID
void C_XAPI::ReleaseSocket(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return;

	shutdown(Socket, SD_BOTH);
	closesocket(Socket);
}
//-----------------------------------------------------------------------------
// �j�wSocketID
bool C_XAPI::BindSocket(IN SOCKET Socket, IN const S_XAddr &sAddr)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(bind(Socket, &sAddr.sAddr, sAddr.ulAddrLen) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("bind socket failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ��ťSocketID
bool C_XAPI::ListenSocket(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(listen(Socket, SOMAXCONN) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("listen socket failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ���oSocketID���s�u�ɶ�
bool C_XAPI::GetConnectTime(IN SOCKET Socket, OUT unsigned long &ulTime)
{
	unsigned long ulConnectTime;
	int iSize = sizeof(ulConnectTime);

	if(getsockopt(Socket, SOL_SOCKET, SO_CONNECT_TIME, reinterpret_cast<char *>(&ulConnectTime), &iSize) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("get socket option failed(SO_CONNECT_TIME)"));

	ulTime = ulConnectTime;

	return true;
}
//-----------------------------------------------------------------------------
// Accept
bool C_XAPI::Accept(IN SOCKET SocketServer, IN SOCKET Socket, IN void *pBuffer, IN OVERLAPPED &sOverlapped)
{
	if(m_pfAcceptEx == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("function null"));

	unsigned long ulRecvs = 0;

	if(m_pfAcceptEx(SocketServer, Socket, pBuffer, 0, XSOCKET_ADDRLENGTH, XSOCKET_ADDRLENGTH, &ulRecvs, &sOverlapped) == FALSE)
	{
		C_ErrorWSA ccWSAError; // ���oWinsock���~�N�X

		// �p�G���O�ƶ���, �N��ܥX���F
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("accept failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// Connect
bool C_XAPI::Connect(IN SOCKET Socket, IN const sockaddr *pAddr, IN int iAddrSize, IN OVERLAPPED &sOverlapped)
{
	if(m_pfConnectEx == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("function null"));

	if(m_pfConnectEx(Socket, pAddr, iAddrSize, nullptr, 0, nullptr, &sOverlapped) == FALSE)
	{
		C_ErrorWSA ccWSAError; // ���oWinsock���~�N�X

		// �p�G���O�ƶ���, �N��ܥX���F
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("connect failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// �]�wAccept�����᪺SocketID
bool C_XAPI::AcceptContext(IN SOCKET SocketServer, IN SOCKET Socket)
{
	if(SocketServer == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socketserver"));

	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(setsockopt(Socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<const char *>(&SocketServer), sizeof(SocketServer)) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("setsockopt failed(SO_UPDATE_ACCEPT_CONTEXT)"));

	return true;
}
//-----------------------------------------------------------------------------
// �]�wConnect�����᪺SocketID
bool C_XAPI::ConnectContext(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(setsockopt(Socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("setsockopt failed(SO_UPDATE_CONNECT_CONTEXT)"));

	return true;
}
//-----------------------------------------------------------------------------
// Disconnect
bool C_XAPI::Disconnect(IN SOCKET Socket, IN OVERLAPPED &sOverlapped)
{
	if(m_pfDisconnectEx == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("function null"));

	// �ƹ�W�o�̬O�_�ݭn��shutdown�ADisconnectEx�O? �ڤ]���M��@@~~
	// �u�O�ثe�o�˧@�T��O���Ī�
	// �o�O���F�קK�����DisconnectEx��, �p�G�Ȥ�ݤ��M����ǰe�ʥ], �h�_�u�������q���N�|�û�����F���F
	// �u�n�����I�sshutdown�A�I�sDisconnectEx, �N�|���`�����_�u�q���F

	if(shutdown(Socket, SD_BOTH) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("shutdown failed"));

	if(m_pfDisconnectEx(Socket, &sOverlapped, TF_REUSE_SOCKET, 0) == FALSE)
	{
		C_ErrorWSA ccWSAError; // ���oWinsock���~�N�X

		// �p�G���O�ƶ���, �N��ܥX���F
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("disconnect failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// Recv
bool C_XAPI::Recv(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped)
{
	unsigned long ulRecvs = 0;
	unsigned long ulFlags = 0;

	// �o�XWSARecv�I�s
	if(WSARecv(Socket, &sWSABuf, 1, &ulRecvs, &ulFlags, &sOverlapped, nullptr) == SOCKET_ERROR)
	{
		C_ErrorWSA ccWSAError; // ���oWinsock���~�N�X

		// �p�G���O�ƶ���, �N��ܥX���F
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("recv failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// Send
bool C_XAPI::Send(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped)
{
	unsigned long ulSends = 0;

	// �o�XWSASend�I�s
	if(WSASend(Socket, &sWSABuf, 1, &ulSends, 0, &sOverlapped, nullptr) == SOCKET_ERROR)
	{
		C_ErrorWSA ccWSAError; // ���oWinsock���~�N�X

		// �p�G���O�ƶ���, �N��ܥX���F
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("send failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// GetAcceptSockAddr
bool C_XAPI::GetAcceptSockAddr(IN void *pBuffer, IN sockaddr &sAddrServer, IN sockaddr &sAddrClient)
{
	if(m_pfGetAcceptExSockAddrs == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("function null"));

	sockaddr *pAddrServer = nullptr;
	sockaddr *pAddrClient = nullptr;
	int iAddrServers = 0;
	int iAddrClients = 0;

	// �ѪR�X��}���c
	m_pfGetAcceptExSockAddrs(pBuffer, 0, XSOCKET_ADDRLENGTH, XSOCKET_ADDRLENGTH, &pAddrServer, &iAddrServers, &pAddrClient, &iAddrClients);
	// �ƻs��}���c
	sAddrServer = *pAddrServer;
	sAddrClient = *pAddrClient;

	return true;
}
//-----------------------------------------------------------------------------
// ��l��Winsock
bool XSocketInitialize(IN WSADATA *pWSAData)
{
	WSADATA sWSAData;

	if(pWSAData == nullptr)
		pWSAData = &sWSAData;

	memset(pWSAData, 0, sizeof(WSADATA));

	C_ErrorWSA ccWSAError = WSAStartup(XSOCKET_WSAVERSION, pWSAData);

	return ccWSAError == WSASUCCESS ? true : C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("initilize wsasocket failed"));
}
//-----------------------------------------------------------------------------
// ����Winsock
void XSocketRelease()
{
	WSACleanup();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------