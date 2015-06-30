/**
 * @file modulelist.h
 * @note 模組列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MODULELIST
#define _MODULELIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 模組資訊結構
 * @ingroup modulelist
 */
struct S_Module
{
	unsigned long ulHandle; ///< 模組的控制代碼
	unsigned long ulProcessID; ///< 此模組所屬處理程序控制代碼
	unsigned long ulAddress; ///< 模組的開始位址
	unsigned long ulSize; ///< 模組的大小, 單位:bytes
	nstring szModuleName; ///< 模組名稱
	nstring szModulePath; ///< 模組路徑

	S_Module(IN MODULEENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief 模組列表類別
 * @ingroup modulelist
 */
class C_ModuleList
{
private:
	//-------------------------------------
	std::vector<S_Module> m_Module; ///< 模組資訊列表
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Module>::const_iterator const_iterator; ///< 模組資訊列表迭代器型別
	//-------------------------------------

public:
	//-------------------------------------
	C_ModuleList();
	virtual ~C_ModuleList();
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
	C_ModuleList::const_iterator Begin() const;
	/**
	 * @brief 取得列表結尾迭代器
	 * @return 迭代器
	 */
	C_ModuleList::const_iterator End() const;
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