/**
 * @file threadlist.h
 * @note 執行緒列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _THREADLIST
#define _THREADLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 執行緒資訊結構
 * @ingroup threadlist
 */
struct S_Thread
{
	unsigned long ulThreadID; ///< 執行緒的控制代碼
	unsigned long ulProcessID; ///< 此執行緒所屬處理程序控制代碼
	long lPriority; ///< 執行緒優先層級

	S_Thread(IN THREADENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief 執行緒列表類別
 * @ingroup threadlist
 */
class C_ThreadList
{
private:
	//-------------------------------------
	std::vector<S_Thread> m_Thread; ///< 執行緒資訊列表
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Thread>::const_iterator const_iterator; ///< 執行緒資訊列表迭代器型別
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadList();
	virtual ~C_ThreadList();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param ulProcessID 處理程序控制代碼
	 * @return true表示執行成功, false則否
	 */
	bool Initialize(IN unsigned long ulProcessID = GetCurrentProcessId());
	/**
	 * @brief 取得列表開頭迭代器
	 * @return 迭代器
	 */
	C_ThreadList::const_iterator Begin() const;
	/**
	 * @brief 取得列表結尾迭代器
	 * @return 迭代器
	 */
	C_ThreadList::const_iterator End() const;
	/**
	 * @brief 取得數量
	 * @return 數量
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
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------