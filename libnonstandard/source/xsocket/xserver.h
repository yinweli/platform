/**
 * @file xserver.h
 * @note 伺服器類別
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
 * @brief 伺服器IOCP執行緒
 * @param pParam 執行緒參數
 * @return 傳回值
 * @ingroup xserver
 */
unsigned int __stdcall XThreadServerIOCP(IN void *pParam);
/**
 * @brief 伺服器處理執行緒
 * @param pParam 執行緒參數
 * @return 傳回值
 * @ingroup xserver
 */
unsigned int __stdcall XThreadServerProc(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief 伺服器資訊結構
 * @ingroup xserver
 */
struct S_XServer
{
	unsigned long ulSocketNormal; ///< 一般SocketID數量
	unsigned long ulSocketExtra; ///< 額外SocketID數量
	unsigned long ulThreads; ///< 執行緒數量
	unsigned long ulConnects; ///< 連線數量
	unsigned long ulNotices; ///< 通知數量
	unsigned long ulOverlappeds; ///< 重疊物件數量
	unsigned long ulOverlappedAccept; ///< 接受連線重疊物件數量
	unsigned long ulOverlappedRecv; ///< 接收重疊物件數量
	unsigned long ulOverlappedSend; ///< 傳送重疊物件數量
	unsigned long ulUnits; ///< 傳輸單元數量
	unsigned long ulUnitRunnings; ///< 執行中傳輸單元數量
	unsigned long ulUnitSuspends; ///< 暫停中傳輸單元數量
	unsigned long ulRecvBytesPerSecond; ///< 每秒接收位元組數
	unsigned long ulSendBytesPerSecond; ///< 每秒傳送位元組數
	unsigned long ulBenchmarkIOCPFPS; ///< IOCP每秒執行次數
	unsigned long ulBenchmarkIOCPLongest; ///< IOCP最長執行時間
	unsigned long ulBenchmarkIOCPAverage; ///< IOCP平均執行時間
	unsigned long ulBenchmarkProcFPS; ///< 處理每秒執行次數
	unsigned long ulBenchmarkProcLongest; ///< 處理最長執行時間
	unsigned long ulBenchmarkProcAverage; ///< 處理平均執行時間

	S_XServer();
};
//-----------------------------------------------------------------------------
/**
 * @brief 伺服器核心類別
 * @ingroup xserver
 */
class C_XServerKernal
{
private:
	//-------------------------------------
	HANDLE m_hIOCP; ///< IOCompletionPort
	SOCKET m_Socket; ///< SocketID
	S_XAddr m_sAddr; ///< 位址資訊
	unsigned long m_ulSocketNormal; ///< 一般SocketID數量
	unsigned long m_ulSocketExtra; ///< 額外SocketID數量
	C_FlowRecord m_ccFlowRecordRecv; ///< 接收流量紀錄物件
	C_FlowRecord m_ccFlowRecordSend; ///< 傳送流量紀錄物件
	C_Benchmark m_ccBenchmarkIOCP; ///< 伺服器IOCP執行效能物件
	C_Benchmark m_ccBenchmarkProc; ///< 伺服器處理執行效能物件
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XServerKernal();
	virtual ~C_XServerKernal();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 設定IOCompletionPort
	 * @param hIOCP IOCompletionPort
	 */
	void IOCP(IN HANDLE hIOCP);
	/**
	 * @brief 取得IOCompletionPort
	 * @return IOCompletionPort
	 */
	HANDLE IOCP() const;
	/**
	 * @brief 設定SocketID
	 * @param Socket SocketID
	 */
	void Socket(IN SOCKET Socket);
	/**
	 * @brief 取得SocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief 設定位址資訊
	 * @param sAddr 位址資訊
	 */
	void Addr(IN const S_XAddr &sAddr);
	/**
	 * @brief 取得位址資訊
	 * @return 位址資訊
	 */
	S_XAddr Addr() const;
	/**
	 * @brief 增加一般SocketID數量
	 * @param ulCount 數量
	 */
	void SocketNormal(IN unsigned long ulCount);
	/**
	 * @brief 取得一般SocketID數量
	 * @return 一般SocketID數量
	 */
	unsigned long SocketNormal() const;
	/**
	 * @brief 增加額外SocketID數量
	 * @param ulCount 數量
	 */
	void SocketExtra(IN unsigned long ulCount);
	/**
	 * @brief 取得額外SocketID數量
	 * @return 額外SocketID數量
	 */
	unsigned long SocketExtra() const;
	/**
	 * @brief 取得總SocketID數量
	 * @return 總SocketID數量
	 */
	unsigned long SocketTotal() const;
	/**
	 * @brief 紀錄接收流量
	 * @param lValue 流量值
	 */
	void RecordRecv(IN long lValue);
	/**
	 * @brief 取得接收流量
	 * @return 接收流量
	 */
	unsigned long RecordRecv() const;
	/**
	 * @brief 紀錄傳送流量
	 * @param lValue 流量值
	 */
	void RecordSend(IN long lValue);
	/**
	 * @brief 取得傳送流量
	 * @return 傳送流量
	 */
	unsigned long RecordSend() const;
	/**
	 * @brief 開始記錄伺服器IOCP執行效能
	 */
	void BenchmarkIOCPStart();
	/**
	 * @brief 結束記錄伺服器IOCP執行效能
	 */
	void BenchmarkIOCPEnd();
	/**
	 * @brief 開始記錄伺服器處理執行效能物件
	 */
	void BenchmarkProcStart();
	/**
	 * @brief 結束記錄伺服器處理執行效能物件
	 */
	void BenchmarkProcEnd();
	/**
	 * @brief 取得伺服器IOCP每秒執行次數
	 * @return 每秒執行次數
	 */
	unsigned long BenchmarkIOCPFPS() const;
	/**
	 * @brief 取得伺服器IOCP最長執行時間
	 * @return 最長執行時間
	 */
	unsigned long BenchmarkIOCPLongest() const;
	/**
	 * @brief 取得伺服器IOCP平均執行時間
	 * @return 平均執行時間
	 */
	unsigned long BenchmarkIOCPAverage() const;
	/**
	 * @brief 取得伺服器處理每秒執行次數
	 * @return 每秒執行次數
	 */
	unsigned long BenchmarkProcFPS() const;
	/**
	 * @brief 取得伺服器處理最長執行時間
	 * @return 最長執行時間
	 */
	unsigned long BenchmarkProcLongest() const;
	/**
	 * @brief 取得伺服器處理平均執行時間
	 * @return 平均執行時間
	 */
	unsigned long BenchmarkProcAverage() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 伺服器類別
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
	C_XAPI m_ccAPI; ///< API物件
	C_XServerKernal m_ccKernal; ///< 核心物件
	C_XListNotice m_ccListNotice; ///< 通知列表
	C_XListOverlapped m_ccListOverlapped; ///< 重疊列表
	C_XListUnit m_ccListUnit; ///< 傳輸單元列表
	C_ThreadMgr m_ccThreadMgr; ///< 執行緒管理器
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 伺服器IOCP執行
	 * @param pOverlapped 重疊指標
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void ServerIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief 伺服器處理執行
	 */
	void ServerProc();
	/**
	 * @brief 開始accept
	 * @note 這個函式會建立一個新的SocketID
	 */
	void AcceptStart();
	/**
	 * @brief 結束accept
	 * @param sOverlapped 重疊物件
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void AcceptFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief 開始recv
	 * @param Socket SocketID
	 */
	void RecvStart(IN SOCKET Socket);
	/**
	 * @brief 結束recv
	 * @param sOverlapped 重疊物件
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void RecvFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief 開始send
	 * @param Socket SocketID
	 */
	void SendStart(IN SOCKET Socket);
	/**
	 * @brief 結束send
	 * @param sOverlapped 重疊物件
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void SendFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief 開始通知
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
	 * @brief 啟動伺服器
	 * @note 注意!啟動伺服器並不會初始化Winsock資源, 使用者需要自己呼叫 XSocketInitialize() 函式\n
	 *       輸入的位址如果只含數字與字元'.'的話, 就會被辨識為文數字位址, 不然的話就會被辨識為網路名稱位址, 使用時要特別注意
	 * @param ccIPData 位址物件
	 * @return true表示成功, false則否
	 */
	bool Start(IN const C_IPData &ccIPData);
	/**
	 * @brief 停止伺服器
	 * @note 注意!停止伺服器並不會釋放Winsock資源, 使用者需要自己呼叫 XSocketRelease() 函式
	 */
	void Stop();
	/**
	 * @brief 增加一般SocketID數量
	 * @note 一般SocketID數量指的是提供客戶端連線的SocketID數量, 如果超過這個數量之後的客戶端都會被中斷連線
	 * @param ulCount 數量
	 * @return true表示成功, false則否
	 */
	bool AddSocketNormal(IN unsigned long ulCount);
	/**
	 * @brief 增加額外SocketID數量
	 * @note 額外SocketID數量指的是當連線數量超過一般SocketID數量時, 用來接收並中斷這些客戶端的SocketID的數量
	 * @param ulCount 數量
	 * @return true表示成功, false則否
	 */
	bool AddSocketExtra(IN unsigned long ulCount);
	/**
	 * @brief 關閉客戶端
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool Disconnect(IN SOCKET Socket);
	/**
	 * @brief 傳送資料到客戶端
	 * @param Socket SocketID
	 * @param pData 傳送資料指標
	 * @param ulSize 傳送資料長度
	 */
	void Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 傳送資料到全部客戶端
	 * @param pData 傳送資料指標
	 * @param ulSize 傳送資料長度
	 */
	void Send(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 取得通知物件列表
	 * @param ulMax 通知物件最大數量
	 * @return 通知物件列表
	 */
	std::vector<C_XNotice> Notice(IN unsigned long ulMax);
	/**
	 * @brief 取得SocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief 取得SocketID連線位址
	 * @param Socket SocketID
	 * @param ccIPDate 位址物件
	 * @return true表示成功, false則否
	 */
	bool Address(IN SOCKET Socket, OUT C_IPData &ccIPDate) const;
	/**
	 * @brief 檢查SocketID是否連線中
	 * @param Socket SocketID
	 * @return true表示連線中, false則否
	 */
	bool IsConnect(IN SOCKET Socket) const;
	/**
	 * @brief 取得伺服器資訊
	 * @return 伺服器資訊
	 */
	S_XServer Infomation() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------