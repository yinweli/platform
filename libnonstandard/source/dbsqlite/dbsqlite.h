/**
 * @file dbsqlite.h
 * @note SQLite資料庫
 * @author yinweli
 */
/**
 * @page 如何使用dbsqlite
 * dbsqlite是個用於利用記憶體建立資料庫功能的元件\n\n
 * 要建立dbsqlite首先以 C_DBSQLite 建立實體\n\n
 * C_DBSQLite ccDB;\n\n
 * 然後呼叫 C_DBSQLite.Open() 函式來啟動資料庫\n
 * 啟動時可以選擇給予資料庫一個檔名路徑, dbsqlite會把資料庫內容記錄到那個檔案裡, 下次在以此檔案開啟資料庫, 會讀取檔案內的資料重建資料庫\n
 * 若是不給予名稱, 則此資料庫只會存在記憶體中\n
 * 使用完畢後可以呼叫 C_DBSQLite.Close() 關閉資料庫\n
 * 要執行SQL語句, 只要呼叫 C_DBSQLite.Execute() 函式執行命令並取得結果\n\n
 * --------------------------------------------------\n
 * Header           : dbsqlite.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref dbsqlite\n
 */
/** @defgroup dbsqlite */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBSQLITE
#define _DBSQLITE
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\sqlite 3.8.7.4\\vc2013_lib_debug\\sqlite_debug.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\sqlite 3.8.7.4\\vc2013_lib_release\\sqlite_release.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\benchmark\benchmark.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\..\..\libthirdparty\sqlite 3.8.7.4\include\sqlite3.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief SQLite錯誤類別
 * @ingroup dbsqlite
 */
class C_ErrorSQLite : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorSQLite(IN sqlite3 *sqlite);
	virtual ~C_ErrorSQLite();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief DBSQLite類別
 * @ingroup dbsqlite
 */
class C_DBSQLite : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< 資料庫型態字串
	//-------------------------------------

private:
	//-------------------------------------
	sqlite3 *m_pDBObj; ///< 資料庫物件指標
	//-------------------------------------
	nstring m_szDBAddr; ///< 資料庫位址
	nstring m_szDBName; ///< 資料庫名稱
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
	C_DBSQLite();
	virtual ~C_DBSQLite();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------