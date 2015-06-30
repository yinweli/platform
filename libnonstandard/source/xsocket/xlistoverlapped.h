/**
 * @file xlistoverlapped.h
 * @note 重疊列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTOVERLAPPED
#define _XLISTOVERLAPPED
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 重疊類型列舉
 * @ingroup xlist
 */
enum ENUM_XOverlapped
{
	ENUM_XOverlapped_NULL = 0, ///< 無效
	ENUM_XOverlapped_Accept, ///< 接受連線
	ENUM_XOverlapped_Connect, ///< 遠端連線
	ENUM_XOverlapped_Recv, ///< 接收
	ENUM_XOverlapped_Send, ///< 傳送

	ENUM_XOverlapped_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief 重疊結構
 * @ingroup xlist
 */
struct S_XOverlapped
{
	OVERLAPPED sOverlapped; ///< 重疊結構
	char cBuffer[XSOCKET_BUFFERSIZE]; ///< 傳輸緩衝區
	ENUM_XOverlapped emType; ///< 重疊類型
	SOCKET Socket; ///< SocketID

	S_XOverlapped();
	S_XOverlapped(IN ENUM_XOverlapped type, IN SOCKET socket);
	operator OVERLAPPED & ();
	operator OVERLAPPED * ();
	bool operator < (IN const S_XOverlapped &rhs) const;
};
//-----------------------------------------------------------------------------
/**
 * @brief 重疊列表類別
 * @ingroup xlist
 */
class C_XListOverlapped
{
private:
	//-------------------------------------
	std::set<S_XOverlapped> m_Overlapped; ///< 重疊列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_XListOverlapped();
	virtual ~C_XListOverlapped();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增重疊物件
	 * @param emType 重疊類型
	 * @param Socket SocketID
	 * @return 重疊指標
	 */
	S_XOverlapped *Add(IN ENUM_XOverlapped emType, IN SOCKET Socket);
	/**
	 * @brief 刪除重疊物件
	 * @param emType 重疊類型
	 * @param Socket SocketID
	 */
	void Del(IN ENUM_XOverlapped emType, IN SOCKET Socket);
	/**
	 * @brief 取得重疊物件數量
	 * @return 重疊物件數量
	 */
	unsigned long Size() const;
	/**
	 * @brief 取得指定重疊類型物件數量
	 * @param emType 重疊類型
	 * @return 重疊物件數量
	 */
	unsigned long Size(IN ENUM_XOverlapped emType) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------