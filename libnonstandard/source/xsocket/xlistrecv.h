/**
 * @file xlistrecv.h
 * @note 接收列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTRECV
#define _XLISTRECV
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 接收資料類別
 * @ingroup xlist
 */
class C_XRecv
{
private:
	//-------------------------------------
	void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	unsigned long m_ulRecv; ///< 接收長度
	//-------------------------------------

public:
	//-------------------------------------
	C_XRecv();
	virtual ~C_XRecv();
	//-------------------------------------
	operator C_XComplete () const;
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param ulSize 資料長度
	 * @return true表示成功, false則否
	 */
	bool Initialize(IN unsigned long ulSize);
	/**
	 * @brief 釋放
	 */
	void Release();
	/**
	 * @brief 新增資料
	 * @param ccPoint 指標器物件
	 */
	void Add(IN C_XPoint &ccPoint);
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	/**
	 * @brief 檢查是否完成
	 * @return true表示完成, false則否
	 */
	bool IsComplete() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 接收列表類別
 * @ingroup xlist
 */
class C_XListRecv
{
private:
	//-------------------------------------
	std::deque<C_XRecv> m_Recv; ///< 接收資料列表
	//-------------------------------------

public:
	//-------------------------------------
	C_XListRecv();
	virtual ~C_XListRecv();
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
	bool Add(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief 取得接收資料物件
	 * @return 接收資料物件
	 */
	C_XRecv Get();
	/**
	 * @brief 取得接收資料數量
	 * @return 接收資料數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------