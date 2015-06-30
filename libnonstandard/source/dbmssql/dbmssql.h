/**
 * @file dbmssql.h
 * @note MSSQL資料庫
 * @author yinweli
 */
/**
 * @page 如何使用dbmssql
 * dbmssql是個用於與MSSQL資料庫連線的元件\n
 * 系統必須要安裝sqlncli10.0, 可在此網址找到 http://go.microsoft.com/fwlink/?LinkId=123717&clcid=0x404 \n\n
 * 要建立dbmssql首先要呼叫COM的初始函式 CoInitialize() 初始化COM元件\n
 * 並且要記得在程式結束時呼叫 CoUninitialize() 把COM元件釋放\n
 * 然後以 C_DBMSSQL 建立實體\n\n
 * C_DBMSSQL ccDB;\n\n
 * 然後呼叫 C_DBMSSQL.Connect() 對資料庫連線\n
 * 連線成功後必須不斷呼叫 C_DBMSSQL.Process() 函式讓元件持續運作\n
 * 使用完畢後可以呼叫 C_DBMSSQL.Disconnect() 對資料庫斷線\n\n
 * 要執行SQL語句, 只要呼叫 C_DBMSSQL.Execute() 函式執行命令並取得結果\n\n
 * --------------------------------------------------\n
 * Header           : dbmssql.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref dbmssql\n
 */
/** @defgroup dbmssql */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBMSSQL
#define _DBMSSQL
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\algorithm\algorithm.h"
#include "..\benchmark\benchmark.h"
#include "..\comtool\comtool.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\debugtool\debugtool.h"
#include "..\memorytool\memorytool.h"
#include "..\..\..\libthirdparty\msda 2.8\include\msdasc.h"
#include "..\..\..\libthirdparty\msda 2.8\include\oledb.h"
#include "..\..\..\libthirdparty\msda 2.8\include\oledberr.h"
#include "..\..\..\libthirdparty\sqlncli 2008\include\sqlncli.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define DBINITCONSTANTS ///< OLEDB必要定義 @ingroup dbmssql
#define INITGUID ///< 定義GUID @ingroup dbmssql
#define OLEDBVER 0x0270 ///< 定義OLEDB版本 @ingroup dbmssql
#define _SQLNCLI_OLEDB_ ///< 定義sqlncli @ingroup dbmssql
//-----------------------------------------------------------------------------
/**
 * @brief MSSQL錯誤類別
 * @ingroup dbmssql
 */
class C_ErrorMSSQL : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorMSSQL(IN IUnknown *object, IN REFIID refiid);
	virtual ~C_ErrorMSSQL();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 綁定欄位類別
 * @ingroup dbmssql
 */
class C_DBMSSQLBind
{
private:
	//-------------------------------------
	std::vector<C_NString> m_ColumnName; ///< 欄位名稱列表
	DBBINDING *m_pBindData; ///< 綁定欄位列表資料
	unsigned long m_ulColumns; ///< 綁定欄位數量
	unsigned long m_ulRowSize; ///< 一行記錄所需的大小
	//-------------------------------------

public:
	//-------------------------------------
	C_DBMSSQLBind();
	virtual ~C_DBMSSQLBind();
	//-------------------------------------
	/**
	 * @brief 建立綁定欄位資料
	 * @return true表示建立成功, false則否
	 */
	bool Create(IN C_ICom<IColumnsInfo> &ccIColumnsInfo);
	/**
	 * @brief 取得綁定欄位列表指標
	 * @return 綁定欄位列表指標
	 */
	const DBBINDING *GetColumnData() const;
	/**
	 * @brief 取得綁定欄位的名稱
	 * @param ulColumnID 欄位編號
	 * @return 欄位名稱
	 */
	nstring GetColumnName(IN unsigned long ulColumnID) const;
	/**
	 * @brief 取得綁定欄位的資料位移值
	 * @param ulColumnID 欄位編號
	 * @return 資料位移值
	 */
	unsigned long GetValueOfs(IN unsigned long ulColumnID) const;
	/**
	 * @brief 取得綁定欄位數量
	 * @return 綁定欄位數量
	 */
	unsigned long GetColumns() const;
	/**
	 * @brief 取得一行記錄所需的大小
	 * @return 一行記錄所需的大小
	 */
	unsigned long GetRowSize() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief MSSQL資料庫類別, 使用OLEDB
 * @ingroup dbmssql
 */
class C_DBMSSQL : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< 資料庫型態字串
	//-------------------------------------

private:
	//-------------------------------------
	C_ICom<ICommandText> m_ccCommand; ///< 執行命令介面
	//-------------------------------------
	nstring m_szDBAddr; ///< 資料庫位址
	nstring m_szDBName; ///< 資料庫名稱
	nstring m_szUserID; ///< 使用者帳號
	nstring m_szPassword; ///< 資料庫密碼
	bool m_bReconnect; ///< 重連旗標
	unsigned long m_ulUpdateTime; ///< 更新時間
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 對資料庫連線
	 * @param szDBAddr 資料庫位址
	 * @param szDBName 資料庫名稱
	 * @param szUserID 資料庫帳號
	 * @param szPassword 資料庫密碼
	 * @param bReConnect 自動重連旗標
	 * @return true表示連線成功, false則否
	 */
	bool DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect);
	/**
	 * @brief 對資料庫斷線
	 * @return true表示執行成功, false則否
	 */
	bool DBDisconnect();
	/**
	 * @brief 定時處理
	 * @return true表示執行成功, false則否
	 */
	bool DBProcess();
	/**
	 * @brief 與資料庫是否連線中
	 * @return true表示執行連線中, false則否
	 */
	bool DBIsConnect();
	/**
	 * @brief 執行命令
	 * @param szCommand SQL語句
	 * @param pStore 執行結果指標
	 * @return true表示執行成功, false則否
	 */
	bool DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore = nullptr);
	/**
	 * @brief 取得資料庫位址
	 * @return 資料庫位址
	 */
	nstring DBAddr() const;
	/**
	 * @brief 取得資料庫名稱
	 * @return 資料庫名稱
	 */
	nstring DBName() const;
	//-------------------------------------

public:
	//-------------------------------------
	C_DBMSSQL();
	virtual ~C_DBMSSQL();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------