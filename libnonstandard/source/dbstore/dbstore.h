/**
 * @file dbstore.h
 * @note 資料庫結果類別
 * @author yinweli
 */
/**
 * @page 如何使用dbstore
 * dbstore是個用於儲存資料庫查詢結果的類別\n\n
 * --------------------------------------------------\n
 * Header           : dbstore.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref dbstore\n
 */
/** @defgroup dbstore */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBSTORE
#define _DBSTORE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫結果錯誤類別
 * @ingroup dbstore
 */
class C_ErrorDBStore : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorDBStore(IN unsigned long line);
	C_ErrorDBStore(IN unsigned long line, IN const estring &column);
	virtual ~C_ErrorDBStore();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫結果類別
 * @ingroup dbstore
 */
class C_DBStore
{
private:
	//-------------------------------------
	std::map<nstring, C_Argu> m_Store; ///< 資料庫結果列表 <索引字串, 資料物件>
	unsigned long m_ulSize; ///< 結果筆數
	//-------------------------------------

public:
	//-------------------------------------
	C_DBStore();
	virtual ~C_DBStore();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增資料
	 * @param ulLine 資料行號
	 * @param szColumn 欄位名稱
	 * @param szData 資料字串
	 */
	void Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::string &szData);
	/**
	 * @brief 新增資料
	 * @param ulLine 資料行號
	 * @param szColumn 欄位名稱
	 * @param szData 資料字串
	 */
	void Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::wstring &szData);
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT bool &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT char &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT short &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned short &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT long &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned long &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT int &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned int &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT float &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT double &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得結果成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::string &r) const;
	/**
	 * @brief 取得資料
	 * @param ulLine 行號
	 * @param szColumn 欄位名稱
	 * @param r 資料
	 * @return true表示取得結果成功, false則否
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::wstring &r) const;
	/**
	 * @brief 取得是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	/**
	 * @brief 取得結果筆數
	 * @return 結果筆數
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------