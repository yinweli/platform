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
// 取得資料指標後, 移動指標位置
const void *C_XPoint::Offset(IN unsigned long ulOfs)
{
	const void *pData = reinterpret_cast<const void *>(reinterpret_cast<const char *>(m_pData) + m_ulPoint);

	m_ulPoint += ulOfs;
	m_ulPoint = std::min(m_ulSize, m_ulPoint);

	return pData;
}
//-----------------------------------------------------------------------------
// 取得資料長度
unsigned long C_XPoint::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
// 取得剩餘長度
unsigned long C_XPoint::Less() const
{
	return m_ulSize > m_ulPoint ? m_ulSize - m_ulPoint : 0;
}
//-----------------------------------------------------------------------------
// 檢查是否結束
bool C_XPoint::IsOver() const
{
	return m_ulPoint >= m_ulSize;
}
//-----------------------------------------------------------------------------
C_XAPI::C_XAPI() : m_pfGetAcceptExSockAddrs(nullptr), m_pfAcceptEx(nullptr), m_pfConnectEx(nullptr), m_pfDisconnectEx(nullptr) {}
//-----------------------------------------------------------------------------
C_XAPI::~C_XAPI() {}
//-----------------------------------------------------------------------------
// 初始化
bool C_XAPI::Initialize()
{
	SOCKET Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED); // 建立一個給載入擴充Winsock函式使用的SocketID

	// 如果沒建立成功就失敗了
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("create socket failed"));

	// 載入Accept函式
	{
		GUID Guid = WSAID_ACCEPTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfAcceptEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(AcceptEx)"));
	}

	// 載入Connect函式
	{
		GUID Guid = WSAID_CONNECTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfConnectEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(ConnectEx)"));
	}

	// 載入Disconnect函式
	{
		GUID Guid = WSAID_DISCONNECTEX;

		if(LoadWSAExtensionFunction(Socket, Guid, reinterpret_cast<void *&>(m_pfDisconnectEx)) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("load function failed(DisconnectEx)"));
	}

	// 載入GetAcceptSockAddr函式
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
// 載入擴充Winsock函式
bool C_XAPI::LoadWSAExtensionFunction(IN SOCKET Socket, IN GUID nFunction, OUT void *&pFunction)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	unsigned long ulBytes = 0;

	// 載入擴充Winsock函式
	if(WSAIoctl(Socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &nFunction, sizeof(nFunction), &pFunction, sizeof(pFunction), &ulBytes, nullptr, nullptr) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("WSAIoctl failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 取得工作執行緒數量
unsigned long C_XAPI::WorkThreads()
{
#ifdef XSOCKET_DEBUG
	return 1; // 除錯模式下只用一個執行緒
#else
	SYSTEM_INFO sSysInfo;

	GetSystemInfo(&sSysInfo); // 取得系統資訊

	return sSysInfo.dwNumberOfProcessors * 2 + 2; // 伺服器端依照微軟推薦為處理器數量 * 2 + 2
#endif
}
//-----------------------------------------------------------------------------
// 分辨位址字串是文數字位址還是網路名稱位址
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
// 建立IOCompletionPort
bool C_XAPI::CreateIOCompletionPort(IN unsigned long ulThreads, OUT HANDLE &hIOCP)
{
	return (hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, ulThreads)) != INVALID_HANDLE_VALUE ? true : C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("create iocp failed"));
}
//-----------------------------------------------------------------------------
// 將SocketID與IOCompletionPort關聯起來
bool C_XAPI::AssociateIOCompletionPort(IN HANDLE hIOCP, IN SOCKET Socket, IN unsigned long ulValue)
{
	return CreateIoCompletionPort(reinterpret_cast<HANDLE>(Socket), hIOCP, ulValue, 0) == hIOCP; // 不需要顯示錯誤訊息, 因為這時候的錯誤可以被忽略
}
//-----------------------------------------------------------------------------
// 釋放IOCompletionPort
bool C_XAPI::ReleaseIOCompletionPort(IN HANDLE hIOCP)
{
	return CloseHandle(hIOCP) != FALSE; // 不需要顯示錯誤訊息, 因為這時候的錯誤可以被忽略
}
//-----------------------------------------------------------------------------
// 取得位址結構
bool C_XAPI::GetHostAddrInfo(IN const C_IPData &ccIPData, OUT S_XAddr &sAddr)
{
	ADDRINFOT sHint, *pAddr = nullptr, *pTemp = nullptr;

	memset(&sHint, 0, sizeof(sHint));
	sHint.ai_flags = ParseAddr(ccIPData.IP());
	sHint.ai_family = AF_INET;
	sHint.ai_socktype = SOCK_STREAM;
	sHint.ai_protocol = IPPROTO_TCP;

	// 取得位址資訊
	if(GetAddrInfo(ccIPData.IP().c_str(), ntox(ccIPData.Port(), 10).c_str(), &sHint, &pAddr) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("get addrinfo failed"));

	// 如果結果為nullptr, 就結束了
	if(pAddr == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("addrinfo null"));

	// 循環取得位址資料, 由於一個電腦可能有多張網卡, 所以可能會取得多個位址資訊
	// 但在這裡只取用符合指定的IP類型, Socket類型, 通訊協定類型的位址資訊
	// 但如果有好幾個位址資訊都符合的話, 就會取得最後一個符合的位址資訊
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

	FreeAddrInfo(pAddr); // 釋放位址資訊

	return true;
}
//-----------------------------------------------------------------------------
// 取得綁定位址結構
bool C_XAPI::GetBindAddrInfo(OUT S_XAddr &sAddr)
{
	ADDRINFOT sHint, *pAddr = nullptr, *pTemp = nullptr;

	memset(&sHint, 0, sizeof(sHint));
	sHint.ai_flags = AI_PASSIVE;
	sHint.ai_family = AF_INET;
	sHint.ai_socktype = SOCK_STREAM;
	sHint.ai_protocol = IPPROTO_TCP;

	// 取得位址資訊
	if(GetAddrInfo(nullptr, __T("0"), &sHint, &pAddr) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("get addrinfo failed"));

	// 如果結果為nullptr, 就結束了
	if(pAddr == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("addrinfo null"));

	// 循環取得位址資料, 由於一個電腦可能有多張網卡, 所以可能會取得多個位址資訊
	// 但在這裡只取用符合指定的IP類型, Socket類型, 通訊協定類型的位址資訊
	// 但如果有好幾個位址資訊都符合的話, 就會取得最後一個符合的位址資訊
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

	FreeAddrInfo(pAddr); // 釋放位址資訊

	return true;
}
//-----------------------------------------------------------------------------
// 建立SocketID
bool C_XAPI::CreateSocket(IN const S_XAddr &sAddr, OUT SOCKET &Socket)
{
	// 建立帶有重疊屬性的SocketID
	if((Socket = WSASocket(sAddr.iFamily, sAddr.iSockType, sAddr.iProtocol, nullptr, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("create socket failed"));

	char cValue = 1;

	// 關閉Nagle演算法
	// Nagle演算法 : TCP在傳輸時為了節省頻寬, 因此會採用此演算法來將過小的封包合併後送出
	//               但是這樣做是以傳輸的即時性做為代價, 因此在重視即時性的網路系統上(例如遊戲伺服器)會關閉此演算法
	if(setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, &cValue, sizeof(cValue)) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("set socket option failed(TCP_NODELAY)"));

	// 設定斷線等待時間
	LINGER sLinger;

	sLinger.l_onoff = 1;
	sLinger.l_linger = 0;

	if(setsockopt(Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char *>(&sLinger), sizeof(sLinger)) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("set socket option failed(SO_LINGER)"));

	return true;
}
//-----------------------------------------------------------------------------
// 釋放SocketID
void C_XAPI::ReleaseSocket(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return;

	shutdown(Socket, SD_BOTH);
	closesocket(Socket);
}
//-----------------------------------------------------------------------------
// 綁定SocketID
bool C_XAPI::BindSocket(IN SOCKET Socket, IN const S_XAddr &sAddr)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(bind(Socket, &sAddr.sAddr, sAddr.ulAddrLen) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("bind socket failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 監聽SocketID
bool C_XAPI::ListenSocket(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("invalid socket"));

	if(listen(Socket, SOMAXCONN) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("listen socket failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 取得SocketID的連線時間
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
		C_ErrorWSA ccWSAError; // 取得Winsock錯誤代碼

		// 如果不是排隊中, 就表示出錯了
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
		C_ErrorWSA ccWSAError; // 取得Winsock錯誤代碼

		// 如果不是排隊中, 就表示出錯了
		if(ccWSAError != WSA_IO_PENDING)
			return C_NOutput::Instance().Error(ERRORNSTD, ccWSAError, __T("connect failed"));
	}//if

	return true;
}
//-----------------------------------------------------------------------------
// 設定Accept完畢後的SocketID
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
// 設定Connect完畢後的SocketID
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

	// 事實上這裡是否需要先shutdown再DisconnectEx呢? 我也不清楚@@~~
	// 只是目前這樣作確實是有效的
	// 這是為了避免當執行DisconnectEx後, 如果客戶端仍然持續傳送封包, 則斷線完成的通知將會永遠都到達不了
	// 只要有先呼叫shutdown再呼叫DisconnectEx, 就會正常收到斷線通知了

	if(shutdown(Socket, SD_BOTH) == SOCKET_ERROR)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWSA(), __T("shutdown failed"));

	if(m_pfDisconnectEx(Socket, &sOverlapped, TF_REUSE_SOCKET, 0) == FALSE)
	{
		C_ErrorWSA ccWSAError; // 取得Winsock錯誤代碼

		// 如果不是排隊中, 就表示出錯了
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

	// 發出WSARecv呼叫
	if(WSARecv(Socket, &sWSABuf, 1, &ulRecvs, &ulFlags, &sOverlapped, nullptr) == SOCKET_ERROR)
	{
		C_ErrorWSA ccWSAError; // 取得Winsock錯誤代碼

		// 如果不是排隊中, 就表示出錯了
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

	// 發出WSASend呼叫
	if(WSASend(Socket, &sWSABuf, 1, &ulSends, 0, &sOverlapped, nullptr) == SOCKET_ERROR)
	{
		C_ErrorWSA ccWSAError; // 取得Winsock錯誤代碼

		// 如果不是排隊中, 就表示出錯了
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

	// 解析出位址結構
	m_pfGetAcceptExSockAddrs(pBuffer, 0, XSOCKET_ADDRLENGTH, XSOCKET_ADDRLENGTH, &pAddrServer, &iAddrServers, &pAddrClient, &iAddrClients);
	// 複製位址結構
	sAddrServer = *pAddrServer;
	sAddrClient = *pAddrClient;

	return true;
}
//-----------------------------------------------------------------------------
// 初始化Winsock
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
// 釋放Winsock
void XSocketRelease()
{
	WSACleanup();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------
