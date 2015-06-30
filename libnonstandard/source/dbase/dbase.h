/**
 * @file dbase.h
 * @note 資料庫基礎介面
 * @author yinweli
 */
/**
 * @page 如何使用dbase
 * dbase是個用於執行資料庫命令的介面類別\n\n
 * --------------------------------------------------\n
 * Header           : dbase.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref dbase\n
 */
/** @defgroup dbase */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBASE
#define _DBASE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\consoletool\consoletool.h"
#include "..\dbstore\dbstore.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫執行基礎類別
 * @ingroup dbase
 */
class C_DBase
{
private:
	//-------------------------------------
	nstring m_szType; ///< 資料庫型態
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

protected:
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
	virtual bool DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect) = 0;
	/**
	 * @brief 對資料庫斷線
	 * @return true表示執行成功, false則否
	 */
	virtual bool DBDisconnect() = 0;
	/**
	 * @brief 定時處理
	 * @return true表示執行成功, false則否
	 */
	virtual bool DBProcess() = 0;
	/**
	 * @brief 與資料庫是否連線中
	 * @return true表示執行連線中, false則否
	 */
	virtual bool DBIsConnect() = 0;
	/**
	 * @brief 執行命令
	 * @param szCommand SQL語句
	 * @param pStore 執行結果指標
	 * @return true表示執行成功, false則否
	 */
	virtual bool DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore = nullptr) = 0;
	/**
	 * @brief 取得資料庫位址
	 * @return 資料庫位址
	 */
	virtual nstring DBAddr() const = 0;
	/**
	 * @brief 取得資料庫名稱
	 * @return 資料庫名稱
	 */
	virtual nstring DBName() const = 0;
	//-------------------------------------

public:
	//-------------------------------------
	C_DBase(IN const nstring &type);
	virtual ~C_DBase();
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
	bool Connect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect);
	/**
	 * @brief 對資料庫斷線
	 */
	void Disconnect();
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 與資料庫是否連線中
	 * @return true表示連線中, false則否
	 */
	bool IsConnect();
	/**
	 * @brief 執行命令
	 * @param szCommand SQL語句
	 * @return true表示執行成功, false則否
	 */
	bool Execute(IN const nstring &szCommand);
	/**
	 * @brief 執行命令
	 * @param szCommand SQL語句
	 * @param ccStore 執行結果
	 * @return true表示執行成功, false則否
	 */
	bool Execute(IN const nstring &szCommand, OUT C_DBStore &ccStore);
	/**
	 * @brief 取得資料庫位址
	 * @return 資料庫位址
	 */
	nstring Addr() const;
	/**
	 * @brief 取得資料庫名稱
	 * @return 資料庫名稱
	 */
	nstring Name() const;
	/**
	 * @brief 取得資料庫型態字串
	 * @return 資料庫型態字串
	 */
	nstring Type() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------