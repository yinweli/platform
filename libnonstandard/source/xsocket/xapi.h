/**
 * @file xapi.h
 * @note API類別
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
//#define XSOCKET_DEBUG ///< xsocket除錯模式定義 @ingroup xapi
#define XSOCKET_WSAVERSION MAKEWORD(2, 2) ///< 使用的Winsock版本號碼 @ingroup xapi
#define XSOCKET_ADDRLENGTH sizeof(sockaddr) + 16 ///< 位址長度 @ingroup xapi
#define XSOCKET_PACKETSIZE USHRT_MAX ///< 傳送封包最大長度 @ingroup xapi
#define XSOCKET_BUFFERSIZE 8192 ///< 傳輸緩衝區長度, 越小傳輸速度越慢, 越大越快, 但是伺服器使用的記憶體也會變多 @ingroup xapi
#define XSOCKET_NOTICESIZE 100 ///< 處理通知次數 @ingroup xapi
#define XSOCKET_CONNINTERVAL 100 ///< 連線間隔時間 @ingroup xapi
#define XSOCKET_TPARAM_SERVER __T("server") ///< 執行緒參數 - 伺服器指標 @ingroup xapi
#define XSOCKET_TPARAM_CLIENT __T("client") ///< 執行緒參數 - 客戶端指標 @ingroup xapi
#define XSOCKET_TPARAM_THREAD __T("thread") ///< 執行緒參數 - 執行緒模式 @ingroup xapi
//-----------------------------------------------------------------------------
typedef unsigned short x_head; ///< 標頭型態 @ingroup xapi
//-----------------------------------------------------------------------------
/**
 * @brief 執行緒模式列舉
 * @ingroup xapi
 */
enum ENUM_XThread
{
	ENUM_XThread_NULL = 0, ///< 無效
	ENUM_XThread_Normal, ///< 正常模式
	ENUM_XThread_Sleep, ///< 休眠模式

	ENUM_XThread_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief 位址結構
 * @ingroup xapi
 */
struct S_XAddr
{
	int iFamily; ///< 位址家族
	int iSockType; ///< Socket型態
	int iProtocol; ///< 協定型態
	nstring szCanonName; ///< 位址名稱
	sockaddr sAddr; ///< 位址結構
	unsigned long ulAddrLen; ///< 位址結構長度

