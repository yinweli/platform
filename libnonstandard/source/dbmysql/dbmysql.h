/**
 * @file dbmysql.h
 * @note MySQL資料庫
 * @author yinweli
 */
/**
 * @page 如何使用dbmysql
 * dbmysql是個用於與MySQL資料庫連線的元件\n\n
 * 要建立dbmysql首先以 C_DBMySQL 建立實體\n\n
 * C_DBMySQL ccDB;\n\n
 * 然後呼叫 C_DBMySQL.Connect() 對資料庫連線\n
 * 連線成功後必須不斷呼叫 C_DBMySQL.Process() 函式讓元件持續運作\n
 * 使用完畢後可以呼叫 C_DBMySQL.Disconnect() 對資料庫斷線\n\n
 * 要執行SQL語句, 只要呼叫 C_DBMySQL.Execute() 函式執行命令並取得結果\n\n
 * --------------------------------------------------\n
 * Header           : dbmysql.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref dbmysql\n
 */
/** @defgroup dbmysql */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBMYSQL
#define _DBMYSQL
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "..\\libthirdparty\\mysql-connector-c-6.1.5-win32\\lib\\libmysql.lib")
//-----------------------------------------------------------------------------
#define _WINSOCK2_ ///< 定義使用 winsock2.h 而不使用 windows.h
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\benchmark\benchmark.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\..\..\libthirdparty\mysql-connector-c-6.1.5-win32\include\mysql.h" ///< 因為它需要winsock, 所以放在_nstd.h的引入檔之後
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief MySQL錯誤類別
 * @ingroup dbmysql
 */
class C_ErrorMySQL : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorMySQL(IN MYSQL *mysql);
	virtual ~C_ErrorMySQL();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief MySQL資料庫類別, 使用OLEDB
 * @ingroup dbmysql
 */
class C_DBMySQL : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< 資料庫型態字串
	//-------------------------------------

private:
	//-------------------------------------
	MYSQL *m_pMySQL; ///< MySQL物件指標
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
	C_DBMySQL();
	virtual ~C_DBMySQL();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------