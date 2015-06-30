/**
 * @file consoleargv.h
 * @note 主控台程式參數類別
 * @author yinweli
 */
/**
 * @page 如何使用consoleargv
 * consoleargv用來幫助讀取主控台程式起始參數(也就是main函式裡帶來的那些參數列)\n
 * 只要建立 C_ConsoleArgv 物件後以main函式的參數呼叫 C_ConsoleArgv.Initialize() 函式就可以了\n\n
 * --------------------------------------------------\n
 * Header           : consoleargv.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref consoleargv
 */
/** @defgroup consoleargv */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CONSOLEARGV
#define _CONSOLEARGV
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 主控台程式參數類別
 * @ingroup consoleargv
 */
class C_ConsoleArgv : public C_Argv
{
public:
	//-------------------------------------
	C_ConsoleArgv(IN unsigned long argc, IN char *argv[]);
	C_ConsoleArgv(IN unsigned long argc, IN wchar_t *argv[]);
	virtual ~C_ConsoleArgv();
	//-------------------------------------
	/**
	 * @brief 取得執行檔路徑
	 * @return 執行檔路徑
	 */
	nstring ExePath() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------