	S_XAddr();
};
//-----------------------------------------------------------------------------
/**
 * @brief 指標器類別
 * @ingroup xapi
 */
class C_XPoint
{
private:
	//-------------------------------------
	const void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	unsigned long m_ulPoint; ///< 指標位置
	//-------------------------------------

public:
	//-------------------------------------
	C_XPoint(IN const void *data, IN unsigned long size);
	virtual ~C_XPoint();
	//-------------------------------------
	/**
	 * @brief 取得資料指標後, 移動指標位置
	 * @param ulOfs 位移植
	 * @return 資料指標
	 */
	const void *Offset(IN unsigned long ulOfs);
	/**
	 * @brief 取得資料長度
	 * @return 資料長度
	 */
	unsigned long Size() const;
	/**
	 * @brief 取得剩餘長度
	 * @return 剩餘長度
	 */
	unsigned long Less() const;
	/**
	 * @brief 檢查是否結束
	 * @return true表示結束, false則否
	 */
	bool IsOver() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief API類別
 * @ingroup xapi
 */
class C_XAPI
{
private:
	//-------------------------------------
	LPFN_GETACCEPTEXSOCKADDRS m_pfGetAcceptExSockAddrs; ///< GetAcceptExSockAddrs函式指標
	LPFN_ACCEPTEX m_pfAcceptEx; ///< AcceptEx函式指標
	LPFN_CONNECTEX m_pfConnectEx; ///< ConnectEx函式指標
	LPFN_DISCONNECTEX m_pfDisconnectEx; ///< DisconnectEx函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_XAPI();
	virtual ~C_XAPI();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @note 錯誤報告函式指標有可能會以多執行緒模式呼叫
	 * @return true表示成功, false則否
	 */
	bool Initialize();
	/**
	 * @brief 載入擴充Winsock函式
	 * @param Socket SocketID
	 * @param nFunction 函式代碼
	 * @param pFunction 函式指標參照
	 * @return true表示成功, false則否
	 */
	bool LoadWSAExtensionFunction(IN SOCKET Socket, IN GUID nFunction, OUT void *&pFunction);
	/**
	 * @brief 取得工作執行緒數量
	 * @return 執行緒數量
	 */
	unsigned long WorkThreads();
	/**
	 * @brief 分辨位址字串是文數字位址還是網路名稱位址
	 * @param szIP 位址
	 * @return AI_NUMERICHOST表示是文數字位址, AI_CANONNAME表示是網路名稱位址
	 */
	unsigned long ParseAddr(IN const nstring &szIP);
	/**
	 * @brief 建立IOCompletionPort
	 * @param ulThreads 執行緒數量
	 * @param hIOCP IOCompletionPort
	 * @return true表示成功, false則否
	 */
	bool CreateIOCompletionPort(IN unsigned long ulThreads, OUT HANDLE &hIOCP);
	/**
	 * @brief 將SocketID與IOCompletionPort關聯起來
	 * @param hIOCP IOCompletionPort
	 * @param Socket SocketID
	 * @param ulValue 自訂值
	 * @return true表示成功, false則否
	 */
	bool AssociateIOCompletionPort(IN HANDLE hIOCP, IN SOCKET Socket, IN unsigned long ulValue);
	/**
	 * @brief 釋放IOCompletionPort
	 * @param hIOCP IOCompletionPort
	 * @return true表示成功, false則否
	 */
	bool ReleaseIOCompletionPort(IN HANDLE hIOCP);
	/**
	 * @brief 取得主控位址結構
	 * @param ccIPData 位址物件
	 * @param sAddr 位址結構
	 * @return true表示成功, false則否
	 */
	bool GetHostAddrInfo(IN const C_IPData &ccIPData, OUT S_XAddr &sAddr);
	/**
	 * @brief 取得綁定位址結構
	 * @param sAddr 位址結構
	 * @return true表示成功, false則否
	 */
	bool GetBindAddrInfo(OUT S_XAddr &sAddr);
	/**
	 * @brief 建立SocketID
	 * @param sAddr 建立資訊
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool CreateSocket(IN const S_XAddr &sAddr, OUT SOCKET &Socket);
	/**
	 * @brief 釋放SocketID
	 * @param Socket 釋放的SocketID
	 */
	void ReleaseSocket(IN SOCKET Socket);
	/**
	 * @brief 綁定SocketID
	 * @param Socket 綁定的SocketID
	 * @param sAddr 位址結構
	 * @return true表示成功, false則否
	 */
	bool BindSocket(IN SOCKET Socket, IN const S_XAddr &sAddr);
	/**
	 * @brief 監聽SocketID
	 * @param Socket 監聽的SocketID
	 * @return true表示成功, false則否
	 */
	bool ListenSocket(IN SOCKET Socket);
	/**
	 * @brief 取得SocketID的連線時間
	 * @param Socket SocketID
	 * @param ulTime 連線時間, 如果尚未連線則傳回0xffffffff
	 * @return true表示成功, false則否
	 */
	bool GetConnectTime(IN SOCKET Socket, OUT unsigned long &ulTime);
	/**
	 * @brief Accept
	 * @param SocketServer 伺服器SocketID
	 * @param Socket 接受的SocketID
	 * @param pBuffer 緩衝區指標
	 * @param sOverlapped 重疊物件
	 * @return true表示成功, false則否
	 */
	bool Accept(IN SOCKET SocketServer, IN SOCKET Socket, IN void *pBuffer, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Connect
	 * @param Socket 連線的SocketID
	 * @param pAddr 連線位址指標
	 * @param iAddrSize 連線位址長度
	 * @param sOverlapped 重疊物件
	 * @return true表示成功, false則否
	 */
	bool Connect(IN SOCKET Socket, IN const sockaddr *pAddr, IN int iAddrSize, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief 設定Accept完畢後的SocketID
	 * @param SocketServer 伺服器SocketID
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool AcceptContext(IN SOCKET SocketServer, IN SOCKET Socket);
	/**
	 * @brief 設定Connect完畢後的SocketID
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool ConnectContext(IN SOCKET Socket);
	/**
	 * @brief Disconnect
	 * @param Socket 斷線的SocketID
	 * @param sOverlapped 重疊物件
	 * @return true表示成功, false則否
	 */
	bool Disconnect(IN SOCKET Socket, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Recv
	 * @param Socket 接收的SocketID
	 * @param sWSABuf 接收緩衝區物件
	 * @param sOverlapped 重疊物件
	 * @return true表示成功, false則否
	 */
	bool Recv(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief Send
	 * @param Socket 傳送的SocketID
	 * @param sWSABuf 傳送緩衝區物件
	 * @param sOverlapped 重疊物件
	 * @return true表示成功, false則否
	 */
	bool Send(IN SOCKET Socket, IN WSABUF &sWSABuf, IN OVERLAPPED &sOverlapped);
	/**
	 * @brief GetAcceptSockAddr
	 * @param pBuffer 接受連線時的緩衝區指標
	 * @param sAddrServer 伺服器位址結構
	 * @param sAddrClient 客戶端位址結構
	 * @return true表示成功, false則否
	 */
	bool GetAcceptSockAddr(IN void *pBuffer, IN sockaddr &sAddrServer, IN sockaddr &sAddrClient);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 初始化Winsock
 * @param pWSAData Winsock初始化資訊指標
 * @return true表示成功, false則否
 * @ingroup xapi
 */
bool XSocketInitialize(IN WSADATA *pWSAData = nullptr);
/**
 * @brief 釋放Winsock
 * @ingroup xapi
 */
void XSocketRelease();
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------