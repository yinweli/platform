/**
 * @file proclist.h
 * @note 處理程序列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PROCLIST
#define _PROCLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 處理程序資訊結構
 * @ingroup proclist
 */
struct S_Process
{
	unsigned long ulProcessID; ///< 處理程序控制代碼
	unsigned long ulParentProcessID; ///< 父處理程序控制代碼
	unsigned long ulThreads; ///< 處理程序擁有的執行緒數量
	nstring szExeFile; ///< 執行檔名稱

	S_Process(IN PROCESSENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief 處理程序列表類別
 * @ingroup proclist
 */
class C_ProcList
{
private:
	//-------------------------------------
	std::vector<S_Process> m_Process; ///< 處理程序資訊列表
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Process>::const_iterator const_iterator; ///< 處理程序資訊列表迭代器型別
	//-------------------------------------

public:
	//-------------------------------------
	C_ProcList();
	virtual ~C_ProcList();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @return true表示執行成功, false則否
	 */
	bool Initialize();
	/**
	 * @brief 取得列表開頭迭代器
	 * @return 迭代器
	 */
	C_ProcList::const_iterator Begin() const;
	/**
	 * @brief 取得列表結尾迭代器
	 * @return 迭代器
	 */
	C_ProcList::const_iterator End() const;
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