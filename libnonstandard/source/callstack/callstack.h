/**
 * @file callstack.h
 * @note callstack輸出系列函式
 * @author yinweli
 */
/**
 * @page 如何使用callstack
 * callstack內的函式用於在執行期輸出callstack\n\n
 * CallStackTrace() 函式的記錄方式是從記錄執行函式的地方往上回推到main為止\n
 * 例如:\n\n
 * main 呼叫 function1\n
 * function1 呼叫 function2\n
 * function2 呼叫 function3\n
 * function3 呼叫 function4\n
 * function4中有一行執行了 CallStackTrace() \n\n
 * 結果就會輸出\n\n
 * CallStackTrace() > function4 > function3 > function2 > function1 > main\n\n
 * 這樣的執行順序\n\n
 * 又例如上面的呼叫順序, 但是 CallStackTrace() 放在main的話\n
 * 就只會輸出 CallStackTrace() > main 的結果\n\n
 * --------------------------------------------------\n
 * Header           : callstack.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref callstack
 */
/** @defgroup callstack */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CALLSTACK
#define _CALLSTACK
//-----------------------------------------------------------------------------
#pragma comment(lib, "dbghelp.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief Callstack結構
 * @ingroup callstack
 */
struct S_CallStack
{
	nstring szFileName; ///< 檔案名稱
	DWORD dwLine; ///< 行號
	DWORD dwDisp; ///< 偏移值
	nstring szFuncName; ///< 函式名稱
	std::vector<int> ArgsList; ///< 參數列表

	/**
	 * @brief 初始化結構
	 */
	void Init();
};
//-----------------------------------------------------------------------------
/**
 * @brief Callstack追蹤, 輸出到結構列表
 * @param CallStack 記錄輸出到此容器中
 * @ingroup callstack
 */
void CallStackTrace(OUT std::vector<S_CallStack> &CallStack);
/**
 * @brief Callstack追蹤, 輸出到記錄檔案
 * @note 如果檔案不存在, 會建立一個
 * @param szFilePath 記錄輸出到此路徑的檔案
 * @ingroup callstack
 */
void CallStackTrace(IN const nstring &szFilePath);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------