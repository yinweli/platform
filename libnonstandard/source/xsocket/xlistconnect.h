/**
 * @file xlistconnect.h
 * @note 連線列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTCONNECT
#define _XLISTCONNECT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 連線結構
 * @ingroup xlist
 */
struct S_XConnect
{
	C_IPData ccIPData; ///< 位址物件
	SOCKET Socket; ///< SocketID

	S_XConnect();
	S_XConnect(IN const C_IPData &ipdata);
};
//-----------------------------------------------------------------------------
/**
 * @brief 連線列表類別
 * @ingroup xlist
 */
class C_XListConnect
{
private:
	//-------------------------------------
	std::vector<S_XConnect> m_Connect; ///< 連線列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XListConnect();
	virtual ~C_XListConnect();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增連線
	 * @param ccIPData 位址物件
	 */
	void Add(IN const C_IPData &ccIPData);
	/**
	 * @brief 設定連線
	 * @param ccIPData 位址物件
	 * @param Socket SocketID
	 */
	void Set(IN const C_IPData &ccIPData, IN SOCKET Socket);
	/**
	 * @brief 設定連線
	 * @param SocketOld 舊的SocketID
	 * @param SocketNew 新的SocketID
	 */
	void Set(IN SOCKET SocketOld, IN SOCKET SocketNew);
	/**
	 * @brief 刪除連線
	 * @param Socket SocketID
	 */
	void Del(IN SOCKET Socket);
	/**
	 * @brief 取得位址物件
	 * @param Socket SocketID
	 * @return 位址物件
	 */
	C_IPData IPData(IN SOCKET Socket) const;
	/**
	 * @brief 取得連線數量
	 * @return 連線數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------