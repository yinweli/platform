/**
 * @file callfunclog.h
 * @note 函式追蹤系列函式
 * @author yinweli
 */
/**
 * @page 如何使用callfunclog
 * callfunclog內的函式用於函式追蹤與追蹤結果輸出\n\n
 * 在程式中的所有函式(或是你想要追蹤的函式)裡添加一行記錄巨集\n
 * 就會在執行期中把呼叫過的函式記錄下來, 但是記錄數量限制在 MAX_LOGCOUNT 這個大小, 超過的話會把舊的記錄刪除以容納新的記錄\n\n
 * 要取得函式記錄列表的話可以呼叫 C_CallFuncLog.Get() 函式\n\n
 * --------------------------------------------------\n
 * Header           : callfunclog.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref callfunclog
 */
/** @defgroup callfunclog */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CALLFUNCLOG
#define _CALLFUNCLOG
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\filetool\filetool.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define MAX_LOGCOUNT 256 ///< 最大記錄數量 @ingroup callfunclog
#define _G_() { nstd::C_CallFuncLog::Instance().Add(__FUNCTIONX__, __FILEX__, __LINE__); } ///< 記錄巨集 @ingroup callfunclog
//-----------------------------------------------------------------------------
/**
 * @brief 記錄呼叫函式結構
 * @ingroup callfunclog
 */
struct S_CallFuncLog
{
	nstring szFunc; ///< 被呼叫的函式名稱
	nstring szFile; ///< 函式被呼叫時的程式碼檔案名稱
	unsigned long ulLine; ///< 函式被呼叫時的行號

	S_CallFuncLog();
	S_CallFuncLog(IN const nstring &func, IN const nstring &file, IN unsigned long line);
};
//-----------------------------------------------------------------------------
/**
 * @brief 記錄呼叫函式類別
 * @ingroup callfunclog
 */
class C_CallFuncLog
{
private:
	//-------------------------------------
	std::list<S_CallFuncLog> m_CallList; ///< 紀錄呼叫列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_CallFuncLog();
	virtual ~C_CallFuncLog();
	//-------------------------------------
	/**
	 * @brief 取得記錄呼叫函式物件
	 * @return 記錄呼叫函式物件
	 */
	static C_CallFuncLog &Instance();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增紀錄
	 * @param szFuncName 被呼叫的函式名稱
	 * @param szFileName 函式被呼叫時的程式碼檔案名稱
	 * @param ulLine 函式被呼叫時的行號
	 */
	void Add(IN const nstring &szFuncName, IN const nstring &szFileName, IN unsigned long ulLine);
	/**
	 * @brief 取得紀錄, 輸出到列表
	 * @param CallList 記錄輸出到此列表
	 */
	void Get(OUT std::list<S_CallFuncLog> &CallList) const;
	/**
	 * @brief 取得紀錄, 輸出到檔案
	 * @param szFilePath 記錄檔案路徑
	 */
	void Get(IN const nstring &szFilePath) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------