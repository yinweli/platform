/**
 * @file database.h
 * @note 資料庫組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DATABASE
#define _DATABASE
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫紀錄結構
 */
struct S_RecordDatabase
{
	cstring szType; ///< 資料庫型態
	cstring szDBAddr; ///< 資料庫位址
	cstring szDBName; ///< 資料庫名稱

	S_RecordDatabase();
	S_RecordDatabase(IN C_DBase &dbase);
};
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫類別
 */
class C_Database
{
private:
	//-------------------------------------
	std::map<cstring, C_DBase *> m_Data; ///< 資料庫資料 <識別名稱, 資料庫指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Database();
	virtual ~C_Database();
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
	 * @brief 新增資料庫
	 * @param szName 識別名稱
	 * @param szType 資料庫型態
	 * @param szDBAddr 資料庫位址
	 * @param szDBName 資料庫名稱
	 * @param szUserID 資料庫帳號
	 * @param szPassword 資料庫密碼
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN const cstring szType, IN const cstring &szDBAddr, IN const cstring &szDBName, IN const cstring &szUserID, IN const cstring &szPassword);
	/**
	 * @brief 取得資料庫指標
	 * @param szName 識別名稱
	 * @return 資料庫指標
	 */
	C_DBase *Get(IN const cstring &szName);
	/**
	 * @brief 取得紀錄列表
	 * @return 紀錄列表
	 */
	std::map<cstring, S_RecordDatabase> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------