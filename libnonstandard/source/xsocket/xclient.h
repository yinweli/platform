/**
 * @file xclient.h
 * @note 客戶端類別
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
 * @brief 客戶端IOCP執行緒
 * @param pParam 執行緒參數
 * @ingroup xclient
 */
unsigned int __stdcall XThreadClientIOCP(IN void *pParam);
/**
 * @brief 客戶端處理執行緒
 * @param pParam 執行緒參數
 * @ingroup xserver
 */
unsigned int __stdcall XThreadClientProc(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief 客戶端資訊結構
 * @ingroup xclient
 */
struct S_XClient
{
	SOCKET Socket; ///< SocketID
	unsigned long ulThreads; ///< 執行緒數量
	unsigned long ulConnects; ///< 連線數量
	unsigned long ulNotices; ///< 通知數量
	unsigned long ulOverlappeds; ///< 重疊物件數量
	unsigned long ulOverlappedConnect; ///< 遠端連線重疊物件數量
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

	S_XClient();
};
//-----------------------------------------------------------------------------
/**
 * @brief 客戶端核心類別
 * @ingroup xclient
 */
class C_XClientKernal
{
private:
	//-------------------------------------
	HANDLE m_hIOCP; ///< IOCompletionPort
	bool m_bAuto; ///< 自動連線旗標
	unsigned long m_ulInterval; ///< 連線間隔時間
	unsigned long m_ulConnect; ///< 連線檢查時間
	C_FlowRecord m_ccRecvFlowRecord; ///< 接收流量紀錄物件
	C_FlowRecord m_ccSendFlowRecord; ///< 傳送流量紀錄物件
	C_Benchmark m_ccBenchmarkIOCP; ///< 伺服器IOCP執行效能物件
	C_Benchmark m_ccBenchmarkProc; ///< 伺服器處理執行效能物件
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XClientKernal();
	virtual ~C_XClientKernal();
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
	 * @brief 設定自動連線旗標
	 * @param bEnable 旗標
	 */
	void Auto(IN bool bEnable);
	/**
	 * @brief 取得自動連線旗標
	 * @return 自動連線旗標
	 */
	bool Auto() const;
	/**
	 * @brief 設定連線間隔時間
	 * @param ulInterval 連線間隔時間
	 */
	void Interval(IN unsigned long ulInterval);
	/**
	 * @brief 取得連線間隔時間
	 * @return 連線間隔時間
	 */
	unsigned long Interval() const;
	/**
	 * @brief 檢查是否可以連線
	 * @return true表示可連線, false則否
	 */
	bool ConnectCheck();
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
 * @brief 客戶端類別
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
	C_XAPI m_ccAPI; ///< API物件
	C_XClientKernal m_ccKernal; ///< 核心物件
	C_XListConnect m_ccListConnect; ///< 連線列表
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
	 * @brief 客戶端IOCP執行
	 * @param pOverlapped 重疊指標
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void ClientIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult);
	/**
	 * @brief 客戶端處理執行
	 */
	void ClientProc();
	/**
	 * @brief 開始connect
	 * @param ccIPData 位址物件
	 */
	void ConnectStart(IN const C_IPData &ccIPData);
	/**
	 * @brief 結束connect
	 * @param sOverlapped 重疊物件
	 * @param ulBytes 傳輸長度
	 * @param bResult 執行結果
	 */
	void ConnectFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult);
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
	C_XClient();
	virtual ~C_XClient();
	//-------------------------------------
	/**
	 * @brief 啟動客戶端
	 * @note 注意!啟動客戶端並不會初始化Winsock資源, 使用者需要自己呼叫 XSocketInitialize() 函式
	 * @param bAuto 自動連線旗標
	 * @param ulInterval 連線間隔時間
	 * @return true表示成功, false則否
	 */
	bool Start(IN bool bAuto, IN unsigned long ulInterval);
	/**
	 * @brief 停止客戶端
	 * @note 注意!停止客戶端並不會釋放Winsock資源, 使用者需要自己呼叫 XSocketRelease() 函式
	 */
	void Stop();
	/**
	 * @brief 連線到伺服器
	 * @note 注意!必須要先呼叫啟動客戶端函式, 不然就無效了\n
	 *       此函式可以重複呼叫, 來連線到不同的伺服器\n
	 *       輸入的位址如果只含數字與字元'.'的話, 就會被辨識為文數字位址, 不然的話就會被辨識為網路名稱位址, 使用時要特別注意
	 * @param ccIPData 位址物件
	 * @return true表示成功, false則否
	 */
	bool Connect(IN const C_IPData &ccIPData);
	/**
	 * @brief 關閉連線
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool Disconnect(IN SOCKET Socket);
	/**
	 * @brief 傳送資料到伺服器
	 * @param Socket SocketID
	 * @param pData 傳送資料指標
	 * @param ulSize 傳送資料長度
	 */
	void Send(IN SOCKET Socket, IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 傳送資料到全部伺服器
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
	 * @brief 取得位址物件
	 * @param Socket SocketID
	 * @return 位址物件
	 */
	C_IPData IPData(IN SOCKET Socket) const;
	/**
	 * @brief 檢查是否與伺服器連線中
	 * @param Socket SocketID
	 * @return true表示連線中, false則否
	 */
	bool IsConnect(IN SOCKET Socket) const;
	/**
	 * @brief 取得客戶端資訊
	 * @return 客戶端資訊
	 */
	S_XClient Infomation() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------