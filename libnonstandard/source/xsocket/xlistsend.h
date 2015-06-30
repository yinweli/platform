/**
 * @file xlistsend.h
 * @note 傳送列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTSEND
#define _XLISTSEND
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 傳送資料類別
 * @ingroup xlist
 */
class C_XSend
{
private:
	//-------------------------------------
	void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	//-------------------------------------

public:
	//-------------------------------------
	C_XSend();
	virtual ~C_XSend();
	//-------------------------------------
	operator WSABUF () const;
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param pData 資料指標
	 * @param ulSize 資料長度
	 * @return true表示成功, false則否
	 */
	bool Initialize(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 釋放
	 */
	void Release();
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 傳送列表類別
 * @ingroup xlist
 */
class C_XListSend
{
private:
	//-------------------------------------
	std::deque<C_XSend> m_Send; ///< 傳送資料列表
	//-------------------------------------

public:
	//-------------------------------------
	C_XListSend();
	virtual ~C_XListSend();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增傳送資料
	 * @param pData 資料指標
	 * @param ulSize 資料長度
	 * @return true表示成功, false則否
	 */
	bool Add(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 取得傳送資料物件
	 * @return 傳送資料物件
	 */
	C_XSend Get();
	/**
	 * @brief 取得傳送資料數量
	 * @return 傳送資料數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------