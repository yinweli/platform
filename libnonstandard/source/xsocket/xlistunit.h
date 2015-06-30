/**
 * @file xlistunit.h
 * @note 傳輸單元列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTUNIT
#define _XLISTUNIT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_XUnit;
//-----------------------------------------------------------------------------
/**
 * @brief 傳輸單元鎖定類別
 * @ingroup xlist
 */
class C_XUnitLock
{
private:
	//-------------------------------------
	C_XUnit *m_pUnit; ///< 傳輸單元指標
	//-------------------------------------
	CRITICAL_SECTION *m_pLock; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XUnitLock();
	C_XUnitLock(IN const C_XUnit *unit);
	virtual ~C_XUnitLock();
	//-------------------------------------
	operator bool () const;
	//-------------------------------------
	C_XUnit *operator -> ();
	//-------------------------------------
	/**
	 * @brief 解鎖傳輸單元
	 */
	void UnLock();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 傳輸單元類別
 * @ingroup xlist
 */
class C_XUnit
{
	//-------------------------------------
	friend C_XUnitLock;
	//-------------------------------------

private:
	//-------------------------------------
	C_XListRecv m_ListRecv; ///< 接收列表
	C_XListSend m_ListSend; ///< 傳送列表
	sockaddr_in m_sAddress; ///< 連線位址
	bool m_bRunning; ///< 執行旗標
	bool m_bRecv; ///< 接收旗標
	bool m_bSend; ///< 傳送旗標
	bool m_bDisconnect; ///< 斷線旗標
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XUnit();
	virtual ~C_XUnit();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增接收資料
	 * @param pData 資料指標
	 * @param ulSize 資料長度
	 * @return true表示成功, false則否
	 */
	bool AddRecv(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 取得接收資料
	 * @return 接收資料
	 */
	C_XRecv GetRecv();
	/**
	 * @brief 取得接收資料是否為空
	 * @return true表示為空, false則否
	 */
	bool RecvEmpty() const;
	/**
	 * @brief 新增傳送資料
	 * @param pData 資料指標
	 * @param ulSize 資料長度
	 * @return true表示成功, false則否
	 */
	bool AddSend(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 取得傳送資料
	 * @return 傳送資料
	 */
	C_XSend GetSend();
	/**
	 * @brief 取得傳送資料是否為空
	 * @return true表示為空, false則否
	 */
	bool SendEmpty() const;
	/**
	 * @brief 設定連線位址
	 * @param sAddress 連線位址
	 */
	void Address(IN const sockaddr &sAddress);
	/**
	 * @brief 取得連線位址
	 * @param szIP ip
	 * @param ulPort port
	 */
	void Address(OUT nstring &szIP, OUT unsigned long &ulPort) const;
	/**
	 * @brief 設定執行旗標
	 * @param bEnable 旗標
	 */
	void Running(IN bool bEnable);
	/**
	 * @brief 取得執行旗標
	 * @return 接收旗標
	 */
	bool Running() const;
	/**
	 * @brief 設定接收旗標
	 * @param bEnable 旗標
	 */
	void Recv(IN bool bEnable);
	/**
	 * @brief 取得接收旗標
	 * @return 接收旗標
	 */
	bool Recv() const;
	/**
	 * @brief 設定傳送旗標
	 * @param bEnable 旗標
	 */
	void Send(IN bool bEnable);
	/**
	 * @brief 取得傳送旗標
	 * @return 傳送旗標
	 */
	bool Send() const;
	/**
	 * @brief 設定斷線旗標
	 * @param bEnable 旗標
	 */
	void Disconnect(IN bool bEnable);
	/**
	 * @brief 取得斷線旗標
	 * @return 傳送旗標
	 */
	bool Disconnect() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 傳輸單元列表類別
 * @ingroup xlist
 */
class C_XListUnit
{
private:
	//-------------------------------------
	std::map<SOCKET, C_XUnit *> m_Unit; ///< 傳輸單元列表 <SocketID, 傳輸單元物件>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XListUnit();
	virtual ~C_XListUnit();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增傳輸單元
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool Add(IN SOCKET Socket);
	/**
	 * @brief 刪除傳輸單元
	 * @param Socket SocketID
	 */
	void Del(IN SOCKET Socket);
	/**
	 * @brief 檢查傳輸單元是否存在
	 * @param Socket SocketID
	 * @return true表示存在, false則否
	 */
	bool IsExist(IN SOCKET Socket) const;
	/**
	 * @brief 鎖定傳輸單元
	 * @param Socket SocketID
	 * @return 傳輸單元鎖定物件
	 */
	C_XUnitLock Lock(IN SOCKET Socket) const;
	/**
	 * @brief 取得全部傳輸單元數量
	 * @return 傳輸單元數量
	 */
	unsigned long Size() const;
	/**
	 * @brief 取得詳細傳輸單元數量
	 * @param bRunning 執行旗標
	 * @return 傳輸單元數量
	 */
	unsigned long Size(IN bool bRunning) const;
	/**
	 * @brief 取得全部SocketID列表
	 * @return SocketID列表
	 */
	std::set<SOCKET> SocketList() const;
	/**
	 * @brief 取得處理SocketID列表
	 * @return SocketID列表
	 */
	std::set<SOCKET> SocketProcess() const;
	/**
	 * @brief 取得斷線SocketID列表
	 * @return SocketID列表
	 */
	std::set<SOCKET> SocketDisconnect() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------