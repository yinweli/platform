/**
 * @file xlistnotice.h
 * @note 通知列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTNOTICE
#define _XLISTNOTICE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 通知列舉
 * @ingroup xlist
 */
enum ENUM_XNotice
{
	ENUM_XNotice_NULL = 0, ///< 無效
	ENUM_XNotice_Connect, ///< 連線完成
	ENUM_XNotice_Disconnect, ///< 斷線完成
	ENUM_XNotice_Receive, ///< 完成資料

	ENUM_XNotice_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief 完成資料類別
 * @ingroup xlist
 */
class C_XComplete
{
private:
	//-------------------------------------
	const void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	//-------------------------------------

public:
	//-------------------------------------
	C_XComplete();
	C_XComplete(IN const void *data, IN unsigned long size);
	virtual ~C_XComplete();
	//-------------------------------------
	/**
	 * @brief 釋放
	 */
	void Release();
	/**
	 * @brief 取得資料指標
	 * @return 資料指標
	 */
	const void *Data() const;
	/**
	 * @brief 取得資料長度
	 * @return 資料長度
	 */
	unsigned long Size() const;
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 通知類別
 * @ingroup xlist
 */
class C_XNotice
{
private:
	//-------------------------------------
	unsigned long m_ulTime; ///< 產生時間, 以timeGetTime函式產生
	ENUM_XNotice m_emType; ///< 通知列舉
	SOCKET m_Socket; ///< SocketID
	C_XComplete m_ccComplete; ///< 完成資料物件
	//-------------------------------------

public:
	//-------------------------------------
	C_XNotice();
	C_XNotice(IN ENUM_XNotice type, IN SOCKET s);
	C_XNotice(IN ENUM_XNotice type, IN SOCKET s, IN const C_XComplete &complete);
	virtual ~C_XNotice();
	//-------------------------------------
	/**
	 * @brief 取得產生時間
	 * @return 產生時間
	 */
	unsigned long Time() const;
	/**
	 * @brief 取得通知列舉
	 * @return 通知列舉
	 */
	ENUM_XNotice Type() const;
	/**
	 * @brief 取得SocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief 取得完成資料物件
	 * @return 完成資料物件
	 */
	C_XComplete Complete() const;
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 通知列表類別
 * @ingroup xlist
 */
class C_XListNotice
{
private:
	//-------------------------------------
	std::deque<C_XNotice> m_Notice; ///< 通知列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XListNotice();
	virtual ~C_XListNotice();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增連線完成通知
	 * @param Socket SocketID
	 */
	void AddConnect(IN SOCKET Socket);
	/**
	 * @brief 新增斷線完成通知
	 * @param Socket SocketID
	 */
	void AddDisconnect(IN SOCKET Socket);
	/**
	 * @brief 新增完成資料通知
	 * @param Socket SocketID
	 * @param ccComplete 完成資料物件
	 */
	void AddReceive(IN SOCKET Socket, IN const C_XComplete &ccComplete);
	/**
	 * @brief 取得通知物件列表
	 * @param ulMax 通知物件最大數量
	 * @return 通知物件列表
	 */
	std::vector<C_XNotice> List(IN unsigned long ulMax);
	/**
	 * @brief 取得通知數量
	 * @return 通知數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------